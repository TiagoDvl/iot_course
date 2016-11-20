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
volatile bool button_pressed = 0;

long milliseconds = 0;
long beforeReaction = 0;
bool isWrongTime = false;

void setupOCR() {
    OCR1A = 16; // Gather 16 interruptions to actually send one.
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

long getReactionInMs() {
    return (milliseconds - beforeReaction);
}

bool isLEDOn() {
    return *pin & (1<<5);
}

void randomizeLED() {
    turnLED(false);
    
    srand(time(NULL));
    int r = rand() % 4;
    
    if (r == 0) {
        r = 1;
    }
    
    printf("Random Number: %d\n", r);
    long wantedTime = milliseconds + (r * 1000);
    while (milliseconds != wantedTime) {
        printf("wantedTime: %ld | milliseconds: %ld\n", wantedTime, milliseconds);
        if (isWrongTime) {
            return;
        }
    }
    
    beforeReaction = milliseconds;
    turnLED(true);
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
    
    TCCR1B |= (1 << WGM12) | (1<<CS02) | (1<<CS00); // Set timer0 with /1024 prescaler
    //     TCCR1B |= (1 << WGM12) | (1<<CS02); // Set timer0 with /256 prescaler
    //     TCCR1B |= (1 << WGM12) | (1<<CS00); // Set timer0 with /64 prescaler
    
    //???
    EICRA &= ~(1 << ISC00); // set INT0 to trigger on
    EICRA |= (1 << ISC01); // FALLING edge (ISC0 = 01)
    EIMSK |= (1 << INT0); // Allow INT0 interrupts 
    
    PCICR |= (1 << PCIE0);     // set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << PCINT0);   // set PCINT0 to trigger an interrupt on state change 
    
    turnTimeInterrupt(true);
    setupOCR();
    turnLED(false);
    
    sei();                     // turn on interrupts
    
    while (1) {
        
    }
}

ISR (INT0_vect) {
    if (bit_is_clear(PIND, PD2) && !button_pressed) {
        button_pressed = 1;
        if (!isGameStarted) {
            isGameStarted = true;
            printf("Game Started! Good Luck. ;)");
            printf("\n");
            randomizeLED();
            return;
        }
        
        
        if (isGameStarted) {
            if (isLEDOn()) {
                turnLED(false);
                printf("Reaction time = %ld ms", getReactionInMs());
                printf("\n");
                setupOCR();
            } else {
                printf("Too Soon! Game Over!");
                printf("\n");
                turnLED(false);
                isWrongTime = true;
                isGameStarted = false;  
            }
        }
    } else if (bit_is_set(PIND, PD2) && button_pressed) {
        button_pressed = 0;
    }    
}

ISR(TIMER1_COMPA_vect) {   
    milliseconds ++;
}