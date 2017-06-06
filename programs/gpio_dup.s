--Accesses the GPIO pin from 10 to 19
ldr r0,=0x20200004

--Set GPIO 16 as an output pin
mov r1,#0x00040000
str r1,[r0]

--Clear pin 16
mov r2,#0x00010000

--pin off
ldr r3,=0x20200028

--pin on
ldr r4,=0x2020001C

while:

--turn pin on
str r2,[r4]

--break
mov r5,#0x3F0000
delay:
sub r5,r5,#1
cmp r5,#0xFF
bne delay

--turn pin off
str r2,[r3]

--break again
mov r5,#0x3F0000
delay:
sub r5,r5,#1
cmp r5,#0xFF
bne delay

b while
