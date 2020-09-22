/*
 *
 */

#ifndef TESTDRIVE_H
#define TESTDRIVE_H


#include "Arduino.h"
#include "config.h"
#include "driveControl.h"

extern const int   mtrLeftFwdPin;
extern const int   mtrLeftRevPin;
extern const int   mtrRightFwdPin;
extern const int   mtrRightRevPin;
extern const float mtrLeftScale;
extern const float mtrRightScale;


/*
 *
 */
void testDrive() {
    static driveControl botDrive(mtrLeftFwdPin, mtrLeftRevPin, mtrLeftScale,
                                 mtrRightFwdPin, mtrRightRevPin, mtrRightScale);
    static int testNum = 0;

    botDrive.loop();

    switch (testNum) {
        /* Straight FWD */
        case 0:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 1");
                botDrive.halt(500);
                testNum++;
            }
            break;

        /* Straight back */
        case 1:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 2");
                botDrive.reverse(1000, 70);
                testNum++;
            }
            break;

        case 2:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 3");
                botDrive.halt(500);
                testNum++;
            }
            break;

        /* Turn left */
        case 3:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 4");
                botDrive.turnLeft(1000, 70);
                testNum++;
            }
            break;

        case 4:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 5");
                botDrive.halt(500);
                testNum++;
            }
            break;

        /* Turn right */
        case 5:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 6");
                botDrive.turnRight(1000, 70);
                testNum++;
            }
            break;

        case 6:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 7");
                botDrive.halt(500);
                testNum++;
            }
            break;
        case 7:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 0");
                botDrive.forward(1000, 70);
                testNum = 0;
            }
    }  // switch
}


#endif
