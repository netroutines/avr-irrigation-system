#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    PORTD |= (1 << PORTD5);
    DDRD  |= (1 << DDD5);

    while (1) {
        PORTD &= ~(1 << PORTD5);
        _delay_ms(1000);

        PORTD |= (1 << PORTD5);
        _delay_ms(1000);
    }

    return 0;
}
