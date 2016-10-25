#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>    // Needed to use interrupts    
#include "uart.h"

volatile char* pb = (char*) 0x25;
volatile char* ddr = (char*) 0x24;
volatile char* pin = (char*) 0x23;

int MAX_INTERRUPT_TIMES = 32;   // This was a random number that i found out to be kind of 1 second.
bool isGameStarted;
bool isLedUp;

void setupPreScaler() {
    TCCR0B = (1<<CS02) | (1<<CS00); // Set timer0 with /1024 prescaler
    //     TCCR0B = (1<<CS02); // Set timer0 with /256 prescaler
    //     TCCR0B = (1<<CS01) | (1<<CS00); // Set timer0 with /64 prescaler
}

void turnLED(bool ledState) {
    if (ledState) {
        *pb |= (1<<5);  // Ligando o LED
    } else {
        *pb &= ~(1<<5); // Desligando o LED
    }
}

bool isLEDOn() {
    return *pin & (1<<0);
}

int main(void)
{
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;
    
    printf("Press Button to Start Game");
    printf("\n");
    
    *ddr |= (1<<5); // Preparando ele pra output
    DDRB &= ~(1 << DDB0);         // Clear the PB0 pin
                                // PB0 (PCINT0 pin) is now an input
    PORTB |= (1 << PORTB0);        // turn On the Pull-up
                                // PB0 is now an input with pull-up enabled
    
    PCICR |= (1 << PCIE0);     // set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << PCINT0);   // set PCINT0 to trigger an interrupt on state change 
    
    TIMSK0=(1<<TOIE0); // Enable the interrupt on overflow for Timer0
    
    
    *pb &= ~(1<<5); // Desligando o LED?
    
    
    sei();                     // turn on interrupts
    
    while(1)
    {
        
    }
}

ISR (PCINT0_vect)
{
    if( (PINB & (1 << PINB0)) == 1 )
    {
        if (!isGameStarted) {
        
            isGameStarted = true;
            printf("Game Started! Good Luck. ;)");
            setupPreScaler();
            return;
        }
        
        if (isGameStarted && isLEDOn()) {
            turnLED(false);
            printf("Time Spent: %d", (int) TCNT0);
            // Mede o Tempo
        }
    }
}

ISR(TIMER0_OVF_vect)
{
    if (MAX_INTERRUPT_TIMES == 0) {
        turnLED(true);
        TCNT0=0x00; // Set timer0 counter initial value to 0
    } else {
        MAX_INTERRUPT_TIMES --;
    }
}

