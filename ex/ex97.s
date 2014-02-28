	.file	"ex97.c"
	.section	.rodata
.LC0:
	.string	"<Widget %p: %s>"
.LC1:
	.string	"%*s"
	.text
	.globl	print_widget
	.type	print_widget, @function
print_widget:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rdx
	leaq	-24(%rbp), %rax
	movl	$.LC0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	asprintf
	movl	%eax, -12(%rbp)
	cmpl	$-1, -12(%rbp)
	jne	.L2
	movl	$-1, %eax
	jmp	.L6
.L2:
	movq	-24(%rbp), %rdx
	movq	-48(%rbp), %rax
	movzbl	12(%rax), %eax
	andl	$32, %eax
	testb	%al, %al
	je	.L4
	movq	-48(%rbp), %rax
	movl	4(%rax), %eax
	negl	%eax
	jmp	.L5
.L4:
	movq	-48(%rbp), %rax
	movl	4(%rax), %eax
.L5:
	movq	-40(%rbp), %rdi
	movq	%rdx, %rcx
	movl	%eax, %edx
	movl	$.LC1, %esi
	movl	$0, %eax
	call	fprintf
	movl	%eax, -12(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movl	-12(%rbp), %eax
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	print_widget, .-print_widget
	.globl	print_widget_arginfo
	.type	print_widget_arginfo, @function
print_widget_arginfo:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	cmpq	$0, -16(%rbp)
	je	.L8
	movq	-24(%rbp), %rax
	movl	$5, (%rax)
.L8:
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	print_widget_arginfo, .-print_widget_arginfo
	.section	.rodata
.LC2:
	.string	"mywidget"
.LC3:
	.string	"|%W| \n"
.LC4:
	.string	"|%35W| \n"
.LC5:
	.string	"|%-35W| \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	$.LC2, -16(%rbp)
	movl	$print_widget_arginfo, %edx
	movl	$print_widget, %esi
	movl	$87, %edi
	call	register_printf_function
	leaq	-16(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	leaq	-16(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	leaq	-16(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.9.0 20130629 (experimental)"
	.section	.note.GNU-stack,"",@progbits
