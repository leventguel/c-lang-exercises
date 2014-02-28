	.file	"fcomp.c"
	.text
	.p2align 4,,15
.globl do_nothing
	.type	do_nothing, @function
do_nothing:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.size	do_nothing, .-do_nothing
	.p2align 4,,15
.globl set_fpu_double
	.type	set_fpu_double, @function
set_fpu_double:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$639, -4(%ebp)
#APP
# 11 "fcomp.c" 1
	fldcw -4(%ebp)
# 0 "" 2
#NO_APP
	leave
	ret
	.size	set_fpu_double, .-set_fpu_double
	.p2align 4,,15
.globl recip
	.type	recip, @function
recip:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	rcnt, %eax
	incl	%eax
	movl	%eax, rcnt
	fildl	8(%ebp)
	fstpl	-8(%ebp)
	fld1
	fdivl	-8(%ebp)
	fstpl	-16(%ebp)
	fldl	-16(%ebp)
	leave
	ret
	.size	recip, .-recip
	.p2align 4,,15
.globl dequal
	.type	dequal, @function
dequal:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	20(%ebp), %eax
	movl	%eax, -12(%ebp)
	fldl	-16(%ebp)
	fldl	-8(%ebp)
	fucompp
	fnstsw	%ax
	andb	$69, %ah
	cmpb	$64, %ah
	sete	%al
	andl	$255, %eax
	leave
	ret
	.size	dequal, .-dequal
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"test1 t1: r1 %f %c= r2 %f\n"
.LC3:
	.string	"test1 t2: r1 %f %c= r2 %f\n"
	.text
	.p2align 4,,15
.globl test1
	.type	test1, @function
test1:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$24, %esp
	movl	8(%ebp), %ebx
	pushl	%ebx
	call	recip
	fstpl	-16(%ebp)
	movl	%ebx, (%esp)
	call	recip
	fstpl	-24(%ebp)
	movl	-20(%ebp), %edx
	pushl	%edx
	movl	-24(%ebp), %eax
	pushl	%eax
	movl	-12(%ebp), %ebx
	pushl	%ebx
	movl	-16(%ebp), %ecx
	pushl	%ecx
	call	dequal
	movl	%eax, %ebx
	addl	$24, %esp
	fldl	-24(%ebp)
	fldl	-16(%ebp)
	fucompp
	fnstsw	%ax
	andb	$69, %ah
	xorb	$64, %ah
	jne	.L8
	movl	$61, %eax
.L6:
	subl	$8, %esp
	movl	-20(%ebp), %edx
	pushl	%edx
	movl	-24(%ebp), %ecx
	pushl	%ecx
	pushl	%eax
	movl	-12(%ebp), %edx
	pushl	%edx
	movl	-16(%ebp), %eax
	pushl	%eax
	pushl	$.LC2
	call	printf
	addl	$24, %esp
	cmpl	$1, %ebx
	sbbl	%eax, %eax
	andl	$-28, %eax
	addl	$61, %eax
	movl	-20(%ebp), %ebx
	pushl	%ebx
	movl	-24(%ebp), %ecx
	pushl	%ecx
	pushl	%eax
	movl	-12(%ebp), %edx
	pushl	%edx
	movl	-16(%ebp), %eax
	pushl	%eax
	pushl	$.LC3
	call	printf
	addl	$32, %esp
	movl	-4(%ebp), %ebx
	leave
	ret
	.p2align 4,,15
.L8:
	movl	$33, %eax
	jmp	.L6
	.size	test1, .-test1
	.section	.rodata.str1.1
.LC4:
	.string	"test2 t1: r1 %f %c= 1.0/10.0\n"
	.text
	.p2align 4,,15
.globl test2
	.type	test2, @function
test2:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$56, %esp
	movl	8(%ebp), %ebx
	pushl	%ebx
	call	recip
	fstpl	-16(%ebp)
	movl	%ebx, -44(%ebp)
	fildl	-44(%ebp)
	fstpl	-24(%ebp)
	fld1
	fdivl	-24(%ebp)
	fstpl	-32(%ebp)
	popl	%eax
	popl	%edx
	fldl	-32(%ebp)
	fldl	-16(%ebp)
	fucompp
	fnstsw	%ax
	andb	$69, %ah
	xorb	$64, %ah
	je	.L14
	movl	$33, %eax
.L12:
	pushl	%eax
	movl	-12(%ebp), %ebx
	pushl	%ebx
	movl	-16(%ebp), %ecx
	pushl	%ecx
	pushl	$.LC4
	call	printf
	addl	$16, %esp
	movl	-4(%ebp), %ebx
	leave
	ret
	.p2align 4,,15
.L14:
	movl	$61, %eax
	jmp	.L12
	.size	test2, .-test2
	.p2align 4,,15
.globl recip_l
	.type	recip_l, @function
recip_l:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	fildl	8(%ebp)
	fstpt	-24(%ebp)
	fldt	-24(%ebp)
	fdivrs	.LC0
	fstpt	-40(%ebp)
	fldt	-40(%ebp)
	leave
	ret
	.size	recip_l, .-recip_l
	.p2align 4,,15
.globl dlequal
	.type	dlequal, @function
dlequal:
	pushl	%ebp
	movl	%esp, %ebp
	fldt	20(%ebp)
	fldt	8(%ebp)
	fucompp
	fnstsw	%ax
	andb	$69, %ah
	cmpb	$64, %ah
	sete	%al
	andl	$255, %eax
	popl	%ebp
	ret
	.size	dlequal, .-dlequal
	.section	.rodata.str1.1
.LC5:
	.string	"test3 t1: r1 %f %c= r2 %f\n"
.LC6:
	.string	"test3 t2: r1 %f %c= r2 %f\n"
.LC7:
	.string	"test3 t3: r1 %f %c= 1.0/10.0\n"
	.text
	.p2align 4,,15
.globl test3
	.type	test3, @function
test3:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$64, %esp
	movl	8(%ebp), %ecx
	pushl	%ecx
	call	recip_l
	popl	%eax
	popl	%edx
	fstpt	-40(%ebp)
	movl	-32(%ebp), %ebx
	pushl	%ebx
	movl	-36(%ebp), %ecx
	pushl	%ecx
	movl	-40(%ebp), %edx
	pushl	%edx
	movl	-32(%ebp), %eax
	pushl	%eax
	movl	-36(%ebp), %ebx
	pushl	%ebx
	movl	-40(%ebp), %ecx
	pushl	%ecx
	call	dlequal
	addl	$32, %esp
	movl	%eax, %ebx
	fldt	-40(%ebp)
	fstl	-16(%ebp)
	fucomp	%st(0)
	fnstsw	%ax
	andb	$69, %ah
	xorb	$64, %ah
	jne	.L21
	movl	$61, %eax
.L18:
	subl	$8, %esp
	movl	-12(%ebp), %edx
	pushl	%edx
	movl	-16(%ebp), %ecx
	pushl	%ecx
	pushl	%eax
	movl	-12(%ebp), %edx
	pushl	%edx
	movl	-16(%ebp), %eax
	pushl	%eax
	pushl	$.LC5
	call	printf
	addl	$32, %esp
	testl	%ebx, %ebx
	je	.L19
	subl	$8, %esp
	movl	-12(%ebp), %ebx
	pushl	%ebx
	movl	-16(%ebp), %ecx
	pushl	%ecx
	pushl	$61
	movl	-12(%ebp), %edx
	pushl	%edx
	movl	-16(%ebp), %eax
	pushl	%eax
	pushl	$.LC6
	call	printf
	addl	$32, %esp
	movl	$61, %eax
.L20:
	pushl	%eax
	movl	-12(%ebp), %ebx
	pushl	%ebx
	movl	-16(%ebp), %ecx
	pushl	%ecx
	pushl	$.LC7
	call	printf
	movl	-4(%ebp), %ebx
	leave
	ret
	.p2align 4,,15
.L21:
	movl	$33, %eax
	jmp	.L18
	.p2align 4,,15
.L19:
	subl	$8, %esp
	movl	-12(%ebp), %edx
	pushl	%edx
	movl	-16(%ebp), %eax
	pushl	%eax
	pushl	$33
	movl	-12(%ebp), %ebx
	pushl	%ebx
	movl	-16(%ebp), %ecx
	pushl	%ecx
	pushl	$.LC6
	call	printf
	addl	$32, %esp
	movl	$33, %eax
	jmp	.L20
	.size	test3, .-test3
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC8:
	.string	"A long double on this machine requires %d bytes\n"
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$4, %esp
	cmpl	$1, (%ecx)
	jle	.L23
	call	set_fpu_double
.L23:
	subl	$12, %esp
	pushl	$10
	call	test1
	movl	$10, (%esp)
	call	test2
	movl	$10, (%esp)
	call	test3
	popl	%eax
	popl	%edx
	pushl	$12
	pushl	$.LC8
	call	printf
	xorl	%eax, %eax
	movl	-4(%ebp), %ecx
	leave
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
.globl rcnt
	.bss
	.align 4
	.type	rcnt, @object
	.size	rcnt, 4
rcnt:
	.zero	4
.globl rlcnt
	.align 4
	.type	rlcnt, @object
	.size	rlcnt, 4
rlcnt:
	.zero	4
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1065353216
	.ident	"GCC: (GNU) 4.5.2"
	.section	.note.GNU-stack,"",@progbits
