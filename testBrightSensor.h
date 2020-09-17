/*
 *
 */

#ifndef TESTBRIGHTSENSOR_H
#define TESTBRIGHTSENSOR_H


#include <Arduino.h>
#include "config.h"
#include "brightSensor.h"
#include "driveControl.h"

extern uint32_t MILLIS;

extern const int brightSensePin;
extern const int brightSenseLedPin;

extern const int   mtrLeftFwdPin;
extern const int   mtrLeftRevPin;
extern const int   mtrRightFwdPin;
extern const int   mtrRightRevPin;
extern const float mtrLeftScale;
extern const float mtrRightScale;

brightSensor lightFollow(brightSensePin, brightSenseLedPin);


/*
 *
 */
void testBrightSensor() {
    static driveControl botDrive(mtrLeftFwdPin,  mtrLeftRevPin,  mtrLeftScale,
                                 mtrRightFwdPin, mtrRightRevPin, mtrRightScale);
    static int state = 0;   
 
    lightFollow.loop();
    botDrive.loop();

    switch (state) {
        /* Search by turning left */
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
        /* Go towards the light */
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
        /* Search by turing slightly right then going to left state */
        case 2:
            Serial.println("state 2");
            if (botDrive.getIsIdle()) {
                botDrive.turnRight(500, 70);
                state = 0;
            }
    }  // switch
    

}


#endif
