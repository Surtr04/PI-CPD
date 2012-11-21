	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
_main:
Leh_func_begin1:
	pushq	%rbp
Ltmp0:
	movq	%rsp, %rbp
Ltmp1:
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$56, %rsp
Ltmp2:
	movl	$1, -56(%rbp)
	movl	$2, -52(%rbp)
	movl	$2, -48(%rbp)
	movl	$1, -44(%rbp)
	movl	$3, -72(%rbp)
	movl	$2, -68(%rbp)
	movl	$2, -64(%rbp)
	movl	$12, -60(%rbp)
	xorl	%eax, %eax
	movq	%rax, %rcx
LBB1_1:
	leaq	-56(%rbp,%rcx), %rdi
	leaq	-88(%rbp,%rcx), %rsi
	movq	%rax, %r10
LBB1_4:
	leaq	-72(%rbp,%r10), %rdx
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
LBB1_2:
	movl	(%rdx,%r8,8), %r11d
	imull	(%rdi,%r8,4), %r11d
	addl	%r11d, %r9d
	incq	%r8
	cmpq	$2, %r8
	jne	LBB1_2
	movl	%r9d, (%rsi,%r10)
	addq	$4, %r10
	cmpq	$8, %r10
	jne	LBB1_4
	addq	$8, %rcx
	cmpq	$16, %rcx
	jne	LBB1_1
	xorl	%ebx, %ebx
	leaq	L_.str(%rip), %r14
	movq	%rbx, %r15
LBB1_9:
	leaq	-88(%rbp,%r15), %r12
	movq	%rbx, %r13
LBB1_7:
	movl	(%r12,%r13,4), %esi
	xorb	%al, %al
	movq	%r14, %rdi
	callq	_printf
	incq	%r13
	cmpq	$2, %r13
	jne	LBB1_7
	movl	$10, %edi
	callq	_putchar
	addq	$8, %r15
	cmpq	$16, %r15
	jne	LBB1_9
	xorl	%eax, %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
Leh_func_end1:

	.section	__TEXT,__cstring,cstring_literals
L_.str:
	.asciz	 "%d "

	.section	__TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame0:
Lsection_eh_frame:
Leh_frame_common:
Lset0 = Leh_frame_common_end-Leh_frame_common_begin
	.long	Lset0
Leh_frame_common_begin:
	.long	0
	.byte	1
	.asciz	 "zR"
	.byte	1
	.byte	120
	.byte	16
	.byte	1
	.byte	16
	.byte	12
	.byte	7
	.byte	8
	.byte	144
	.byte	1
	.align	3
Leh_frame_common_end:
	.globl	_main.eh
_main.eh:
Lset1 = Leh_frame_end1-Leh_frame_begin1
	.long	Lset1
Leh_frame_begin1:
Lset2 = Leh_frame_begin1-Leh_frame_common
	.long	Lset2
Ltmp3:
	.quad	Leh_func_begin1-Ltmp3
Lset3 = Leh_func_end1-Leh_func_begin1
	.quad	Lset3
	.byte	0
	.byte	4
Lset4 = Ltmp0-Leh_func_begin1
	.long	Lset4
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset5 = Ltmp1-Ltmp0
	.long	Lset5
	.byte	13
	.byte	6
	.byte	4
Lset6 = Ltmp2-Ltmp1
	.long	Lset6
	.byte	131
	.byte	7
	.byte	140
	.byte	6
	.byte	141
	.byte	5
	.byte	142
	.byte	4
	.byte	143
	.byte	3
	.align	3
Leh_frame_end1:


.subsections_via_symbols
