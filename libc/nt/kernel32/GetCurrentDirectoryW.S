#include "libc/nt/codegen.h"
.imp	kernel32,__imp_GetCurrentDirectoryW,GetCurrentDirectoryW,0

	.text.windows
        .ftrace1
GetCurrentDirectory:
        .ftrace2
#ifdef __x86_64__
	push	%rbp
	mov	%rsp,%rbp
	mov	__imp_GetCurrentDirectoryW(%rip),%rax
	jmp	__sysv2nt
#elif defined(__aarch64__)
	mov	x0,#0
	ret
#endif
	.endfn	GetCurrentDirectory,globl
	.previous
