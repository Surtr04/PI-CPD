	.section	__TEXT,__text,regular,pure_instructions
	.globl	_showMatrix
	.align	4, 0x90
_showMatrix:
Leh_func_begin1:
	pushq	%rbp
Ltmp0:
	movq	%rsp, %rbp
Ltmp1:
	subq	$16, %rsp
Ltmp2:
	movq	%rdi, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	LBB1_5
LBB1_1:
	movl	$0, -16(%rbp)
	jmp	LBB1_3
LBB1_2:
	movq	-8(%rbp), %rax
	movl	-12(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	(%rax,%rcx,8), %rax
	movl	-16(%rbp), %ecx
	movslq	%ecx, %rcx
	movss	(%rax,%rcx,4), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movb	$1, %al
	leaq	L_.str(%rip), %rcx
	movq	%rcx, %rdi
	callq	_printf
	movl	-16(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
LBB1_3:
	movl	-16(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB1_2
	movl	$10, %eax
	movl	%eax, %edi
	callq	_putchar
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
LBB1_5:
	movl	-12(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB1_1
	addq	$16, %rsp
	popq	%rbp
	ret
Leh_func_end1:

	.globl	_transposeMatrix
	.align	4, 0x90
_transposeMatrix:
Leh_func_begin2:
	pushq	%rbp
Ltmp3:
	movq	%rsp, %rbp
Ltmp4:
	subq	$48, %rsp
Ltmp5:
	movq	%rdi, -8(%rbp)
	xorb	%al, %al
	callq	_initMatrix
	movq	%rax, -40(%rbp)
	movl	$0, -28(%rbp)
	jmp	LBB2_5
LBB2_1:
	movl	$0, -32(%rbp)
	jmp	LBB2_3
LBB2_2:
	movq	-40(%rbp), %rax
	movl	-28(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	(%rax,%rcx,8), %rax
	movq	-8(%rbp), %rcx
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	movq	(%rcx,%rdx,8), %rcx
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	movss	(%rcx,%rdx,4), %xmm0
	movl	-32(%rbp), %ecx
	movslq	%ecx, %rcx
	movss	%xmm0, (%rax,%rcx,4)
	movl	-32(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -32(%rbp)
LBB2_3:
	movl	-32(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB2_2
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
LBB2_5:
	movl	-28(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB2_1
	movq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
Leh_func_end2:

	.globl	_dotProductTransposed
	.align	4, 0x90
_dotProductTransposed:
Leh_func_begin3:
	pushq	%rbp
Ltmp6:
	movq	%rsp, %rbp
Ltmp7:
	subq	$64, %rsp
Ltmp8:
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movabsq	$0, %rax
	cvtsi2ssq	%rax, %xmm0
	movss	%xmm0, -48(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	callq	_transposeMatrix
	movq	%rax, -56(%rbp)
	movl	$0, -36(%rbp)
	jmp	LBB3_8
LBB3_1:
	movl	$0, -40(%rbp)
	jmp	LBB3_6
LBB3_2:
	movl	$0, -44(%rbp)
	jmp	LBB3_4
LBB3_3:
	movq	-8(%rbp), %rax
	movl	-36(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	(%rax,%rcx,8), %rax
	movl	-44(%rbp), %ecx
	movslq	%ecx, %rcx
	movss	(%rax,%rcx,4), %xmm0
	movq	-56(%rbp), %rax
	movl	-40(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	(%rax,%rcx,8), %rax
	movl	-44(%rbp), %ecx
	movslq	%ecx, %rcx
	movss	(%rax,%rcx,4), %xmm1
	mulss	%xmm1, %xmm0
	movss	-48(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -48(%rbp)
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -44(%rbp)
LBB3_4:
	movl	-44(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB3_3
	movq	-24(%rbp), %rax
	movl	-36(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	(%rax,%rcx,8), %rax
	movl	-40(%rbp), %ecx
	movslq	%ecx, %rcx
	movss	-48(%rbp), %xmm0
	movss	%xmm0, (%rax,%rcx,4)
	movabsq	$0, %rax
	cvtsi2ssq	%rax, %xmm0
	movss	%xmm0, -48(%rbp)
	movl	-40(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -40(%rbp)
LBB3_6:
	movl	-40(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB3_2
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
LBB3_8:
	movl	-36(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB3_1
	movl	$0, -32(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	addq	$64, %rsp
	popq	%rbp
	ret
Leh_func_end3:

	.globl	_dotProduct
	.align	4, 0x90
_dotProduct:
Leh_func_begin4:
	pushq	%rbp
Ltmp9:
	movq	%rsp, %rbp
Ltmp10:
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movabsq	$0, %rax
	cvtsi2ssq	%rax, %xmm0
	movss	%xmm0, -48(%rbp)
	movl	$0, -36(%rbp)
	jmp	LBB4_8
LBB4_1:
	movl	$0, -40(%rbp)
	jmp	LBB4_6
LBB4_2:
	movl	$0, -44(%rbp)
	jmp	LBB4_4
LBB4_3:
	movq	-8(%rbp), %rax
	movl	-36(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	(%rax,%rcx,8), %rax
	movl	-44(%rbp), %ecx
	movslq	%ecx, %rcx
	movss	(%rax,%rcx,4), %xmm0
	movq	-16(%rbp), %rax
	movl	-44(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	(%rax,%rcx,8), %rax
	movl	-40(%rbp), %ecx
	movslq	%ecx, %rcx
	movss	(%rax,%rcx,4), %xmm1
	mulss	%xmm1, %xmm0
	movss	-48(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -48(%rbp)
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -44(%rbp)
LBB4_4:
	movl	-44(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB4_3
	movq	-24(%rbp), %rax
	movl	-36(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	(%rax,%rcx,8), %rax
	movl	-40(%rbp), %ecx
	movslq	%ecx, %rcx
	movss	-48(%rbp), %xmm0
	movss	%xmm0, (%rax,%rcx,4)
	movabsq	$0, %rax
	cvtsi2ssq	%rax, %xmm0
	movss	%xmm0, -48(%rbp)
	movl	-40(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -40(%rbp)
LBB4_6:
	movl	-40(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB4_2
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
LBB4_8:
	movl	-36(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB4_1
	movl	$0, -32(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	popq	%rbp
	ret
Leh_func_end4:

	.globl	_initRandMatrix
	.align	4, 0x90
_initRandMatrix:
Leh_func_begin5:
	pushq	%rbp
Ltmp11:
	movq	%rsp, %rbp
Ltmp12:
	subq	$48, %rsp
Ltmp13:
	movabsq	$80, %rax
	movq	%rax, %rdi
	callq	_malloc
	movq	%rax, -32(%rbp)
	movl	$0, -20(%rbp)
	jmp	LBB5_5
LBB5_1:
	movabsq	$40, %rax
	movq	%rax, %rdi
	callq	_malloc
	movq	-32(%rbp), %rcx
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movq	%rax, (%rcx,%rdx,8)
	movl	$0, -24(%rbp)
	jmp	LBB5_3
LBB5_2:
	movq	-32(%rbp), %rax
	movl	-20(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	(%rax,%rcx,8), %rax
	movq	%rax, -40(%rbp)
	callq	_rand
	movl	%eax, %ecx
	movl	$1374389535, %esi
	movl	%ecx, %eax
	imull	%esi
	movl	%edx, %eax
	movl	%eax, %esi
	shrl	$31, %esi
	sarl	$5, %eax
	leal	(%rax,%rsi), %eax
	imull	$100, %eax, %eax
	negl	%eax
	leal	1(%rcx,%rax), %eax
	cvtsi2ss	%eax, %xmm0
	movslq	-24(%rbp), %rax
	movq	-40(%rbp), %rcx
	movss	%xmm0, (%rcx,%rax,4)
	movl	-24(%rbp), %eax
	leal	1(%rax), %eax
	movl	%eax, -24(%rbp)
LBB5_3:
	movl	-24(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB5_2
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
LBB5_5:
	movl	-20(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB5_1
	movq	-32(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
Leh_func_end5:

	.globl	_initMatrix
	.align	4, 0x90
_initMatrix:
Leh_func_begin6:
	pushq	%rbp
Ltmp14:
	movq	%rsp, %rbp
Ltmp15:
	subq	$32, %rsp
Ltmp16:
	movabsq	$80, %rax
	movq	%rax, %rdi
	callq	_malloc
	movq	%rax, -32(%rbp)
	movl	$0, -20(%rbp)
	jmp	LBB6_2
LBB6_1:
	movabsq	$40, %rax
	movq	%rax, %rdi
	callq	_malloc
	movq	-32(%rbp), %rcx
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movq	%rax, (%rcx,%rdx,8)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
LBB6_2:
	movl	-20(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB6_1
	movq	-32(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	ret
Leh_func_end6:

	.globl	_initUnitMatrix
	.align	4, 0x90
_initUnitMatrix:
Leh_func_begin7:
	pushq	%rbp
Ltmp17:
	movq	%rsp, %rbp
Ltmp18:
	subq	$32, %rsp
Ltmp19:
	movabsq	$80, %rax
	movq	%rax, %rdi
	callq	_malloc
	movq	%rax, -32(%rbp)
	movl	$0, -20(%rbp)
	jmp	LBB7_5
LBB7_1:
	movabsq	$40, %rax
	movq	%rax, %rdi
	callq	_malloc
	movq	-32(%rbp), %rcx
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movq	%rax, (%rcx,%rdx,8)
	movl	$0, -24(%rbp)
	jmp	LBB7_3
LBB7_2:
	movq	-32(%rbp), %rax
	movl	-20(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	(%rax,%rcx,8), %rax
	movl	-24(%rbp), %ecx
	movslq	%ecx, %rcx
	movabsq	$1, %rdx
	cvtsi2ssq	%rdx, %xmm0
	movss	%xmm0, (%rax,%rcx,4)
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
LBB7_3:
	movl	-24(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB7_2
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
LBB7_5:
	movl	-20(%rbp), %eax
	cmpl	$9, %eax
	jle	LBB7_1
	movq	-32(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	ret
Leh_func_end7:

	.globl	_main
	.align	4, 0x90
_main:
Leh_func_begin8:
	pushq	%rbp
Ltmp20:
	movq	%rsp, %rbp
Ltmp21:
	subq	$48, %rsp
Ltmp22:
	movl	%edi, %eax
	movl	%eax, -4(%rbp)
	movq	%rsi, -16(%rbp)
	callq	_initRandMatrix
	movq	%rax, -32(%rbp)
	callq	_initUnitMatrix
	movq	%rax, -40(%rbp)
	callq	_initMatrix
	movq	%rax, -48(%rbp)
	leaq	-21(%rbp), %rax
	movq	%rax, %rdi
	callq	_gets
	movq	-40(%rbp), %rax
	movq	-32(%rbp), %rcx
	movq	-48(%rbp), %rdx
	movq	%rax, %rdi
	movq	%rcx, %rsi
	callq	_dotProduct
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	callq	_showMatrix
	movl	-20(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	ret
Leh_func_end8:

	.section	__TEXT,__cstring,cstring_literals
L_.str:
	.asciz	 " %f "

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
	.globl	_showMatrix.eh
_showMatrix.eh:
Lset1 = Leh_frame_end1-Leh_frame_begin1
	.long	Lset1
Leh_frame_begin1:
Lset2 = Leh_frame_begin1-Leh_frame_common
	.long	Lset2
Ltmp23:
	.quad	Leh_func_begin1-Ltmp23
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
	.align	3
Leh_frame_end1:

	.globl	_transposeMatrix.eh
_transposeMatrix.eh:
Lset6 = Leh_frame_end2-Leh_frame_begin2
	.long	Lset6
Leh_frame_begin2:
Lset7 = Leh_frame_begin2-Leh_frame_common
	.long	Lset7
Ltmp24:
	.quad	Leh_func_begin2-Ltmp24
Lset8 = Leh_func_end2-Leh_func_begin2
	.quad	Lset8
	.byte	0
	.byte	4
Lset9 = Ltmp3-Leh_func_begin2
	.long	Lset9
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset10 = Ltmp4-Ltmp3
	.long	Lset10
	.byte	13
	.byte	6
	.align	3
Leh_frame_end2:

	.globl	_dotProductTransposed.eh
_dotProductTransposed.eh:
Lset11 = Leh_frame_end3-Leh_frame_begin3
	.long	Lset11
Leh_frame_begin3:
Lset12 = Leh_frame_begin3-Leh_frame_common
	.long	Lset12
Ltmp25:
	.quad	Leh_func_begin3-Ltmp25
Lset13 = Leh_func_end3-Leh_func_begin3
	.quad	Lset13
	.byte	0
	.byte	4
Lset14 = Ltmp6-Leh_func_begin3
	.long	Lset14
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset15 = Ltmp7-Ltmp6
	.long	Lset15
	.byte	13
	.byte	6
	.align	3
Leh_frame_end3:

	.globl	_dotProduct.eh
_dotProduct.eh:
Lset16 = Leh_frame_end4-Leh_frame_begin4
	.long	Lset16
Leh_frame_begin4:
Lset17 = Leh_frame_begin4-Leh_frame_common
	.long	Lset17
Ltmp26:
	.quad	Leh_func_begin4-Ltmp26
Lset18 = Leh_func_end4-Leh_func_begin4
	.quad	Lset18
	.byte	0
	.byte	4
Lset19 = Ltmp9-Leh_func_begin4
	.long	Lset19
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset20 = Ltmp10-Ltmp9
	.long	Lset20
	.byte	13
	.byte	6
	.align	3
Leh_frame_end4:

	.globl	_initRandMatrix.eh
_initRandMatrix.eh:
Lset21 = Leh_frame_end5-Leh_frame_begin5
	.long	Lset21
Leh_frame_begin5:
Lset22 = Leh_frame_begin5-Leh_frame_common
	.long	Lset22
Ltmp27:
	.quad	Leh_func_begin5-Ltmp27
Lset23 = Leh_func_end5-Leh_func_begin5
	.quad	Lset23
	.byte	0
	.byte	4
Lset24 = Ltmp11-Leh_func_begin5
	.long	Lset24
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset25 = Ltmp12-Ltmp11
	.long	Lset25
	.byte	13
	.byte	6
	.align	3
Leh_frame_end5:

	.globl	_initMatrix.eh
_initMatrix.eh:
Lset26 = Leh_frame_end6-Leh_frame_begin6
	.long	Lset26
Leh_frame_begin6:
Lset27 = Leh_frame_begin6-Leh_frame_common
	.long	Lset27
Ltmp28:
	.quad	Leh_func_begin6-Ltmp28
Lset28 = Leh_func_end6-Leh_func_begin6
	.quad	Lset28
	.byte	0
	.byte	4
Lset29 = Ltmp14-Leh_func_begin6
	.long	Lset29
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset30 = Ltmp15-Ltmp14
	.long	Lset30
	.byte	13
	.byte	6
	.align	3
Leh_frame_end6:

	.globl	_initUnitMatrix.eh
_initUnitMatrix.eh:
Lset31 = Leh_frame_end7-Leh_frame_begin7
	.long	Lset31
Leh_frame_begin7:
Lset32 = Leh_frame_begin7-Leh_frame_common
	.long	Lset32
Ltmp29:
	.quad	Leh_func_begin7-Ltmp29
Lset33 = Leh_func_end7-Leh_func_begin7
	.quad	Lset33
	.byte	0
	.byte	4
Lset34 = Ltmp17-Leh_func_begin7
	.long	Lset34
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset35 = Ltmp18-Ltmp17
	.long	Lset35
	.byte	13
	.byte	6
	.align	3
Leh_frame_end7:

	.globl	_main.eh
_main.eh:
Lset36 = Leh_frame_end8-Leh_frame_begin8
	.long	Lset36
Leh_frame_begin8:
Lset37 = Leh_frame_begin8-Leh_frame_common
	.long	Lset37
Ltmp30:
	.quad	Leh_func_begin8-Ltmp30
Lset38 = Leh_func_end8-Leh_func_begin8
	.quad	Lset38
	.byte	0
	.byte	4
Lset39 = Ltmp20-Leh_func_begin8
	.long	Lset39
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset40 = Ltmp21-Ltmp20
	.long	Lset40
	.byte	13
	.byte	6
	.align	3
Leh_frame_end8:


.subsections_via_symbols
