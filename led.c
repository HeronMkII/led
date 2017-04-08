#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()

int main(void)
{
    DDRC = 0x00;
    DDRC |= 0x01; //PC0

    while(1) {
        PORTC = 0x01;
        _delay_ms(500);
        PORTC = 0x00;
        _delay_ms(500);
    }
}
