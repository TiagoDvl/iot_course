export ARDUINO_PATH=/home/tiagodvl/Documents/arduino-1.6.12/
export PATH=${ARDUINO_PATH}/hardware/tools/avr/bin:${PATH}
avr-gcc -mmcu=atmega328 -Os prog.c -o prog.x
avr-objcopy -j .text -j .data -O ihex prog.x prog.hex
avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -D -Uflash:w:prog.hex:i

// Do Batata
avr-gcc -Os -mmcu=atmega328 main.o uart.o -o main.x
