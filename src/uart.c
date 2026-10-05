#include <avr/io.h>
#include <stdint.h>

#include "config.h"
#include "uart.h"

#define UART_UBRR ((F_CPU / (16UL * UART_BAUD)) - 1UL)

void uart_init(void)
{
    UBRR0H = (uint8_t)(UART_UBRR >> 8);
    UBRR0L = (uint8_t)UART_UBRR;

    /* Enable transmitter. */
    UCSR0B = (1 << TXEN0);

    /* 8 data bits, 1 stop bit, no parity. */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_write_char(char c)
{
    while (!(UCSR0A & (1 << UDRE0))) {
    }

    UDR0 = c;
}

void uart_write_string(const char *text)
{
    while (*text != '\0') {
        uart_write_char(*text++);
    }
}

void uart_write_uint16(uint16_t value)
{
    char buffer[5];
    uint8_t index = 0;

    if (value == 0) {
        uart_write_char('0');
        return;
    }

    while (value > 0) {
        buffer[index++] = (char)('0' + (value % 10));
        value /= 10;
    }

    while (index > 0) {
        uart_write_char(buffer[--index]);
    }
}
