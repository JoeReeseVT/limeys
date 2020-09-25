/*
 *
 */

#ifndef TESTPATHFOLLOW_H
#define TESTPATHFOLLOW_H

#include <Arduino.h>
#include <limits.h>  // for ULONG_MAX
#include "driveControl.h"


const int   sensorPin      = A1;
const int   mtrLeftFwdPin  = 9;
const int   mtrLeftRevPin  = 10;
const int   mtrRightFwdPin = 5;
const int   mtrRightRevPin = 6;
const float mtrLeftScale   = 1.0;
const float mtrRightScale  = 1.0;
const int   mtrSpeed       = 80;

driveControl botDrive(mtrLeftFwdPin,  mtrLeftRevPin,  mtrLeftScale,
                      mtrRightFwdPin, mtrRightRevPin, mtrRightScale);

/*
 *  Goes through the cases in a set sequence. Once we reach a dead end,
 *  state does not change any more, we just return true forever.
 *
 *  SCRIPT:
 *  Start forward on black
 *  When you hit blue, turn about 90 degrees right (about 1 sec)
 *  When you hit yellow, turn a little right
 *  When you hit red, stop
 */
bool testPathFollow() {
    static driveControl botDrive(mtrLeftFwdPin, mtrLeftRevPin, mtrLeftScale,
                                 mtrRightFwdPin, mtrRightRevPin, mtrRightScale);

    static int state = 0;
    static uint32_t timer = MILLIS;
    static bool isComplete = false;  // Whether we've reached a dead end

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
            if (not digitalRead(sensorPin)) {
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
            if (analogRead(sensorPin) >= 400) {
                botDrive.halt();
                botDrive.turnLeft(500, mtrSpeed);
                Serial.println("Lost track, turning left");
                state = 5;
            }
            break;

        case 5:  // If we didn't find the track, try turning the other direction; else if we did return to state 3
            if (analogRead(sensorPin) < 400) {
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
            if (analogRead(sensorPin) < 400) {
                Serial.println("Right turn successful");
                botDrive.halt();
                state = 3;
            } else if (botDrive.getIsIdle()) {
                Serial.println("Right turn failed, giving up");
                state = 7;
            }
            break;

        case 7:
            isComplete = true;

    }  // switch

    return isComplete;
}


#endif
