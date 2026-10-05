#include <stdint.h>

#include "adc.h"
#include "config.h"
#include "soil_sensor.h"

#define SOIL_ADC_CHANNEL 2U

uint16_t soil_sensor_read(void)
{
    uint32_t sum = 0;

    for (uint8_t i = 0; i < SOIL_SAMPLE_COUNT; i++) {
        sum += adc_read(SOIL_ADC_CHANNEL);
    }

    return (uint16_t)(sum / SOIL_SAMPLE_COUNT);
}
