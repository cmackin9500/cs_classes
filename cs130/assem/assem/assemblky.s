.section .rodata
output:    .asciz "%d %c %d\n"
under:    .asciz "Not enough arguments\n"
over:    .asciz "Too many arguments\n"

.section .text
.global main
main:

addi    sp, sp, -9

ld        a0, 0(sp)

sd        ra, 0(sp)
sd        a0, 8(sp)
sd        a1, 16(sp)
sd        a2, 24(sp)

ld        a0, 0(sp)

addi    sp, sp, 24
ret

