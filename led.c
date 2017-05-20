#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/cpufunc.h> // for _NOP()
#include <util/delay.h>  // for _delay_ms()

// SPI pins
// CLK/SCK - pin 28 - PB7
// MISO - pin 8 - PB0
// MOSI - pin - PB1
// old CS - pin 18 - PC5
// CS - PB2

/*
 * Before SPI is enabled, the power reduction register must have the SPI bit (the third bit)
 * set to 0.
 */

void set_cs_low() {
    PORTB &= ~(_BV(PB2));
}

void set_cs_high() {
    PORTB |= _BV(PB2);
}

void init_spi(void) {
    // PRR = _BV(2); // because PRRSPI is bit 2 (counting from 0)
    // set SCK and MOSI as output pins
    // set CS as an output pin
    DDRB |= _BV(PB7) | _BV(PB2) | _BV(PB1);
    //PORTB &= ~(_BV(PB7)); // drive CLK low
    //DDRC |= _BV(PC5);
    SPCR |= _BV(6) | _BV(4) | _BV(1);
    // enable SPI, set mode to master, set SCK freq to f_io/64
}

char send_spi(char cmd) {
    // depending on which device you're transmitting to, you're going to need
    // to configure the data mode to match the device's settings
    // thankfully, the thermometer we're using is compatible with the default
    // data mode (SPI mode 0).
    //
    SPDR = cmd;
    while (!(SPSR & _BV(7)));

    return SPDR;
}

void delay(int sec) {
    for (int i = 0; i < sec; i++) {
        for (int j = 0; j < 10; j++) {
            _delay_ms(100);
            // can't delay for more than 200ms without weird behaviour
        }
    }
}

void readout(char d) {
    for (int i = 0; i < 8; i++) {
        // ensure the LEDs are off
        PORTC &= ~(_BV(PC0));
        PORTB &= ~(_BV(PB6));

        if (d & _BV(i)) {
            // shine blue for 1
            PORTC |= _BV(PC0);
        } else {
            // shine red for 0
            PORTB |= _BV(PB6);
        }

        delay(10);
        // ensure the LEDs are off
        PORTC &= ~(_BV(PC0));
        PORTB &= ~(_BV(PB6));
        delay(10);
    }
}

int main(void)
{
    // initialize port C0 as an ouput pin, and drive it low
    // this is the blue LED
    DDRC |= _BV(PC0);
    // init port B6 as an output pin, drive it low
    // this is the red LED
    DDRB |= _BV(PB6);

    init_spi();
    set_cs_low();
    //send_spi(0x3D); // nop - returns status byte
    //send_spi(0x35); // enable TX
    set_cs_high();
    //delay(3); // wait for RESET

    //char a = send_spi(0x3D); // NOP cmd to get status byte
    //readout(a);
}
