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
#include "libc/elf/def.h"
#include "libc/elf/elf.h"
#include "libc/elf/scalar.h"
#include "libc/elf/struct/ehdr.h"
#include "libc/elf/struct/sym.h"

/**
 * Returns pointer to elf symbol table.
 *
 * @param elf points to the start of the executable image
 * @param mapsize is the number of bytes past `elf` we can access
 * @param section_type is usually `SHT_SYMTAB` or `SHT_DYNSYM`
 * @param out_count optionally receives number of elements in res
 * @return pointer to symbol array, or null on error
 */
Elf64_Sym *GetElfSymbolTable(const Elf64_Ehdr *elf,  //
                             size_t mapsize,         //
                             int section_type,       //
                             Elf64_Xword *out_count) {
  int i;
  Elf64_Shdr *shdr;
  for (i = elf->e_shnum; i > 0; --i) {
    if ((shdr = GetElfSectionHeaderAddress(elf, mapsize, i - 1)) &&  //
        shdr->sh_entsize == sizeof(Elf64_Sym) &&                     //
        shdr->sh_type == section_type) {
      if (out_count) *out_count = shdr->sh_size / sizeof(Elf64_Sym);
      return GetElfSectionAddress(elf, mapsize, shdr);
    }
  }
  return 0;
}
