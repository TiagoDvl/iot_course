#include <SoftwareSerial.h> 

#define rxPin 8
#define txPin 9

SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin); 
char communcation;
char sendC;

void setup() {
  // put your setup code here, to run once:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(1200); 
  Serial.begin(1200);

}

void loop() {

  if (Serial.available() > 0) {
//    sendC = Serial.read();
    mySerial.println(Serial.readString());
  }


  if (mySerial.available() > 0){
//  communcation = mySerial.readString();     
  //Serial.print("Roseane mandou: ");
  Serial.println(mySerial.readString());  
  }
  
}
