/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TESTMOTOR_H
#define TESTMOTOR_H


#include <Arduino.h>
#include "motorControl.h"

extern uint32_t MILLIS;


int mtrLeftFwdPin  = 4,
    mtrLeftRevPin  = 5,
    mtrRightFwdPin = 2,
    mtrRightRevPin = 3;

    
motorControl leftMotor(mtrLeftFwdPin,   mtrLeftRevPin);
motorControl rightMotor(mtrRightFwdPin, mtrRightRevPin);


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool wait(uint32_t delay_ms) {
	static uint32_t timer = MILLIS;

	if (MILLIS - timer >= delay_ms) {
		timer = MILLIS;
		return true;
	}
	else
		return false;
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void testMotor() {
	static int testNum = 0;
 
	leftMotor.loop();
	rightMotor.loop();
	
	switch (testNum) {
		/* Straight FWD */
		case 0:
			leftMotor.setVelocity(70, FWD);
			rightMotor.setVelocity(70, FWD);
			if (wait(1000)) {
				Serial.println("Switching to 1");
				leftMotor.setVelocity(0, FWD);
				rightMotor.setVelocity(0, FWD);
				testNum++;
			}
			break;
			
		/* Straight back */
		case 1:
			if (wait(500)) {
				Serial.println("Switching to 2");
				leftMotor.setVelocity(70, REV);
				rightMotor.setVelocity(70, REV);
				testNum++;
			}
			break;
		
		case 2:
			if (wait(1000)) {
				Serial.println("Switching to 3");
				leftMotor.setVelocity(0, REV);
				rightMotor.setVelocity(0, REV);
				testNum++;
			}
			break;
		
		/* Turn left */
		case 3:
			if (wait(500)) {
				Serial.println("Switching to 4");
				leftMotor.setVelocity(70, FWD);
				rightMotor.setVelocity(70, REV);
				testNum++;
			}
			break;
		case 4:
			if (wait(1000)) {
				Serial.println("Switching to 5");
				leftMotor.setVelocity(0, FWD);
				rightMotor.setVelocity(0, REV);
				testNum++;
			}
			break;
		
		/* Turn right */
		case 5:
			if (wait(500)) {
				Serial.println("Switching to 6");
				leftMotor.setVelocity(70, REV);
				rightMotor.setVelocity(70, FWD);
				testNum++;
			}
			break;
		case 6:
			if (wait(1000)) {
				Serial.println("Switching to 7");
				leftMotor.setVelocity(0, FWD);
				rightMotor.setVelocity(0, REV);
				testNum++;
			}
			break;
		
		case 7:
			if (wait(500)) {
				Serial.println("Switching to 0");
				testNum = 0;
			}
			break;
			
	} // switch
}


#endif
