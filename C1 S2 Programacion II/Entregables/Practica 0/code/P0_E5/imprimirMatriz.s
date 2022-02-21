	.file	"imprimirMatriz.c"
	.section .rdata,"dr"
LC0:
	.ascii "%f \0"
LC1:
	.ascii "La matriz no existe\0"
	.text
	.globl	_imprimirMatriz
	.def	_imprimirMatriz;	.scl	2;	.type	32;	.endef
_imprimirMatriz:
LFB14:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	cmpl	$0, 8(%ebp)
	je	L2
	movl	$0, -12(%ebp)
	jmp	L3
L6:
	movl	$0, -16(%ebp)
	jmp	L4
L5:
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	imull	-12(%ebp), %eax
	movl	%eax, %ecx
	movl	-16(%ebp), %eax
	addl	%ecx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	flds	(%eax)
	fstpl	4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	addl	$1, -16(%ebp)
L4:
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-16(%ebp), %eax
	jg	L5
	movl	$10, (%esp)
	call	_putchar
	addl	$1, -12(%ebp)
L3:
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L6
	movl	$10, (%esp)
	call	_putchar
	jmp	L8
L2:
	movl	$LC1, (%esp)
	call	_puts
L8:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_putchar;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
