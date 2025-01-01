#include "file_system.h"
#include "uart.h"
#include <stdint.h>
#include "editor.h"
#include "strings.h"
#include "./programs/calc.h"
#include "./programs/log.h"

FileSystem fs;

void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    while (n--) {
        *d++ = *s++;
    }

    return dest;
}


void init_fs(){
	fs.file_count = 0;
}
int create_directory(const char *name){
	if(fs.file_count >= MAX_FILES){
		uart_puts("FileSystem is full, cannot create directory.\r\n");
		return -1;
	}
	for (int i = 0; i < fs.file_count; i++){
		if(my_strcmp(fs.files[i].name, name) == 0){
			uart_puts("Directory already exist.\r\n");
			return -1;
		}
	}
	my_strcpy(fs.files[fs.file_count].name, name);
	fs.files[fs.file_count].is_directory = 1;
	fs.file_count++;
	uart_puts("Directory created. \r\n");
	return 0;
}
int create_file(const char *name){
	if(fs.file_count >= MAX_FILES){
		uart_puts("FileSystem is full, cannot crete file. \r\n");
		return -1;
	}
	for (int i = 0; i < fs.file_count; i++){
		if(my_strcmp(fs.files[i].name, name) == 0){
			uart_puts("File already exist.\r\n");
			return -1;
		}
	}
	my_strcpy(fs.files[fs.file_count].name, name);
	fs.files[fs.file_count].is_directory = 0;
	fs.files[fs.file_count].content[0] = '\0';
	fs.file_count++;
	uart_puts("File created.\r\n");
	return 0;
}
int delete_file(const char *name) {
    if (fs.file_count == 0) {
        uart_puts("No files to delete.\r\n");
        return -1;
    }
    for (int i = 0; i < fs.file_count; i++) {
        if (!fs.files[i].is_directory && my_strcmp(fs.files[i].name, name) == 0) {
            for (int j = i; j < fs.file_count - 1; j++) {
                fs.files[j] = fs.files[j + 1];
            }
            fs.file_count--;
            uart_puts("File deleted.\r\n");
            return 0;
        }
    }

    uart_puts("File not found.\r\n");
    return -1;
}



void list_directory(){
	uart_puts("Directories:\r\n");
	if(fs.file_count == 0){
		uart_puts("No directories.\r\n");
	}else{
		for (int i = 0; i < fs.file_count; i++){
			if(fs.files[i].is_directory){
				uart_puts(fs.files[i].name);
				uart_putc('\r');
				uart_putc('\n');
			}
		}
	}
}

File *find_file(const char *name){
	for (int i = 0; i < fs.file_count; i++){
		if(!fs.files[i].is_directory && my_strcmp(fs.files[i].name, name) == 0){
			return &fs.files[i];
		}
	}
	return NULL;
}
void process_command(const char *cmd, int *debug_mode, char command_history[][100], int command_history_count) {
    uart_puts("\r\n");
    
    if(my_strcmp(cmd, "help") == 0){
        uart_puts("Avaible commands: help, echo <message>, debug on, debug off, mkdir <name>, ls, mkf <file> edit <file>. \r\n");
    }else if(my_strncmp(cmd, "echo ", 5) == 0){
        uart_puts(cmd + 5);
        uart_putc('\r');
        uart_putc('\n');
    }else if(my_strcmp(cmd, "debug on") == 0){
        *debug_mode = 1;
        uart_puts("Debug mode enabled. \r\n");
    }else if(my_strcmp(cmd, "debug off") == 0){
        *debug_mode = 0;
        uart_puts("Debug mode disable. \r\n");
    }else if (my_strcmp(cmd, "log") == 0) {
        show_command_history(command_history, command_history_count);
    }else if(my_strncmp(cmd, "mkdir ", 6) == 0){
		create_directory(cmd + 6);
	}else if(my_strncmp(cmd, "edit ", 5) == 0){
		File *file = find_file(cmd + 5);
		if (file){
			edit_file(file);
		}else{
			uart_puts("File not found.\n\r");
		}
	}else if(my_strncmp(cmd, "mkf ", 4) == 0){
		create_file(cmd + 4);
	}else if (my_strcmp(cmd, "ls") == 0){
		list_directory();
	}else if (my_strncmp(cmd, "rm -f ", 6) == 0){
		delete_file(cmd + 6);
	}else if(my_strncmp(cmd, "calc ", 5) == 0) {
		int result = eval(cmd + 5);
		char buffer[32];
		my_itoa(result, buffer);
		uart_puts("Result: ");
		uart_puts(buffer);
		uart_puts("\r\n");
	}else{
		uart_puts("Unknown command. \r\n");
	}
}
void print_command(const char *cmd, int debug_mode){
	if(debug_mode){
		uart_puts("\r\nReceived command: ");
		uart_puts(cmd);
		uart_putc('\r');
		uart_putc('\n');
	}
}
