# atmega test

This file contains a simple program to test whether a particular ATMega32 based
board is working properly.

## Instruction to build and run from scratch

First, install [homebrew](https://brew.sh/). Next, do

```
$ brew tap osx-cross/avr
$ brew install avr-libc
$ brew install avrdude --with-usb
```

This intalls the AVR GCC toolchain along with software to write binary files
to the ATMega's flash memory.

It may also be necessary to patch `avrdude.conf` to support the m32m1. This can
be found online.

To build the program, run

```
$ make
```

To upload the program to the MCU, run

```
$ make upload
```

## Finding the correct USB port

To see all connected USB devices do

```
$ ls /dev/tty.usb*
```

The USB device corresponding to the programmer is almost always the device
with the lowest id. To ease compilation, open the makefile and change the
value of `PORT` to this device's location.
