#include <avr/io.h>
#include <stdint.h>

#include "adc.h"

void adc_init(void)
{
    /*
     * AVcc as voltage reference.
     */
    ADMUX = (1 << REFS0);

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

    /*
     * Disable the digital input buffer on ADC2.
     * We only use this pin as an analog input.
     */
    DIDR0 |= (1 << ADC2D);
}

uint16_t adc_read(uint8_t channel)
{
    /*
     * Preserve the voltage reference bits and select
     * ADC channel 0...7.
     */
    ADMUX = (ADMUX & 0xF0U) | (channel & 0x0FU);

    /* Start conversion. */
    ADCSRA |= (1 << ADSC);

    /* Wait for conversion to complete. */
    while (ADCSRA & (1 << ADSC)) {
    }

    return ADC;
}
