/*
 *
 */

#ifndef TESTDRIVE_H
#define TESTDRIVE_H


#include "Arduino.h"
#include "driveControl.h"

int mtrLeftFwdPin  = 9;
int mtrLeftRevPin  = 10;
int mtrRightFwdPin = 6;
int mtrRightRevPin = 5;

driveControl botDrive(mtrLeftFwdPin, mtrLeftRevPin, 0, mtrRightFwdPin, mtrRightRevPin, 0);

/*
 *
 */
void testDrive() {
    static int testNum = 0;

    botDrive.loop();

    switch (testNum) {
        /* Straight FWD */
        case 0:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 1");
                botDrive.halt(5000);
                testNum++;
            }
            break;

        /* Straight back */
        case 1:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 2");
                botDrive.reverse(10000, 70);
                testNum++;
            }
            break;

        case 2:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 3");
                botDrive.halt(5000);
                testNum++;
            }
            break;

        /* Turn left */
        case 3:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 4");
                botDrive.turnLeft(10000, 70);
                testNum++;
            }
            break;

        case 4:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 5");
                botDrive.halt(5000);
                testNum++;
            }
            break;

        /* Turn right */
        case 5:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 6");
                botDrive.turnRight(10000, 70);
                testNum++;
            }
            break;

        case 6:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 7");
                botDrive.halt(5000);
                testNum++;
            }
            break;
        case 7:
            if (botDrive.getIsIdle()) {
                Serial.println("Switching to 0");
                botDrive.forward(10000, 70);
                testNum = 0;
            }
    }  // switch
}


#endif
