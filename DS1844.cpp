/*
  DS1844.h - Library for controlling a Maxim Integrated DS1844 Quad Digital Potentiometer
  Created by Matt Westwick; March 23, 2013
  Released into the public domain.
 
 
 UPDATES
 2020/07/29:1544> (UTC-5)
 			- changed "int" to "int16_t". int is a signed 4-byte value on Arduino
 			Due and SAMD boards, while int is a signed 2-byte value on ATmega-
 			based boards which could cause some inconsistent behavior across
 			different architectures. (editor: Orlando S. Hoilett).
*/



#include "Arduino.h"
#include "Wire.h"
#include "DS1844.h"


DS1844::DS1844(int16_t address)
{
  Wire.begin();
  this->address=address;
  /*
  Addresses for common configurations:
  A0, A1, A2 low -> 0101000 -> 0x28
  A0 high; A1, A2 low -> 0101001 -> 0x29
  A0, A1 high; A2 low -> 0101011 -> 0x2B
  A0, A1, A2 high -> 0101111 -> 0x2F
  */
}

void DS1844::write(int16_t pot, int16_t value) {    //value is between 0 and 63
  
  if (value > 63) {  //prevents values that are too large from overwriting address bits
  value = 63;
  }
  
  if (pot > 3) { //prevents mistransmission of address bits
	pot = 3;
  }
  
  byte bvalue = byte(value);
  byte bpot = byte(pot);
  
  bpot = bpot << 6;
  byte SendWriteVal = bpot + bvalue;
  
  Wire.beginTransmission(this->address);
  Wire.write(SendWriteVal); //0101-000-0 then 00-****** then 01-****** etc.
  Wire.endTransmission();
}

int16_t DS1844::read(int16_t pot) {
  int16_t PotRead[4];
  int16_t j = 0;
  int16_t address = this->address;
  Wire.requestFrom(address, 4);
  while (Wire.available()) {
   PotRead[j] = Wire.read();
   j++;
  }
  
  return PotRead[pot];
}
