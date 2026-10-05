#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

static void uart_init(void)
{
    /*
     * 9600 baud @ 16 MHz
     *
     * UBRR = F_CPU / (16 * baud) - 1
     *      ≈ 103
     */
    UBRR0H = 0;
    UBRR0L = 103;

    /* Enable transmitter. */
    UCSR0B = (1 << TXEN0);

    /* 8 data bits, 1 stop bit, no parity. */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

static void uart_write_char(char c)
{
    while (!(UCSR0A & (1 << UDRE0))) {
        /* Wait until transmit buffer is empty. */
    }

    UDR0 = c;
}

static void uart_write_string(const char *text)
{
    while (*text != '\0') {
        uart_write_char(*text);
        text++;
    }
}

static void uart_write_uint16(uint16_t value)
{
    char buffer[5];
    uint8_t index = 0;

    if (value == 0) {
        uart_write_char('0');
        return;
    }

    while (value > 0) {
        buffer[index++] = '0' + (value % 10);
        value /= 10;
    }

    while (index > 0) {
        uart_write_char(buffer[--index]);
    }
}

static void adc_init(void)
{
    /*
     * AVcc as voltage reference.
     * ADC2 selected initially.
     */
    ADMUX = (1 << REFS0) | (1 << MUX1);

    /*
     * Enable ADC.
     *
     * Prescaler = 128:
     * 16 MHz / 128 = 125 kHz ADC clock.
     */
    ADCSRA =
        (1 << ADEN) |
        (1 << ADPS2) |
        (1 << ADPS1) |
        (1 << ADPS0);
}

static uint16_t adc_read(void)
{
    /* Start conversion. */
    ADCSRA |= (1 << ADSC);

    /* Wait until conversion completes. */
    while (ADCSRA & (1 << ADSC)) {
    }

    return ADC;
}

int main(void)
{
    uart_init();
    adc_init();

    while (1) {
        uint16_t moisture = adc_read();

        uart_write_string("ADC2 = ");
        uart_write_uint16(moisture);
        uart_write_string("\r\n");

        _delay_ms(1000);
    }

    return 0;
}
