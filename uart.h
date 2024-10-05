#ifndef UART_H
#define UART_H

#define UART0_BASE 0x09000000
#define UART0_DR (UART0_BASE + 0x00)
#define UART0_FR (UART0_BASE + 0x18)

void uart_putc(char c);
char uart_getc();
void uart_puts(const char *str);

#endif