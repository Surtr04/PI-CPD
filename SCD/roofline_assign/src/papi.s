	.text
Ltext0:
	.cstring
LC0:
	.ascii "\12Error: %d - %s\12\0"
	.text
	.align 4,0x90
	.globl _handle_error
_handle_error:
LFB15:
LM1:
LVL0:
LM2:
	movslq	%edi, %rax
LM3:
	subq	$8, %rsp
LCFI0:
LM4:
	movl	%edi, %edx
LM5:
	leaq	(%rax,%rax), %rcx
	salq	$5, %rax
	leaq	LC0(%rip), %rsi
	subq	%rcx, %rax
	leaq	_p_errors(%rip), %rcx
	addq	%rax, %rcx
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
LVL1:
	xorl	%eax, %eax
	call	_fprintf
LVL2:
LM6:
	movl	$-1, %edi
	call	_exit
LVL3:
LFE15:
	.cstring
LC1:
	.ascii "%s\11\0"
LC2:
	.ascii "\11%llu\11\0"
LC3:
	.ascii "\11%llu\12\0"
	.text
	.align 4,0x90
	.globl _run_papi
_run_papi:
LFB16:
LM7:
	movq	%rbx, -48(%rsp)
LM8:
	movl	$83951616, %edi
LM9:
	movq	%rbp, -40(%rsp)
	movq	%r12, -32(%rsp)
	movq	%r13, -24(%rsp)
	movq	%r14, -16(%rsp)
	movq	%r15, -8(%rsp)
	subq	$6744, %rsp
LCFI1:
LM10:
	call	_PAPI_library_init
LVL4:
LM11:
	testl	%eax, %eax
	jg	L20
L4:
LM12:
	testl	%eax, %eax
	js	L21
LM13:
	movq	_event_set@GOTPCREL(%rip), %rbx
LM14:
	movq	%rbx, %rdi
LM15:
	movl	$-1, (%rbx)
LM16:
	call	_PAPI_create_eventset
LVL5:
	testl	%eax, %eax
	jne	L22
LM17:
	movq	_current_event@GOTPCREL(%rip), %r12
	leaq	_papi_events(%rip), %rbp
	movq	%rsp, %rsi
	movslq	(%r12), %rax
	movl	0(%rbp,%rax,4), %edi
	call	_PAPI_get_event_info
LVL6:
	testl	%eax, %eax
	jne	L23
LM18:
	movslq	(%r12), %rax
	movl	(%rbx), %edi
	movl	0(%rbp,%rax,4), %esi
	call	_PAPI_add_event
LVL7:
	testl	%eax, %eax
	jne	L24
LM19:
	call	_PAPI_get_virt_usec
LVL8:
	movq	%rax, %r14
LVL9:
LM20:
	movq	_op@GOTPCREL(%rip), %rax
LVL10:
	movl	(%rax), %eax
	testl	%eax, %eax
LM21:
	movl	$0, %eax
LM22:
	jne	L25
LM23:
	call	_dotProduct_papi
LVL11:
L10:
LM24:
	call	_PAPI_get_virt_usec
LVL12:
LM25:
	movq	___stdoutp@GOTPCREL(%rip), %r13
	leaq	4(%rsp), %rdx
	leaq	LC1(%rip), %rsi
LM26:
	movq	%rax, %r15
LVL13:
LM27:
	xorl	%eax, %eax
LVL14:
	movq	0(%r13), %rdi
	call	_fprintf
LVL15:
LM28:
	movq	0(%r13), %rdi
	leaq	LC2(%rip), %rsi
	movq	_event_value@GOTPCREL(%rip), %rax
	movq	(%rax), %rdx
	xorl	%eax, %eax
	call	_fprintf
LVL16:
LM29:
	movq	0(%r13), %rdi
	movq	%r15, %rdx
	leaq	LC3(%rip), %rsi
	subq	%r14, %rdx
	xorl	%eax, %eax
	call	_fprintf
LVL17:
LM30:
	movslq	(%r12), %rax
	movl	(%rbx), %edi
	movl	0(%rbp,%rax,4), %esi
	call	_PAPI_remove_event
LVL18:
	testl	%eax, %eax
	jne	L26
LM31:
	movq	6696(%rsp), %rbx
	movq	6704(%rsp), %rbp
	movq	6712(%rsp), %r12
	movq	6720(%rsp), %r13
	movq	6728(%rsp), %r14
LVL19:
	movq	6736(%rsp), %r15
LVL20:
	addq	$6744, %rsp
LCFI2:
	ret
LVL21:
	.align 4,0x90
L25:
LCFI3:
LM32:
	call	_dotProductTransposed_papi
LVL22:
	jmp	L10
LVL23:
L26:
LM33:
	movl	$4, %edi
	call	_handle_error
LVL24:
L24:
LM34:
	movl	$3, %edi
	call	_handle_error
LVL25:
L23:
LM35:
	movl	$5, %edi
	call	_handle_error
LVL26:
L22:
LM36:
	movl	$2, %edi
	call	_handle_error
LVL27:
L21:
LM37:
	movl	$1, %edi
	call	_handle_error
LVL28:
L20:
LM38:
	cmpl	$83951616, %eax
	je	L4
	xorl	%edi, %edi
	call	_handle_error
LVL29:
LFE16:
	.cstring
LC4:
	.ascii "wrong number of arguments\0"
	.section __TEXT,__text_startup,regular,pure_instructions
	.align 4
	.globl _main
_main:
LFB17:
LM39:
LVL30:
	pushq	%r12
LCFI4:
LM40:
	cmpl	$3, %edi
LM41:
	pushq	%rbp
LCFI5:
	pushq	%rbx
LCFI6:
LM42:
	jle	L33
LM43:
	movq	8(%rsi), %rdi
LVL31:
	movq	%rsi, %rbx
	call	_atoi
LVL32:
	movq	_size@GOTPCREL(%rip), %rdx
LM44:
	movq	16(%rbx), %rdi
LM45:
	movl	%eax, (%rdx)
LM46:
	call	_atoi
LVL33:
	movq	_op@GOTPCREL(%rip), %rbp
LM47:
	movq	24(%rbx), %rdi
LM48:
	movl	%eax, 0(%rbp)
LM49:
	call	_atoi
LVL34:
	movq	_current_event@GOTPCREL(%rip), %rdx
LM50:
	movl	$24, %edi
LM51:
	movl	%eax, (%rdx)
LM52:
	call	_malloc
LVL35:
	movq	_m@GOTPCREL(%rip), %rbx
LVL36:
LM53:
	movl	0(%rbp), %edx
LM54:
	movq	%rax, %r12
	movq	%rax, (%rbx)
LM55:
	xorl	%eax, %eax
LM56:
	testl	%edx, %edx
	je	L34
LM57:
	call	_initRandMatrix
LVL37:
LM58:
	movq	(%rbx), %rbp
LM59:
	movq	%rax, (%r12)
LM60:
	xorl	%eax, %eax
	call	_initUnitMatrix
LVL38:
	movq	%rax, %rdi
	call	_transposeMatrix
LVL39:
L32:
	movq	%rax, 8(%rbp)
LM61:
	xorl	%eax, %eax
	movq	(%rbx), %rbp
	call	_initMatrix
LVL40:
	movq	%rax, 16(%rbp)
LM62:
	xorl	%eax, %eax
	call	_run_papi
LVL41:
LM63:
	movq	(%rbx), %rdi
	call	_free
LVL42:
LM64:
	popq	%rbx
LCFI7:
	xorl	%eax, %eax
	popq	%rbp
LCFI8:
	popq	%r12
LCFI9:
	ret
L34:
LCFI10:
LM65:
	call	_initRandMatrix
LVL43:
LM66:
	movq	(%rbx), %rbp
LM67:
	movq	%rax, (%r12)
LM68:
	xorl	%eax, %eax
	call	_initUnitMatrix
LVL44:
	jmp	L32
LVL45:
L33:
LM69:
	movq	___stderrp@GOTPCREL(%rip), %rax
	movl	$25, %edx
	movl	$1, %esi
LVL46:
	leaq	LC4(%rip), %rdi
LVL47:
	movq	(%rax), %rcx
	call	_fwrite
LVL48:
LM70:
	movl	$1, %edi
	call	_exit
LVL49:
LFE17:
	.globl _papi_events
	.data
	.align 5
_papi_events:
	.long	-2147483589
	.long	-2147483598
	.long	-2147483595
	.long	-2147483594
	.long	-2147483546
	.long	-2147483596
	.long	-2147483584
	.long	-2147483648
	.long	-2147483583
	.long	-2147483646
	.long	-2147483582
	.comm	_op,4,2
	.comm	_current_event,4,2
	.comm	_event_value,16,4
	.comm	_event_set,4,2
	.comm	_m,8,3
	.comm	_size,4,2
	.data
	.align 5
_p_errors:
	.ascii "ERR_PAPI_INIT\0"
	.space 16
	.ascii "ERR_PAPI_INIT2\0"
	.space 15
	.ascii "ERR_PAPI_EVENT_SET\0"
	.space 11
	.ascii "ERR_PAPI_ADD_EVENT\0"
	.space 11
	.ascii "ERR_PAPI_REMOVE_EVENT\0"
	.space 8
	.ascii "ERR_PAPI_GET_EVENT_INFO\0"
	.space 6
	.ascii "ERR_PAPI_START\0"
	.space 15
	.ascii "ERR_PAPI_STOP\0"
	.space 16
	.section __DWARF,__debug_frame,regular,debug
Lsection__debug_frame:
Lframe0:
	.set L$set$0,LECIE0-LSCIE0
	.long L$set$0
LSCIE0:
	.long	0xffffffff
	.byte	0x1
	.ascii "\0"
	.byte	0x1
	.byte	0x78
	.byte	0x10
	.byte	0xc
	.byte	0x7
	.byte	0x8
	.byte	0x90
	.byte	0x1
	.align 3
LECIE0:
LSFDE0:
	.set L$set$1,LEFDE0-LASFDE0
	.long L$set$1
LASFDE0:
	.set L$set$2,Lframe0-Lsection__debug_frame
	.long L$set$2
	.quad	LFB15
	.set L$set$3,LFE15-LFB15
	.quad L$set$3
	.byte	0x4
	.set L$set$4,LCFI0-LFB15
	.long L$set$4
	.byte	0xe
	.byte	0x10
	.align 3
LEFDE0:
LSFDE2:
	.set L$set$5,LEFDE2-LASFDE2
	.long L$set$5
LASFDE2:
	.set L$set$6,Lframe0-Lsection__debug_frame
	.long L$set$6
	.quad	LFB16
	.set L$set$7,LFE16-LFB16
	.quad L$set$7
	.byte	0x4
	.set L$set$8,LCFI1-LFB16
	.long L$set$8
	.byte	0xe
	.byte	0xe0,0x34
	.byte	0x83
	.byte	0x7
	.byte	0x86
	.byte	0x6
	.byte	0x8c
	.byte	0x5
	.byte	0x8d
	.byte	0x4
	.byte	0x8e
	.byte	0x3
	.byte	0x8f
	.byte	0x2
	.byte	0x4
	.set L$set$9,LCFI2-LCFI1
	.long L$set$9
	.byte	0xa
	.byte	0xe
	.byte	0x8
	.byte	0x4
	.set L$set$10,LCFI3-LCFI2
	.long L$set$10
	.byte	0xb
	.align 3
LEFDE2:
LSFDE4:
	.set L$set$11,LEFDE4-LASFDE4
	.long L$set$11
LASFDE4:
	.set L$set$12,Lframe0-Lsection__debug_frame
	.long L$set$12
	.quad	LFB17
	.set L$set$13,LFE17-LFB17
	.quad L$set$13
	.byte	0x4
	.set L$set$14,LCFI4-LFB17
	.long L$set$14
	.byte	0xe
	.byte	0x10
	.byte	0x8c
	.byte	0x2
	.byte	0x4
	.set L$set$15,LCFI5-LCFI4
	.long L$set$15
	.byte	0xe
	.byte	0x18
	.byte	0x86
	.byte	0x3
	.byte	0x4
	.set L$set$16,LCFI6-LCFI5
	.long L$set$16
	.byte	0xe
	.byte	0x20
	.byte	0x83
	.byte	0x4
	.byte	0x4
	.set L$set$17,LCFI7-LCFI6
	.long L$set$17
	.byte	0xa
	.byte	0xe
	.byte	0x18
	.byte	0x4
	.set L$set$18,LCFI8-LCFI7
	.long L$set$18
	.byte	0xe
	.byte	0x10
	.byte	0x4
	.set L$set$19,LCFI9-LCFI8
	.long L$set$19
	.byte	0xe
	.byte	0x8
	.byte	0x4
	.set L$set$20,LCFI10-LCFI9
	.long L$set$20
	.byte	0xb
	.align 3
LEFDE4:
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$21,LECIE1-LSCIE1
	.long L$set$21
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.byte	0x1
	.byte	0x78
	.byte	0x10
	.byte	0x1
	.byte	0x10
	.byte	0xc
	.byte	0x7
	.byte	0x8
	.byte	0x90
	.byte	0x1
	.align 3
LECIE1:
LSFDE7:
	.set L$set$22,LEFDE7-LASFDE7
	.long L$set$22
LASFDE7:
	.long	LASFDE7-EH_frame1
	.quad	LFB15-.
	.set L$set$23,LFE15-LFB15
	.quad L$set$23
	.byte	0
	.byte	0x4
	.set L$set$24,LCFI0-LFB15
	.long L$set$24
	.byte	0xe
	.byte	0x10
	.align 3
LEFDE7:
LSFDE9:
	.set L$set$25,LEFDE9-LASFDE9
	.long L$set$25
LASFDE9:
	.long	LASFDE9-EH_frame1
	.quad	LFB16-.
	.set L$set$26,LFE16-LFB16
	.quad L$set$26
	.byte	0
	.byte	0x4
	.set L$set$27,LCFI1-LFB16
	.long L$set$27
	.byte	0xe
	.byte	0xe0,0x34
	.byte	0x83
	.byte	0x7
	.byte	0x86
	.byte	0x6
	.byte	0x8c
	.byte	0x5
	.byte	0x8d
	.byte	0x4
	.byte	0x8e
	.byte	0x3
	.byte	0x8f
	.byte	0x2
	.byte	0x4
	.set L$set$28,LCFI2-LCFI1
	.long L$set$28
	.byte	0xa
	.byte	0xe
	.byte	0x8
	.byte	0x4
	.set L$set$29,LCFI3-LCFI2
	.long L$set$29
	.byte	0xb
	.align 3
LEFDE9:
LSFDE11:
	.set L$set$30,LEFDE11-LASFDE11
	.long L$set$30
LASFDE11:
	.long	LASFDE11-EH_frame1
	.quad	LFB17-.
	.set L$set$31,LFE17-LFB17
	.quad L$set$31
	.byte	0
	.byte	0x4
	.set L$set$32,LCFI4-LFB17
	.long L$set$32
	.byte	0xe
	.byte	0x10
	.byte	0x8c
	.byte	0x2
	.byte	0x4
	.set L$set$33,LCFI5-LCFI4
	.long L$set$33
	.byte	0xe
	.byte	0x18
	.byte	0x86
	.byte	0x3
	.byte	0x4
	.set L$set$34,LCFI6-LCFI5
	.long L$set$34
	.byte	0xe
	.byte	0x20
	.byte	0x83
	.byte	0x4
	.byte	0x4
	.set L$set$35,LCFI7-LCFI6
	.long L$set$35
	.byte	0xa
	.byte	0xe
	.byte	0x18
	.byte	0x4
	.set L$set$36,LCFI8-LCFI7
	.long L$set$36
	.byte	0xe
	.byte	0x10
	.byte	0x4
	.set L$set$37,LCFI9-LCFI8
	.long L$set$37
	.byte	0xe
	.byte	0x8
	.byte	0x4
	.set L$set$38,LCFI10-LCFI9
	.long L$set$38
	.byte	0xb
	.align 3
LEFDE11:
	.text
Letext0:
	.section __DWARF,__debug_info,regular,debug
Lsection__debug_info:
Ldebug_info0:
	.long	0x1099
	.word	0x2
	.set L$set$39,Ldebug_abbrev0-Lsection__debug_abbrev
	.long L$set$39
	.byte	0x8
	.byte	0x1
	.ascii "GNU C 4.7.2\0"
	.byte	0x1
	.ascii "papi.c\0"
	.ascii "/Users/rmb/Documents/MEI/CPD/PI-CPD/roofline_assign/src\0"
	.quad	Ltext0
	.quad	Letext0
	.set L$set$40,Ldebug_line0-Lsection__debug_line
	.long L$set$40
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.ascii "signed char\0"
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.ascii "unsigned char\0"
	.byte	0x2
	.byte	0x2
	.byte	0x5
	.ascii "short int\0"
	.byte	0x2
	.byte	0x2
	.byte	0x7
	.ascii "short unsigned int\0"
	.byte	0x2
	.byte	0x4
	.byte	0x5
	.ascii "int\0"
	.byte	0x2
	.byte	0x4
	.byte	0x7
	.ascii "unsigned int\0"
	.byte	0x3
	.ascii "__int64_t\0"
	.byte	0x2
	.byte	0x2e
	.long	0xd7
	.byte	0x2
	.byte	0x8
	.byte	0x5
	.ascii "long long int\0"
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.ascii "long long unsigned int\0"
	.byte	0x2
	.byte	0x8
	.byte	0x5
	.ascii "long int\0"
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.ascii "sizetype\0"
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.ascii "char\0"
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.ascii "long unsigned int\0"
	.byte	0x4
	.byte	0x8
	.byte	0x3
	.ascii "__darwin_off_t\0"
	.byte	0x3
	.byte	0x6e
	.long	0xc6
	.byte	0x3
	.ascii "fpos_t\0"
	.byte	0x4
	.byte	0x55
	.long	0x139
	.byte	0x5
	.ascii "__sbuf\0"
	.byte	0x10
	.byte	0x4
	.byte	0x60
	.long	0x18d
	.byte	0x6
	.ascii "_base\0"
	.byte	0x4
	.byte	0x61
	.long	0x18d
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x6
	.ascii "_size\0"
	.byte	0x4
	.byte	0x62
	.long	0xaf
	.byte	0x2
	.byte	0x23
	.byte	0x8
	.byte	0
	.byte	0x7
	.byte	0x8
	.long	0x7b
	.byte	0x5
	.ascii "__sFILE\0"
	.byte	0x98
	.byte	0x4
	.byte	0x82
	.long	0x2e3
	.byte	0x6
	.ascii "_p\0"
	.byte	0x4
	.byte	0x83
	.long	0x18d
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x6
	.ascii "_r\0"
	.byte	0x4
	.byte	0x84
	.long	0xaf
	.byte	0x2
	.byte	0x23
	.byte	0x8
	.byte	0x6
	.ascii "_w\0"
	.byte	0x4
	.byte	0x85
	.long	0xaf
	.byte	0x2
	.byte	0x23
	.byte	0xc
	.byte	0x6
	.ascii "_flags\0"
	.byte	0x4
	.byte	0x86
	.long	0x8c
	.byte	0x2
	.byte	0x23
	.byte	0x10
	.byte	0x6
	.ascii "_file\0"
	.byte	0x4
	.byte	0x87
	.long	0x8c
	.byte	0x2
	.byte	0x23
	.byte	0x12
	.byte	0x6
	.ascii "_bf\0"
	.byte	0x4
	.byte	0x88
	.long	0x15d
	.byte	0x2
	.byte	0x23
	.byte	0x18
	.byte	0x6
	.ascii "_lbfsize\0"
	.byte	0x4
	.byte	0x89
	.long	0xaf
	.byte	0x2
	.byte	0x23
	.byte	0x28
	.byte	0x6
	.ascii "_cookie\0"
	.byte	0x4
	.byte	0x8c
	.long	0x137
	.byte	0x2
	.byte	0x23
	.byte	0x30
	.byte	0x6
	.ascii "_close\0"
	.byte	0x4
	.byte	0x8d
	.long	0x2f3
	.byte	0x2
	.byte	0x23
	.byte	0x38
	.byte	0x6
	.ascii "_read\0"
	.byte	0x4
	.byte	0x8e
	.long	0x319
	.byte	0x2
	.byte	0x23
	.byte	0x40
	.byte	0x6
	.ascii "_seek\0"
	.byte	0x4
	.byte	0x8f
	.long	0x339
	.byte	0x2
	.byte	0x23
	.byte	0x48
	.byte	0x6
	.ascii "_write\0"
	.byte	0x4
	.byte	0x90
	.long	0x364
	.byte	0x2
	.byte	0x23
	.byte	0x50
	.byte	0x6
	.ascii "_ub\0"
	.byte	0x4
	.byte	0x93
	.long	0x15d
	.byte	0x2
	.byte	0x23
	.byte	0x58
	.byte	0x6
	.ascii "_extra\0"
	.byte	0x4
	.byte	0x94
	.long	0x375
	.byte	0x2
	.byte	0x23
	.byte	0x68
	.byte	0x6
	.ascii "_ur\0"
	.byte	0x4
	.byte	0x95
	.long	0xaf
	.byte	0x2
	.byte	0x23
	.byte	0x70
	.byte	0x6
	.ascii "_ubuf\0"
	.byte	0x4
	.byte	0x98
	.long	0x37b
	.byte	0x2
	.byte	0x23
	.byte	0x74
	.byte	0x6
	.ascii "_nbuf\0"
	.byte	0x4
	.byte	0x99
	.long	0x38b
	.byte	0x2
	.byte	0x23
	.byte	0x77
	.byte	0x6
	.ascii "_lb\0"
	.byte	0x4
	.byte	0x9c
	.long	0x15d
	.byte	0x2
	.byte	0x23
	.byte	0x78
	.byte	0x6
	.ascii "_blksize\0"
	.byte	0x4
	.byte	0x9f
	.long	0xaf
	.byte	0x3
	.byte	0x23
	.byte	0x88,0x1
	.byte	0x6
	.ascii "_offset\0"
	.byte	0x4
	.byte	0xa0
	.long	0x14f
	.byte	0x3
	.byte	0x23
	.byte	0x90,0x1
	.byte	0
	.byte	0x8
	.byte	0x1
	.long	0xaf
	.long	0x2f3
	.byte	0x9
	.long	0x137
	.byte	0
	.byte	0x7
	.byte	0x8
	.long	0x2e3
	.byte	0x8
	.byte	0x1
	.long	0xaf
	.long	0x313
	.byte	0x9
	.long	0x137
	.byte	0x9
	.long	0x313
	.byte	0x9
	.long	0xaf
	.byte	0
	.byte	0x7
	.byte	0x8
	.long	0x11a
	.byte	0x7
	.byte	0x8
	.long	0x2f9
	.byte	0x8
	.byte	0x1
	.long	0x14f
	.long	0x339
	.byte	0x9
	.long	0x137
	.byte	0x9
	.long	0x14f
	.byte	0x9
	.long	0xaf
	.byte	0
	.byte	0x7
	.byte	0x8
	.long	0x31f
	.byte	0x8
	.byte	0x1
	.long	0xaf
	.long	0x359
	.byte	0x9
	.long	0x137
	.byte	0x9
	.long	0x359
	.byte	0x9
	.long	0xaf
	.byte	0
	.byte	0x7
	.byte	0x8
	.long	0x35f
	.byte	0xa
	.long	0x11a
	.byte	0x7
	.byte	0x8
	.long	0x33f
	.byte	0xb
	.ascii "__sFILEX\0"
	.byte	0x1
	.byte	0x7
	.byte	0x8
	.long	0x36a
	.byte	0xc
	.long	0x7b
	.long	0x38b
	.byte	0xd
	.long	0x10e
	.byte	0x2
	.byte	0
	.byte	0xc
	.long	0x7b
	.long	0x39b
	.byte	0xd
	.long	0x10e
	.byte	0
	.byte	0
	.byte	0x3
	.ascii "FILE\0"
	.byte	0x4
	.byte	0xa1
	.long	0x193
	.byte	0xc
	.long	0x11a
	.long	0x3b7
	.byte	0xd
	.long	0x10e
	.byte	0x3f
	.byte	0
	.byte	0xe
	.byte	0x4
	.byte	0x8
	.byte	0x30
	.long	0xbb1
	.byte	0xf
	.ascii "PAPI_L1_DCM_idx\0"
	.byte	0
	.byte	0xf
	.ascii "PAPI_L1_ICM_idx\0"
	.byte	0x1
	.byte	0xf
	.ascii "PAPI_L2_DCM_idx\0"
	.byte	0x2
	.byte	0xf
	.ascii "PAPI_L2_ICM_idx\0"
	.byte	0x3
	.byte	0xf
	.ascii "PAPI_L3_DCM_idx\0"
	.byte	0x4
	.byte	0xf
	.ascii "PAPI_L3_ICM_idx\0"
	.byte	0x5
	.byte	0xf
	.ascii "PAPI_L1_TCM_idx\0"
	.byte	0x6
	.byte	0xf
	.ascii "PAPI_L2_TCM_idx\0"
	.byte	0x7
	.byte	0xf
	.ascii "PAPI_L3_TCM_idx\0"
	.byte	0x8
	.byte	0xf
	.ascii "PAPI_CA_SNP_idx\0"
	.byte	0x9
	.byte	0xf
	.ascii "PAPI_CA_SHR_idx\0"
	.byte	0xa
	.byte	0xf
	.ascii "PAPI_CA_CLN_idx\0"
	.byte	0xb
	.byte	0xf
	.ascii "PAPI_CA_INV_idx\0"
	.byte	0xc
	.byte	0xf
	.ascii "PAPI_CA_ITV_idx\0"
	.byte	0xd
	.byte	0xf
	.ascii "PAPI_L3_LDM_idx\0"
	.byte	0xe
	.byte	0xf
	.ascii "PAPI_L3_STM_idx\0"
	.byte	0xf
	.byte	0xf
	.ascii "PAPI_BRU_IDL_idx\0"
	.byte	0x10
	.byte	0xf
	.ascii "PAPI_FXU_IDL_idx\0"
	.byte	0x11
	.byte	0xf
	.ascii "PAPI_FPU_IDL_idx\0"
	.byte	0x12
	.byte	0xf
	.ascii "PAPI_LSU_IDL_idx\0"
	.byte	0x13
	.byte	0xf
	.ascii "PAPI_TLB_DM_idx\0"
	.byte	0x14
	.byte	0xf
	.ascii "PAPI_TLB_IM_idx\0"
	.byte	0x15
	.byte	0xf
	.ascii "PAPI_TLB_TL_idx\0"
	.byte	0x16
	.byte	0xf
	.ascii "PAPI_L1_LDM_idx\0"
	.byte	0x17
	.byte	0xf
	.ascii "PAPI_L1_STM_idx\0"
	.byte	0x18
	.byte	0xf
	.ascii "PAPI_L2_LDM_idx\0"
	.byte	0x19
	.byte	0xf
	.ascii "PAPI_L2_STM_idx\0"
	.byte	0x1a
	.byte	0xf
	.ascii "PAPI_BTAC_M_idx\0"
	.byte	0x1b
	.byte	0xf
	.ascii "PAPI_PRF_DM_idx\0"
	.byte	0x1c
	.byte	0xf
	.ascii "PAPI_L3_DCH_idx\0"
	.byte	0x1d
	.byte	0xf
	.ascii "PAPI_TLB_SD_idx\0"
	.byte	0x1e
	.byte	0xf
	.ascii "PAPI_CSR_FAL_idx\0"
	.byte	0x1f
	.byte	0xf
	.ascii "PAPI_CSR_SUC_idx\0"
	.byte	0x20
	.byte	0xf
	.ascii "PAPI_CSR_TOT_idx\0"
	.byte	0x21
	.byte	0xf
	.ascii "PAPI_MEM_SCY_idx\0"
	.byte	0x22
	.byte	0xf
	.ascii "PAPI_MEM_RCY_idx\0"
	.byte	0x23
	.byte	0xf
	.ascii "PAPI_MEM_WCY_idx\0"
	.byte	0x24
	.byte	0xf
	.ascii "PAPI_STL_ICY_idx\0"
	.byte	0x25
	.byte	0xf
	.ascii "PAPI_FUL_ICY_idx\0"
	.byte	0x26
	.byte	0xf
	.ascii "PAPI_STL_CCY_idx\0"
	.byte	0x27
	.byte	0xf
	.ascii "PAPI_FUL_CCY_idx\0"
	.byte	0x28
	.byte	0xf
	.ascii "PAPI_HW_INT_idx\0"
	.byte	0x29
	.byte	0xf
	.ascii "PAPI_BR_UCN_idx\0"
	.byte	0x2a
	.byte	0xf
	.ascii "PAPI_BR_CN_idx\0"
	.byte	0x2b
	.byte	0xf
	.ascii "PAPI_BR_TKN_idx\0"
	.byte	0x2c
	.byte	0xf
	.ascii "PAPI_BR_NTK_idx\0"
	.byte	0x2d
	.byte	0xf
	.ascii "PAPI_BR_MSP_idx\0"
	.byte	0x2e
	.byte	0xf
	.ascii "PAPI_BR_PRC_idx\0"
	.byte	0x2f
	.byte	0xf
	.ascii "PAPI_FMA_INS_idx\0"
	.byte	0x30
	.byte	0xf
	.ascii "PAPI_TOT_IIS_idx\0"
	.byte	0x31
	.byte	0xf
	.ascii "PAPI_TOT_INS_idx\0"
	.byte	0x32
	.byte	0xf
	.ascii "PAPI_INT_INS_idx\0"
	.byte	0x33
	.byte	0xf
	.ascii "PAPI_FP_INS_idx\0"
	.byte	0x34
	.byte	0xf
	.ascii "PAPI_LD_INS_idx\0"
	.byte	0x35
	.byte	0xf
	.ascii "PAPI_SR_INS_idx\0"
	.byte	0x36
	.byte	0xf
	.ascii "PAPI_BR_INS_idx\0"
	.byte	0x37
	.byte	0xf
	.ascii "PAPI_VEC_INS_idx\0"
	.byte	0x38
	.byte	0xf
	.ascii "PAPI_RES_STL_idx\0"
	.byte	0x39
	.byte	0xf
	.ascii "PAPI_FP_STAL_idx\0"
	.byte	0x3a
	.byte	0xf
	.ascii "PAPI_TOT_CYC_idx\0"
	.byte	0x3b
	.byte	0xf
	.ascii "PAPI_LST_INS_idx\0"
	.byte	0x3c
	.byte	0xf
	.ascii "PAPI_SYC_INS_idx\0"
	.byte	0x3d
	.byte	0xf
	.ascii "PAPI_L1_DCH_idx\0"
	.byte	0x3e
	.byte	0xf
	.ascii "PAPI_L2_DCH_idx\0"
	.byte	0x3f
	.byte	0xf
	.ascii "PAPI_L1_DCA_idx\0"
	.byte	0xc0,0
	.byte	0xf
	.ascii "PAPI_L2_DCA_idx\0"
	.byte	0xc1,0
	.byte	0xf
	.ascii "PAPI_L3_DCA_idx\0"
	.byte	0xc2,0
	.byte	0xf
	.ascii "PAPI_L1_DCR_idx\0"
	.byte	0xc3,0
	.byte	0xf
	.ascii "PAPI_L2_DCR_idx\0"
	.byte	0xc4,0
	.byte	0xf
	.ascii "PAPI_L3_DCR_idx\0"
	.byte	0xc5,0
	.byte	0xf
	.ascii "PAPI_L1_DCW_idx\0"
	.byte	0xc6,0
	.byte	0xf
	.ascii "PAPI_L2_DCW_idx\0"
	.byte	0xc7,0
	.byte	0xf
	.ascii "PAPI_L3_DCW_idx\0"
	.byte	0xc8,0
	.byte	0xf
	.ascii "PAPI_L1_ICH_idx\0"
	.byte	0xc9,0
	.byte	0xf
	.ascii "PAPI_L2_ICH_idx\0"
	.byte	0xca,0
	.byte	0xf
	.ascii "PAPI_L3_ICH_idx\0"
	.byte	0xcb,0
	.byte	0xf
	.ascii "PAPI_L1_ICA_idx\0"
	.byte	0xcc,0
	.byte	0xf
	.ascii "PAPI_L2_ICA_idx\0"
	.byte	0xcd,0
	.byte	0xf
	.ascii "PAPI_L3_ICA_idx\0"
	.byte	0xce,0
	.byte	0xf
	.ascii "PAPI_L1_ICR_idx\0"
	.byte	0xcf,0
	.byte	0xf
	.ascii "PAPI_L2_ICR_idx\0"
	.byte	0xd0,0
	.byte	0xf
	.ascii "PAPI_L3_ICR_idx\0"
	.byte	0xd1,0
	.byte	0xf
	.ascii "PAPI_L1_ICW_idx\0"
	.byte	0xd2,0
	.byte	0xf
	.ascii "PAPI_L2_ICW_idx\0"
	.byte	0xd3,0
	.byte	0xf
	.ascii "PAPI_L3_ICW_idx\0"
	.byte	0xd4,0
	.byte	0xf
	.ascii "PAPI_L1_TCH_idx\0"
	.byte	0xd5,0
	.byte	0xf
	.ascii "PAPI_L2_TCH_idx\0"
	.byte	0xd6,0
	.byte	0xf
	.ascii "PAPI_L3_TCH_idx\0"
	.byte	0xd7,0
	.byte	0xf
	.ascii "PAPI_L1_TCA_idx\0"
	.byte	0xd8,0
	.byte	0xf
	.ascii "PAPI_L2_TCA_idx\0"
	.byte	0xd9,0
	.byte	0xf
	.ascii "PAPI_L3_TCA_idx\0"
	.byte	0xda,0
	.byte	0xf
	.ascii "PAPI_L1_TCR_idx\0"
	.byte	0xdb,0
	.byte	0xf
	.ascii "PAPI_L2_TCR_idx\0"
	.byte	0xdc,0
	.byte	0xf
	.ascii "PAPI_L3_TCR_idx\0"
	.byte	0xdd,0
	.byte	0xf
	.ascii "PAPI_L1_TCW_idx\0"
	.byte	0xde,0
	.byte	0xf
	.ascii "PAPI_L2_TCW_idx\0"
	.byte	0xdf,0
	.byte	0xf
	.ascii "PAPI_L3_TCW_idx\0"
	.byte	0xe0,0
	.byte	0xf
	.ascii "PAPI_FML_INS_idx\0"
	.byte	0xe1,0
	.byte	0xf
	.ascii "PAPI_FAD_INS_idx\0"
	.byte	0xe2,0
	.byte	0xf
	.ascii "PAPI_FDV_INS_idx\0"
	.byte	0xe3,0
	.byte	0xf
	.ascii "PAPI_FSQ_INS_idx\0"
	.byte	0xe4,0
	.byte	0xf
	.ascii "PAPI_FNV_INS_idx\0"
	.byte	0xe5,0
	.byte	0xf
	.ascii "PAPI_FP_OPS_idx\0"
	.byte	0xe6,0
	.byte	0xf
	.ascii "PAPI_SP_OPS_idx\0"
	.byte	0xe7,0
	.byte	0xf
	.ascii "PAPI_DP_OPS_idx\0"
	.byte	0xe8,0
	.byte	0xf
	.ascii "PAPI_VEC_SP_idx\0"
	.byte	0xe9,0
	.byte	0xf
	.ascii "PAPI_VEC_DP_idx\0"
	.byte	0xea,0
	.byte	0xf
	.ascii "PAPI_REF_CYC_idx\0"
	.byte	0xeb,0
	.byte	0xf
	.ascii "PAPI_END_idx\0"
	.byte	0xec,0
	.byte	0
	.byte	0xc
	.long	0x11a
	.long	0xbc2
	.byte	0x10
	.long	0x10e
	.word	0x3ff
	.byte	0
	.byte	0x2
	.byte	0x4
	.byte	0x4
	.ascii "float\0"
	.byte	0x11
	.ascii "event_info\0"
	.word	0x1a18
	.byte	0x5
	.word	0x3bc
	.long	0xd72
	.byte	0x12
	.ascii "event_code\0"
	.byte	0x5
	.word	0x3bd
	.long	0xb6
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x12
	.ascii "symbol\0"
	.byte	0x5
	.word	0x3bf
	.long	0xbb1
	.byte	0x2
	.byte	0x23
	.byte	0x4
	.byte	0x12
	.ascii "short_descr\0"
	.byte	0x5
	.word	0x3c0
	.long	0x3a7
	.byte	0x3
	.byte	0x23
	.byte	0x84,0x8
	.byte	0x12
	.ascii "long_descr\0"
	.byte	0x5
	.word	0x3c2
	.long	0xbb1
	.byte	0x3
	.byte	0x23
	.byte	0xc4,0x8
	.byte	0x12
	.ascii "component_index\0"
	.byte	0x5
	.word	0x3c7
	.long	0xaf
	.byte	0x3
	.byte	0x23
	.byte	0xc4,0x10
	.byte	0x12
	.ascii "units\0"
	.byte	0x5
	.word	0x3c8
	.long	0x3a7
	.byte	0x3
	.byte	0x23
	.byte	0xc8,0x10
	.byte	0x12
	.ascii "location\0"
	.byte	0x5
	.word	0x3c9
	.long	0xaf
	.byte	0x3
	.byte	0x23
	.byte	0x88,0x11
	.byte	0x12
	.ascii "data_type\0"
	.byte	0x5
	.word	0x3ca
	.long	0xaf
	.byte	0x3
	.byte	0x23
	.byte	0x8c,0x11
	.byte	0x12
	.ascii "value_type\0"
	.byte	0x5
	.word	0x3cb
	.long	0xaf
	.byte	0x3
	.byte	0x23
	.byte	0x90,0x11
	.byte	0x12
	.ascii "timescope\0"
	.byte	0x5
	.word	0x3cc
	.long	0xaf
	.byte	0x3
	.byte	0x23
	.byte	0x94,0x11
	.byte	0x12
	.ascii "update_type\0"
	.byte	0x5
	.word	0x3cd
	.long	0xaf
	.byte	0x3
	.byte	0x23
	.byte	0x98,0x11
	.byte	0x12
	.ascii "update_freq\0"
	.byte	0x5
	.word	0x3ce
	.long	0xaf
	.byte	0x3
	.byte	0x23
	.byte	0x9c,0x11
	.byte	0x12
	.ascii "count\0"
	.byte	0x5
	.word	0x3d4
	.long	0xb6
	.byte	0x3
	.byte	0x23
	.byte	0xa0,0x11
	.byte	0x12
	.ascii "event_type\0"
	.byte	0x5
	.word	0x3d9
	.long	0xb6
	.byte	0x3
	.byte	0x23
	.byte	0xa4,0x11
	.byte	0x12
	.ascii "derived\0"
	.byte	0x5
	.word	0x3dc
	.long	0x3a7
	.byte	0x3
	.byte	0x23
	.byte	0xa8,0x11
	.byte	0x12
	.ascii "postfix\0"
	.byte	0x5
	.word	0x3df
	.long	0xd72
	.byte	0x3
	.byte	0x23
	.byte	0xe8,0x11
	.byte	0x12
	.ascii "code\0"
	.byte	0x5
	.word	0x3e4
	.long	0xd82
	.byte	0x3
	.byte	0x23
	.byte	0xe8,0x13
	.byte	0x12
	.ascii "name\0"
	.byte	0x5
	.word	0x3e9
	.long	0xd92
	.byte	0x3
	.byte	0x23
	.byte	0x98,0x14
	.byte	0x12
	.ascii "note\0"
	.byte	0x5
	.word	0x3ee
	.long	0xbb1
	.byte	0x3
	.byte	0x23
	.byte	0x98,0x2c
	.byte	0
	.byte	0xc
	.long	0x11a
	.long	0xd82
	.byte	0xd
	.long	0x10e
	.byte	0xff
	.byte	0
	.byte	0xc
	.long	0xb6
	.long	0xd92
	.byte	0xd
	.long	0x10e
	.byte	0xb
	.byte	0
	.byte	0xc
	.long	0x11a
	.long	0xda8
	.byte	0xd
	.long	0x10e
	.byte	0xb
	.byte	0xd
	.long	0x10e
	.byte	0xff
	.byte	0
	.byte	0x13
	.ascii "PAPI_event_info_t\0"
	.byte	0x5
	.word	0x3f3
	.long	0xbcb
	.byte	0x5
	.ascii "mat\0"
	.byte	0x18
	.byte	0x6
	.byte	0xb
	.long	0xe05
	.byte	0x6
	.ascii "matrixA\0"
	.byte	0x6
	.byte	0xc
	.long	0xe05
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x6
	.ascii "matrixB\0"
	.byte	0x6
	.byte	0xd
	.long	0xe05
	.byte	0x2
	.byte	0x23
	.byte	0x8
	.byte	0x6
	.ascii "matrixC\0"
	.byte	0x6
	.byte	0xe
	.long	0xe05
	.byte	0x2
	.byte	0x23
	.byte	0x10
	.byte	0
	.byte	0x7
	.byte	0x8
	.long	0xe0b
	.byte	0x7
	.byte	0x8
	.long	0xbc2
	.byte	0x3
	.ascii "matrices\0"
	.byte	0x6
	.byte	0xf
	.long	0xdc2
	.byte	0x5
	.ascii "p_error\0"
	.byte	0x1e
	.byte	0x7
	.byte	0x9
	.long	0xe45
	.byte	0x6
	.ascii "err_code\0"
	.byte	0x7
	.byte	0xa
	.long	0xe45
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0
	.byte	0xc
	.long	0x11a
	.long	0xe55
	.byte	0xd
	.long	0x10e
	.byte	0x1d
	.byte	0
	.byte	0x3
	.ascii "papi_error\0"
	.byte	0x7
	.byte	0xb
	.long	0xe21
	.byte	0x14
	.byte	0x1
	.ascii "handle_error\0"
	.byte	0x1
	.byte	0x9
	.byte	0x1
	.quad	LFB15
	.quad	LFE15
	.set L$set$41,LLST0-Lsection__debug_loc
	.long L$set$41
	.long	0xea4
	.byte	0x15
	.ascii "err_no\0"
	.byte	0x1
	.byte	0x9
	.long	0xaf
	.set L$set$42,LLST1-Lsection__debug_loc
	.long L$set$42
	.byte	0
	.byte	0x16
	.byte	0x1
	.ascii "run_papi\0"
	.byte	0x1
	.byte	0x24
	.quad	LFB16
	.quad	LFE16
	.set L$set$43,LLST2-Lsection__debug_loc
	.long L$set$43
	.long	0xf1b
	.byte	0x17
	.ascii "papi_version\0"
	.byte	0x1
	.byte	0x26
	.long	0xaf
	.set L$set$44,LLST3-Lsection__debug_loc
	.long L$set$44
	.byte	0x17
	.ascii "start_time\0"
	.byte	0x1
	.byte	0x27
	.long	0xe8
	.set L$set$45,LLST4-Lsection__debug_loc
	.long L$set$45
	.byte	0x17
	.ascii "end_time\0"
	.byte	0x1
	.byte	0x27
	.long	0xe8
	.set L$set$46,LLST5-Lsection__debug_loc
	.long L$set$46
	.byte	0x18
	.ascii "inf\0"
	.byte	0x1
	.byte	0x30
	.long	0xda8
	.byte	0x3
	.byte	0x91
	.byte	0xa0,0x4b
	.byte	0
	.byte	0x19
	.byte	0x1
	.ascii "main\0"
	.byte	0x1
	.byte	0x46
	.byte	0x1
	.long	0xaf
	.quad	LFB17
	.quad	LFE17
	.set L$set$47,LLST6-Lsection__debug_loc
	.long L$set$47
	.long	0xf62
	.byte	0x15
	.ascii "argc\0"
	.byte	0x1
	.byte	0x46
	.long	0xaf
	.set L$set$48,LLST7-Lsection__debug_loc
	.long L$set$48
	.byte	0x15
	.ascii "argv\0"
	.byte	0x1
	.byte	0x46
	.long	0xf62
	.set L$set$49,LLST8-Lsection__debug_loc
	.long L$set$49
	.byte	0
	.byte	0x7
	.byte	0x8
	.long	0x313
	.byte	0xc
	.long	0xe55
	.long	0xf78
	.byte	0xd
	.long	0x10e
	.byte	0x7
	.byte	0
	.byte	0x18
	.ascii "p_errors\0"
	.byte	0x7
	.byte	0x18
	.long	0xf68
	.byte	0x9
	.byte	0x3
	.quad	_p_errors
	.byte	0x1a
	.ascii "__stdoutp\0"
	.byte	0x4
	.byte	0xa5
	.long	0xfa5
	.byte	0x1
	.byte	0x1
	.byte	0x7
	.byte	0x8
	.long	0x39b
	.byte	0x1a
	.ascii "__stderrp\0"
	.byte	0x4
	.byte	0xa6
	.long	0xfa5
	.byte	0x1
	.byte	0x1
	.byte	0x1b
	.ascii "size\0"
	.byte	0x6
	.byte	0x9
	.long	0xaf
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	_size
	.byte	0x1b
	.ascii "m\0"
	.byte	0x6
	.byte	0x12
	.long	0xfe9
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	_m
	.byte	0x7
	.byte	0x8
	.long	0xe11
	.byte	0x1b
	.ascii "event_set\0"
	.byte	0x7
	.byte	0x6
	.long	0xaf
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	_event_set
	.byte	0xc
	.long	0xd7
	.long	0x101b
	.byte	0xd
	.long	0x10e
	.byte	0x1
	.byte	0
	.byte	0x1b
	.ascii "event_value\0"
	.byte	0x7
	.byte	0x7
	.long	0x100b
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	_event_value
	.byte	0x1b
	.ascii "current_event\0"
	.byte	0x1
	.byte	0x10
	.long	0xaf
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	_current_event
	.byte	0x1b
	.ascii "op\0"
	.byte	0x1
	.byte	0x11
	.long	0xaf
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	_op
	.byte	0xc
	.long	0xaf
	.long	0x107e
	.byte	0xd
	.long	0x10e
	.byte	0xa
	.byte	0
	.byte	0x1b
	.ascii "papi_events\0"
	.byte	0x1
	.byte	0x14
	.long	0x106e
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	_papi_events
	.byte	0
	.section __DWARF,__debug_abbrev,regular,debug
Lsection__debug_abbrev:
Ldebug_abbrev0:
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.byte	0x8
	.byte	0x13
	.byte	0xb
	.byte	0x3
	.byte	0x8
	.byte	0x1b
	.byte	0x8
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0x10
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0x2
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0x8
	.byte	0
	.byte	0
	.byte	0x3
	.byte	0x16
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x4
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0x5
	.byte	0x13
	.byte	0x1
	.byte	0x3
	.byte	0x8
	.byte	0xb
	.byte	0xb
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x6
	.byte	0xd
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x38
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x7
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x8
	.byte	0x15
	.byte	0x1
	.byte	0x27
	.byte	0xc
	.byte	0x49
	.byte	0x13
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0x5
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xa
	.byte	0x26
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xb
	.byte	0x13
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3c
	.byte	0xc
	.byte	0
	.byte	0
	.byte	0xc
	.byte	0x1
	.byte	0x1
	.byte	0x49
	.byte	0x13
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xd
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0xe
	.byte	0x4
	.byte	0x1
	.byte	0xb
	.byte	0xb
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xf
	.byte	0x28
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x1c
	.byte	0xd
	.byte	0
	.byte	0
	.byte	0x10
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0x5
	.byte	0
	.byte	0
	.byte	0x11
	.byte	0x13
	.byte	0x1
	.byte	0x3
	.byte	0x8
	.byte	0xb
	.byte	0x5
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x12
	.byte	0xd
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0x38
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x13
	.byte	0x16
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x14
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0xc
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x27
	.byte	0xc
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0x40
	.byte	0x6
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x15
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0x16
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0xc
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0x40
	.byte	0x6
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x17
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0x18
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x19
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0xc
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x27
	.byte	0xc
	.byte	0x49
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0x40
	.byte	0x6
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x1a
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x3f
	.byte	0xc
	.byte	0x3c
	.byte	0xc
	.byte	0
	.byte	0
	.byte	0x1b
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x3f
	.byte	0xc
	.byte	0x2
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0
	.section __DWARF,__debug_loc,regular,debug
Lsection__debug_loc:
Ldebug_loc0:
LLST0:
	.quad	LFB15
	.quad	LCFI0
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	LCFI0
	.quad	LFE15
	.word	0x2
	.byte	0x77
	.byte	0x10
	.quad	0
	.quad	0
LLST1:
	.quad	LVL0
	.quad	LVL1
	.word	0x1
	.byte	0x55
	.quad	LVL1
	.quad	LVL2-1
	.word	0x1
	.byte	0x51
	.quad	0
	.quad	0
LLST2:
	.quad	LFB16
	.quad	LCFI1
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	LCFI1
	.quad	LCFI2
	.word	0x3
	.byte	0x77
	.byte	0xe0,0x34
	.quad	LCFI2
	.quad	LCFI3
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	LCFI3
	.quad	LFE16
	.word	0x3
	.byte	0x77
	.byte	0xe0,0x34
	.quad	0
	.quad	0
LLST3:
	.quad	LVL4
	.quad	LVL5-1
	.word	0x1
	.byte	0x50
	.quad	LVL27
	.quad	LVL28-1
	.word	0x1
	.byte	0x50
	.quad	LVL28
	.quad	LVL29-1
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST4:
	.quad	LVL9
	.quad	LVL10
	.word	0x1
	.byte	0x50
	.quad	LVL10
	.quad	LVL19
	.word	0x1
	.byte	0x5e
	.quad	LVL21
	.quad	LVL24
	.word	0x1
	.byte	0x5e
	.quad	0
	.quad	0
LLST5:
	.quad	LVL13
	.quad	LVL14
	.word	0x1
	.byte	0x50
	.quad	LVL14
	.quad	LVL20
	.word	0x1
	.byte	0x5f
	.quad	LVL23
	.quad	LVL24
	.word	0x1
	.byte	0x5f
	.quad	0
	.quad	0
LLST6:
	.quad	LFB17
	.quad	LCFI4
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	LCFI4
	.quad	LCFI5
	.word	0x2
	.byte	0x77
	.byte	0x10
	.quad	LCFI5
	.quad	LCFI6
	.word	0x2
	.byte	0x77
	.byte	0x18
	.quad	LCFI6
	.quad	LCFI7
	.word	0x2
	.byte	0x77
	.byte	0x20
	.quad	LCFI7
	.quad	LCFI8
	.word	0x2
	.byte	0x77
	.byte	0x18
	.quad	LCFI8
	.quad	LCFI9
	.word	0x2
	.byte	0x77
	.byte	0x10
	.quad	LCFI9
	.quad	LCFI10
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	LCFI10
	.quad	LFE17
	.word	0x2
	.byte	0x77
	.byte	0x20
	.quad	0
	.quad	0
LLST7:
	.quad	LVL30
	.quad	LVL31
	.word	0x1
	.byte	0x55
	.quad	LVL45
	.quad	LVL47
	.word	0x1
	.byte	0x55
	.quad	0
	.quad	0
LLST8:
	.quad	LVL30
	.quad	LVL32-1
	.word	0x1
	.byte	0x54
	.quad	LVL32-1
	.quad	LVL36
	.word	0x1
	.byte	0x53
	.quad	LVL45
	.quad	LVL46
	.word	0x1
	.byte	0x54
	.quad	0
	.quad	0
	.section __DWARF,__debug_pubnames,regular,debug
Lsection__debug_pubnames:
	.long	0x8b
	.word	0x2
	.set L$set$50,Ldebug_info0-Lsection__debug_info
	.long L$set$50
	.long	0x109d
	.long	0xe67
	.ascii "handle_error\0"
	.long	0xea4
	.ascii "run_papi\0"
	.long	0xf1b
	.ascii "main\0"
	.long	0xfbe
	.ascii "size\0"
	.long	0xfd5
	.ascii "m\0"
	.long	0xfef
	.ascii "event_set\0"
	.long	0x101b
	.ascii "event_value\0"
	.long	0x1039
	.ascii "current_event\0"
	.long	0x1059
	.ascii "op\0"
	.long	0x107e
	.ascii "papi_events\0"
	.long	0
	.section __DWARF,__debug_pubtypes,regular,debug
Lsection__debug_pubtypes:
	.long	0xaf
	.word	0x2
	.set L$set$51,Ldebug_info0-Lsection__debug_info
	.long L$set$51
	.long	0x109d
	.long	0xc6
	.ascii "__int64_t\0"
	.long	0x139
	.ascii "__darwin_off_t\0"
	.long	0x14f
	.ascii "fpos_t\0"
	.long	0x15d
	.ascii "__sbuf\0"
	.long	0x193
	.ascii "__sFILE\0"
	.long	0x39b
	.ascii "FILE\0"
	.long	0xbcb
	.ascii "event_info\0"
	.long	0xda8
	.ascii "PAPI_event_info_t\0"
	.long	0xdc2
	.ascii "mat\0"
	.long	0xe11
	.ascii "matrices\0"
	.long	0xe21
	.ascii "p_error\0"
	.long	0xe55
	.ascii "papi_error\0"
	.long	0
	.section __DWARF,__debug_aranges,regular,debug
Lsection__debug_aranges:
	.long	0x3c
	.word	0x2
	.set L$set$52,Ldebug_info0-Lsection__debug_info
	.long L$set$52
	.byte	0x8
	.byte	0
	.word	0
	.word	0
	.quad	Ltext0
	.set L$set$53,Letext0-Ltext0
	.quad L$set$53
	.quad	LFB17
	.set L$set$54,LFE17-LFB17
	.quad L$set$54
	.quad	0
	.quad	0
	.section __DWARF,__debug_line,regular,debug
Lsection__debug_line:
Ldebug_line0:
	.set L$set$55,LELT0-LSLT0
	.long L$set$55
LSLT0:
	.word	0x2
	.set L$set$56,LELTP0-LASLTP0
	.long L$set$56
LASLTP0:
	.byte	0x1
	.byte	0x1
	.byte	0xf6
	.byte	0xf2
	.byte	0xd
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x1
	.ascii "/usr/include"
	.byte	0
	.ascii "/usr/include/i386"
	.byte	0
	.ascii "/usr/include/sys"
	.byte	0
	.ascii "/usr/local/include"
	.byte	0
	.byte	0
	.ascii "papi.c\0"
	.byte	0
	.byte	0
	.byte	0
	.ascii "i386/_types.h\0"
	.byte	0x1
	.byte	0
	.byte	0
	.ascii "sys/_types.h\0"
	.byte	0x1
	.byte	0
	.byte	0
	.ascii "stdio.h\0"
	.byte	0x1
	.byte	0
	.byte	0
	.ascii "papi.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "matrixDotProduct.h\0"
	.byte	0
	.byte	0
	.byte	0
	.ascii "papi_errors.h\0"
	.byte	0
	.byte	0
	.byte	0
	.ascii "papiStdEventDefs.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.byte	0
LELTP0:
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM39
	.byte	0x5c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM40
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM41
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM42
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM43
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM44
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM45
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM46
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM47
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM48
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM49
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM50
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM51
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM52
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM53
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM54
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM55
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM56
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM57
	.byte	0x1e
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM58
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM59
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM60
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM61
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM62
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM63
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM64
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM65
	.byte	0x3
	.byte	0x6f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM66
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM67
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM68
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM69
	.byte	0x3
	.byte	0x73
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM70
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LFE17
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM1
	.byte	0x1f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM2
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM3
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM4
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM5
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM6
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM7
	.byte	0x30
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM8
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM9
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM10
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM11
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM12
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM13
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM14
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM15
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM16
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM17
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM18
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM19
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM20
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM21
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM22
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM23
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM24
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM25
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM26
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM27
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM28
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM29
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM30
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM31
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM32
	.byte	0x3
	.byte	0x73
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM33
	.byte	0x20
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM34
	.byte	0x3
	.byte	0x73
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM35
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM36
	.byte	0x14
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM37
	.byte	0x14
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM38
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	Letext0
	.byte	0
	.byte	0x1
	.byte	0x1
LELT0:
	.subsections_via_symbols
