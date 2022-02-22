// Lab 9
// COSC130
// This lab takes a 64 bit virtual address from the user. Once it takes it in, it will disect the parts into VPN[0], VPN[1], VPN[2], and page offset and tell the user. If the command line arguments is less than 2, it will print out an error message and notify the user. If it is over 2, it will ignore them.
// Casey Mackinnon
// April 1st 2019
// Recieved help from TA Leroy, TA Chris, and TA Jacob

.section .rodata
level:	.asciz "  Level   Index  Byte Offset\n"
vpn:	.asciz "VPN[%03d] = %-5d(%4d)\n"
po:		.asciz "PO       = %x\n"
scan:	.asciz "0x%lx"
argc:	.asciz "Usage: %s 0x<address>\n"

.section .text
.global main
main:
	addi	sp, sp, -32
	sd		ra, 0(sp)
	sd		s0, 8(sp)
	mv		s0, a1			// s0 = *argv[]

//	if(argc >= 2) { jump 1 forward }
	li		t0, 2
	bge		a0, t0, 1f
	la		a0, argc
	ld		a1, 0(a1)		// a1 = argv[1]
//	printf("Usage: argv[0] 0x<address>\n);
	call	printf@plt	
	ld		ra, 0(sp)
	ld		s0, 8(sp)
	addi	sp, sp, 32
	ret
//	if the user types in less than 2 command line arguments, it will notfiy the user and returns

1:
//	sscanf(argv[1], "0x%lx", sp+24)
	sd		s1, 16(sp)
	ld		a0, 8(s0)
	la		a1, scan
	addi	a2, sp, 24		// sp+24 = loaded in byte
	call	sscanf@plt

//	printf("  Level   Index  Byte Offset\n")
	la		a0, level
	call printf@plt

	ld		s0, 24(sp)		// s0 = address
	li		s1, 2			// int i = 2

1:
//	for(int i = 2; i > -1; --i) 
//	if(i == -1) { jump to end }
	li		t1, -1
	beq		s1, t1, 1f
	la		a0, vpn
	li		t2, 9			// t2 = shifter = 9
	li		t3, 0x1ff		// t3 = mask = 0x1ff
	mv		t4, s0			// t4 = address

	mul		t2, t2, s1		// t2 = i*9
	addi	t2, t2, 12
	srl		t4, t4,	t2		// t4 >>= i*9 + 12
	and		t3, t4, t3		// shifted address & mask

//	load in all the neccessary components in a0, a1, a2, and a3.
	mv		a1, s1
	mv		a2, t3
	li		t4, 8
	mul		t4, t3, t4		// vpn*8
	mv		a3, t4

//	printf("VPN[%03d] = %-5d(%4d)\n", i, vpn, vpn*8)
	call printf@plt
	
	addi	s1, s1, -1		// --i
	j		1b

1:
//	printf(po:     .asciz "PO       = %x\n", po)
	li		t0, 0xfff
	and		a1, t0, s0
	la		a0, po
	call	printf@plt

//	load back all the components back into the stack
	ld		ra, 0(sp)
	ld		s0, 8(sp)
	ld		s1, 16(sp)
	addi	sp, sp, 32
	ret
