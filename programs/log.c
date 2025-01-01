// log.c
#include "../uart.h"
#include "../strings.h"

// Виведення історії команд
void show_command_history(char command_history[][100], int command_history_count) {
    uart_puts("Command history:\r\n");
    for (int i = 0; i < command_history_count; i++) {
        uart_puts(command_history[i]);
        uart_puts("\r\n");
    }
}
