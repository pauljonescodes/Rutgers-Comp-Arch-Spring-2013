	.file	"mystery.c"
	.text
.globl add
	.type	add, @function
add:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	popl	%ebp
	ret
	.size	add, .-add
.globl compute_fib
	.type	compute_fib, @function
compute_fib:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %eax
	movl	num(,%eax,4), %eax
	cmpl	$-1, %eax
	je	.L4
	movl	8(%ebp), %eax
	movl	num(,%eax,4), %eax
	movl	%eax, -24(%ebp)
	jmp	.L6
.L4:
	movl	$-1, -8(%ebp)
	cmpl	$0, 8(%ebp)
	jne	.L7
	movl	$0, -8(%ebp)
	jmp	.L9
.L7:
	cmpl	$1, 8(%ebp)
	jne	.L10
	movl	$1, -8(%ebp)
	jmp	.L9
.L10:
	movl	8(%ebp), %eax
	subl	$2, %eax
	movl	%eax, (%esp)
	call	compute_fib
	movl	%eax, %ebx
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, (%esp)
	call	compute_fib
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	add
	movl	%eax, -8(%ebp)
.L9:
	movl	8(%ebp), %eax
	movl	num(,%eax,4), %eax
	cmpl	$-1, %eax
	jne	.L12
	movl	8(%ebp), %edx
	movl	-8(%ebp), %eax
	movl	%eax, num(,%edx,4)
.L12:
	movl	8(%ebp), %eax
	movl	num(,%eax,4), %eax
	movl	%eax, -24(%ebp)
.L6:
	movl	-24(%ebp), %eax
	addl	$28, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	compute_fib, .-compute_fib
	.section	.rodata
.LC0:
	.string	"Value:   %d\n"
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
	movl	4(%ecx), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	atoi
	movl	%eax, -12(%ebp)
	movl	$0, -8(%ebp)
	jmp	.L16
.L17:
	movl	-8(%ebp), %eax
	movl	$-1, num(,%eax,4)
	addl	$1, -8(%ebp)
.L16:
	cmpl	$199, -8(%ebp)
	jle	.L17
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	compute_fib
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	$0, %eax
	addl	$36, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.comm	num,800,32
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-51)"
	.section	.note.GNU-stack,"",@progbits
