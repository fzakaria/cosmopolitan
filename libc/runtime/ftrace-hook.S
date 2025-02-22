/*-*- mode:unix-assembly; indent-tabs-mode:t; tab-width:8; coding:utf-8     -*-│
│vi: set et ft=asm ts=8 tw=8 fenc=utf-8                                     :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2021 Justine Alexandra Roberts Tunney                              │
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
#include "libc/macros.internal.h"
.privileged

ftrace_hook:
#ifdef __x86_64__

	cmp	$0,__ftrace(%rip)
	jle	1f
	push	%rbp
	mov	%rsp,%rbp
	push	%rax
	push	%rax
	push	%rdi
	push	%rsi
	push	%rdx
	push	%rcx
	push	%r8
	push	%r9
	call	ftracer
	pop	%r9
	pop	%r8
	pop	%rcx
	pop	%rdx
	pop	%rsi
	pop	%rdi
	pop	%rax
	pop	%rax
	pop	%rbp
1:	ret

#elif defined(__aarch64__)

	adrp	x9,__ftrace
	ldr	w9,[x9,#:lo12:__ftrace]
	cmp	w9,0
	ble	1f
	stp	x29,x30,[sp,-96]!
	mov	x29,sp
	stp	x0,x1,[sp,16]
	stp	x2,x3,[sp,32]
	stp	x4,x5,[sp,48]
	stp	x6,x7,[sp,64]
	str	x8,[sp,80]
	bl	ftracer
	ldr	x8,[sp,80]
	ldp	x6,x7,[sp,64]
	ldp	x4,x5,[sp,48]
	ldp	x2,x3,[sp,32]
	ldp	x0,x1,[sp,16]
	ldp	x29,x30,[sp],96
1:	ret

#endif /* __x86_64__ */
	.endfn	ftrace_hook,globl
