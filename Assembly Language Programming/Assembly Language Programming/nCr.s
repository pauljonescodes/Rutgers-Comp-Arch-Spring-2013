.globl Factorial
	.type	Factorial, @function
Factorial:
  # Your code for Factorial should go here

pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$1, -4(%ebp)
	jmp	.L2
.L4:
	movl	$-1, %eax
	jmp	.L5
.L3:
	movl	-4(%ebp), %eax
	imull	8(%ebp), %eax
	jo	.L4
	movl	%eax, -4(%ebp)
	subl	$1, 8(%ebp)
.L2:
	cmpl	$0, 8(%ebp)
	jg	.L3
	movl	-4(%ebp), %eax
.L5:
	leave
	ret
	.size	Factorial, .-Factorial

.globl nCr
	.type	nCr, @function
nCr:
  # Your code for nCr should go here

	pushl	%ebp
	movl	%esp, %ebp
	subl	$36, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	Factorial
	movl	%eax, -20(%ebp)
	cmpl	$-1, -20(%ebp)
	jne	.L6
	movl	$-1, %eax
	jmp	.L7
.L6:
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	Factorial
	movl	%eax, -16(%ebp)
	cmpl	$-1, -16(%ebp)
	jne	.L8
	movl	$-1, %eax
	jmp	.L7
.L8:
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, (%esp)
	call	Factorial
	movl	%eax, -12(%ebp)
	cmpl	$-1, -12(%ebp)
	jne	.L9
	movl	$-1, %eax
	jmp	.L7
.L9:
	movl	-16(%ebp), %eax
	imull	-12(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-20(%ebp), %eax
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	-8(%ebp)
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
.L7:
	leave
	ret
	.size	nCr, .-nCr
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-3)"
	.section	.note.GNU-stack,"",@progbits
