#include "file_system.h"
#include "uart.h"
#include <stdint.h>
#include "editor.h"
#include "strings.h"
#include "./programs/calc.h"
#include "./programs/log.h"

FileSystem fs;

int debug_mode = 0; // Ініціалізація змінної режиму дебагу
int current_directory_index = 0; // Індекс поточного каталогу
char current_directory[100] = "user";

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
	create_directory("user");
	current_directory_index = 0;
}

int create_directory(const char *name){
	if(fs.file_count >= MAX_FILES){
		uart_puts(RED "FileSystem is full, cannot create directory.\r\n" RESET);
		return -1;
	}
	for (int i = 0; i < fs.file_count; i++){
		if(my_strcmp(fs.files[i].name, name) == 0){
			uart_puts(YELLOW "Directory already exist.\r\n" RESET);
			return -1;
		}
	}
	if (name[0] == '.'){
		uart_puts(RED "Cannot create hidden directories.\r\n" RESET);
		return -2; // Заборона створення прихованих файлів
	}
	// Створюємо нову директорію: задаємо її ім'я, прапорець та вказуємо, що її батько – поточний каталог
	my_strcpy(fs.files[fs.file_count].name, name);
	fs.files[fs.file_count].is_directory = 1;
	fs.files[fs.file_count].parent = current_directory_index;
	fs.file_count++;
	uart_puts(GREEN "Directory created. \r\n" RESET);
	return 0;
}
int create_file(const char *name){
	if(fs.file_count >= MAX_FILES){
		uart_puts(RED "FileSystem is full, cannot crete file. \r\n" RESET);
		return -1;
	}
	for (int i = 0; i < fs.file_count; i++){
        if(!fs.files[i].is_directory && 
           my_strcmp(fs.files[i].name, name) == 0 &&
           fs.files[i].parent == current_directory_index){
            uart_puts(YELLOW "File already exists.\r\n" RESET);
            return -1;
        }
    }
	if (name[0] == '.'){
		uart_puts(RED "Cannot create hidden file.\r\n" RESET);
		return -2; // Заборона створення прихованих файлів
	}
    my_strcpy(fs.files[fs.file_count].name, name);
    fs.files[fs.file_count].is_directory = 0;
    fs.files[fs.file_count].content[0] = '\0';
    fs.files[fs.file_count].parent = current_directory_index;
    fs.file_count++;
    uart_puts(GREEN "File created.\r\n" RESET);
    return 0;
}
// Видалення файлу у поточному каталозі
int delete_file(const char *name) {
    int found = 0;
    for (int i = 0; i < fs.file_count; i++) {
        if(!fs.files[i].is_directory && 
           my_strcmp(fs.files[i].name, name) == 0 &&
           fs.files[i].parent == current_directory_index) {
            // Зсуваємо файли вліво, щоб видалити знайдений елемент
            for (int j = i; j < fs.file_count - 1; j++) {
                fs.files[j] = fs.files[j + 1];
            }
            fs.file_count--;
            uart_puts(GREEN "File deleted.\r\n" RESET);
            return 0;
        }
    }
    uart_puts(YELLOW "File not found.\r\n" RESET);
    return -1;
}


// Перелік директорій у поточному каталозі
void list_directory() {
    uart_puts("Current directory: ");
    // Виводимо ім'я поточного каталогу
    uart_puts(fs.files[current_directory_index].name);
    uart_puts("\r\nDirectories:\r\n");
    int found = 0;
    for (int i = 0; i < fs.file_count; i++) {
        if(fs.files[i].is_directory && fs.files[i].parent == current_directory_index) {
            if (fs.files[i].name[0] == '.' && !debug_mode) {
                continue;
            }
            uart_puts(fs.files[i].name);
            uart_putc('\r');
            uart_putc('\n');
            found = 1;
        }
    }
    if (!found) {
        uart_puts("No directories.\r\n");
    }
}



// Перелік файлів у поточному каталозі
void list_files(){
    uart_puts("Files:\r\n");
    int found = 0;
    for (int i = 0; i < fs.file_count; i++){
        if(!fs.files[i].is_directory && fs.files[i].parent == current_directory_index){
            uart_puts(fs.files[i].name);
            uart_putc('\r');
            uart_putc('\n');
            found = 1;
        }
    }
    if(!found){
        uart_puts("No files.\r\n");
    }
}

void change_directory(const char *name) {
    if (my_strcmp(name, "..") == 0) {
        if (current_directory_index == 0) { // Already at root
            uart_puts(YELLOW "Already in root directory.\r\n" RESET);
            return;
        }
        current_directory_index = fs.files[current_directory_index].parent; // Move to parent
        char *last_slash = my_strrchr(current_directory, '/');
        if (last_slash) *last_slash = '\0';
        uart_puts(GREEN "Moved to parent directory.\r\n" RESET);
        return;
    }

    for (int i = 0; i < fs.file_count; i++) {
        if (fs.files[i].is_directory && my_strcmp(fs.files[i].name, name) == 0 &&
            fs.files[i].parent == current_directory_index) {
            current_directory_index = i;  // Update current directory index
            my_strcat(current_directory, "/");
            my_strcat(current_directory, name);
            uart_puts(GREEN "Moved to directory: ");
            uart_puts(current_directory);
            uart_puts("\r\n" RESET);
            return;
        }
    }
    uart_puts(RED "Directory not found.\r\n" RESET);
}


// Пошук файлу у поточному каталозі
File *find_file(const char *name){
    for (int i = 0; i < fs.file_count; i++){
        if(!fs.files[i].is_directory && 
           my_strcmp(fs.files[i].name, name) == 0 &&
           fs.files[i].parent == current_directory_index) {
            if (fs.files[i].name[0] == '.' && !debug_mode) {
                return NULL; // Приховуємо файл, якщо дебаг вимкнений
            }
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
	}else if (my_strncmp(cmd, "cd ", 3) == 0) {
		change_directory(cmd + 3);
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
	}else if(my_strncmp(cmd, "mkd ", 4) == 0){
		create_directory(cmd + 4);
	}else if (my_strcmp(cmd, "ls") == 0){
		list_directory();
	}else if(my_strcmp(cmd, "ls -f") == 0){
		list_files();
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
		uart_puts(YELLOW "Unknown command. \r\n" RESET);
	}
}
void print_command(const char *cmd, int debug_mode){
	if(debug_mode){
		uart_puts(LIGHT_BLUE "\r\nReceived command: " RESET);
		uart_puts(cmd);
		uart_putc('\r');
		uart_putc('\n');
	}
}
