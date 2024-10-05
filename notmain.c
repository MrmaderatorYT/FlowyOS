#include "uart.h"
#include "file_system.h"		

void notmain(void){
	char c;
	char command[100];
	int index = 0;
	int debug_mode = 0;//0 - debug off, 1 - on
	uart_puts("UART test... \n");
	init_fs();
	while(1){
		c = uart_getc();
		if(c == '\r'){
			command[index] = '\0';
			print_command(command, debug_mode);
			process_command(command, &debug_mode);
			index = 0;
		} else if (c == '\b' || c == 127){
			if(index > 0){
				index--;
				uart_puts("\b \b");
			}
		} else{
			if(index < sizeof(command)-1){
				command[index++] = c;
				uart_putc(c);
			}
		}
	}
}