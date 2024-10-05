#include "editor.h"
#include "uart.h"
#include "strings.h"

void edit_file(File *file){
	char c;
	int index = 0;
	uart_puts("\r\nEntering edit mode. Press Ctrl + Q to save and exit.\r\n");
	
	if (file -> content[0] != '\0'){
		uart_puts(file->content);
		index = my_strlen(file->content);
	}
	while(1){
		c = uart_getc();
		
		if(c == 17){ //Ctrl + Q
			file->content[index] = '\0';
			uart_puts("\r\nFile saved and exited edit mode.\r\n");
			break;
		}else if (c == '\b' || c == 127){
			if(index > 0){
				index--;
				uart_puts("\b \b");
			}
		}else if (c == '\r'){
			if(index < MAX_FILE_SIZE -1){
				file-> content[index++]='\n';
				uart_putc('\r');
				uart_putc('\n');
			}
		}else{
			if(index < MAX_FILE_SIZE -1){
				file->content[index++] = c;
				uart_putc(c);
			}
		}
	}
}
		
	