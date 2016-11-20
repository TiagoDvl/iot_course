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
bool isWaitingTime;
long isSlow;

long milliseconds = 0;
long beforeReaction = 0;
bool isWrongTime = false;

int r;
long deboucerTime = 0;

void setupOCR() {
  OCR0A = 16; // Gather 16 interruptions to actually send one.
}

void turnLED(bool ledState) {
  if (ledState) {
    *pb |= (1<<5);  // Ligando o LED
  } else {
    *pb &= ~(1<<5); // Desligando o LED
  }
}

void getMillis() {
    return milliseconds;
}

void getMicro() {
    return getMilis() * 1000 + TCNT0 * 4;
}

void turnTimeInterrupt(bool interruptState) {
  if (interruptState) {
    TIMSK0 |= (1 << OCIE0A);
  } else {
    TIMSK0 &= ~(1 << OCIE0A);
  }
  
}

long getReactionInMs() {
  return (milliseconds - beforeReaction);
}

bool isLEDOn() {
  return *pin & (1<<5);
}

void randomizeLED() {
  isSlow = 0;
  turnLED(false);
  
  srand(milliseconds);
  r = (rand() % 3) + 1;
  
  printf("Random Number: %d\n", r);
  isWaitingTime = true;
  TCNT1 = 0;
  
  TIMSK1 |= (1 << OCIE1A);
  OCR1A = 16 * (r * 1000);
  
  beforeReaction = milliseconds;
}

int main(void) {
  uart_init();
  stdout = &uart_output;
  stdin  = &uart_input;
  
  printf("Press Button to Start Game\n");
  
  *ddr |= (1<<5); // Preparando ele pra output
  DDRD &= ~(1 << DDD2); // PD2 (PCINT0 pin) is now an input 
  PORTD |= (1 << PORTD2); // PD2 is now with pull-up enabled 
  
  TCCR0B |= (1 << WGM12) | (1<<CS02) | (1<<CS00); // Set timer1 with /1024 prescaler
  TCCR1B |= (1 << WGM12) | (1<<CS02) | (1<<CS00); // Set timer1 with /1024 prescaler  
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
  if (deboucerTime == 0) {
    
  } else {
    if ((milliseconds - deboucerTime) < 50) {
      return;
    }
  }
  
  deboucerTime = milliseconds;
  
  if (!isGameStarted) {
    isGameStarted = true;
    isSlow = 0;
    printf("Game Started! Good Luck. ;)\n");
    randomizeLED();
    return;
  }
  
  
  if (isGameStarted) {
    if (isLEDOn()) {
      turnLED(false);
      printf("Reaction time = %ld ms\n", getReactionInMs());
      printf("\n");
      randomizeLED();
    } else {
      printf("Too Soon! Game Over!\n");
      turnLED(false);
      isWrongTime = true;
      isGameStarted = false;  
    }
  }   
}

ISR(TIMER1_COMPA_vect) {
  if (isWaitingTime) {
    turnLED(true);
    isWaitingTime = false;
  }
}

ISR(TIMER0_COMPA_vect) {
  milliseconds ++;
  isSlow ++;
  if (isGameStarted && isSlow == 500) {
      printf("So Slow! Game Over!\n");
      turnLED(false);
      isWrongTime = true;
      isGameStarted = false;
  }
}