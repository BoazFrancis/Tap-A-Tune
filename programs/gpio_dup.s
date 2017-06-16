--Accesses the GPIO pin from 10 to 19
ldr r0,=0x20200004

--Set GPIO 16 as an output pin
mov r1,#1
lsl r1,#18
str r1,[r0]

--Clear pin 16
mov r2,#1
lsl r2,#16

--pin off
ldr r3,=0x2020001C


--pin on
ldr r4,=0x20200028

while:

--turn pin on
str r2,[r4]

--Delay by iteratively decrementing a large number by 1
--until it is equal to a smaller number
mov r5,#0x3F0000
off_delay:
sub r5,r5,#1
cmp r5,#0xFF
bne off_delay

--turn pin off
str r2,[r3]

--Delay by iteratively decrementing a large number by 1
--until it is equal to a smaller number
mov r5,#0x3F0000
on_delay:
sub r5,r5,#1
cmp r5,#0xFF
bne on_delay

b while
