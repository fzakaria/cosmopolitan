/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
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
#include "libc/intrin/likely.h"
#include "libc/str/str.h"
#include "libc/str/unicode.h"
#include "libc/str/wcwidth_osx.internal.h"

extern const uint8_t kEastAsianWidth[];
extern const uint32_t kEastAsianWidthBits;
extern const uint8_t kCombiningChars[];
extern const uint32_t kCombiningCharsBits;

/**
 * Returns cell width of monospace character.
 */
int wcwidth(wchar_t c) {
#ifdef __x86_64__
  if (LIKELY(32 <= c && c < 127)) {
    return 1;
  } else if (!c) {
    return 0;
  } else if ((uint32_t)c > 0x10FFFD ||  //
             (0 < c && c < 32) ||       //
             (0x7f <= c && c < 0xA0)) {
    return -1;
  } else if ((0 <= c && c < kCombiningCharsBits) &&
             !!(kCombiningChars[c >> 3] & (1 << (c & 7)))) {
    return 0;
  } else if (0 <= c && c < kEastAsianWidthBits) {
    return 1 + !!(kEastAsianWidth[c >> 3] & (1 << (c & 7)));
  } else {
    return 1;
  }
#else
  int res;
  if (LIKELY(32 <= c && c < 127)) return 1;
  if (VERY_UNLIKELY((uint32_t)c >= 0x100000)) {
    if ((uint32_t)c <= 0x10FFFD) return 1;
    return -1;
  }
  res = _wcwidth_osx(c);
  if (VERY_UNLIKELY(!res)) {
    if (!c) return 0;
    if (iswcntrl(c)) return -1;
  }
  return res;
#endif
}
