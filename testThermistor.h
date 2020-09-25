/*
 *
 */

#ifndef TESTTHERMISTOR_H
#define TESTTHERMISTOR_H

#include <Arduino.h>
#include <limits.h>  // for ULONG_MAX
#include "thermistor.h"

const int  sensorPin      = A5;
const int  outLedPin      = 7;


void testThermistor() {
  thermistor thermObject(sensorPin, outLedPin);
  
  thermObject.init();
  thermObject.checkFirstValue();
  thermObject.loop();

}

#endif
