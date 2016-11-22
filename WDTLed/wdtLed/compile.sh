avr-gcc -mmcu=atmega328 -Os wdtLed.c uart.o -o prog.x
avr-objcopy -j .text -j .data -O ihex prog.x prog.hex
avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -D -Uflash:w:prog.hex:i
