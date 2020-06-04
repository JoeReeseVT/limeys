/*
 *
 */

#include <limits.h>
#include "hallSensor.h"

extern uint32_t MILLIS;


/*
 * Sets the detected flag to false
 */
hallSensor::hallSensor(int sensorPin, hallMode_t mode) {
    this -> sensorPin = sensorPin;
    this -> mode = mode;
    detected = false;
    pinMode(sensorPin, INPUT);
}


/*
 *
 */
void hallSensor::loop() {
    detectField();
}


/*
 * Changes logic depending on if hall sensor is active high or active low
 */
bool hallSensor::detectField() {
    bool pin = digitalRead(sensorPin);
    if ((pin and mode == ACTIVE_HIGH) or (!pin and mode == ACTIVE_LOW)) {
        detected = true;
        return true;
    }
    else {return false;}
}


/*
 * True if the magnet has been detected since the last function call
 * clears the detected bool when it is called
 */
bool hallSensor::getDetected() {
    bool temp = detected;
    detected = false;
    return temp;
}
