	.file	"111_optimized.cpp"
	.text
	.p2align 4,,15
	.globl	__Z5checkiii
	.def	__Z5checkiii;	.scl	2;	.type	32;	.endef
__Z5checkiii:
LFB28:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	movl	12(%esp), %edx
	xorl	%eax, %eax
	movl	8(%esp), %ecx
	movl	_old_rnk(,%edx,4), %ebx
	cmpl	%ebx, _old_rnk(,%ecx,4)
	je	L7
	popl	%ebx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.p2align 4,,10
L7:
	.cfi_restore_state
	addl	16(%esp), %edx
	addl	16(%esp), %ecx
	movl	_old_rnk(,%edx,4), %eax
	cmpl	%eax, _old_rnk(,%ecx,4)
	sete	%al
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
LFE28:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "%s\0"
LC1:
	.ascii "%d%c\0"
	.section	.text.startup,"x"
	.p2align 4,,15
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB29:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	andl	$-16, %esp
	subl	$32, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	call	___main
	movl	$_s, 4(%esp)
	movl	$LC0, (%esp)
	call	_scanf
	movl	$_s, %ecx
L9:
	movl	(%ecx), %edx
	addl	$4, %ecx
	leal	-16843009(%edx), %eax
	notl	%edx
	andl	%edx, %eax
	andl	$-2139062144, %eax
	je	L9
	movl	%ecx, 24(%esp)
	testl	$32896, %eax
	jne	L11
	addl	$2, %ecx
	shrl	$16, %eax
	movl	%ecx, 24(%esp)
L11:
	movl	%eax, %ecx
	addb	%al, %cl
	sbbl	$_s+3, 24(%esp)
	movl	24(%esp), %edi
	leal	1(%edi), %eax
	movl	%eax, 20(%esp)
	movl	$1, %eax
	movl	20(%esp), %ecx
	testl	%edi, %edi
	je	L14
	.p2align 4,,10
L15:
	movsbl	_s-1(%eax), %edx
	movl	%edx, _rnk(,%eax,4)
	addl	$1, %eax
	addl	$1, _bsk(,%edx,4)
	cmpl	%eax, %ecx
	jne	L15
L14:
	movl	$1, %eax
	.p2align 4,,10
L13:
	movl	_bsk-4(,%eax,4), %edx
	addl	%edx, _bsk(,%eax,4)
	addl	$1, %eax
	cmpl	$151, %eax
	jne	L13
	movl	24(%esp), %edi
	movl	%edi, %eax
	testl	%edi, %edi
	je	L45
	.p2align 4,,10
L16:
	movl	_rnk(,%eax,4), %ecx
	movl	_bsk(,%ecx,4), %edx
	leal	-1(%edx), %ebx
	movl	%eax, _suf(,%edx,4)
	movl	%ebx, _bsk(,%ecx,4)
	subl	$1, %eax
	jne	L16
	cmpl	$1, 24(%esp)
	je	L36
	movl	24(%esp), %eax
	movl	$150, %ebx
	leal	20(,%eax,4), %edi
	addl	$1, %eax
	movl	%eax, 20(%esp)
	movl	%edi, 16(%esp)
	movl	$1, %edi
	.p2align 4,,10
L32:
	movl	24(%esp), %esi
	xorl	%eax, %eax
	movl	%esi, %edx
	movl	%esi, %ecx
	subl	%edi, %edx
	subl	%edx, %ecx
	cmpl	%edx, %esi
	jle	L20
	movl	24(%esp), %esi
	.p2align 4,,10
L21:
	movl	%esi, %edx
	subl	%eax, %edx
	addl	$1, %eax
	movl	%edx, _tmp(,%eax,4)
	cmpl	%eax, %ecx
	jne	L21
L20:
	movl	$1, %esi
	movl	20(%esp), %ecx
	jmp	L19
	.p2align 4,,10
L39:
	movl	%edx, %esi
L19:
	movl	_suf(,%esi,4), %edx
	cmpl	%edi, %edx
	jle	L22
	addl	$1, %eax
	subl	%edi, %edx
	movl	%edx, _tmp(,%eax,4)
L22:
	leal	1(%esi), %edx
	cmpl	%ecx, %edx
	jne	L39
	leal	20(,%ebx,4), %eax
	movl	$0, 4(%esp)
	movl	%eax, 8(%esp)
	movl	$_bsk, (%esp)
	call	_memset
	movl	$1, %eax
	jmp	L23
	.p2align 4,,10
L63:
	movl	%edx, %eax
L23:
	movl	_tmp(,%eax,4), %edx
	movl	_rnk(,%edx,4), %edx
	movl	%edx, _sot(,%eax,4)
	addl	$1, _bsk(,%edx,4)
	leal	1(%eax), %edx
	cmpl	%eax, %esi
	jne	L63
	testl	%ebx, %ebx
	je	L24
	addl	$1, %ebx
	movl	$1, %eax
	.p2align 4,,10
L28:
	movl	_bsk-4(,%eax,4), %edx
	addl	%edx, _bsk(,%eax,4)
	addl	$1, %eax
	cmpl	%ebx, %eax
	jne	L28
L24:
	movl	24(%esp), %ebx
	.p2align 4,,10
L27:
	movl	_sot(,%ebx,4), %edx
	movl	_bsk(,%edx,4), %eax
	leal	-1(%eax), %ecx
	movl	%ecx, _bsk(,%edx,4)
	movl	_tmp(,%ebx,4), %edx
	movl	%edx, _suf(,%eax,4)
	subl	$1, %ebx
	jne	L27
	movl	16(%esp), %eax
	movl	$_rnk, 4(%esp)
	movl	$_old_rnk, (%esp)
	movl	%eax, 8(%esp)
	call	_memcpy
	movl	$1, %eax
	movl	%edi, 28(%esp)
	jmp	L31
	.p2align 4,,10
L29:
	addl	$1, %ebx
	movl	%ebx, _rnk(,%edx,4)
	leal	1(%eax), %edx
	cmpl	%eax, %esi
	je	L64
L40:
	movl	%edx, %eax
L31:
	movl	_suf-4(,%eax,4), %ecx
	movl	_suf(,%eax,4), %edx
	movl	_old_rnk(,%ecx,4), %edi
	cmpl	%edi, _old_rnk(,%edx,4)
	jne	L29
	movl	28(%esp), %edi
	addl	28(%esp), %ecx
	movl	_old_rnk(,%ecx,4), %ecx
	addl	%edx, %edi
	cmpl	%ecx, _old_rnk(,%edi,4)
	jne	L29
	movl	%ebx, _rnk(,%edx,4)
	leal	1(%eax), %edx
	cmpl	%eax, %esi
	jne	L40
	.p2align 4,,10
L64:
	movl	28(%esp), %edi
	addl	%edi, %edi
	cmpl	%edi, 24(%esp)
	jg	L32
L36:
	movl	24(%esp), %esi
	movl	$1, %ebx
	.p2align 4,,10
L35:
	xorl	%eax, %eax
	cmpl	%ebx, %esi
	movl	$LC1, (%esp)
	setne	%al
	subl	$1, %eax
	andl	$-22, %eax
	addl	$32, %eax
	movl	%eax, 8(%esp)
	movl	_suf(,%ebx,4), %eax
	addl	$1, %ebx
	movl	%eax, 4(%esp)
	call	_printf
	cmpl	%ebx, %esi
	jge	L35
L45:
	leal	-12(%ebp), %esp
	xorl	%eax, %eax
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE29:
	.globl	_s
	.bss
	.align 32
_s:
	.space 1000010
	.globl	_sot
	.align 32
_sot:
	.space 4000040
	.globl	_tmp
	.align 32
_tmp:
	.space 4000040
	.globl	_suf
	.align 32
_suf:
	.space 4000040
	.globl	_bsk
	.align 32
_bsk:
	.space 4000040
	.globl	_rnk
	.align 32
_rnk:
	.space 8000080
	.globl	_old_rnk
	.align 32
_old_rnk:
	.space 8000080
	.ident	"GCC: (MinGW.org GCC-8.2.0-5) 8.2.0"
	.def	_scanf;	.scl	2;	.type	32;	.endef
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	_memcpy;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
