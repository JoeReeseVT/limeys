#include "led.h"
#include "Arduino.h"

extern unsigned long MILLIS;

#include <math.h>

/*
led::led() {
  pwm_max = 255;
  pin     = -1;
  
  mode    = STOP;
  duty    = 1000;
  timer   = 0;
  wait    = 1000;
  flashes = 1;
}
*/

led::led(const int pin, const int pwm_max) {
  this->pwm_max = pwm_max;
	this->pin     = pin;
  pinMode(this->pin, OUTPUT);
  
	mode    = STOP;
	duty    = 1000;
	timer   = 0;
	wait    = 1000;
	flashes = 1;
}


void led::setOff() {
	setMode(STOP);
}


void led::phaseInvert() {
  timer += period / 2;
}


/* Parameters:
 *  mode    : One of the led modes enumerated in led.h
 *  period  : Period of cyclic functions, in milliseconds 
 *  flashes : Number of flashes during FLASH mode
 *  wait    : Time between each burst of flashes in FLASH mode (milliseconds)
 * 
 * * * * * * * * * * * * * * * * * * * * * * */
void led::setMode(mode_t mode, unsigned long period, int flashes, unsigned long wait) {
	this->mode = mode;
	
	if (period)
		this->period = period;
    
	if (flashes)
		this->flashes = flashes;
    
	if (wait)
		this->wait = wait;
}


bool led::isOn() {
  return duty > 0;
}


/* This is where all the control actually happens */
void led::loop() {
//  static unsigned long speedLimiter = MILLIS;
//  if (MILLIS - speedLimiter >= 10) {
//    speedLimiter = MILLIS;
  	switch (mode) {
  
  		case BLINK:
  			if (MILLIS - timer >= period >> 1) { // Quick divide by 2
  				timer = MILLIS;
  				duty = pwm_max * not duty;
  			}
  			break;
  
  		/* This is sorta complicated. We flash flashes times with 
  		 * the given period. Then we turn off for wait ms. Then we 
  		 * start over by resetting the timer.
  		 * 
  		 * Uses the fact that odd multiples of half the blink period 
  		 * should be ON
  		 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  		case FLASH:
  			if (MILLIS - timer >= period * flashes + wait)
  				timer = MILLIS;
  			else if (MILLIS - timer >= period * flashes)
  				duty = 0;
  			else if ((((MILLIS - timer)) / (period >> 1)) % 2)
  				duty = pwm_max;
  			else 
  				duty = 0;
  			break;
  
  		/* "Breathe" by half the cycle of sin(x * 2pi / (period * 2)) */
  		case PULSE:
  			duty = pwm_max * sin(fmod(MILLIS, period) * PI / (double)period);
  			break;
  
  		case SOLID:
  			duty = pwm_max;
  			break;
  
  		case STOP:
  			duty = 0;	
  			break;
  	} // switch
	analogWrite(pin, duty);
//  } // if
}
