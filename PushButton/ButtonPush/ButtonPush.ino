volatile char* pb = (char*) 0x25;
volatile char* ddr = (char*) 0x24; // points ddrB variable to the DDRB register address 
volatile char* pin = (char*) 0x23; // You should tell to compiler that
                          // the value of the PINB may change at any time 

                          // Pra ler o estado PIN
                          // Pra escrever PORT

bool read_value;


void setup() {
  *ddr |= (1<<5); // Preparando ele pra output
  *ddr &= ~(1<<0);  // Preparando ele pra input
}

void loop() {
 read_value = *pin & (1<<0);
  if (read_value) {
    *pb |= (1<<5);
  } else {
    *pb &= ~(1<<5);
  }
}
