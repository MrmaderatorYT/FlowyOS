.globl _start
_start:
    mov sp,#0x20000
    bl notmain
hang:
    b hang

.globl PUT32
PUT32:
    str r1,[r0]
    bx lr
	