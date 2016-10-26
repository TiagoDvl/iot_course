#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>    // Needed to use interrupts  
#include <util/delay.h>
#include "uart.h"

volatile char* pb = (char*) 0x25;
volatile char* ddr = (char*) 0x24;
volatile char* pin = (char*) 0x23;

bool isGameStarted;
bool isLedUp;

void setupPreScaler() {
    int r = rand() % 4;
    
    // Gambs? :(
    if(r == 0) {
        r++;
    }
    
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

long getCyclesInMs(long cycles) {
    return (cycles*1000) / 15625;
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
    DDRD &= ~(1 << DDD2); // PD2 (PCINT0 pin) is now an input 
    PORTD |= (1 << PORTD2); // PD2 is now with pull-up enabled 
    
    //???
    EICRA &= ~(1 << ISC00); // set INT0 to trigger on
    EICRA |= (1 << ISC01); // FALLING edge (ISC0 = 01)
    EIMSK |= (1 << INT0); // Allow INT0 interrupts 
    
    PCICR |= (1 << PCIE0);     // set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << PCINT0);   // set PCINT0 to trigger an interrupt on state change 
    
    turnTimeInterrupt(true);
    turnLED(false);
    
    sei();                     // turn on interrupts
    
    while (1) {
        
    }
}

ISR (INT0_vect) {
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
            printf("Reaction time = %ld ms", getCyclesInMs((long)TCNT1));
            printf("\n");
            setupPreScaler();
            turnTimeInterrupt(true);
        } else {
            printf("Too Soon! Game Over!");
            printf("\n");
            turnLED(false);
            isGameStarted = false;
        }
    } 
}

ISR(TIMER1_COMPA_vect) {   
    turnLED(true);
    TCNT1=0x00; 
    turnTimeInterrupt(false);
}

