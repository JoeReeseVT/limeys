#include "botUI.h"
#include "Arduino.h"
#include <math.h>


/* Allocate the actual space for the data members */
const int     botUI::N_COLORS;
constexpr int botUI::PINS[N_COLORS];
mode_t        botUI::modes[N_COLORS];
unsigned long botUI::periods[N_COLORS];
unsigned long botUI::timers[N_COLORS];
unsigned long botUI::waits[N_COLORS];
int           botUI::numFlashes[N_COLORS];
int           botUI::duties[N_COLORS];


botUI::botUI() {
	for (int i = 0; i < N_COLORS; i++) {
		pinMode(PINS[i], OUTPUT);
    modes[i]      = STOP;
    duties[i]     = 1000;
    timers[i]     = 0;
    waits[i]      = 1000;
    numFlashes[i] = 1;
	}
}


/* Reset the pins to high-Z just in case this is run for some reasion*/
botUI::~botUI() {
	for (int i = 0; i < N_COLORS; i++)
		pinMode(PINS[i], INPUT);
}


void botUI::allStop() {
  for (int i = 0; i < N_COLORS; i++)
    setMode((color_t)i, STOP);
}


void botUI::setMode(color_t color, mode_t mode, unsigned long period, int numFlash, unsigned long wait) {
  modes[color] = mode;
  if (period)
    periods[color] = period;
  if (numFlash)
    numFlashes[color] = numFlash;
  if (wait)
    waits[color] = wait;
}


/* STUB */
bool botUI::getInput(int pin) {
  return true;
}


/* This is where all the control actually happens */
void botUI::ledLoop() {
	static const int PWM_MAX = 255;

	for (int i = 0; i < N_COLORS; i++) {
		switch (modes[i]) {
      
			/* Turn the LED on for half the peiod, off for the next half */
			case BLINK: {
				if (millis() - timers[i] >= periods[i] >> 1) { // Quick divide by 2
					timers[i] = millis();
					duties[i] = PWM_MAX * not duties[i];
				}
				break;
			}

      /* This is sorta complicated. We flash numFlashes[i] times with the given period.
       * then we turn off for waits[i] milliseconds.
       * Then we start over by resetting the timer.
       */
      case FLASH: {
        if (millis() - timers[i] >= periods[i] * numFlashes[i] + waits[i])
          timers[i] = millis();
        else if (millis() - timers[i] >= periods[i] * numFlashes[i])
          duties[i] = 0;
        else if ((((millis() - timers[i])) / (periods[i] >> 1)) % 2) // If time elapsed is an odd multiple of period/2
          duties[i] = PWM_MAX;
        else 
          duties[i] = 0;
        break;
      }

			/* Oscillate by half the cycle of sin(x * 2pi / (period * 2)) */
			case PULSE: {
				duties[i] = PWM_MAX * sin(fmod(millis(), periods[i]) * PI / (double)periods[i]);
				break;
			}

      case SOLID: {
        duties[i] = PWM_MAX;
        break;
      }

			case STOP: {
				duties[i] = 0;	
				break;
			}
		}

		analogWrite(PINS[i], duties[i]);

	}
}
