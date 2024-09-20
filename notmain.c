#include <stdint.h>

#define UART0_BASE 0x09000000
#define UART0_DR (UART0_BASE + 0x00)
#define UART0_FR (UART0_BASE + 0x18)

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


void notmain(void){
	char c;
	uart_puts("UART test... \n");
	while(1){
		c = uart_getc();
		if(c == '\r'){
			uart_putc('\n');
		} else if (c == '\b' || c == 127){
			uart_puts("\b \b");
		} else{
			uart_putc(c);
		}
	}
}
