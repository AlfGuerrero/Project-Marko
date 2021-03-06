/* Name: Alfrancis Guerrero, Heewon Suh
   Date: 6/2/2016
   Notes: Arduino file run w/Processing and Bluetooth Module Device
*/

#include "pitches.h"
#include <NewPing.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

#define ECHO_PIN 11
#define TRIGGER_PIN 12
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int finalMelody = NOTE_C4;
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4
};



int mDataSent[2] = {0, 0};
int mPotPin = A0;
int mValue;
int mDistance;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  mValue    = 0;
  mDistance = 0;
}

void loop() {
  delay(50);
  mDistance = sonar.ping_cm();

  mValue = map(mDistance, 5000, 180 , 0, 255);
  mValue = constrain(mValue , 0, 255);
  
  int noteDuration = 1000 / mDistance;
  tone(8, finalMelody, noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  noTone(8);

  Serial.print(mDistance);
  Serial.println();

  delay(50);
  mySerial.listen();
  while (mySerial.available() >= 0 ) {
    mySerial.write((int)mValue);
    mySerial.write((int)50);
  }
}

