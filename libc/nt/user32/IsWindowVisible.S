#include "libc/nt/codegen.h"
.imp	user32,__imp_IsWindowVisible,IsWindowVisible,2090

	.text.windows
        .ftrace1
IsWindowVisible:
        .ftrace2
#ifdef __x86_64__
	push	%rbp
	mov	%rsp,%rbp
	mov	%rdi,%rcx
	sub	$32,%rsp
	call	*__imp_IsWindowVisible(%rip)
	leave
#elif defined(__aarch64__)
	mov	x0,#0
#endif
	ret
	.endfn	IsWindowVisible,globl
	.previous
