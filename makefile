CC = avr-gcc
CFLAGS = -g -mmcu=atmega32m1
PROG = stk500 # the Pololu acts like the STK500
MCU = m32m1
PORT = /dev/tty.usbmodem177

OBJS = ./build/led.o
ELFS = ./build/led.elf

led: $(OBJS)
	$(CC) $(CFLAGS) -o ./build/led.elf ./build/led.o
	avr-objcopy -j .text -j .data -O ihex ./build/led.elf ./build/led.hex

./build/led.o:
	$(CC) $(CFLAGS) -Os -c led.c
	@mv led.o ./build/led.o

.PHONY: clean upload

clean:
	rm ./build/*

upload: led
	avrdude -c $(PROG) -p $(MCU) -P $(PORT) -U flash:w:./build/led.hex
