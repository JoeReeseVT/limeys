/*
 *
 */

#include <Arduino.h>
#include "thermistor.h"

extern uint32_t MILLIS;


/*  
 *
 */
thermistor::thermistor(int sensorPin, int outputPin, float thermThreshold) {
    this->sensorPin = sensorPin;
    this->outputPin = outputPin;
    this->thermThreshold = thermThreshold; 

    pinMode(sensorPin, INPUT_PULLUP);
    pinMode(outputPin, OUTPUT);

    currThermValue = analogRead(sensorPin);
    firstThermValue = currThermValue;
}


/*
 *  Returns true if temperature change is over threshold, else false.
 */
bool thermistor::loop() {
    currThermValue = analogRead(sensorPin);

    if ((currThermValue - firstThermValue) > thermThreshold) {
        digitalWrite(outputPin, HIGH);
        return true;
    } else {
        digitalWrite(outputPin, LOW);
        return false;
    }
}

