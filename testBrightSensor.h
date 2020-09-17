/*
 *
 */

#ifndef TESTBRIGHTSENSOR_H
#define TESTBRIGHTSENSOR_H


#include <Arduino.h>
#include "brightSensor.h"
#include "driveControl.h"

extern uint32_t MILLIS;

const int sensorPin  = 7;

int mtrLeftFwdPin  = 9;
int mtrLeftRevPin  = 10;
int mtrRightFwdPin = 5;
int mtrRightRevPin = 6;

brightSensor lightFollow(sensorPin);
driveControl botDrive(mtrLeftFwdPin, mtrLeftRevPin, 0, mtrRightFwdPin, mtrRightRevPin, 0);

/*
 *
 */
void testBrightSensor() {
    static int state = 0;   
 
    lightFollow.loop();
    botDrive.loop();

    switch (state) {
        /* Search */
        case 0:
            Serial.println("state 0");
            if (lightFollow.getState()) {
                Serial.println("Found Light");
                botDrive.halt();
                state = 1;
            } if (botDrive.getIsIdle()) {
                botDrive.turnLeft(500, 70);
            }
            break;

        case 1:
            Serial.println("state 1");
            if (not lightFollow.getState()) {
                botDrive.halt();
                state = 2;
                Serial.println("Switching to 2");
            } if (botDrive.getIsIdle()) {
                Serial.println("forward");
                botDrive.forward(1000, 70);
            }
            break;
        case 2:
            Serial.println("state 2");
            if (botDrive.getIsIdle()) {
                botDrive.turnRight(500, 70);
                state = 0;
            }
    }  // switch
    

}


#endif
