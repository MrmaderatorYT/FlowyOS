#ifndef UART_H
#define UART_H

#define UART0_BASE 0x09000000
#define UART0_DR (UART0_BASE + 0x00)
#define UART0_FR (UART0_BASE + 0x18)

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[31m"
#define BLUE "\x1B[34m"
#define VIOLET "\x1B[35m"
#define LIGHT_BLUE "\x1B[36m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"

void uart_putc(char c);
char uart_getc();
void uart_puts(const char *str);

#endif