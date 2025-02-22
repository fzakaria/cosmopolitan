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
#include "libc/elf/elf.h"
#include "libc/elf/scalar.h"
#include "libc/elf/struct/ehdr.h"
#include "libc/str/str.h"

/**
 * Returns `strtab + i` from elf string table.
 *
 * @param elf points to the start of the executable image
 * @param mapsize is the number of bytes past `elf` we can access
 * @param strtab is double-nul string list from GetElfStringTable()
 * @param i is byte index into strtab where needed string starts
 * @return pointer to nul terminated string, or null on error
 */
char *GetElfString(const Elf64_Ehdr *elf,  // validated
                   size_t mapsize,         // validated
                   const char *strtab,     // validated
                   Elf64_Word i) {         // foreign
  const char *e;
  e = (const char *)elf;
  if (strtab < e) return 0;
  if (strtab >= e + mapsize) return 0;
  if (strtab + i >= e + mapsize) return 0;
  if (!memchr(strtab + i, 0, (e + mapsize) - (strtab + i))) return 0;
  return (char *)strtab + i;
}
