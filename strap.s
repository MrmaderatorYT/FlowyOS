.global _main
_main:
    ldr x30, =stack_top	// setup stack
    mov sp, x30
    bl notmain
    b .
	