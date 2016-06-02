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
/*
  while (mySerial.available() >= 0) {
    //int inValue = mySerial.read();

    for (int i = 0; i > 2; i++)
    {
      mByte[i] = mySerial.read();
    }

    mVal = mByte[0];
    mVal2 = mByte[1];
    Serial.print((int)mVal);
    Serial.print(" ");
    Serial.println((int)mVal2);

  }


   while (mySerial.available() > 0)
  {
    for (int i = 0; i < 2; i++)
    {
      mByte[i] = mySerial.read();
      Serial.print("mByteRead");
      Serial.println((int)mByte[i]);
    }

    //mVal= mySerial.read();

    mVal = (int)mByte[0];
    mVal2 = (int)mByte[1];

    myservo.write((int)mVal);

    mByteSent[0] = (int)mVal;
    mByteSent[1] = (int)mVal2;

    for (int i = 0; i < 2; i++)
    {

      mySerial.write((int)mByteSent[i]);
      Serial.print("mByteSent");
      Serial.println((int)mByteSent[i]);
    }



  }
  if (Serial.available())
  {
  mVal = Serial.read();
  Serial.println((char)mVal);
  myservo.write((int)mVal);

  mWrite = mVal;
  Serial.println((char)mWrite);
  }*/
