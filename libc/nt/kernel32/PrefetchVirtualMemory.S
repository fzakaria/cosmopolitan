#include "libc/nt/codegen.h"
.imp	kernel32,__imp_PrefetchVirtualMemory,PrefetchVirtualMemory,0

	.text.windows
        .ftrace1
PrefetchVirtualMemory:
        .ftrace2
#ifdef __x86_64__
	push	%rbp
	mov	%rsp,%rbp
	mov	__imp_PrefetchVirtualMemory(%rip),%rax
	jmp	__sysv2nt
#elif defined(__aarch64__)
	mov	x0,#0
	ret
#endif
	.endfn	PrefetchVirtualMemory,globl
	.previous
