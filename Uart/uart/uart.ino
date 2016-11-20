#include <avr/io.h>
#include <avr/interrupt.h>
#define USART_BAUDRATE 9600 // Defines the baud rate
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1) // Calculate the prescale
int main (void) {
 UCSR0B |= (1<<RXEN0) | (1<<TXEN0); // Enable transmitter and receiver circuitry
 UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01); // Use 8-bit character sizes
 UBRR0H = (BAUD_PRESCALE >> 8); // Set the Baud Rate Register High
 UBRR0L = BAUD_PRESCALE; // Set the Baud Rate Register Low
 UCSR0B |= (1<<RXEN0)|(1<<RXCIE0); // Enable reception and RC complete interrupt
 sei(); // Enable the Global Interrupt Enable flag
 for (;;) {} // Loop forever
}
ISR(USART_RX_vect) { // Interruption function
 char recieved_byte;
 recieved_byte = UDR0; // Grab the byte from the serial port
 while((UCSR0A & (1<<UDRE0)) == 0 ){} // Wait until the port is ready to be written to
 UDR0 = 1; // Write the byte to the serial port
 while((UCSR0A & (1<<UDRE0)) == 0 ){} // Wait until the port is ready to be written to
 UDR0 = recieved_byte; // Write the byte to the serial port
}
