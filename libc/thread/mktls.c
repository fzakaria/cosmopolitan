/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2022 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "ape/sections.internal.h"
#include "libc/dce.h"
#include "libc/intrin/asan.internal.h"
#include "libc/intrin/asancodes.h"
#include "libc/intrin/atomic.h"
#include "libc/macros.internal.h"
#include "libc/mem/mem.h"
#include "libc/runtime/internal.h"
#include "libc/runtime/runtime.h"
#include "libc/str/str.h"
#include "libc/thread/spawn.h"
#include "libc/thread/tls.h"

#define I(x) ((uintptr_t)x)

void Bzero(void *, size_t) asm("bzero");  // gcc bug

static char *_mktls_finish(struct CosmoTib **out_tib, char *mem,
                           struct CosmoTib *tib) {
  struct CosmoTib *old;
  old = __get_tls();
  Bzero(tib, sizeof(*tib));
  tib->tib_self = tib;
  tib->tib_self2 = tib;
  tib->tib_ftrace = old->tib_ftrace;
  tib->tib_strace = old->tib_strace;
  tib->tib_sigmask = old->tib_sigmask;
  atomic_store_explicit(&tib->tib_tid, -1, memory_order_relaxed);
  if (out_tib) {
    *out_tib = tib;
  }
  return mem;
}

static char *_mktls_below(struct CosmoTib **out_tib) {
  char *tls;
  struct CosmoTib *neu;

  // allocate memory for tdata, tbss, and tib
  tls = memalign(TLS_ALIGNMENT, I(_tls_size) + sizeof(struct CosmoTib));
  if (!tls) return 0;

  // poison memory between tdata and tbss
  if (IsAsan()) {
    __asan_poison(tls + I(_tdata_size), I(_tbss_offset) - I(_tdata_size),
                  kAsanProtected);
  }

  // initialize .tdata
  if (I(_tdata_size)) {
    memmove(tls, _tdata_start, I(_tdata_size));
  }

  // clear .tbss
  Bzero(tls + I(_tbss_offset), I(_tbss_size));

  // set up thread information block
  return _mktls_finish(out_tib, tls, (struct CosmoTib *)(tls + I(_tls_size)));
}

static char *_mktls_above(struct CosmoTib **out_tib) {
  size_t hiz, siz;
  char *mem, *dtv, *tls;
  struct CosmoTib *tib, *old;

  // allocate memory for tdata, tbss, and tib
  hiz = ROUNDUP(sizeof(*tib) + 2 * sizeof(void *), I(_tls_align));
  siz = hiz + I(_tls_size);
  mem = memalign(TLS_ALIGNMENT, siz);
  if (!mem) return 0;

  // poison memory between tdata and tbss
  if (IsAsan()) {
    __asan_poison(mem + hiz + I(_tdata_size), I(_tbss_offset) - I(_tdata_size),
                  kAsanProtected);
  }

  tib = (struct CosmoTib *)mem;
  dtv = mem + sizeof(*tib);
  tls = mem + hiz;

  // set dtv
  ((uintptr_t *)dtv)[0] = 1;
  ((void **)dtv)[1] = tls;

  // initialize .tdata
  if (I(_tdata_size)) {
    memmove(tls, _tdata_start, I(_tdata_size));
  }

  // clear .tbss
  if (I(_tbss_size)) {
    Bzero(tls + I(_tbss_offset), I(_tbss_size));
  }

  // set up thread information block
  return _mktls_finish(out_tib, mem, tib);
}

/**
 * Allocates thread-local storage memory for new thread.
 * @return buffer that must be released with free()
 */
char *_mktls(struct CosmoTib **out_tib) {
  __require_tls();
#ifdef __x86_64__
  return _mktls_below(out_tib);
#else
  return _mktls_above(out_tib);
#endif
}
