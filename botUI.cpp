#include "botUI.h"
#include "Arduino.h"
#include <math.h>


botUI::botUI(const int PIN_ARR[], const int LENGTH) {
	N_COLORS = LENGTH;
	for (int i = 0; i < N_COLORS; i++) {
		PINS[i] = PIN_ARR[i];
		pinMode(PINS[i], OUTPUT);
		modes[i]      = STOP;
		duties[i]     = 1000;
		timers[i]     = 0;
		waits[i]      = 1000;
		numFlashes[i] = 1;
	}
}


void botUI::allStop() {
	for (int i = 0; i < N_COLORS; i++)
		setMode((color_t)i, STOP);
}


void botUI::setMode(color_t color, mode_t mode, 
                unsigned long period, int numFlash, unsigned long wait) {
	modes[color] = mode;
	if (period)
		periods[color] = period;
	if (numFlash)
		numFlashes[color] = numFlash;
	if (wait)
		waits[color] = wait;
}


/* STUB */
//bool botUI::getInput(int pin) {
//  return true;
//}


/* This is where all the control actually happens */
void botUI::loop() {
	static const int PWM_MAX = 255;

	for (int i = 0; i < N_COLORS; i++) {
		switch (modes[i]) {

			case BLINK:
				if (millis() - timers[i] >= periods[i] >> 1) { // Quick divide by 2
					timers[i] = millis();
					duties[i] = PWM_MAX * not duties[i];
				}
				break;

			/* This is sorta complicated. We flash numFlashes[i] times with 
			 * the given period. Then we turn off for waits[i] ms. Then we 
			 * start over by resetting the timer.
			 * 
			 * Uses the fact that odd multiples of half the blink period 
			 * should be ON
			 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
			case FLASH:
				if (millis() - timers[i] >= periods[i] * numFlashes[i] + waits[i])
					timers[i] = millis();
				else if (millis() - timers[i] >= periods[i] * numFlashes[i])
					duties[i] = 0;
				else if ((((millis() - timers[i])) / (periods[i] >> 1)) % 2)
					duties[i] = PWM_MAX;
				else 
					duties[i] = 0;
				break;

			/* "Breathe" by half the cycle of sin(x * 2pi / (period * 2)) */
			case PULSE:
				duties[i] = PWM_MAX * sin(fmod(millis(), periods[i]) 
				                    * PI / (double)periods[i]);
				break;

			case SOLID:
				duties[i] = PWM_MAX;
				break;

			case STOP:
				duties[i] = 0;	
				break;
		} // switch

		analogWrite(PINS[i], duties[i]);

	} // for
}
