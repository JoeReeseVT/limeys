/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TESTDRIVE_H
#define TESTDRIVE_H


#include "Arduino.h"
#include "driveControl.h"

int mtrLeftFwdPin  = 4,
    mtrLeftRevPin  = 5,
    mtrRightFwdPin = 2,
    mtrRightRevPin = 3;

driveControl botDrive(mtrLeftFwdPin, mtrLeftRevPin, mtrRightFwdPin, mtrRightRevPin);


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void testDrive() {
	static int testNum = 0;

	botDrive.loop();

	switch (testNum) {
		/* Straight FWD */
		case 0:
			if (not botDrive.getIsMoving()) {
				Serial.println("Switching to 1");
				botDrive.stop(500);
				testNum++;
			}
			break;
			
		/* Straight back */
		case 1:
			if (not botDrive.getIsMoving()) {
				Serial.println("Switching to 2");
				botDrive.reverse(1000, 70);
				testNum++;
			}
			break;
		
		case 2:
			if (not botDrive.getIsMoving()) {
				Serial.println("Switching to 3");
				botDrive.stop(500);
				testNum++;
			}
			break;
		
		/* Turn left */
		case 3:
			if (not botDrive.getIsMoving()) {
				Serial.println("Switching to 4");
				botDrive.turnLeft(1000, 70);
				testNum++;
			}
			break;
			
		case 4:
			if (not botDrive.getIsMoving()) {
				Serial.println("Switching to 5");
				botDrive.stop(500);
				testNum++;
			}
			break;
		
		/* Turn right */
		case 5:
			if (not botDrive.getIsMoving()) {
				Serial.println("Switching to 6");
				botDrive.turnRight(1000, 70);
				testNum++;
			}
			break;
			
		case 6:
			if (not botDrive.getIsMoving()) {
				Serial.println("Switching to 7");
				botDrive.stop(500);
				testNum++;
			}
			break;
		case 7:
			if (not botDrive.getIsMoving()) {
				Serial.println("Switching to 0");
				botDrive.forward(1000, 70);
				testNum = 0;
			}
			
	} // switch
}


#endif
