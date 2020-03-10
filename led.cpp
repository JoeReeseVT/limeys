/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <Arduino.h>
#include <math.h>
#include "led.h"

extern uint32_t MILLIS;


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
led::led(const int ledPin) {
	ledInit(ledPin, 255);
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
led::led(const int ledPin, const int pwmMax) {
	ledInit(ledPin, pwmMax);
}


/* FLASH: This is sorta complicated. We flash flashes times with 
 * the given period. Then we turn off for wait ms. Then we 
 * start over by resetting the timer.
 * 
 * Uses the fact that odd multiples of half the blink period 
 * should be ON
 *
 * SIGNAL: After the number of flashes * the period of each flash elapses,
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
void led::loop() {
	switch (mode) {

		case BLINK:
			if (MILLIS - timer >= period / 2) { // Quick divide by 2
				timer = MILLIS;
				duty = pwmMax * not duty;
			}
			break;

		case FLASH:
			if (MILLIS - timer >= period * flashes + wait)
				timer = MILLIS;
			else if (MILLIS - timer >= period * flashes)
				duty = 0;
			else if ((((MILLIS - timer)) / (period / 2)) % 2)
				duty = pwmMax;
			else 
				duty = 0;
			break;

        case SIGNAL:
			if (MILLIS - timer >= period * flashes)
				mode  = STOP;
			else if (((MILLIS - timer) / (period / 2)) % 2)
				duty = pwmMax;
			else 
				duty = 0;
			break;

		/* "Breathe" by half the cycle of sin(x * 2pi / (period * 2)) */
		case PULSE:
			duty = pwmMax * sin(fmod(MILLIS, period) * PI / (float)period);
			break;

		case SOLID:
			duty = pwmMax;
			break;

		case STOP:
			duty = 0;	
			break;
	} // switch
 
	analogWrite(ledPin, duty);
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
bool led::isOn() {
	return duty > 0;
}


/* Parameters:
 *	mode    : One of the led modes enumerated in led.h
 *	period  : Period of cyclic functions, in milliseconds 
 *	flashes : Number of flashes during FLASH mode
 *	wait    : Time between each burst of flashes in FLASH mode (milliseconds)
 *	
 * Effects: Resets timer every time setMode is called
 * * * * * * * * * * * * * * * * * * * * * * */
void led::setMode(mode_t mode) {
	setMode(mode, this->period, this->flashes, this->wait);
}


void led::setMode(mode_t mode, uint32_t period) {
	setMode(mode, period, this->flashes, this->wait);
}


void led::setMode(mode_t mode, uint32_t period, int flashes) {
	setMode(mode, period, flashes, this->wait);
}


void led::setMode(mode_t mode, uint32_t period, int flashes, uint32_t wait) {
	timer = MILLIS;
	this->mode    = mode;
	this->period  = period;
	this->flashes = flashes;
	this->wait    = wait;
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
void led::setOff() {
	setMode(STOP);
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  
void led::phaseInvert() {
	timer += period / 2;
}


void led::ledInit(int ledPin, int pwmMax) {
	this->ledPin  = ledPin;
	this->pwmMax  = pwmMax;
	this->mode    = mode;
	this->period  = 1000;
	this->flashes = 1;
	this->wait    = 0;

	timer = 0;
	duty  = 0;
	
	pinMode(ledPin, OUTPUT);
}
