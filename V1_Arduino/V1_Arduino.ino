/* Name: Alfrancis Guerrero
   Date: 6/2/2016
   Notes: Arduino file run w/Processing and Bluetooth Module Device
*/

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

#define ECHOPIN 11                            // Pin to receive echo pulse
#define TRIGPIN 12                           // Pin to send trigger pulse
#include "pitches.h"
// notes in the melody:

int finalMelody = NOTE_C4;
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4
};



int mDataSent[2] = {0, 0};
int mPotPin = A0;
int mValue;
void setup() {
  mValue = 0;
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
}

void loop() {


  //Serial.println(mValue);
  long distanceCm, distanceIn;
  digitalWrite(TRIGPIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);                   // Send pin low again
  int distance = pulseIn(ECHOPIN, HIGH);        // Read in times pulse

  mValue = map(distance, 5000, 180 , 0, 255);
  mValue = constrain(mValue , 0, 255);
  // convert the time into a distance
  distanceCm = distance / 29.1 / 2 ;
  distanceIn = distance / 74 / 2;

  //duration of note
  int noteDuration = 100 / distanceCm;
  tone(8, finalMelody, noteDuration);

  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  // stop the tone playing:
  noTone(8);
  if (distanceCm <= 0) {
 //   Serial.println("Out of range");
  }
  else {
    Serial.print(distanceIn);
    Serial.print("in, ");
    Serial.print(distanceCm);
    Serial.print("cm");
    Serial.println();
  }


  delay(50);
  mySerial.listen();

  //while (mySerial.available() >= 0 ) {
  mySerial.write((int)mValue);
  mySerial.write((int)50);
  //}
}

