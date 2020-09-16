/*
 *
 */

#include <Arduino.h>
#include <math.h>
#include "thermistor.h"

extern uint32_t MILLIS;

/*
 *
 */
thermistor::thermistor(int sensorPinIn, int outputPinIn) {
    sensorPin = sensorPinIn;
    outputPin = outputPinIn;
    thermThreshold = 0.1; // (V)
}

/*
 *
 */
void thermistor::init(){
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(outputPin, OUTPUT);
}

/*
 *
 */
void thermistor::loop(){
  while(true){
    checkCurrentValue();

    if ((currThermVoltage - firstThermVoltage) > thermThreshold)
    {
      digitalWrite(outputPin, HIGH);
    }
  }
}

/*
 *
 */
void thermistor::checkFirstValue(){
  currThermValue = analogRead(sensorPin);
  firstThermVoltage = currThermValue * (5.0 / 1023);
}

/*
 *
 */
void thermistor::checkCurrentValue(){
  currThermValue = analogRead(sensorPin);
  currThermVoltage = currThermValue * (5.0 / 1023); 
}
