/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TESTHALLSENSOR_H
#define TESTHALLSENSOR_H


#include <Arduino.h>
#include "hallSensor.h"

extern uint32_t MILLIS;

hallSensor hallRight = hallSensor(30, ACTIVE_LOW);

/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void testHallSensor() {

  hallRight.loop();
  
  if (hallRight.getDetected()) {
        Serial.println("Found");
  }
  
}


#endif
