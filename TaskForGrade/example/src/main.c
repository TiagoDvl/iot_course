#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#define DataPort PORTC // Using PortC as our Dataport

volatile char* pb = (char*) 0x25;
volatile char* ddr = (char*) 0x24; // points ddrB variable to the DDRB register address 
volatile char* pin = (char*) 0x23; // You should tell to compiler that the value of the PINB may change at any time.
bool read_value;

ISR (INT0_vect) {
    printf("Interruption");
}

void buttonsSetup() {
    
    *ddr |= (1<<5); // Preparando ele pra output
    *ddr &= ~(1<<0);  // Preparando ele pra input
    
    printf("Setup Button Complete");
}

int main (void)
{
    // Initialize UART
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;
    
    buttonsSetup();
    
    // Printf works!
    //  printf("Printf works!!!\n");
    //  printf("You can even print integer GOD PLEASE HELP ME (%d)!!!\n", (int) 12345);
    DataPort = 0x01;	// Initialize Dataport to 1
    GICR = 1<<INT0;					// Enable INT0
    MCUCR = 1<<ISC01 | 1<<ISC00;	// Trigger INT0 on rising edge
    sei();
    
    while(1) { 
        /*
         *        read_value = *pin & (1<<0);
         *        if (read_value) {
         *pb |= (1<<5);
    } else {
        *pb &= ~(1<<5);
    }
    */
        if(DataPort >= 0x80)
            DataPort = 1;
        else
            DataPort = DataPort << 1;	// Shift to the left
            
    }
}


