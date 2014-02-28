    .extern XOpenDisplay
	    .extern XCreateWindow
	    .extern XMapWindow
	    .extern XNextEvent
	    .extern exit

	.globl main

main:
	    pushl    %ebp
	    movl    %esp, %ebp

	    pushl    $0
	    call    XOpenDisplay
	    addl    $4, %esp
	    movl    %eax, dpy

	    movl    $2048, value_mask
	    movl    $4, win_attr+40
	    pushl    $win_attr
	    pushl    value_mask
	    pushl    $0
	    pushl    $0
	    pushl    $0
	    pushl    $4
	    pushl    $100
	    pushl    $100
	    pushl    $0
	    pushl    $0

	    movl    dpy, %ecx
	    movl    dpy, %eax
	    movl    132(%eax), %edx
	    movl    %edx, %eax
	    sall    $2, %eax
	    addl    %edx, %eax
	    movl    %eax, %edx
	    sall    $4, %edx
	    movl    140(%ecx), %eax
	    pushl    8(%eax,%edx)
	    pushl    dpy
	    call    XCreateWindow
	    addl    $48, %esp
	    movl    %eax, win

	    pushl    win
	    pushl    dpy
	    call    XMapWindow
	    addl    $8, %esp
	.L2:
	    pushl    $event
	    pushl    dpy
	    call    XNextEvent
	    addl    $8, %esp

	    movl    event, %eax
	    cmpl    $4, %eax
	    je    .L7
	    jmp    .L2
	.L7:
	    pushl    $0
	    call    exit
	.Lfe1:
	    .comm    dpy,4,4
	    .comm    win,4,4
	    .comm    value_mask,4,4
	    .comm    win_attr,60,64
	    .comm    event,20,4
	