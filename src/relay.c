#include <avr/io.h>
#include <stdbool.h>

#include "relay.h"

void relay_init(void)
{
    /*
     * Relay is active-low.
     *
     * Set output level HIGH before changing the pin
     * direction to avoid an unwanted activation pulse.
     */
    PORTD |= (1 << PORTD5);
    DDRD  |= (1 << DDD5);
}

void relay_on(void)
{
    PORTD &= ~(1 << PORTD5);
}

void relay_off(void)
{
    PORTD |= (1 << PORTD5);
}

bool relay_is_on(void)
{
    return (PORTD & (1 << PORTD5)) == 0;
}
