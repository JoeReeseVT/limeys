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
thermistor::thermistor(int sensorPin, int outputPin, float thermThreshold) {
    this->sensorPin = sensorPin;
    this->outputPin = outputPin;
    this->thermThreshold = thermThreshold; // (V)
}

/*
 *
 */
void thermistor::init() {
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(outputPin, OUTPUT);
}

/*
 *
 */
void thermistor::loop() {
  while (true) {
    checkCurrentValue();

    if ((currThermVoltage - firstThermVoltage) > thermThreshold) {
      digitalWrite(outputPin, HIGH);
    }
  }
}

/*
 *
 */
void thermistor::checkFirstValue() {
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
