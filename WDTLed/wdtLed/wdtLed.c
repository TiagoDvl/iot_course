#define F_CPU 16000000UL 
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

volatile unsigned long millis;
const int BOUNCE_THRESHOLD = 150;  // ms

long hard_button_pin2_press;
long button_pin2_press;

void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();

  /* Now enter sleep mode. */
  sleep_mode();

  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */

  /* Re-enable the peripherals. */
  power_all_enable();
}

/*
void setSleepMode(char mode) {
  switch (mode) {
    case "IDLE_MODE":
      SMCR &= ~(1 << SM0);
      SMCR &= ~(1 << SM1);
      SMCR &= ~(1 << SM2);
      break;
    case "POWER_DOWN_MODE":
      SMCR &= ~(1 << SM0);
      SMCR |= (1 << SM1);
      break;
    case "POWER_SAVE_MODE":
      SMCR |= (1 << SM1) | (1 << SM0);
      break;
    case "STANDBY_MODE":
      SMCR &= ~(1 << SM0);
      SMCR |= (1 << SM2) | (1 << SM1);
      break;
    case "EXT_STANDBY_MODE":
      SMCR |= (1 << SM2) | (1 << SM1) | (1 << SM0);
      break;
  }
}
*/

void watchdogSetup(void) {
  cli();
  wdt_reset();
  /*
    WDTCSR configuration:
    WDIE = 1: Interrupt Enable
    WDE = 1 :Reset Enable
    See table for time-out variations:
    WDP3 = 0 :For 1000ms Time-out
    WDP2 = 1 :For 1000ms Time-out
    WDP1 = 1 :For 1000ms Time-out
    WDP0 = 0 :For 1000ms Time-out
  */
  // Enter Watchdog Configuration mode:
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  /* Clear the reset flag. */
  //MCUSR &= ~(1<<WDRF);

  // Set Watchdog settings:
  WDTCSR = (1 << WDIE) | (0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (0 << WDP0);

  /* Enable the WD interrupt (note no reset). */
  //WDTCSR |= _BV(WDIE);

  sei();
}

/* 
 * This method is responsible to configure all pin2 registers
 * also initialize some variables to implement debouncing
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
 * This method is responsible to create a timer interruption for
 * each millisecond configured by prescaler. This will be used to count
 * time for some application responsibilities.
 */
void timer0_setup() {
    // set mode to "interval"
    TCCR0A |= (1 << WGM01);
    // enable ISR(COMPA)
    TIMSK0 |= (1 << OCIE0A);
    // set initial value
    TCNT0 = 0;
    // set interval count
    OCR0A = 250;
    // set prescaler to /64
    TCCR0B |= (1 << CS01) | (1 << CS00);

    millis = 0;
}

int main(void) {
  watchdogSetup();
  button_pin2_setup();
  timer0_setup();
  uart_init();
  stdout = &uart_output;
  stdin  = &uart_input;

  printf("Hajimeru3\n");

  while (1) {
    _delay_ms(100);
    enterSleep();
  }
}

// Interruption for WatchDogs.
ISR(WDT_vect) {
  printf("WDT\n");
}

// Interruption for Button.
ISR(INT0_vect) {
    //unsigned long now = timer0_millis();
    unsigned long now = 0;
    if (now - hard_button_pin2_press >= BOUNCE_THRESHOLD) {
        button_pin2_press = now;
    }

    hard_button_pin2_press = now;
    printf("PushButton with time: %d\n ", millis);
}

// Interruption for Timer.
ISR(TIMER0_COMPA_vect) { 
    millis++;
    if (millis % 1000 == 0) {
        printf ("%d", millis);
    }
}