#include "Wire.h"
boolean proSend = true;

void setup()
{
  //Serial.print(sizeof(65535)/sizeof(int));
  
  Serial.begin(9600);

  establishContact();  // send a byte to establish contact until receiver responds
}

void loop()
{
  long val = 156031545;
  
  if(proSend == true)
  {
    //Serial.print(ceil(sizeof(65535)));
    Serial.write(sizeof(val));
    for(int i=0; i < sizeof(val); i++)
    {
      Serial.write(val >> i*8);
    }
    proSend = false;
  }
  
  //Serial.write(val);
  //Serial.write(val >> (sizeOf(val)/sizeof(int)));
}

void establishContact() {
  
}

