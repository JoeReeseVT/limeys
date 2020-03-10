/* 
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef LED_H
#define LED_H


#include <Arduino.h>


/* Enumerates the different kinds of patterns for LED control.
 *	 BLINK : Steady ON/OFF pattern
 *	 FLASH : Blink a certain number of times, pause, then repeat
 *	 PULSE : Gradually "breathe" on and off
 *	 SOLID : Continuous ON
 *	 STOP  : Continuous OFF
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
enum mode_t {
	BLINK,
	FLASH,
    SIGNAL, // Like flash but only runs once then goes to STOP
	PULSE,
	SOLID,
	STOP
};


class led {
	public:
		led(const int ledPin);
		led(const int ledPin, const int pwmMax);

		void loop();
		 
		bool isOn();
		void setMode(mode_t mode);
		void setMode(mode_t mode, uint32_t period);		
		void setMode(mode_t mode, uint32_t period, int flashes);
		void setMode(mode_t mode, uint32_t period, int flashes, uint32_t wait);
		void setOff();
		void phaseInvert();

	private:
		void ledInit(int ledPin, int pwmMax);

		uint32_t period, 
		         timer, 
		         wait;
		
		mode_t mode;

		int ledPin,
		    pwmMax,
		    flashes,
		    duty;
};


#endif
