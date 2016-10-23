#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>    // Needed to use interrupts    
#include "uart.h"

int main(void)
{
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;
    
    DDRB &= ~(1 << DDB0);         // Clear the PB0 pin
                                  // PB0 (PCINT0 pin) is now an input
    
    PORTB |= (1 << PORTB0);        // turn On the Pull-up
                                   // PB0 is now an input with pull-up enabled
    
    PCICR |= (1 << PCIE0);     // set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << PCINT0);   // set PCINT0 to trigger an interrupt on state change 
    
    sei();                     // turn on interrupts
    
    while(1)
    {
        /*main program loop here */
    }
}



ISR (PCINT0_vect)
{
    if( (PINB & (1 << PINB0)) == 1 )
    {
        printf("Low to High");
        printf("\n");
    }
    else
    {
        /* HIGH to LOW pin change */
        printf("High to Low");
        printf("\n");
    }
}