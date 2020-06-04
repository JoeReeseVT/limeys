/*
 *
 */

#ifndef TESTPATHFOLLOW_H
#define TESTPATHFOLLOW_H

#include <Arduino.h>
#include <limits.h>  // for ULONG_MAX
#include "driveControl.h"
#include "lightSensor.h"


const int   sensorPin      = A0;
const int   redLedPin      = 12;
const int   blueLedPin     = 11;
const int   mtrLeftFwdPin  = 4;
const int   mtrLeftRevPin  = 5;
const int   mtrRightFwdPin = 2;
const int   mtrRightRevPin = 3;
const float mtrLeftScale   = 1.3;
const float mtrRightScale  = 1.0;


lightSensor  botSense(sensorPin, redLedPin, blueLedPin);
driveControl botDrive(mtrLeftFwdPin,  mtrLeftRevPin,  1.3,
                      mtrRightFwdPin, mtrRightRevPin, 1.0);


/*
 * SCRIPT:
 * Start forward on black
 * When you hit blue, turn about 90 degrees right (about 1 sec)
 * When you hit yellow, turn a little right
 * When you hit red, stop
 */
void testPathFollow() {
    static int testNum = 0;

    botDrive.loop();
    botSense.loop();

    switch (testNum) {

        case 0:  // 5-second stop
            botDrive.halt(5000);
            ++testNum;
            break;

        case 1:  // Go forward until you hit blue
            botDrive.forward(ULONG_MAX, 45);
            if (botSense.detectTrack() == BLU_TK) {
                botDrive.halt();
                ++testNum;
            }
            break;

        case 2:  // Turn 90 deg right
            botDrive.turnRight(1000, 70);
            ++testNum;
            break;

        case 3:  // Forward until yellow, then stop
            botDrive.forward(ULONG_MAX, 45);
            if (botSense.detectTrack() == YLW_TK) {
                botDrive.halt();
                ++testNum;
            }
            break;

        case 4:  // Turn a little right
            botDrive.turnRight(250, 70);  // DBG TEST THIS!!
            ++testNum;
            break;

        case 5:  // Forward till red, then stop FINALLY
            botDrive.forward(ULONG_MAX, 45);
            if (botSense.detectTrack() == RED_TK) {
                botDrive.halt();
                ++testNum;
            }
            break;

        default:
            {;}  // NULL
            break;

    }  // switch
}


#endif
