// Basic time unit for a single dot on morse
int BASIC_TIME_UNIT = 150;

// Message provided
String msg = "HELLO IOT WORLD";

int UNIT_DOT = BASIC_TIME_UNIT;
int UNIT_DASH = BASIC_TIME_UNIT * 3;
int UNIT_WITHIN_LETTERS = BASIC_TIME_UNIT;
int UNITS_BETWEEN_LETTERS = BASIC_TIME_UNIT * 3;
int UNITS_BETWEEN_WORDS = BASIC_TIME_UNIT *7;

class Morse {
  // Got 100 just because I need a size to declare;
  public : int sequence[100]; 

  virtual void makeItShine(int size) {
    int i;
    for (i = 0; i < size; i = i + 1) {
      if ((i % 2) == 0) {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(sequence[i]);
        Serial.print("HIGH");
        Serial.print(i);
        Serial.println(" ");
      } else {
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(sequence[i]);
        Serial.print("LOW");
        Serial.print(i);
        Serial.println(" ");
      }
    }
  }

  virtual void  getA(){
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DASH;

    makeItShine(3);
  }

  virtual void getB() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DOT;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DOT;

    makeItShine(7);
  }

  virtual void getC() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DASH;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DOT;

    makeItShine(7);
  }

  virtual void getD() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DOT;

    makeItShine(5);
  }

  virtual void getE() {
    sequence[0] = UNIT_DOT;

    makeItShine(1);
  }

  virtual void getF() {
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DASH;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DOT;

    makeItShine(7);
  }

  virtual void getG() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DASH;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DOT;

    makeItShine(5);
  }

  virtual void getH() {
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DOT;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DOT;

    makeItShine(7);
  }

  virtual void getI() {
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;

    makeItShine(3);
  }

  virtual void getJ() {
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DASH;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DASH;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DASH;

    makeItShine(7);
  }

  virtual void getK() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DASH;

    makeItShine(5);
  }

  virtual void getL() {
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DASH;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DOT;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DOT;
    
    makeItShine(7);
  }

  virtual void getM() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DASH;
    
    makeItShine(3);
  }

  virtual void getN() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    

    makeItShine(3);
  }

  virtual void getO() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DASH;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DASH;

    makeItShine(5);
  }

  virtual void getP() {
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DASH;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DASH;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DOT;

    makeItShine(7);
  }
  
  virtual void getQ() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DASH;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DOT;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DASH;
    
    makeItShine(7);
  }

  virtual void getR() {
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DASH;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DOT;
    
    makeItShine(5);
  }

  virtual void getS() {
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DOT;
    
    makeItShine(5);
  }

  virtual void getT() {
    sequence[0] = UNIT_DASH;
    
    makeItShine(1);
  }

  virtual void getU() {
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DASH;
    
    makeItShine(5);
  }

  virtual void getV() {
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DOT;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DASH;
    
    makeItShine(7);
  }

  virtual void getW() {
    sequence[0] = UNIT_DOT;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DASH;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DASH;
    
    makeItShine(5);
  }

  virtual void getX() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DOT;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DASH;
    
    makeItShine(7);
  }

  virtual void getY() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DOT;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DASH;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DASH;
    
    makeItShine(7);
  }

  virtual void getZ() {
    sequence[0] = UNIT_DASH;
    sequence[1] = UNIT_WITHIN_LETTERS;
    sequence[2] = UNIT_DASH;
    sequence[3] = UNIT_WITHIN_LETTERS;
    sequence[4] = UNIT_DOT;
    sequence[5] = UNIT_WITHIN_LETTERS;
    sequence[6] = UNIT_DOT;    

    makeItShine(7);
  }

  virtual void getSpaceBetweenWords() {
    sequence[0] = UNITS_BETWEEN_WORDS;

    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(sequence[0]); 
  }

  virtual void getSpaceBetweenLetters() {
    sequence [0] = UNITS_BETWEEN_LETTERS;

    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(sequence[0]);
  }
  
};

Morse *morse;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  morse = new Morse();
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  int i;

  for (i = 0; i < msg.length(); i = i + 1){
    switch (msg[i]) {
      case 'A': morse->getA();
        break;
      case 'B': morse->getB();
        break;
      case 'C': morse->getC();
        break;
      case 'D': morse->getD();
        break;
      case 'E': morse->getE();
        break;
      case 'F': morse->getF();
        break;
      case 'G': morse->getG();
        break;
      case 'H': morse->getH();
        break;
      case 'I': morse->getI();
        break;
      case 'J': morse->getJ();
        break;
      case 'K': morse->getK();
        break;
      case 'L': morse->getL();
        break;
      case 'M': morse->getM();
        break;
      case 'N': morse->getN();
        break;
      case 'O': morse->getO();
        break;
      case 'P': morse->getP();
        break;
      case 'Q': morse->getQ();
        break;
      case 'R': morse->getR();
        break;
      case 'S': morse->getS();
        break;
      case 'T': morse->getT();
        break;
      case 'U': morse->getU();
        break;
      case 'V': morse->getV();
        break;
      case 'W': morse->getW();
        break;
      case 'X': morse->getX();
        break;
      case 'Y': morse->getY();
        break;
      case 'Z': morse->getZ();
        break;
      case ' ': morse->getSpaceBetweenWords();
      default:
        Serial.println("Error");
        Serial.print(msg[i]);
    }
    morse->getSpaceBetweenLetters();
  }
}
