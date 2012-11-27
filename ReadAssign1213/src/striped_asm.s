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

;k loop 2 loads 2 stores 9 insts
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
;i loop 	
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