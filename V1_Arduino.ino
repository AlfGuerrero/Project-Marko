/* Name: Alfrancis Guerrero 
 * Date: 6/2/2016 
 * Notes: Arduino file run w/Processing and Bluetooth Module Device
 */

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);


int mDataSent[2] = {0, 0};
int mPotPin = A0;
int mValue;
void setup() {
  mValue = 0;
  Serial.begin(9600);
  mySerial.begin(9600);

}

void loop() {

  mValue = analogRead(mPotPin);
  mValue = map(mValue, 0, 1023, 0, 255);
  mValue = constrain(mValue , 0, 255);
  //Serial.println(mValue);

  mySerial.listen();

  //while (mySerial.available() >= 0 ) {
  mySerial.write((int)mValue);
  mySerial.write((int)50);
  //}
}


void BluetoothSent(int Sensor_01, int Sensor_02)
{
  mDataSent[0] = Sensor_01;
  mDataSent[1] = Sensor_02;

  mySerial.write((int)mDataSent[0]);
  //mySerial.write((int)mDataSent[1]);

}
