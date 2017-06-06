ldr r0,=0x20200004

mov r1,#0x00040000
str r1,[r0]

mov r2,#0x00010000

ldr r3,=0x2020001C
ldr r4,=0x20200028

while:

str r2,[r4]

mov r5,#0x3F0000
delay:
sub r5,r5,#1
cmp r5,#0
bne delay

str r2,[r3]

mov r5,#0x3F0000
delay2:
sub r5,r5,#1
cmp r5,#0
bne delay2

b while
