#include "libc/nt/codegen.h"
.imp	MsWSock,__imp_DisconnectEx,DisconnectEx,0

	.text.windows
        .ftrace1
DisconnectEx:
        .ftrace2
#ifdef __x86_64__
	push	%rbp
	mov	%rsp,%rbp
	mov	__imp_DisconnectEx(%rip),%rax
	jmp	__sysv2nt
#elif defined(__aarch64__)
	mov	x0,#0
	ret
#endif
	.endfn	DisconnectEx,globl
	.previous
