#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>    // Needed to use interrupts    
#include "uart.h"

volatile char* pb = (char*) 0x25;
volatile char* ddr = (char*) 0x24;
volatile char* pin = (char*) 0x23;

bool isGameStarted;
bool isLedUp;

void setupPreScaler() {
    int r = rand() % 4;
    printf("Random Number: %d", r);
    printf("\n");
    
    
    TCCR1B |= (1 << WGM12) | (1<<CS02) | (1<<CS00); // Set timer0 with /1024 prescaler
    //     TCCR1B |= (1 << WGM12) | (1<<CS02); // Set timer0 with /256 prescaler
    //     TCCR1B |= (1 << WGM12) | (1<<CS00); // Set timer0 with /64 prescaler
    
    OCR1A = 16 * 1000 * r; // Since prescaller set poke to be called each 1ms, multiply by 1000 gives 1 second.
}

void turnLED(bool ledState) {
    if (ledState) {
        *pb |= (1<<5);  // Ligando o LED
    } else {
        *pb &= ~(1<<5); // Desligando o LED
    }
}

void turnTimeInterrupt(bool interruptState) {
    if (interruptState) {
        TIMSK1 |= (1 << OCIE1A);
    } else {
        TIMSK1 &= ~(1 << OCIE1A);
    }
    
}

bool isLEDOn() {
    return *pin & (1<<5);
}

int main(void) {
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
    
    turnTimeInterrupt(true);
    
    
    *pb &= ~(1<<5); // Desligando o LED?
    
    
    sei();                     // turn on interrupts
    
    while (1) {
        
    }
}

ISR (PCINT0_vect) {
    if( (PINB & (1 << PINB0)) == 1 ) {
        if (!isGameStarted) {
            isGameStarted = true;
            printf("Game Started! Good Luck. ;)");
            printf("\n");
            setupPreScaler();
            return;
        }
        
        if (isGameStarted) {
            if (isLEDOn() && ((int) TCNT1 > 0)) {
                turnLED(false);
                printf("Pressed in: %d time", (int) TCNT1);
                printf("\n");
            } else {
                turnTimeInterrupt(true);
            }
        } 
    }
}

ISR(TIMER1_COMPA_vect) {   
    turnLED(true);
    TCNT1=0x00; 
    turnTimeInterrupt(false);
}

