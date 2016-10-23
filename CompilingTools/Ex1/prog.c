char foo(void);
int main(void)
{
 volatile char* DDRB = (char*) 0x20 + 0x04;
 volatile char* PORTB = (char*) 0x20 + 0x05;
 *DDRB = 0xFF;
 *PORTB = 0xFF;
 return 0;
}
