/*
 *
 */

#ifndef TESTTHERMISTOR_H
#define TESTTHERMISTOR_H

#include <Arduino.h>
#include <limits.h>  // for ULONG_MAX
#include "config.h"
#include "thermistor.h"

extern const int   thermPin;
extern const int   thermLedPin;
extern const float thermDefaultThresh;

void testThermistor() {
  thermistor thermObject(thermPin, thermLedPin, thermDefaultThresh);
  
  thermObject.init();
  thermObject.checkFirstValue();
  thermObject.loop();

}

#endif
