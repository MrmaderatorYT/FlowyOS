#include "uart.h"
#include <stdint.h>

void uart_putc(char c){
    volatile uint32_t *UARTFR = (uint32_t *)UART0_FR;
    volatile uint32_t *UARTDR = (uint32_t *)UART0_DR;
    
    // Wait until the UART is ready to transmit
    while(*UARTFR & (1<<5)){
        // Do nothing
    }
    *UARTDR = (uint32_t)c;  // Ensure the character is correctly cast
}

char uart_getc(){
    volatile uint32_t *UARTFR = (uint32_t *)UART0_FR;
    volatile uint32_t *UARTDR = (uint32_t *)UART0_DR;
    
    // Wait until the UART has received data
    while(*UARTFR & (1<<4)){
        // Do nothing
    }
    return (char)(*UARTDR & 0xFF);  // Mask to get the correct character
}

void uart_puts(const char *str){
    while (*str){
        uart_putc(*str++);
    }
}