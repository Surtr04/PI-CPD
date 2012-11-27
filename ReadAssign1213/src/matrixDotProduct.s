	.section	__TEXT,__text,regular,pure_instructions
	.globl	_showMatrix
	.align	4, 0x90
_showMatrix:
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
	subq	$8, %rsp
Ltmp2:
	movq	_size@GOTPCREL(%rip), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jle	LBB1_6
	movq	%rdi, %rbx
	xorl	%r14d, %r14d
	leaq	L_.str(%rip), %r15
	movq	_size@GOTPCREL(%rip), %r12
	.align	4, 0x90
LBB1_4:
	testl	%eax, %eax
	jle	LBB1_3
	xorl	%r13d, %r13d
	.align	4, 0x90
LBB1_2:
	movq	(%rbx,%r14,8), %rax
	movss	(%rax,%r13,4), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movq	%r15, %rdi
	movb	$1, %al
	callq	_printf
	incq	%r13
	cmpl	(%r12), %r13d
	jl	LBB1_2
LBB1_3:
	incq	%r14
	movl	$10, %edi
	callq	_putchar
	movl	(%r12), %eax
	cmpl	%eax, %r14d
	jl	LBB1_4
LBB1_6:
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
Leh_func_end1:

	.globl	_dotProduct
	.align	4, 0x90
_dotProduct:
Leh_func_begin2:
	pushq	%rbp
Ltmp3:
	movq	%rsp, %rbp
Ltmp4:
	pushq	%r15
	pushq	%r14
	pushq	%r12
	pushq	%rbx
Ltmp5:
	movq	_size@GOTPCREL(%rip), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jle	LBB2_11
	xorl	%ecx, %ecx
	movl	$1, %r8d
	movq	_size@GOTPCREL(%rip), %r9
	jmp	LBB2_9
	.align	4, 0x90
LBB2_2:
	leal	-1(%rax), %r14d
	incq	%r14
	cmpl	$1, %eax
	cmovleq	%r8, %r14
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	.align	4, 0x90
LBB2_3:
	movq	(%rsi,%rax,8), %r15
	movq	(%rdi,%r11,8), %r12
	movss	(%r12,%rax,4), %xmm1
	mulss	(%r15,%rbx,4), %xmm1
	addss	%xmm1, %xmm0
	incq	%rax
	cmpq	%rax, %r14
	jne	LBB2_3
LBB2_4:
	movq	(%rdx,%r11,8), %rax
	movss	%xmm0, (%rax,%rbx,4)
	movl	(%r9), %eax
	cmpl	%eax, %r10d
	jge	LBB2_8
	movq	%r10, %rbx
LBB2_6:
	leaq	1(%rbx), %r10
	testl	%eax, %eax
	jg	LBB2_2
	pxor	%xmm0, %xmm0
	jmp	LBB2_4
LBB2_8:
	cmpl	%eax, %ecx
	jge	LBB2_11
LBB2_9:
	movq	%rcx, %r11
	leaq	1(%r11), %rcx
	testl	%eax, %eax
	jle	LBB2_8
	xorl	%ebx, %ebx
	jmp	LBB2_6
LBB2_11:
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
Leh_func_end2:

	.globl	_initUnitMatrix
	.align	4, 0x90
_initUnitMatrix:
Leh_func_begin3:
	pushq	%rbp
Ltmp6:
	movq	%rsp, %rbp
Ltmp7:
	pushq	%r15
	pushq	%r14
	pushq	%r12
	pushq	%rbx
Ltmp8:
	movq	_size@GOTPCREL(%rip), %rax
	movslq	(%rax), %rbx
	leaq	(,%rbx,8), %rdi
	callq	_malloc
	testq	%rbx, %rbx
	movq	%rax, %r14
	jle	LBB3_5
	xorl	%r15d, %r15d
	movq	%r15, %r12
	.align	4, 0x90
LBB3_2:
	leaq	(,%rbx,4), %rdi
	callq	_malloc
	movq	%rax, (%r14,%r12,8)
	incq	%r12
	movq	%r15, %rcx
	.align	4, 0x90
LBB3_3:
	movl	$1065353216, (%rax,%rcx,4)
	incq	%rcx
	cmpl	%ebx, %ecx
	jl	LBB3_3
	cmpl	%ebx, %r12d
	jl	LBB3_2
LBB3_5:
	movq	%r14, %rax
	popq	%rbx
	popq	%r12
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
Leh_func_end3:

	.globl	_initMatrix
	.align	4, 0x90
_initMatrix:
Leh_func_begin4:
	pushq	%rbp
Ltmp9:
	movq	%rsp, %rbp
Ltmp10:
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	subq	$8, %rsp
Ltmp11:
	movq	_size@GOTPCREL(%rip), %rax
	movslq	(%rax), %rbx
	leaq	(,%rbx,8), %rdi
	callq	_malloc
	testq	%rbx, %rbx
	movq	%rax, %r14
	jle	LBB4_3
	xorl	%r15d, %r15d
	.align	4, 0x90
LBB4_2:
	leaq	(,%rbx,4), %rdi
	callq	_malloc
	movq	%rax, (%r14,%r15,8)
	incq	%r15
	cmpl	%ebx, %r15d
	jl	LBB4_2
LBB4_3:
	movq	%r14, %rax
	addq	$8, %rsp
	popq	%rbx
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
Leh_func_end4:

	.globl	_transposeMatrix
	.align	4, 0x90
_transposeMatrix:
Leh_func_begin5:
	pushq	%rbp
Ltmp12:
	movq	%rsp, %rbp
Ltmp13:
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$8, %rsp
Ltmp14:
	movq	%rdi, %rbx
	movq	_size@GOTPCREL(%rip), %rax
	movslq	(%rax), %r14
	leaq	(,%r14,8), %rdi
	callq	_malloc
	testq	%r14, %r14
	movq	%rax, -48(%rbp)
	jle	LBB5_9
	movl	%r14d, %r15d
	movq	%r14, %r12
	shlq	$2, %r12
	movq	%rax, %r13
	.align	4, 0x90
LBB5_2:
	movq	%r12, %rdi
	callq	_malloc
	movq	%rax, (%r13)
	addq	$8, %r13
	decq	%r15
	jne	LBB5_2
	testl	%r14d, %r14d
	jle	LBB5_9
	xorl	%eax, %eax
	movq	_size@GOTPCREL(%rip), %rcx
	.align	4, 0x90
LBB5_8:
	movq	%rax, %rdx
	leaq	1(%rdx), %rax
	testl	%r14d, %r14d
	jle	LBB5_7
	movq	-48(%rbp), %r14
	movq	(%r14,%rdx,8), %rsi
	xorl	%edi, %edi
	.align	4, 0x90
LBB5_6:
	movq	(%rbx,%rdi,8), %r14
	movss	(%r14,%rdx,4), %xmm0
	movss	%xmm0, (%rsi,%rdi,4)
	movl	(%rcx), %r14d
	incq	%rdi
	cmpl	%r14d, %edi
	jl	LBB5_6
LBB5_7:
	cmpl	%r14d, %eax
	jl	LBB5_8
LBB5_9:
	movq	-48(%rbp), %rax
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
Leh_func_end5:

	.globl	_dotProductTransposed
	.align	4, 0x90
_dotProductTransposed:
Leh_func_begin6:
	pushq	%rbp
Ltmp15:
	movq	%rsp, %rbp
Ltmp16:
	pushq	%r15
	pushq	%r14
	pushq	%r12
	pushq	%rbx
Ltmp17:
	movq	%rdx, %rbx
	movq	%rdi, %r14
	movq	%rsi, %rdi
	callq	_transposeMatrix
	movq	_size@GOTPCREL(%rip), %rcx
	movl	(%rcx), %ecx
	testl	%ecx, %ecx
	jle	LBB6_11
	xorl	%edx, %edx
	movl	$1, %esi
	movq	_size@GOTPCREL(%rip), %rdi
	jmp	LBB6_9
	.align	4, 0x90
LBB6_2:
	leal	-1(%rcx), %r11d
	incq	%r11
	cmpl	$1, %ecx
	cmovleq	%rsi, %r11
	movq	(%rax,%r10,8), %rcx
	pxor	%xmm0, %xmm0
	xorl	%r15d, %r15d
	.align	4, 0x90
LBB6_3:
	movq	(%r14,%r9,8), %r12
	movss	(%r12,%r15,4), %xmm1
	mulss	(%rcx,%r15,4), %xmm1
	incq	%r15
	cmpq	%r15, %r11
	addss	%xmm1, %xmm0
	jne	LBB6_3
LBB6_4:
	movq	(%rbx,%r9,8), %rcx
	movss	%xmm0, (%rcx,%r10,4)
	movl	(%rdi), %ecx
	cmpl	%ecx, %r8d
	jge	LBB6_8
	movq	%r8, %r10
LBB6_6:
	leaq	1(%r10), %r8
	testl	%ecx, %ecx
	jg	LBB6_2
	pxor	%xmm0, %xmm0
	jmp	LBB6_4
LBB6_8:
	cmpl	%ecx, %edx
	jge	LBB6_11
LBB6_9:
	movq	%rdx, %r9
	leaq	1(%r9), %rdx
	testl	%ecx, %ecx
	jle	LBB6_8
	xorl	%r10d, %r10d
	jmp	LBB6_6
LBB6_11:
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
Leh_func_end6:

	.globl	_initRandMatrix
	.align	4, 0x90
_initRandMatrix:
Leh_func_begin7:
	pushq	%rbp
Ltmp18:
	movq	%rsp, %rbp
Ltmp19:
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
Ltmp20:
	movq	_size@GOTPCREL(%rip), %rax
	movslq	(%rax), %rbx
	leaq	(,%rbx,8), %rdi
	callq	_malloc
	testq	%rbx, %rbx
	movq	%rax, -56(%rbp)
	jle	LBB7_6
	movq	$0, -48(%rbp)
	movl	$1374389535, %r14d
	movq	_size@GOTPCREL(%rip), %r15
	.align	4, 0x90
LBB7_2:
	movslq	%ebx, %r12
	leaq	(,%r12,4), %rdi
	callq	_malloc
	movq	-48(%rbp), %rdx
	movq	-56(%rbp), %rcx
	movq	%rax, (%rcx,%rdx,8)
	incq	%rdx
	movq	%rdx, -48(%rbp)
	testl	%r12d, %r12d
	jle	LBB7_5
	movq	%rax, %r12
	xorl	%r13d, %r13d
	.align	4, 0x90
LBB7_4:
	callq	_rand
	movl	%eax, %ecx
	movl	%ecx, %eax
	imull	%r14d
	movl	%edx, %eax
	shrl	$31, %eax
	sarl	$5, %edx
	addl	%eax, %edx
	imull	$100, %edx, %eax
	negl	%eax
	leal	1(%rcx,%rax), %eax
	cvtsi2ss	%eax, %xmm0
	movss	%xmm0, (%r12,%r13,4)
	movl	(%r15), %ebx
	incq	%r13
	cmpl	%ebx, %r13d
	jl	LBB7_4
LBB7_5:
	movq	-48(%rbp), %rax
	cmpl	%ebx, %eax
	jl	LBB7_2
LBB7_6:
	movq	-56(%rbp), %rax
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
Leh_func_end7:

	.globl	_dotProductTransposed_papi
	.align	4, 0x90
_dotProductTransposed_papi:
Leh_func_begin8:
	pushq	%rbp
Ltmp21:
	movq	%rsp, %rbp
Ltmp22:
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	subq	$8, %rsp
Ltmp23:
	movq	_event_set@GOTPCREL(%rip), %rax
	movl	(%rax), %edi
	callq	_PAPI_start
	testl	%eax, %eax
	je	LBB8_2
	movl	$6, %edi
	xorb	%al, %al
	callq	_handle_error
LBB8_2:
	movq	_size@GOTPCREL(%rip), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jle	LBB8_13
	xorl	%ecx, %ecx
	movq	_m@GOTPCREL(%rip), %rdx
	movl	$1, %esi
	movq	_size@GOTPCREL(%rip), %rdi
	jmp	LBB8_11
	.align	4, 0x90
LBB8_4:
	leal	-1(%rax), %ebx
	incq	%rbx
	cmpl	$1, %eax
	cmovleq	%rsi, %rbx
	movq	8(%r9), %rax
	movq	(%rax,%r11,8), %rax
	pxor	%xmm0, %xmm0
	xorl	%r14d, %r14d
	.align	4, 0x90
LBB8_5:
	movq	(%r9), %r15
	movq	(%r15,%r10,8), %r15
	movss	(%r15,%r14,4), %xmm1
	mulss	(%rax,%r14,4), %xmm1
	incq	%r14
	cmpq	%r14, %rbx
	addss	%xmm1, %xmm0
	jne	LBB8_5
LBB8_6:
	movq	16(%r9), %r9
	movq	(%r9,%r10,8), %r9
	movss	%xmm0, (%r9,%r11,4)
	movl	(%rdi), %eax
	cmpl	%eax, %r8d
	jge	LBB8_10
	movq	%r8, %r11
LBB8_8:
	leaq	1(%r11), %r8
	testl	%eax, %eax
	movq	(%rdx), %r9
	jg	LBB8_4
	pxor	%xmm0, %xmm0
	jmp	LBB8_6
LBB8_10:
	cmpl	%eax, %ecx
	jge	LBB8_13
LBB8_11:
	movq	%rcx, %r10
	leaq	1(%r10), %rcx
	testl	%eax, %eax
	jle	LBB8_10
	xorl	%r11d, %r11d
	jmp	LBB8_8
LBB8_13:
	movq	_event_set@GOTPCREL(%rip), %rax
	movl	(%rax), %edi
	movq	_event_value@GOTPCREL(%rip), %rsi
	callq	_PAPI_stop
	testl	%eax, %eax
	je	LBB8_15
	movl	$7, %edi
	xorb	%al, %al
	callq	_handle_error
LBB8_15:
	xorl	%eax, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
Leh_func_end8:

	.globl	_dotProduct_papi
	.align	4, 0x90
_dotProduct_papi:
Leh_func_begin9:
	pushq	%rbp
Ltmp24:
	movq	%rsp, %rbp
Ltmp25:
	pushq	%r15
	pushq	%r14
	pushq	%r12
	pushq	%rbx
Ltmp26:
	movq	_event_set@GOTPCREL(%rip), %rax
	movl	(%rax), %edi
	callq	_PAPI_start
	testl	%eax, %eax
	je	LBB9_2
	movl	$6, %edi
	xorb	%al, %al
	callq	_handle_error
LBB9_2:
	movq	_size@GOTPCREL(%rip), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jle	LBB9_13
	xorl	%ecx, %ecx
	movq	_m@GOTPCREL(%rip), %rdx
	movl	$1, %esi
	movq	_size@GOTPCREL(%rip), %rdi
	jmp	LBB9_11
	.align	4, 0x90
LBB9_4:
	leal	-1(%rax), %ebx
	incq	%rbx
	cmpl	$1, %eax
	cmovleq	%rsi, %rbx
	movq	8(%r9), %rax
	pxor	%xmm0, %xmm0
	xorl	%r14d, %r14d
	.align	4, 0x90
LBB9_5:
	movq	(%rax,%r14,8), %r15
	movq	(%r9), %r12
	movq	(%r12,%r10,8), %r12
	movss	(%r12,%r14,4), %xmm1
	mulss	(%r15,%r11,4), %xmm1
	addss	%xmm1, %xmm0
	incq	%r14
	cmpq	%r14, %rbx
	jne	LBB9_5
LBB9_6:
	movq	16(%r9), %r9
	movq	(%r9,%r10,8), %r9
	movss	%xmm0, (%r9,%r11,4)
	movl	(%rdi), %eax
	cmpl	%eax, %r8d
	jge	LBB9_10
	movq	%r8, %r11
LBB9_8:
	leaq	1(%r11), %r8
	testl	%eax, %eax
	movq	(%rdx), %r9
	jg	LBB9_4
	pxor	%xmm0, %xmm0
	jmp	LBB9_6
LBB9_10:
	cmpl	%eax, %ecx
	jge	LBB9_13
LBB9_11:
	movq	%rcx, %r10
	leaq	1(%r10), %rcx
	testl	%eax, %eax
	jle	LBB9_10
	xorl	%r11d, %r11d
	jmp	LBB9_8
LBB9_13:
	movq	_event_set@GOTPCREL(%rip), %rax
	movl	(%rax), %edi
	movq	_event_value@GOTPCREL(%rip), %rsi
	callq	_PAPI_stop
	testl	%eax, %eax
	je	LBB9_15
	movl	$7, %edi
	xorb	%al, %al
	callq	_handle_error
LBB9_15:
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
Leh_func_end9:

	.comm	_size,4,2
	.comm	_event_set,4,2
	.comm	_m,8,3
	.comm	_event_value,16,4
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
Ltmp27:
	.quad	Leh_func_begin1-Ltmp27
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

	.globl	_dotProduct.eh
_dotProduct.eh:
Lset7 = Leh_frame_end2-Leh_frame_begin2
	.long	Lset7
Leh_frame_begin2:
Lset8 = Leh_frame_begin2-Leh_frame_common
	.long	Lset8
Ltmp28:
	.quad	Leh_func_begin2-Ltmp28
Lset9 = Leh_func_end2-Leh_func_begin2
	.quad	Lset9
	.byte	0
	.byte	4
Lset10 = Ltmp3-Leh_func_begin2
	.long	Lset10
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset11 = Ltmp4-Ltmp3
	.long	Lset11
	.byte	13
	.byte	6
	.byte	4
Lset12 = Ltmp5-Ltmp4
	.long	Lset12
	.byte	131
	.byte	6
	.byte	140
	.byte	5
	.byte	142
	.byte	4
	.byte	143
	.byte	3
	.align	3
Leh_frame_end2:

	.globl	_initUnitMatrix.eh
_initUnitMatrix.eh:
Lset13 = Leh_frame_end3-Leh_frame_begin3
	.long	Lset13
Leh_frame_begin3:
Lset14 = Leh_frame_begin3-Leh_frame_common
	.long	Lset14
Ltmp29:
	.quad	Leh_func_begin3-Ltmp29
Lset15 = Leh_func_end3-Leh_func_begin3
	.quad	Lset15
	.byte	0
	.byte	4
Lset16 = Ltmp6-Leh_func_begin3
	.long	Lset16
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset17 = Ltmp7-Ltmp6
	.long	Lset17
	.byte	13
	.byte	6
	.byte	4
Lset18 = Ltmp8-Ltmp7
	.long	Lset18
	.byte	131
	.byte	6
	.byte	140
	.byte	5
	.byte	142
	.byte	4
	.byte	143
	.byte	3
	.align	3
Leh_frame_end3:

	.globl	_initMatrix.eh
_initMatrix.eh:
Lset19 = Leh_frame_end4-Leh_frame_begin4
	.long	Lset19
Leh_frame_begin4:
Lset20 = Leh_frame_begin4-Leh_frame_common
	.long	Lset20
Ltmp30:
	.quad	Leh_func_begin4-Ltmp30
Lset21 = Leh_func_end4-Leh_func_begin4
	.quad	Lset21
	.byte	0
	.byte	4
Lset22 = Ltmp9-Leh_func_begin4
	.long	Lset22
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset23 = Ltmp10-Ltmp9
	.long	Lset23
	.byte	13
	.byte	6
	.byte	4
Lset24 = Ltmp11-Ltmp10
	.long	Lset24
	.byte	131
	.byte	5
	.byte	142
	.byte	4
	.byte	143
	.byte	3
	.align	3
Leh_frame_end4:

	.globl	_transposeMatrix.eh
_transposeMatrix.eh:
Lset25 = Leh_frame_end5-Leh_frame_begin5
	.long	Lset25
Leh_frame_begin5:
Lset26 = Leh_frame_begin5-Leh_frame_common
	.long	Lset26
Ltmp31:
	.quad	Leh_func_begin5-Ltmp31
Lset27 = Leh_func_end5-Leh_func_begin5
	.quad	Lset27
	.byte	0
	.byte	4
Lset28 = Ltmp12-Leh_func_begin5
	.long	Lset28
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset29 = Ltmp13-Ltmp12
	.long	Lset29
	.byte	13
	.byte	6
	.byte	4
Lset30 = Ltmp14-Ltmp13
	.long	Lset30
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
Leh_frame_end5:

	.globl	_dotProductTransposed.eh
_dotProductTransposed.eh:
Lset31 = Leh_frame_end6-Leh_frame_begin6
	.long	Lset31
Leh_frame_begin6:
Lset32 = Leh_frame_begin6-Leh_frame_common
	.long	Lset32
Ltmp32:
	.quad	Leh_func_begin6-Ltmp32
Lset33 = Leh_func_end6-Leh_func_begin6
	.quad	Lset33
	.byte	0
	.byte	4
Lset34 = Ltmp15-Leh_func_begin6
	.long	Lset34
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset35 = Ltmp16-Ltmp15
	.long	Lset35
	.byte	13
	.byte	6
	.byte	4
Lset36 = Ltmp17-Ltmp16
	.long	Lset36
	.byte	131
	.byte	6
	.byte	140
	.byte	5
	.byte	142
	.byte	4
	.byte	143
	.byte	3
	.align	3
Leh_frame_end6:

	.globl	_initRandMatrix.eh
_initRandMatrix.eh:
Lset37 = Leh_frame_end7-Leh_frame_begin7
	.long	Lset37
Leh_frame_begin7:
Lset38 = Leh_frame_begin7-Leh_frame_common
	.long	Lset38
Ltmp33:
	.quad	Leh_func_begin7-Ltmp33
Lset39 = Leh_func_end7-Leh_func_begin7
	.quad	Lset39
	.byte	0
	.byte	4
Lset40 = Ltmp18-Leh_func_begin7
	.long	Lset40
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset41 = Ltmp19-Ltmp18
	.long	Lset41
	.byte	13
	.byte	6
	.byte	4
Lset42 = Ltmp20-Ltmp19
	.long	Lset42
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
Leh_frame_end7:

	.globl	_dotProductTransposed_papi.eh
_dotProductTransposed_papi.eh:
Lset43 = Leh_frame_end8-Leh_frame_begin8
	.long	Lset43
Leh_frame_begin8:
Lset44 = Leh_frame_begin8-Leh_frame_common
	.long	Lset44
Ltmp34:
	.quad	Leh_func_begin8-Ltmp34
Lset45 = Leh_func_end8-Leh_func_begin8
	.quad	Lset45
	.byte	0
	.byte	4
Lset46 = Ltmp21-Leh_func_begin8
	.long	Lset46
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset47 = Ltmp22-Ltmp21
	.long	Lset47
	.byte	13
	.byte	6
	.byte	4
Lset48 = Ltmp23-Ltmp22
	.long	Lset48
	.byte	131
	.byte	5
	.byte	142
	.byte	4
	.byte	143
	.byte	3
	.align	3
Leh_frame_end8:

	.globl	_dotProduct_papi.eh
_dotProduct_papi.eh:
Lset49 = Leh_frame_end9-Leh_frame_begin9
	.long	Lset49
Leh_frame_begin9:
Lset50 = Leh_frame_begin9-Leh_frame_common
	.long	Lset50
Ltmp35:
	.quad	Leh_func_begin9-Ltmp35
Lset51 = Leh_func_end9-Leh_func_begin9
	.quad	Lset51
	.byte	0
	.byte	4
Lset52 = Ltmp24-Leh_func_begin9
	.long	Lset52
	.byte	14
	.byte	16
	.byte	134
	.byte	2
	.byte	4
Lset53 = Ltmp25-Ltmp24
	.long	Lset53
	.byte	13
	.byte	6
	.byte	4
Lset54 = Ltmp26-Ltmp25
	.long	Lset54
	.byte	131
	.byte	6
	.byte	140
	.byte	5
	.byte	142
	.byte	4
	.byte	143
	.byte	3
	.align	3
Leh_frame_end9:


.subsections_via_symbols
