/*
 * Flash light class
 */

#include <Arduino.h>
#include "brightSensor.h"

/*
 * Contructor sets pin value
 */
brightSensor::brightSensor(int sensorPin, int ledPin) {
        
    this->sensorPin = sensorPin;
    this->ledPin    = ledPin;
    pinMode(sensorPin, INPUT);
    pinMode(ledPin, OUTPUT);
}


/*
 * Loop function
 */
void brightSensor::loop() {
    isLight = not digitalRead(sensorPin);
    
    // turn green led on
    if (isLight) {
        digitalWrite(ledPin, HIGH);
    } else {
        digitalWrite(ledPin, LOW);
    }
}

/*
 * Lets the user get the state of the pin
 */
bool brightSensor::getState() {
    return isLight;
}
