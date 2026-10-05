#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

#include "adc.h"
#include "config.h"
#include "relay.h"
#include "soil_sensor.h"
#include "uart.h"

static void print_status(
    uint16_t moisture,
    bool pump_on,
    uint16_t cooldown_seconds)
{
    uart_write_string("ADC2 = ");
    uart_write_uint16(moisture);

    uart_write_string(" | pump = ");

    if (pump_on) {
        uart_write_string("ON");
    } else {
        uart_write_string("OFF");
    }

    uart_write_string(" | cooldown = ");
    uart_write_uint16(cooldown_seconds);

    uart_write_string("\r\n");
}

int main(void)
{
    uint8_t pump_on_seconds = 0;
    uint16_t cooldown_seconds = 0;

    uart_init();
    adc_init();
    relay_init();

    uart_write_string("\r\n");
    uart_write_string("AVR Irrigation System\r\n");
    uart_write_string("---------------------\r\n");

    while (1) {
        uint16_t moisture = soil_sensor_read();
        bool pump_on = relay_is_on();

        if (pump_on) {
            pump_on_seconds++;

            if (moisture <= SOIL_WET_THRESHOLD) {
                relay_off();

                pump_on_seconds = 0;
                cooldown_seconds = PUMP_COOLDOWN_SECONDS;

                uart_write_string(
                    "Pump OFF: wet soil threshold reached.\r\n");
            }
            else if (pump_on_seconds >= PUMP_MAX_ON_SECONDS) {
                relay_off();

                pump_on_seconds = 0;
                cooldown_seconds = PUMP_COOLDOWN_SECONDS;

                uart_write_string(
                    "Pump OFF: maximum runtime reached.\r\n");
            }
        }
        else {
            pump_on_seconds = 0;

            if (cooldown_seconds > 0) {
                cooldown_seconds--;
            }
            else if (moisture >= SOIL_DRY_THRESHOLD) {
                relay_on();

                uart_write_string(
                    "Pump ON: dry soil detected.\r\n");
            }
        }

        print_status(
            moisture,
            relay_is_on(),
            cooldown_seconds);

        _delay_ms(1000);
    }

    return 0;
}
