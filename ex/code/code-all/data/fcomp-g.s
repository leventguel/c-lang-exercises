	.file	"fcomp.c"
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.p2align 4,,15
.globl do_nothing
	.type	do_nothing, @function
do_nothing:
.LFB0:
	.file 1 "fcomp.c"
	.loc 1 5 0
	.cfi_startproc
	pushl	%ebp
.LCFI0:
	.cfi_def_cfa_offset 8
	movl	%esp, %ebp
	.cfi_offset 5, -8
.LCFI1:
	.cfi_def_cfa_register 5
	.loc 1 5 0
	popl	%ebp
	.cfi_restore 5
.LCFI2:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	do_nothing, .-do_nothing
	.p2align 4,,15
.globl set_fpu_double
	.type	set_fpu_double, @function
set_fpu_double:
.LFB1:
	.loc 1 9 0
	.cfi_startproc
	pushl	%ebp
.LCFI3:
	.cfi_def_cfa_offset 8
	movl	%esp, %ebp
	.cfi_offset 5, -8
.LCFI4:
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 10 0
	movl	$639, -4(%ebp)
.LVL0:
	.loc 1 11 0
#APP
# 11 "fcomp.c" 1
	fldcw -4(%ebp)
# 0 "" 2
	.loc 1 12 0
#NO_APP
	leave
	.cfi_restore 5
.LCFI5:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	set_fpu_double, .-set_fpu_double
	.p2align 4,,15
.globl recip
	.type	recip, @function
recip:
.LFB2:
	.loc 1 18 0
	.cfi_startproc
.LVL1:
	pushl	%ebp
.LCFI6:
	.cfi_def_cfa_offset 8
	movl	%esp, %ebp
	.cfi_offset 5, -8
.LCFI7:
	.cfi_def_cfa_register 5
	.loc 1 19 0
	movl	rcnt, %eax
	incl	%eax
	movl	%eax, rcnt
	.loc 1 20 0
	fld1
	fidivl	8(%ebp)
	.loc 1 21 0
	popl	%ebp
	.cfi_restore 5
.LCFI8:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	recip, .-recip
	.p2align 4,,15
.globl dequal
	.type	dequal, @function
dequal:
.LFB3:
	.loc 1 23 0
	.cfi_startproc
.LVL2:
	pushl	%ebp
.LCFI9:
	.cfi_def_cfa_offset 8
	movl	%esp, %ebp
	.cfi_offset 5, -8
.LCFI10:
	.cfi_def_cfa_register 5
	.loc 1 24 0
	fldl	16(%ebp)
	fldl	8(%ebp)
	fucompp
	fnstsw	%ax
	andb	$69, %ah
	cmpb	$64, %ah
	sete	%al
	andl	$255, %eax
	.loc 1 25 0
	popl	%ebp
	.cfi_restore 5
.LCFI11:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
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
.LFB4:
	.loc 1 27 0
	.cfi_startproc
.LVL3:
	pushl	%ebp
.LCFI12:
	.cfi_def_cfa_offset 8
	movl	%esp, %ebp
	.cfi_offset 5, -8
.LCFI13:
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	movl	8(%ebp), %ebx
	.cfi_offset 3, -12
	.loc 1 31 0
	pushl	%ebx
	.cfi_escape 0x2e,0x4
	call	recip
	fstpl	-16(%ebp)
.LVL4:
	.loc 1 32 0
	pushl	%ebx
	call	recip
.LVL5:
	.loc 1 34 0
	subl	$8, %esp
	fstl	(%esp)
	movl	-12(%ebp), %ecx
	pushl	%ecx
	movl	-16(%ebp), %edx
	pushl	%edx
	fstpl	-40(%ebp)
	.cfi_escape 0x2e,0x10
	call	dequal
.LVL6:
	movl	%eax, %ebx
.LVL7:
	.loc 1 35 0
	addl	$24, %esp
	fldl	-40(%ebp)
.LVL8:
	fldl	-16(%ebp)
.LVL9:
	fucomp	%st(1)
	fnstsw	%ax
.LVL10:
	andb	$69, %ah
	xorb	$64, %ah
	jne	.L8
	movl	$61, %eax
.L6:
	.loc 1 35 0 is_stmt 0 discriminator 3
	subl	$16, %esp
	fstl	(%esp)
	pushl	%eax
	movl	-12(%ebp), %eax
	pushl	%eax
	movl	-16(%ebp), %ecx
	pushl	%ecx
	pushl	$.LC2
	fstpl	-40(%ebp)
	.cfi_escape 0x2e,0x20
	call	printf
	.loc 1 36 0 is_stmt 1 discriminator 3
	addl	$16, %esp
	cmpl	$1, %ebx
	sbbl	%eax, %eax
	andl	$-28, %eax
	addl	$61, %eax
	fldl	-40(%ebp)
	fstpl	(%esp)
	pushl	%eax
	movl	-12(%ebp), %edx
	pushl	%edx
	movl	-16(%ebp), %eax
	pushl	%eax
	pushl	$.LC3
	call	printf
	addl	$32, %esp
	.loc 1 37 0 discriminator 3
	movl	-4(%ebp), %ebx
.LVL11:
	leave
	.cfi_remember_state
	.cfi_restore 5
.LCFI14:
	.cfi_def_cfa 4, 4
	.cfi_restore 3
	ret
.LVL12:
	.p2align 4,,15
.L8:
.LCFI15:
	.cfi_restore_state
	.loc 1 35 0
	movl	$33, %eax
	jmp	.L6
	.cfi_endproc
.LFE4:
	.size	test1, .-test1
	.section	.rodata.str1.1
.LC4:
	.string	"test2 t1: r1 %f %c= 1.0/10.0\n"
	.text
	.p2align 4,,15
.globl test2
	.type	test2, @function
test2:
.LFB5:
	.loc 1 41 0
	.cfi_startproc
.LVL13:
	pushl	%ebp
.LCFI16:
	.cfi_def_cfa_offset 8
	movl	%esp, %ebp
	.cfi_offset 5, -8
.LCFI17:
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %ebx
	.cfi_offset 3, -12
	.loc 1 44 0
	pushl	%ebx
	.cfi_escape 0x2e,0x4
	call	recip
.LVL14:
	.loc 1 45 0
	fld1
.LVL15:
	pushl	%ebx
	fidivl	(%esp)
	fxch	%st(1)
	.loc 1 46 0
	popl	%ebx
	popl	%eax
	fucom	%st(1)
	fnstsw	%ax
	fstp	%st(1)
	andb	$69, %ah
	xorb	$64, %ah
	je	.L14
	movl	$33, %eax
.L12:
	.loc 1 46 0 is_stmt 0 discriminator 3
	pushl	%eax
	subl	$8, %esp
	fstpl	(%esp)
	pushl	$.LC4
	.cfi_escape 0x2e,0x10
	call	printf
	addl	$16, %esp
	.loc 1 47 0 is_stmt 1 discriminator 3
	movl	-4(%ebp), %ebx
	leave
	.cfi_remember_state
	.cfi_restore 5
.LCFI18:
	.cfi_def_cfa 4, 4
	.cfi_restore 3
	ret
	.p2align 4,,15
.L14:
.LCFI19:
	.cfi_restore_state
	.loc 1 46 0
	movl	$61, %eax
	jmp	.L12
	.cfi_endproc
.LFE5:
	.size	test2, .-test2
	.p2align 4,,15
.globl recip_l
	.type	recip_l, @function
recip_l:
.LFB6:
	.loc 1 53 0
	.cfi_startproc
.LVL16:
	pushl	%ebp
.LCFI20:
	.cfi_def_cfa_offset 8
	movl	%esp, %ebp
	.cfi_offset 5, -8
.LCFI21:
	.cfi_def_cfa_register 5
	.loc 1 54 0
	fld1
	fidivl	8(%ebp)
	.loc 1 55 0
	popl	%ebp
	.cfi_restore 5
.LCFI22:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	recip_l, .-recip_l
	.p2align 4,,15
.globl dlequal
	.type	dlequal, @function
dlequal:
.LFB7:
	.loc 1 59 0
	.cfi_startproc
.LVL17:
	pushl	%ebp
.LCFI23:
	.cfi_def_cfa_offset 8
	movl	%esp, %ebp
	.cfi_offset 5, -8
.LCFI24:
	.cfi_def_cfa_register 5
	.loc 1 60 0
	fldt	20(%ebp)
	fldt	8(%ebp)
	fucompp
	fnstsw	%ax
	andb	$69, %ah
	cmpb	$64, %ah
	sete	%al
	andl	$255, %eax
	.loc 1 61 0
	popl	%ebp
	.cfi_restore 5
.LCFI25:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
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
.LFB8:
	.loc 1 63 0
	.cfi_startproc
.LVL18:
	pushl	%ebp
.LCFI26:
	.cfi_def_cfa_offset 8
	movl	%esp, %ebp
	.cfi_offset 5, -8
.LCFI27:
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.loc 1 67 0
	movl	8(%ebp), %edx
	pushl	%edx
	.cfi_offset 3, -12
	.cfi_escape 0x2e,0x4
	call	recip_l
	subl	$20, %esp
.LVL19:
	.loc 1 70 0
	fld	%st(0)
	fstpt	12(%esp)
	fld	%st(0)
	fstpt	(%esp)
	fstpt	-40(%ebp)
	.cfi_escape 0x2e,0x18
	call	dlequal
.LVL20:
	addl	$24, %esp
	movl	%eax, %ebx
.LVL21:
	.loc 1 72 0
	fldt	-40(%ebp)
.LVL22:
	fstl	-16(%ebp)
	fldl	-16(%ebp)
.LVL23:
	fxch	%st(1)
	fucomp	%st(0)
	fnstsw	%ax
.LVL24:
	andb	$69, %ah
	xorb	$64, %ah
	jne	.L21
	movl	$61, %eax
.L18:
	.loc 1 72 0 is_stmt 0 discriminator 3
	subl	$16, %esp
	fstl	(%esp)
	pushl	%eax
	subl	$8, %esp
	fstl	(%esp)
	pushl	$.LC5
	fstpl	-40(%ebp)
	.cfi_escape 0x2e,0x20
	call	printf
	.loc 1 74 0 is_stmt 1 discriminator 3
	addl	$32, %esp
	testl	%ebx, %ebx
	fldl	-40(%ebp)
	je	.L19
	subl	$16, %esp
	fstl	(%esp)
	pushl	$61
	subl	$8, %esp
	fstpl	(%esp)
	pushl	$.LC6
	call	printf
	addl	$32, %esp
	.loc 1 76 0 discriminator 3
	movl	$61, %eax
	fldl	-40(%ebp)
.L20:
	pushl	%eax
	subl	$8, %esp
	fstpl	(%esp)
	pushl	$.LC7
	.cfi_escape 0x2e,0x10
	call	printf
	.loc 1 78 0 discriminator 3
	movl	-4(%ebp), %ebx
.LVL25:
	leave
	.cfi_remember_state
	.cfi_restore 5
.LCFI28:
	.cfi_def_cfa 4, 4
	.cfi_restore 3
	ret
.LVL26:
	.p2align 4,,15
.L21:
.LCFI29:
	.cfi_restore_state
	.loc 1 72 0
	movl	$33, %eax
	jmp	.L18
	.p2align 4,,15
.L19:
	.loc 1 74 0
	subl	$16, %esp
	fstl	(%esp)
	pushl	$33
	subl	$8, %esp
	fstl	(%esp)
	pushl	$.LC6
	fstpl	-40(%ebp)
	.cfi_escape 0x2e,0x20
	call	printf
	addl	$32, %esp
	.loc 1 76 0
	movl	$33, %eax
	fldl	-40(%ebp)
	jmp	.L20
	.cfi_endproc
.LFE8:
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
.LFB9:
	.loc 1 80 0
	.cfi_startproc
.LVL27:
	leal	4(%esp), %ecx
.LCFI30:
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0x0
	pushl	%ecx
.LCFI31:
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$4, %esp
.LVL28:
	.loc 1 85 0
	cmpl	$1, (%ecx)
	jle	.L23
	.loc 1 86 0
	call	set_fpu_double
.L23:
	.loc 1 87 0
	subl	$12, %esp
	pushl	$10
	.cfi_escape 0x2e,0x10
	call	test1
	.loc 1 89 0
	movl	$10, (%esp)
	call	test2
	.loc 1 91 0
	movl	$10, (%esp)
	call	test3
	.loc 1 93 0
	popl	%ecx
	popl	%eax
	pushl	$12
	pushl	$.LC8
	call	printf
	.loc 1 95 0
	xorl	%eax, %eax
	movl	-4(%ebp), %ecx
.LCFI32:
	.cfi_def_cfa 1, 0
	leave
	leal	-4(%ecx), %esp
.LCFI33:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE9:
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
	.text
.Letext0:
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LFB0-.Ltext0
	.long	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI0-.Ltext0
	.long	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI1-.Ltext0
	.long	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI2-.Ltext0
	.long	.LFE0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0x0
	.long	0x0
.LLST1:
	.long	.LFB1-.Ltext0
	.long	.LCFI3-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI3-.Ltext0
	.long	.LCFI4-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI4-.Ltext0
	.long	.LCFI5-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI5-.Ltext0
	.long	.LFE1-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0x0
	.long	0x0
.LLST2:
	.long	.LFB2-.Ltext0
	.long	.LCFI6-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI6-.Ltext0
	.long	.LCFI7-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI7-.Ltext0
	.long	.LCFI8-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI8-.Ltext0
	.long	.LFE2-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0x0
	.long	0x0
.LLST3:
	.long	.LFB3-.Ltext0
	.long	.LCFI9-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI9-.Ltext0
	.long	.LCFI10-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI10-.Ltext0
	.long	.LCFI11-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI11-.Ltext0
	.long	.LFE3-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0x0
	.long	0x0
.LLST4:
	.long	.LFB4-.Ltext0
	.long	.LCFI12-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI12-.Ltext0
	.long	.LCFI13-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI13-.Ltext0
	.long	.LCFI14-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI14-.Ltext0
	.long	.LCFI15-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI15-.Ltext0
	.long	.LFE4-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	0x0
	.long	0x0
.LLST5:
	.long	.LVL4-.Ltext0
	.long	.LVL5-1-.Ltext0
	.value	0x1
	.byte	0x5b
	.long	.LVL5-1-.Ltext0
	.long	.LFE4-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 -24
	.long	0x0
	.long	0x0
.LLST6:
	.long	.LVL5-.Ltext0
	.long	.LVL6-1-.Ltext0
	.value	0x1
	.byte	0x5b
	.long	.LVL8-.Ltext0
	.long	.LVL9-.Ltext0
	.value	0x1
	.byte	0x5b
	.long	0x0
	.long	0x0
.LLST7:
	.long	.LVL7-.Ltext0
	.long	.LVL10-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL10-.Ltext0
	.long	.LVL11-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL12-.Ltext0
	.long	.LFE4-.Ltext0
	.value	0x1
	.byte	0x53
	.long	0x0
	.long	0x0
.LLST8:
	.long	.LFB5-.Ltext0
	.long	.LCFI16-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI16-.Ltext0
	.long	.LCFI17-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI17-.Ltext0
	.long	.LCFI18-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI18-.Ltext0
	.long	.LCFI19-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI19-.Ltext0
	.long	.LFE5-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	0x0
	.long	0x0
.LLST9:
	.long	.LVL14-.Ltext0
	.long	.LVL15-.Ltext0
	.value	0x1
	.byte	0x5b
	.long	0x0
	.long	0x0
.LLST10:
	.long	.LFB6-.Ltext0
	.long	.LCFI20-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI20-.Ltext0
	.long	.LCFI21-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI21-.Ltext0
	.long	.LCFI22-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI22-.Ltext0
	.long	.LFE6-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0x0
	.long	0x0
.LLST11:
	.long	.LFB7-.Ltext0
	.long	.LCFI23-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI23-.Ltext0
	.long	.LCFI24-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI24-.Ltext0
	.long	.LCFI25-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI25-.Ltext0
	.long	.LFE7-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0x0
	.long	0x0
.LLST12:
	.long	.LFB8-.Ltext0
	.long	.LCFI26-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI26-.Ltext0
	.long	.LCFI27-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI27-.Ltext0
	.long	.LCFI28-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI28-.Ltext0
	.long	.LCFI29-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI29-.Ltext0
	.long	.LFE8-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	0x0
	.long	0x0
.LLST13:
	.long	.LVL19-.Ltext0
	.long	.LVL20-1-.Ltext0
	.value	0x1
	.byte	0x5b
	.long	.LVL22-.Ltext0
	.long	.LVL23-.Ltext0
	.value	0x1
	.byte	0x5b
	.long	0x0
	.long	0x0
.LLST14:
	.long	.LVL19-.Ltext0
	.long	.LVL20-1-.Ltext0
	.value	0x1
	.byte	0x5b
	.long	.LVL22-.Ltext0
	.long	.LVL23-.Ltext0
	.value	0x1
	.byte	0x5b
	.long	0x0
	.long	0x0
.LLST15:
	.long	.LVL21-.Ltext0
	.long	.LVL24-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL24-.Ltext0
	.long	.LVL25-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL26-.Ltext0
	.long	.LFE8-.Ltext0
	.value	0x1
	.byte	0x53
	.long	0x0
	.long	0x0
.LLST16:
	.long	.LFB9-.Ltext0
	.long	.LCFI30-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI30-.Ltext0
	.long	.LCFI31-.Ltext0
	.value	0x2
	.byte	0x71
	.sleb128 0
	.long	.LCFI31-.Ltext0
	.long	.LCFI32-.Ltext0
	.value	0x3
	.byte	0x75
	.sleb128 -4
	.byte	0x6
	.long	.LCFI32-.Ltext0
	.long	.LCFI33-.Ltext0
	.value	0x3
	.byte	0x71
	.sleb128 -4
	.byte	0x6
	.long	.LCFI33-.Ltext0
	.long	.LFE9-.Ltext0
	.value	0x5
	.byte	0x74
	.sleb128 -4
	.byte	0x6
	.byte	0x23
	.uleb128 0x4
	.long	0x0
	.long	0x0
	.section	.debug_info
	.long	0x306
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF26
	.byte	0x1
	.long	.LASF27
	.long	.LASF28
	.long	.Ltext0
	.long	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF7
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF8
	.uleb128 0x4
	.byte	0x4
	.long	0x71
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF9
	.uleb128 0x5
	.long	0x4f
	.uleb128 0x6
	.byte	0x1
	.long	.LASF29
	.byte	0x1
	.byte	0x5
	.long	.LFB0
	.long	.LFE0
	.long	.LLST0
	.uleb128 0x7
	.byte	0x1
	.long	.LASF30
	.byte	0x1
	.byte	0x9
	.long	.LFB1
	.long	.LFE1
	.long	.LLST1
	.long	0xb8
	.uleb128 0x8
	.long	.LASF14
	.byte	0x1
	.byte	0xa
	.long	0x25
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0x0
	.uleb128 0x9
	.byte	0x1
	.long	.LASF11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.long	0xe4
	.long	.LFB2
	.long	.LFE2
	.long	.LLST2
	.long	0xe4
	.uleb128 0xa
	.long	.LASF13
	.byte	0x1
	.byte	0x12
	.long	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.byte	0x0
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.long	.LASF10
	.uleb128 0x9
	.byte	0x1
	.long	.LASF12
	.byte	0x1
	.byte	0x17
	.byte	0x1
	.long	0x4f
	.long	.LFB3
	.long	.LFE3
	.long	.LLST3
	.long	0x121
	.uleb128 0xb
	.string	"x"
	.byte	0x1
	.byte	0x17
	.long	0xe4
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xb
	.string	"y"
	.byte	0x1
	.byte	0x17
	.long	0xe4
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.byte	0x0
	.uleb128 0xc
	.byte	0x1
	.long	.LASF15
	.byte	0x1
	.byte	0x1b
	.byte	0x1
	.long	.LFB4
	.long	.LFE4
	.long	.LLST4
	.long	0x17d
	.uleb128 0xa
	.long	.LASF13
	.byte	0x1
	.byte	0x1b
	.long	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xd
	.string	"r1"
	.byte	0x1
	.byte	0x1c
	.long	0xe4
	.long	.LLST5
	.uleb128 0xd
	.string	"r2"
	.byte	0x1
	.byte	0x1c
	.long	0xe4
	.long	.LLST6
	.uleb128 0xe
	.string	"t1"
	.byte	0x1
	.byte	0x1d
	.long	0x4f
	.uleb128 0xd
	.string	"t2"
	.byte	0x1
	.byte	0x1d
	.long	0x4f
	.long	.LLST7
	.byte	0x0
	.uleb128 0xc
	.byte	0x1
	.long	.LASF16
	.byte	0x1
	.byte	0x29
	.byte	0x1
	.long	.LFB5
	.long	.LFE5
	.long	.LLST8
	.long	0x1bd
	.uleb128 0xa
	.long	.LASF13
	.byte	0x1
	.byte	0x29
	.long	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xd
	.string	"r1"
	.byte	0x1
	.byte	0x2a
	.long	0xe4
	.long	.LLST9
	.uleb128 0xe
	.string	"t1"
	.byte	0x1
	.byte	0x2b
	.long	0x4f
	.byte	0x0
	.uleb128 0x9
	.byte	0x1
	.long	.LASF17
	.byte	0x1
	.byte	0x35
	.byte	0x1
	.long	0x1e9
	.long	.LFB6
	.long	.LFE6
	.long	.LLST10
	.long	0x1e9
	.uleb128 0xa
	.long	.LASF13
	.byte	0x1
	.byte	0x35
	.long	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.byte	0x0
	.uleb128 0x2
	.byte	0xc
	.byte	0x4
	.long	.LASF18
	.uleb128 0x9
	.byte	0x1
	.long	.LASF19
	.byte	0x1
	.byte	0x3b
	.byte	0x1
	.long	0x4f
	.long	.LFB7
	.long	.LFE7
	.long	.LLST11
	.long	0x226
	.uleb128 0xb
	.string	"x"
	.byte	0x1
	.byte	0x3b
	.long	0x1e9
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xb
	.string	"y"
	.byte	0x1
	.byte	0x3b
	.long	0x1e9
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.byte	0x0
	.uleb128 0xc
	.byte	0x1
	.long	.LASF20
	.byte	0x1
	.byte	0x3f
	.byte	0x1
	.long	.LFB8
	.long	.LFE8
	.long	.LLST12
	.long	0x28c
	.uleb128 0xa
	.long	.LASF13
	.byte	0x1
	.byte	0x3f
	.long	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xd
	.string	"r1"
	.byte	0x1
	.byte	0x40
	.long	0x1e9
	.long	.LLST13
	.uleb128 0xd
	.string	"r2"
	.byte	0x1
	.byte	0x40
	.long	0x1e9
	.long	.LLST14
	.uleb128 0xe
	.string	"t1"
	.byte	0x1
	.byte	0x41
	.long	0x4f
	.uleb128 0xd
	.string	"t2"
	.byte	0x1
	.byte	0x41
	.long	0x4f
	.long	.LLST15
	.uleb128 0xe
	.string	"t3"
	.byte	0x1
	.byte	0x41
	.long	0x4f
	.byte	0x0
	.uleb128 0x9
	.byte	0x1
	.long	.LASF21
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.long	0x4f
	.long	.LFB9
	.long	.LFE9
	.long	.LLST16
	.long	0x2d2
	.uleb128 0xa
	.long	.LASF22
	.byte	0x1
	.byte	0x50
	.long	0x4f
	.byte	0x2
	.byte	0x71
	.sleb128 0
	.uleb128 0xa
	.long	.LASF23
	.byte	0x1
	.byte	0x50
	.long	0x2d2
	.byte	0x2
	.byte	0x71
	.sleb128 4
	.uleb128 0xf
	.long	.LASF13
	.byte	0x1
	.byte	0x51
	.long	0x4f
	.byte	0xa
	.byte	0x0
	.uleb128 0x4
	.byte	0x4
	.long	0x6b
	.uleb128 0x10
	.long	.LASF24
	.byte	0x1
	.byte	0x10
	.long	0x78
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.long	.LASF24
	.byte	0x1
	.byte	0x10
	.long	0x78
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	rcnt
	.uleb128 0x11
	.long	.LASF25
	.byte	0x1
	.byte	0x32
	.long	0x78
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	rlcnt
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.long	0x97
	.value	0x2
	.long	.Ldebug_info0
	.long	0x30a
	.long	0x7d
	.string	"do_nothing"
	.long	0x91
	.string	"set_fpu_double"
	.long	0xb8
	.string	"recip"
	.long	0xeb
	.string	"dequal"
	.long	0x121
	.string	"test1"
	.long	0x17d
	.string	"test2"
	.long	0x1bd
	.string	"recip_l"
	.long	0x1f0
	.string	"dlequal"
	.long	0x226
	.string	"test3"
	.long	0x28c
	.string	"main"
	.long	0x2e5
	.string	"rcnt"
	.long	0x2f7
	.string	"rlcnt"
	.long	0x0
	.section	.debug_pubtypes,"",@progbits
	.long	0xe
	.value	0x2
	.long	.Ldebug_info0
	.long	0x30a
	.long	0x0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.value	0x0
	.value	0x0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0x0
	.long	0x0
	.section	.debug_str,"MS",@progbits,1
.LASF12:
	.string	"dequal"
.LASF26:
	.string	"GNU C 4.5.2"
.LASF5:
	.string	"short int"
.LASF28:
	.string	"/mnt/hd/prg/c/ex/code/code-all/data"
.LASF11:
	.string	"recip"
.LASF13:
	.string	"denom"
.LASF1:
	.string	"unsigned char"
.LASF17:
	.string	"recip_l"
.LASF3:
	.string	"long unsigned int"
.LASF2:
	.string	"short unsigned int"
.LASF10:
	.string	"double"
.LASF19:
	.string	"dlequal"
.LASF21:
	.string	"main"
.LASF0:
	.string	"unsigned int"
.LASF7:
	.string	"long long unsigned int"
.LASF27:
	.string	"fcomp.c"
.LASF14:
	.string	"mode"
.LASF22:
	.string	"argc"
.LASF6:
	.string	"long long int"
.LASF9:
	.string	"char"
.LASF25:
	.string	"rlcnt"
.LASF24:
	.string	"rcnt"
.LASF23:
	.string	"argv"
.LASF8:
	.string	"long int"
.LASF18:
	.string	"long double"
.LASF4:
	.string	"signed char"
.LASF29:
	.string	"do_nothing"
.LASF15:
	.string	"test1"
.LASF16:
	.string	"test2"
.LASF20:
	.string	"test3"
.LASF30:
	.string	"set_fpu_double"
	.ident	"GCC: (GNU) 4.5.2"
	.section	.note.GNU-stack,"",@progbits
