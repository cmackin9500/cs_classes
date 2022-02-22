// Lab 7
// COSC130
// This lab will take a left and right intergers and spits out the answer to it using RISCV. The user is able to specify the integer and operand. If the user types in too much or too little command line arguments, it will print out a message.
// Casey Mackinnon
// March 1st 2019
// Recieved help from TA Daniel and TA Chris.

.section .rodata
output:		.asciz "Result: %d %c %d = %d\n"
int_scan:	.asciz "%d"
char_scan:	.asciz "%c"
over:		.asciz "Too many arguments\n"
under:		.asciz "Not enough arguments\n"
unknown:	.asciz "Unknown operator '%c'\n"


.section .text
.global main
main:
//		sp + 0: ra register
//		sp + 8: s0's old value
//		sp + 16: s1's old value
//		sp + 24: s2's old value
//		sp + 32: int left
//		sp + 36: char op
//		sp + 37: int right

		addi	sp, sp, -41
		sd		ra, 0(sp)

		li		t0, 4
		blt		a0, t0, not_enough		// if argc is less than 4, it jumps to not_enough
		bgt		a0, t0, too_many		// if argc is less than 4, it jumps to not_enough

		sd		s0, 8(sp)				// s0 = *(sp + 8)
		sd		s1, 16(sp)				// s1 = *(sp + 16)
		sd		s2, 24(sp)				// s2 = *(sp + 24)
	
		ld		s0, 8(a1)				// s0 = argv[1]
		ld		s1, 16(a1)				// s1 = argv[2]
		ld		s2, 24(a1)				// s2 = argv[3]

//		sscanf(argv[1], "%d", &left)
		mv		a0, s0					// a0 = argv[1]
		la		a1, int_scan			// a1 = "%d"
		addi	a2, sp, 32				// a2 = sp + 32
		call	sscanf		

//		scanf(argv[2], "%c", &operand)
		mv		a0, s1					// a0 = argv[2]
		la		a1, char_scan			// a1 = "%c"
		addi	a2, sp, 36				// a2 = sp + 36
		call	sscanf
	
//		scanf(argv[3], "%d", &right)
		mv		a0, s2					// a0 = agrv[3]
		la		a1, int_scan			// a1 = "%d"
		addi	a2, sp, 37				// a2 = sp + 37
		call	sscanf

		lw		a0, 32(sp)
		lw		a1, 37(sp)

// bunch of if statements to determine the operand and jumps
// go through all operands in if statment. If all false then the operand is invalid.

		lb		t2, 36(sp)
//		if(operand == '+')
		li		t1,	'+'		
		beq		t2, t1, addition

//		if(operand == '-')
		li		t1, '-'
		beq		t2, t1, subtraction

//		if(operand == 'x')
		li		t1, 'x'
		beq		t2, t1, multiplication

//		if(operand == '/')
		li		t1, '/'
		beq		t2, t1, division

//		if(operand == '%')
		li		t1, '%'
		beq		t2, t1, remainder

//		printf("Unknown operator '%c'\n)
		la		a0, unknown
		lb		a1, 36(sp)
		call	printf
		j		exit

//		a0 = add(left, right)
addition:
		call	add
		j		printout

//		a0 = sub(left, right)
subtraction:
		call	sub
		j		printout

//		a0 = mul(left, right)
multiplication:
		call	mul
		j		printout

//		a0 = div(left, right)
division:
		call	div
		j		printout

//		a0 = rem(left, right)
remainder:
		call	rem
		j		printout

printout:
//		printf("Result: %d %c %d\n", left, operand, right)
		mv		a4, a0			// a4 = a0
		la		a0, output		// a0 = "Result: %d %c %d\n"
		lw		a1, 32(sp)		// a1 = left
		lb		a2, 36(sp)		// a2 = operand
		lw		a3, 37(sp)		// a3 = right
		call	printf
		j		exit

//		printf("Too many arguments\n")
too_many:
		la		a0, over
		call	printf
		j		exit

//		printf("Not enough arguments"\n)
not_enough:
		la		a0, under
		call	printf
		j		exit

exit:
//		load back the stacks
		ld		ra, 0(sp)
		ld		s0, 8(a1)
		ld		s1, 16(a1)
		ld		s2, 24(a1)
		addi	sp, sp, 41
		ret


//		int add(int left, int right) 
//		{	
//			return (left + right);
//		}
.global add
add:
		add		a0, a0, a1
		ret

//		int sub(int left, int right) 
//		{	
//			return (left - right)
//		}
.global sub
sub:
		sub		a0, a0, a1
		ret

//		int mul(int left, int right) 
//		{	
//			return (left * right);
//		}
.global mul
mul:
		mul		a0, a0, a1
		ret

//		int div(int left, int right) 
//		{	
//			if(right == 0) {
//				return -1;
//			}
//			return (left / right);
//		}
.global div
div:
		div		a0, a0, a1
		li		t0, -1
		beq		a1, t0, return
return:
		ret

//		int rem(int left, int right) 
//		{	
//			if(right == 0) {
//				return 0;
//			}
//			return (left % right);
//		}
.global rem
rem:
		rem		a0, a0, a1
		li		t0, 0
		beq		a1, t0, zero
		j		answer
zero:
		mv		a0, t0
answer:
		ret

