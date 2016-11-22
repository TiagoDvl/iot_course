#define F_CPU 16000000UL

#define IDLE_MODE 0
#define POWER_DOWN_MODE 1
#define POWER_SAVE_MODE 2
#define STANDBY_MODE 3
#define EXT_STANDBY_MODE 4

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>    // Needed to use interrupts
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "uart.h"

volatile char* pb = (char*) 0x25;
volatile char* ddr = (char*) 0x24;

const int BOUNCE_THRESHOLD = 150;  // ms

long hard_button_pin2_press = 0;
long button_pin2_press = 0;
volatile long tot_overflow = 0;
volatile long beginingOfProcess = 0;
volatile long upTime = 0;
long momentOfAwake = 0;

long getMillis() {
    return (tot_overflow * 16.32) + (TCNT2 * 0.064);
}

void turnLED(bool ledState) {
  if (ledState) {
    *pb |= (1<<5);  // Ligando o LED
  } else {
    *pb &= ~(1<<5); // Desligando o LED
  }
}

void enterSleep() {
  set_sleep_mode(POWER_SAVE_MODE);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_cpu();
}

void watchdogSetup(void) {
  cli();
  wdt_reset();
  
  // Enter Watchdog Configuration mode:
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  /* Clear the reset flag. */
  //MCUSR &= ~(1<<WDRF);

  // Set Watchdog settings:
  WDTCSR = (1 << WDIE) | (0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (0 << WDP0);

  /* Enable the WD interrupt (note no reset). */
  //WDTCSR |= _BV(WDIE);
}

/*
   This method is responsible to configure all pin2 registers
   also initialize some variables to implement debouncing
*/
void button_pin2_setup(void) {
  // set button as input
  DDRD &= ~(1 << DDD2);

  // allow interrupts
  EIMSK = (1 << INT0);

  // request falling edge changes
  EICRA &= ~(1 << ISC00);
  EICRA |= (1 << ISC01);

  button_pin2_press = 0;
  hard_button_pin2_press = 0;
}

/*
   This method is responsible to create a timer interruption for
   each millisecond configured by prescaler. This will be used to count
   time for some application responsibilities.
*/
void timer2_init() {
  // set up timer with prescaler = 1024.
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);

  // initialize counter
  TCNT2 = 0;

  // enable overflow interrupt
  TIMSK2 |= (1 << TOIE2);
  // initialize overflow counter variable
  tot_overflow = 0;
}

int main(void) {
  *ddr |= (1<<5); // Preparando LED pra output
  //watchdogSetup();
  button_pin2_setup();
  timer2_init();
  uart_init();
  stdout = &uart_output;
  stdin  = &uart_input;

  printf("This is the Start\n");
  set_sleep_mode(POWER_SAVE_MODE);
  sei();

  while (1) {
    turnLED(false);
    long now = getMillis();
    upTime = upTime + (now - momentOfAwake);
    printf("Active Time: %ld\n", (upTime*100)/getMillis());
//     printf ("Full time: %ld\n", now);
    enterSleep();
  }
  
  return 0;
}

// Interruption for WatchDogs.
ISR(WDT_vect) {
  printf("WDT\n");
}

// Interruption for Button.
ISR(INT0_vect) {
  
  unsigned long now = getMillis();
  
  if (now - hard_button_pin2_press >= BOUNCE_THRESHOLD) {
    hard_button_pin2_press = now;
  } else {
      return;
  }
  
  beginingOfProcess = now;
  turnLED(true);
  printf("Time in milliseconds since boot: %ld\n ", beginingOfProcess);
}

// Interruption for Timer2.
ISR(TIMER2_OVF_vect) {
  // keep a track of number of overflows
  momentOfAwake = getMillis();
  tot_overflow ++;
}