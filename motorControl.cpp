/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include "Arduino.h"
#include "motorControl.h"

extern uint32_t MILLIS;


/* Constructor sets direction to FWD and speed to 0
 * and sets pin modes.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
motorControl::motorControl(int fwdPin, int revPin) {
	initMotor(fwdPin, revPin, 1.0);
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
motorControl::motorControl(int fwdPin, int revPin, float scalar) {
	initMotor(fwdPin, revPin, scalar);
}


/* Uses a cosine to ramp between one velocity and the next.
 * If deltaT is 0, outputs tgt - (delta / 2) * 2, i.e. just the previous tgt.
 * If deltaT is RAMP_TIME, outputs tgt - 0,				i.e. just the current tgt.
 * Everything in between is handled appropriately.
 * 	// TODO Sinusoidal acceleration curve
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void motorControl::loop() {


	/*
	static uint32_t deltaT;
	deltaT = MILLIS - accelTimer;

	if (deltaT <= RAMP_TIME) 
		for (int i = FWD; i <= REV; i++)
			curPwms[i] = tgtPwms[i] - (deltas[i] / 2) 
									 * (cos(deltaT * PI / RAMP_TIME) + 1);
	*/

	analogWrite(fwdPin, tgtPwmFwd);
	analogWrite(revPin, tgtPwmRev);
}

	
/* Speed control: Set the active pin to spd, set the other to 0.
 * If velocity setpoint changes, reset the acceleration ramp timer
 * and update the deltas 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void motorControl::setVelocity(int spd, spin_t spin) {
	if (spin != spin or (spd != tgtPwmFwd and spd != tgtPwmRev)) {
		this->spin = spin;
		
		accelTimer = MILLIS;
		
		deltaFwd = curPwmFwd - tgtPwmFwd;
		deltaRev = curPwmRev - tgtPwmRev;
	}
	
	tgtPwmFwd = scalar * spd * (int)(not spin); 
	tgtPwmRev = scalar * spd * (int)(spin);
}


/* Shorthand function for stopping the motor
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void motorControl::halt() {
	setVelocity(0, spin);
}


void motorControl::initMotor(int fwdPin, int revPin, float scalar) {
	this->fwdPin = fwdPin;
	this->revPin = revPin;
	this->scalar = scalar;
	
	pinMode(fwdPin, OUTPUT);
	pinMode(revPin, OUTPUT);

	setVelocity(0, FWD);
}
