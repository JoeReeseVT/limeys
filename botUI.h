#ifndef BOTUI_H
#define BOTUI_H

#include <Arduino.h>

/* Enumerates the different kinds of patterns for LED control.
 *   BLINK : Steady ON/OFF pattern
 *   FLASH : Blink a certain number of times, pause, then repeat
 *   PULSE : Gradually "breathe" on and off
 *   SOLID : Continuous ON
 *   STOP  : Continuous OFF
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
enum mode_t {
	BLINK,
	FLASH,
	PULSE,
	SOLID,
	STOP
};


/* This defines the order of colors when indexing */
enum color_t {
	RED,
	ORN,
	GRN,
	BLU
};


/* botUI class
 * 
 * Purpose: Control a set of LEDs and/or speakers, and read inputs from
 *   switches and/or buttons.
 * 
 * NOTE: Pin numbers should be given in the same order as declared in
 *   the type enumeration, e.g. {RED, ORN, GRN, BLU}.
 *     
 * Data members:
 *   modes   : What each LED's mode is set to (see mode_t enum above)
 *   periods : For modes that blink, sets period of blink cycle (ms)
 *   timers  : Each pin has an independent timer for pattern timing
 *   waits   : For modes that have a pause, sets length of pause (ms)
 *   duties  : Current PWM duty cycle value (0-255) for each pin
 *   numFlashes : For modes that flash, sets # of flashes per cycle
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class botUI {
	private:
		int N_COLORS;
		int PINS[];
   
		mode_t        modes[];
		unsigned long periods[];
		unsigned long timers[];
		unsigned long waits[];
		int           numFlashes[];
		int           duties[];

	public:
		botUI(const int PINS_ARRAY[], const int LENGTH); // Sets pin modes and initializes all colors to STOP
		
		void loop(); 
		void setMode(color_t color, mode_t mode, unsigned long period = 0, int numFlash = 0, unsigned long wait = 0);
		void allStop();

    //TODO: functions for get input
    //static bool getInput(int pin);
};

#endif
