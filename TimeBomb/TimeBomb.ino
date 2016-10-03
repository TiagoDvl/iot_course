int MAX_BOMB_TIME = 500;
int MIN_BOMB_TIME = 0;
int FACTOR = 20;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  int currentTime = MAX_BOMB_TIME;
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(currentTime);                // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(currentTime);

  if (currentTime <= MAX_BOMB_TIME) {
    currentTime = currentTime + FACTOR;
  } else if (currentTime >= MIN_BOMB_TIME) {
    currentTime = currentTime - FACTOR;
  }
}
