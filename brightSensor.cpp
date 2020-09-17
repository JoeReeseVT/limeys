/*
 * Flash light class
 */

#include <Arduino.h>
#include "brightSensor.h"

/*
 * Contructor sets pin value
 */
brightSensor::brightSensor(int sensorPin) {
    this->sensorPin = sensorPin;
    pinMode(sensorPin, INPUT);
}


/*
 * Loop function
 */
void brightSensor::loop() {
    pinState = not digitalRead(sensorPin);
}

/*
 * Lets the user get the state of the pin
 */
bool brightSensor::getState() {
    return pinState;
}
