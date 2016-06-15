/* Name: Alfrancis Guerrero, Heewon Suh
   Date: 6/2/2016
   Notes: Arduino file run w/Processing and Bluetooth Module Device
*/
#include <NewPing.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


//int noteDuration;
//int finalMelody = NOTE_C4;
//int pauseBetweenNotes;

int mPiezo = 8;

int mDataSent[2] = {0, 0};
int mPotPin = A0;
int mValue;
int mDistance;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(mPiezo, OUTPUT);

  mValue    = 0;
  mDistance = 0;
}

void loop() {
  
  delay(50);
  mDistance = sonar.ping_cm();
  mValue = map(mDistance, 400, 0 , 255, 0);
  mValue = constrain(mValue , 0, 255);

  Serial.println(mValue);
  
  mySerial.listen();
  mySerial.write((int)mValue);
  mySerial.write((int)50);
  
  if (mDistance <= 50 && mDistance > 0)
  {
    analogWrite(mPiezo, 1023);
    delay(mValue / 2);
    analogWrite(mPiezo, 0);
  }
  //Serial.println(mValue);
  //while (mySerial.available() >= 0 ) {

  //  }
}

