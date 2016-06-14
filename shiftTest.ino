#include "Wire.h"

void setup()
{

  Serial.begin(9600);

  establishContact();  // send a byte to establish contact until receiver responds
}

void loop()
{
  int val = 65535;
  Serial.write(val);
  Serial.write(val >> 8);
}

void establishContact() {
  
}
