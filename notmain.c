void notmain ( void )
{
    const char *msg = "Hello, ARM world!\n";
    char *uart = (char *)0x101f1000;  // UART base address for ARM

    while (*msg) {
        *uart = *msg++;
    }
}

