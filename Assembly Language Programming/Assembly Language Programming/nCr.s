	.section	__TEXT,__text,regular,pure_instructions
	.globl	_choose
	.align	4, 0x90
_choose:
Leh_func_begin1:
	pushq	%rbp
Ltmp0:
	movq	%rsp, %rbp
Ltmp1:
	subq	$16, %rsp
Ltmp2:
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-8(%rbp), %eax
	cmpl	$0, %eax
	jne	LBB1_2
	movl	$1, -16(%rbp)
	jmp	LBB1_3
LBB1_2:
	movl	-8(%rbp), %eax
	subl	$1, %eax
	movl	-4(%rbp), %ecx
	subl	$1, %ecx
	movl	%ecx, %edi
	movl	%eax, %esi
	callq	_choose
	movl	%eax, %ecx
	movl	-4(%rbp), %esi
	imull	%esi, %ecx
	movl	-8(%rbp), %esi
	movl	%ecx, %eax
	cltd
	idivl	%esi
	movl	%eax, %ecx
	movl	%ecx, -16(%rbp)
LBB1_3:
	movl	-16(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	ret
Leh_func_end1:

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
	.globl	_choose.eh
_choose.eh:
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
	.align	3
Leh_frame_end1:


.subsections_via_symbols
