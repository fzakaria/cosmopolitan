/*-*- mode:unix-assembly; indent-tabs-mode:t; tab-width:8; coding:utf-8     -*-│
│vi: set et ft=asm ts=8 tw=8 fenc=utf-8                                     :vi│
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
#include "libc/dce.h"
#include "libc/macros.internal.h"
#include "libc/notice.inc"
#include "libc/runtime/internal.h"
.section .start,"ax",@progbits

//	System Five userspace program entrypoint.
//
//	@param	rsp is [n,argv₀..argvₙ₋₁,0,envp₀..,0,auxv₀..,0,..]
//	@note	FreeBSD is special (see freebsd/lib/csu/amd64/...)
//	@note	NetBSD will only zero the call-clobbered registers
//	@note	ape.S and ape-loader both set RCX to XNU on Darwin
//	@noreturn
_start:
#ifdef __x86_64__

#if SupportsXnu()
//	Hack for detecting M1 Rosetta environment.
//	https://github.com/jart/cosmopolitan/issues/429#issuecomment-1166704377
	cmp	$-1,%ebx
	jne	0f
	cmp	$+1,%edx
	jne	0f
	mov	$_HOSTXNU,%cl
	xor	%edi,%edi
0:
#endif

#if SupportsFreebsd()
//	detect free besiyata dishmaya
	test	%rdi,%rdi
	cmovnz	%rdi,%rsp
	jz	0f
	movb	$_HOSTFREEBSD,%cl
0:
#endif

//	set operating system when already detected
	mov	%cl,__hostos(%rip)

//	get startup timestamp as early as possible
//	its used by --strace flag and kprintf() %T
	rdtsc
	ezlea	kStartTsc,bx
	mov	%eax,(%rbx)
	mov	%edx,4(%rbx)

//	translates arguments from old stack abi
	mov	(%rsp),%ebx			// argc
	lea	8(%rsp),%rsi			// argv
	lea	16(%rsp,%rbx,8),%rdx		// envp
	mov	%rsp,__oldstack(%rip)

//	setup a stack frame
//	align stack to GetStackSize() so GetStackAddr() is fast
	.weak	ape_stack_memsz
	mov	$ape_stack_memsz,%r8d
	mov	$ape_stack_align,%r9d
	cmp	$_HOSTMETAL,%cl
	cmove	%r9d,%r8d
	neg	%r8
	and	%r8,%rsp
	xor	%ebp,%ebp
//	bofram	9f

//	make win32 imps noop
	.weak	ape_idata_iat
	.weak	ape_idata_iatend
	ezlea	_missingno,ax
	ezlea	ape_idata_iat,di
	ezlea	ape_idata_iatend,cx
	sub	%rdi,%rcx
	shr	$3,%ecx
	rep stosq

//	scan through environment varis
//	find start of auxiliary values
	xor	%eax,%eax
	or	$-1,%ecx
	mov	%rdx,%rdi
	repnz scasq
	mov	%rdi,%rcx			// auxv

#if SupportsXnu()
//	xnu doesn't have auxiliary values
	testb	IsXnu()
	jz	1f				// polyfill xnu auxv
	push	$0				// auxv[1][1]=0
	push	$0				// auxv[1][0]=0
	mov	%rsp,%rcx			// auxv
#endif

//	enter cosmopolitan runtime
1:	mov	%ebx,%edi
	call	cosmo
9:	.unreachable

////////////////////////////////////////////////////////////////////////////////
#elif defined(__aarch64__)

//	save original stack pointer
//	this is the first argument to cosmo() below
	mov	x0,sp

//	align stack to GetStackSize() so GetStackAddr() is fast
	mov	x1,sp
	.weak	ape_stack_memsz
	ldr	x2,=ape_stack_memsz
	neg	x2,x2
	and	x1,x2,x1
	mov	sp,x1

//	setup backtraces
	mov	x29,#0

//	second arg shall be struct Syslib passed by ape-m1.c
//	used to talk to apple's authoritarian libraries
//	should be set to zero on other platforms
	mov	x1,x15

//	switch to c code
	bl	cosmo
	.unreachable

////////////////////////////////////////////////////////////////////////////////
#else
#error "architecture unsupported"
#endif /* __x86_64__ */
	.endfn	_start,weak,hidden
