/*
 *
 */

#ifndef TESTPATHFOLLOW_H
#define TESTPATHFOLLOW_H

#include <Arduino.h>
#include <limits.h>  // for ULONG_MAX
#include "config.h"
#include "driveControl.h"


extern const int   pathSensePin;
extern const int   mtrLeftFwdPin;
extern const int   mtrLeftRevPin;
extern const int   mtrRightFwdPin;
extern const int   mtrRightRevPin;
extern const float mtrLeftScale;
extern const float mtrRightScale;
extern const int   mtrSpeed;

driveControl botDrive(mtrLeftFwdPin,  mtrLeftRevPin,  mtrLeftScale,
                      mtrRightFwdPin, mtrRightRevPin, mtrRightScale);


void testPathFollow() {
    static int state = 0;
    static uint32_t timer = MILLIS;

    botDrive.loop();

    // We really don't need to check the path that often, every 5 ms is plenty
    if (MILLIS - timer < 5) { return; }
    timer = MILLIS;

    switch (state) {

        case 0:  // 5s halt
            botDrive.halt(5000);
            Serial.println("5s halt...");
            state = 1;
            break;

        case 1:  // Start going forward...
            if (botDrive.getIsIdle()) {
                botDrive.forward(ULONG_MAX, mtrSpeed);
                Serial.println("Going forward");
                state = 2;
            } 
            break;

        case 2:  // ... until we find the test track
            if (not digitalRead(pathSensePin)) {
                botDrive.halt();
                Serial.println("Found black track");
                state = 3;
            }
            break;

        case 3:  // After a brief pause, continue forward again...
            if (botDrive.getIsIdle()) {
                botDrive.forward(ULONG_MAX, mtrSpeed);
                Serial.println("Following track");
                state = 4;
            }
            break;

        case 4:  // ... until we lose the track, in which case we turn to try and find it
            if (analogRead(pathSensePin) >= 400) {
                botDrive.halt();
                botDrive.turnLeft(500, mtrSpeed);
                Serial.println("Lost track, turning left");
                state = 5;
            }
            break;

        case 5:  // If we didn't find the track, try turning the other direction; else if we did return to state 3
            if (analogRead(pathSensePin) < 400) {
                Serial.println("Left turn successful");
                botDrive.halt();
                state = 3;
            } else if (botDrive.getIsIdle()) {
                botDrive.turnRight(1000, mtrSpeed);
                Serial.println("Left turn failed, turning right");
                state = 6;
            }
            break;

        case 6:  // If we still can't find the track, give up!
            if (analogRead(pathSensePin) < 400) {
                Serial.println("Right turn successful");
                botDrive.halt();
                state = 3;
            } else if (botDrive.getIsIdle()) {
                Serial.println("Right turn failed, giving up");
                state = 7;
            }
            break;
            
        case 7:
            {;}

    }  // switch
}


#endif
