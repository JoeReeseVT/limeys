/*
 * Flash light sensor class interface
 */

#ifndef BRIGHTSENSOR_H
#define BRIGHTSENSOR_H


#include <Arduino.h>


class brightSensor {
    public:
        brightSensor(int sensorPin);
        
        void loop();
        bool getState();
    private:
        int  sensorPin;
        bool pinState;
};


#endif
