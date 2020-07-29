/*
  DS1844.h - Library for controlling a Maxim Integrated DS1844 Quad Digital Potentiometer
  Created by Matt Westwick; March 23, 2013
  Released into the public domain.
*/

#ifndef DS1844_h
#define DS1844_h
#include "Arduino.h"
#include <wiring_private.h>

class DS1844
{
  int16_t address;
  public:
    DS1844(int16_t address);
    void write(int16_t pot, int16_t value);
    int16_t read(int16_t pot);
  //private:
    //int _address;
};

#endif
