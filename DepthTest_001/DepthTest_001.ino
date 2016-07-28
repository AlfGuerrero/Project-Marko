#include "Wire.h"
boolean proSend = true;
int val = 0;
int valNum;
int lightArray[4];

void setup()
{
  //Serial.print(sizeof(65535)/sizeof(int));
  
  Serial.begin(9600);

  lightArray[1] = 2;
  lightArray[2] = 3;
  lightArray[3] = 4;

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  int val = 0;
  
  establishContact();  // send a byte to establish contact until receiver responds
}

void loop()
{
  
  
  //valNum = Serial.read();         // read it and store it in val
  //print(valNum);
  
  if(Serial.available())
  { 
    val = int(Serial.read());
  }
  
  //val=0;

  
  for(int i=1; i<=3; i++)
  {
    if(i <= val)
    {
      digitalWrite(lightArray[i], HIGH);
    }
    else if (i>val)
    {
      digitalWrite(lightArray[i], LOW);
    }
    
  }
  //digitalWrite(, HIGH);
  /*
    //Serial.print(ceil(sizeof(65535)));
    Serial.write(sizeof(val));
    for(int i=0; i < sizeof(val); i++)
    {
      Serial.write(val >> i*8);
    }
    proSend = false;
  }
  */
  //Serial.write(val);
  //Serial.write(val >> (sizeOf(val)/sizeof(int)));
}

void establishContact() {
  
}

