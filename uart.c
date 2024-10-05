#include "uart.h"
#include <stdint.h>

void uart_putc(char c){
	volatile uint32_t *UARTFR = (uint32_t *)UART0_FR;
	volatile uint32_t *UARTDR = (uint32_t *)UART0_DR;
	
	while(*UARTFR & (1<<5)){
		
	}
	*UARTDR = c;
}
char uart_getc(){
	volatile uint32_t *UARTFR = (uint32_t *)UART0_FR;
	volatile uint32_t *UARTDR = (uint32_t *)UART0_DR;
	
	while(*UARTFR & (1<<4)){
			
	}
	return *UARTDR & 0xFF;
}
void uart_puts(const char *str){
	while (*str){
		uart_putc(*str++);
	}
}
