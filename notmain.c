#define UART0_BASE 0x09000000
#define UART0_DR (UART0_BASE + 0x00)
#define UART0_FR (UART0_BASE + 0x18)

#define MAX_FILES 16
#define MAX_NAME_LEGTH 32

typedef unsigned long size_t;
typedef unsigned int uint32_t;

typedef struct{
	char name [MAX_NAME_LEGTH];
	int is_directory;
} File;
typedef struct{
	File files[MAX_FILES];
	int file_count;
} FileSystem;

FileSystem fs;

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

int my_strcmp(const char *s1, const char *s2){
	while (*s1 && (*s1 == *s2)){
		s1++;
		s2++;
	}
	return (unsigned char)*s1 - (unsigned char)*s2;
}
int my_strncmp(const char *s1, const char *s2, size_t n){
	while (n > 0){
		if(*s1 != *s2){
			return (unsigned char)*s1 - (unsigned char)*s2;
		}
		if (*s1 == '\0'){
			return 0;
		}
		s1++;
		s2++;
		n--;
	}
	return 0;
}
void my_strcpy(char *dest, const char *src){
	while(*src){
		*dest++ = *src++;
	}
	*dest = '\0';
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
	
			
void process_command(const char *cmd, int *debug_mode){
	uart_puts("\r\n");
	
	if(my_strcmp(cmd, "help") == 0){
		uart_puts("Avaible commands: help, echo <message>, debug on, debug off, mkdir <name>, ls. \r\n");
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
	}else if(my_strncmp(cmd, "mkdir ", 6) == 0){
		create_directory(cmd + 6);
	}else if (my_strcmp(cmd, "ls") == 0){
		list_directory();
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
