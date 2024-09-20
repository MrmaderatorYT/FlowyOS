.global _start
_start:
    ldr x0, =0x20000
	mov sp, x0
	bl notmain
hang:
    b hang

.global PUT32
PUT32:
    str w1,[x0]
    ret
	
