#ifndef LED_H
#define LED_H

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


class led {
	public:
    led();
		led(const int pin, const int pwm_max); // Sets pin modes and initializes all colors to STOP
		
		void loop(); 
    bool isOn();
    void phaseInvert();
		void setMode(mode_t mode, unsigned long period = 0, int numFlash = 0, unsigned long wait = 0);
		void setOff();

  private:
    int pin;
    int pwm_max;
    mode_t        mode;
    unsigned long period;
    unsigned long timer;
    unsigned long wait;
    int           flashes;
    int           duty;
};

#endif
