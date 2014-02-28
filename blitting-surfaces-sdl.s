	.file	"blitting-surfaces-sdl.c"
	.section	.rodata
.LC0:
	.string	"Unable to initialize SDL: %s\n"
.LC1:
	.string	"Unable to set video mode: %s\n"
.LC2:
	.string	"rb"
.LC3:
	.string	"test-image.bmp"
.LC4:
	.string	"Unable to load bitmap."
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$36, %esp
	subl	$12, %esp
	pushl	$32
	call	SDL_Init
	addl	$16, %esp
	testl	%eax, %eax
	je	.L2
	call	SDL_GetError
	movl	$.LC0, %edx
	subl	$8, %esp
	pushl	%eax
	pushl	%edx
	call	printf
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L3
.L2:
	subl	$12, %esp
	pushl	$SDL_Quit
	call	atexit
	addl	$16, %esp
	pushl	$0
	pushl	$16
	pushl	$480
	pushl	$640
	call	SDL_SetVideoMode
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	cmpl	$0, -12(%ebp)
	jne	.L4
	call	SDL_GetErrorff
	movl	$.LC1, %edx
	subl	$8, %esp
	pushl	%eax
	pushl	%edx
	call	printf
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L3
.L4:
	subl	$8, %esp
	pushl	$.LC2
	pushl	$.LC3
	call	SDL_RWFromFile
	addl	$16, %esp
	subl	$8, %esp
	pushl	$1
	pushl	%eax
	call	SDL_LoadBMP_RW
	addl	$16, %esp
	movl	%eax, -16(%ebp)
	cmpl	$0, -16(%ebp)
	jne	.L5
	subl	$12, %esp
	pushl	$.LC4
	call	puts
	addl	$16, %esp
	movl	$1, %eax
	jmp	.L3
.L5:
	movw	$0, -24(%ebp)
	movw	$0, -22(%ebp)
	movl	-16(%ebp), %eax
	movl	8(%eax), %eax
	movw	%ax, -20(%ebp)
	movl	-16(%ebp), %eax
	movl	12(%eax), %eax
	movw	%ax, -18(%ebp)
	movw	$0, -32(%ebp)
	movw	$0, -30(%ebp)
	movl	-16(%ebp), %eax
	movl	8(%eax), %eax
	movw	%ax, -28(%ebp)
	movl	-16(%ebp), %eax
	movl	12(%eax), %eax
	movw	%ax, -26(%ebp)
	leal	-32(%ebp), %eax
	pushl	%eax
	pushl	-12(%ebp)
	leal	-24(%ebp), %eax
	pushl	%eax
	pushl	-16(%ebp)
	call	SDL_UpperBlit
	addl	$16, %esp
	subl	$12, %esp
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	-12(%ebp)
	call	SDL_UpdateRect
	addl	$32, %esp
	subl	$12, %esp
	pushl	$3000
	call	SDL_Delay
	addl	$16, %esp
	subl	$12, %esp
	pushl	-16(%ebp)
	call	SDL_FreeSurface
	addl	$16, %esp
	movl	$0, %eax
.L3:
	movl	-4(%ebp), %ecx
	leave
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.5.3"
	.section	.note.GNU-stack,"",@progbits
