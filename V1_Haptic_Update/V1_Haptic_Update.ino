#define ECHOPIN 2                            // Pin to receive echo pulse
#define TRIGPIN 3                            // Pin to send trigger pulse
#include "pitches.h"
// notes in the melody:

int finalMelody = NOTE_C4;
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4,4,4,4,4 };

void setup(){
  Serial.begin(9600);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
}

void loop(){
  long distanceCm, distanceIn;
  digitalWrite(TRIGPIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);                   // Send pin low again
  int distance = pulseIn(ECHOPIN, HIGH);        // Read in times pulse
  
  // convert the time into a distance
  distanceCm = distance / 29.1 / 2 ;
  distanceIn = distance / 74 / 2;
  
  //duration of note
  int noteDuration = 1000/distance;
  //tone(8, finalMelody, noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  if (distanceCm <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distanceIn);
    Serial.print("in, ");
    Serial.print(distanceCm);
    Serial.print("cm");
    Serial.println();
  }
  delay(50);                                    // Wait 50mS before next ranging
}
