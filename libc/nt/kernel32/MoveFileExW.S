#include "libc/nt/codegen.h"
.imp	kernel32,__imp_MoveFileExW,MoveFileExW,0

	.text.windows
        .ftrace1
__MoveFileEx:
        .ftrace2
#ifdef __x86_64__
	push	%rbp
	mov	%rsp,%rbp
	mov	__imp_MoveFileExW(%rip),%rax
	jmp	__sysv2nt
#elif defined(__aarch64__)
	mov	x0,#0
	ret
#endif
	.endfn	__MoveFileEx,globl
	.previous
