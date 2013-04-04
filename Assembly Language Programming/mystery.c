#include <stdio.h>

/*
 * So I can read that there are three functions.
 * 
 *     1. main
 *     2. compute_fib and
 *     3. add
 * 
 * I'm going to start with the simplest, add, and see where I get.
 */

int add(int a, int b) {
	
	/*
	 pushl	%ebp			; standard stuff
	 movl	%esp, %ebp		; standard stuff
	 movl	12(%ebp), %eax	; second variable into %eax
	 addl	8(%ebp), %eax	; add the first variable into %eax
	 popl	%ebp			; standard stuff
	 ret					; return
	 */
	
	return a + b;
}

int compute_fib(int a) {
	/*
	 compute_fib:
	 pushl	%ebp				; standard stuff
	 movl	%esp, %ebp			; same
	 pushl	%ebx				;
	 subl	$28, %esp			; subtracting the literal 28 from the stack pointer
								; perhaps this is a hint to how many variables there are
	 movl	8(%ebp), %eax		; moving "first" thing into %eax, starting to get interesting
	 movl	num(,%eax,4), %eax	;
	 cmpl	$-1, %eax			;
	 je	.L4						; this test for equality with -1 and what's in eax, if true, move to .L4
								; considering this is fibonacci, I imagine some sort of comparision in 
								; a loop
	 
								; I'm under the impression that this fuzzy hard to read
								; multiplying stuff is the optimization, and I'm getting the
								; impression that it's something to do with an array.
	 
	 movl	8(%ebp), %eax		;
	 movl	num(,%eax,4), %eax	; it's not clear to my why, but this but this moves the number that is
								; 4 times the thing into eax into eax
	 movl	%eax, -24(%ebp)		;
	 jmp	.L6					;
	 */
	 
	/*
	 .L4:
	 movl	$-1, -8(%ebp)
	 cmpl	$0, 8(%ebp)
	 jne	.L7
	 movl	$0, -8(%ebp)
	 jmp	.L9
	 */
	
	if (a == 0)
		return 0;
	
	/*
	 .L7:
	 cmpl	$1, 8(%ebp)
	 jne	.L10			; if not equal to 1, jump to 10
	 movl	$1, -8(%ebp)
	 jmp	.L9
	 */
	
	else if (a == 1)
		return 1;
	
	/*
	 .L10:
	 movl	8(%ebp), %eax
	 subl	$2, %eax
	 movl	%eax, (%esp)
	 call	compute_fib		; RECURSION
	 movl	%eax, %ebx
	 movl	8(%ebp), %eax
	 subl	$1, %eax
	 movl	%eax, (%esp)
	 call	compute_fib		; RECURSION (double?)
	 movl	%ebx, 4(%esp)
	 movl	%eax, (%esp)
	 call	add				; CALLING OUR EARLIER FUNCTION!
	 movl	%eax, -8(%ebp)
	 
	 
	 this block easily translates into C, it's even somewhat readble
	 
	 */
	
	else {
		return compute_fib(a - 1) + compute_fib(a - 2);
	}
	
	/*
	 .L9:
	 movl	8(%ebp), %eax
	 movl	num(,%eax,4), %eax
	 cmpl	$-1, %eax
	 jne	.L12
	 movl	8(%ebp), %edx
	 movl	-8(%ebp), %eax
	 movl	%eax, num(,%edx,4)
	 */
	 
	if (a != -1)
		return a;
	
	/*
	 .L12:
	 movl	8(%ebp), %eax
	 movl	num(,%eax,4), %eax
	 movl	%eax, -24(%ebp)
	 */
	
	return -1;
	
	/*
	 .L6:
	 movl	-24(%ebp), %eax
	 addl	$28, %esp
	 popl	%ebx
	 popl	%ebp
	 ret
	 */
}


int main() {
	
}
