#ifndef BOTUI_H
#define BOTUI_H

#include <Arduino.h>

enum mode_t {
  SOLID,
	BLINK,
	FLASH,
	PULSE,
	STOP
};

/* This defines the order of colors when indexing */
enum color_t {
	RED,
	ORN,
	GRN,
	BLU
};

class botUI {
	public:
		botUI(); // Sets pin modes and initializes all colors to STOP
		~botUI();
		
	  static void ledLoop();	
		static bool getInput(int pin);
    static void setMode(color_t color, mode_t mode, unsigned long period = 0, int numFlash = 0, unsigned long wait = 0);
    static void allStop();

    //TODO: functions for get input

	private:
  
    /* * * * * * * * * * * LED PIN NUMBERS * * * * * * * * * * */
    /*                                                         */
		static const int     N_COLORS = 4;
		static constexpr int PINS[N_COLORS] = {2, 5, 3, 4};
    /*                                                         */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
   
		static mode_t        modes[N_COLORS];
		static unsigned long periods[N_COLORS];
		static int           duties[N_COLORS];
		static unsigned long timers[N_COLORS];
    static int           numFlashes[N_COLORS];
    static unsigned long waits[N_COLORS];
};

#endif
