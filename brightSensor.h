/*
 * Flash light sensor class interface
 */

#ifndef BRIGHTSENSOR_H
#define BRIGHTSENSOR_H


#include <Arduino.h>
#include "led.h"

class brightSensor {
    public:
        brightSensor(int sensorPin, int ledPin);
            
        void loop();
        bool getState();
    private:
        int  sensorPin;
        int  ledPin;
        bool isLight;
};


#endif
