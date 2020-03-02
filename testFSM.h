/* Test function for the part 1A state machine.
 
 * This was originally written using the botUI class, which has since been
 * deprecated. Instead it emulates the original behavior using the newer
 * led class.
 *
 * The test consists of reading inputs from switches/buttons and lighting up
 * different colored LEDs in response to them. State is tracked using the 
 * state_t enumerated type. The actual definition/description of the state
 * machine is arbitrary; the point is just to demonstrate the concept.
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#ifndef TESTFSM_H
#define TESTFSM_H


#include <Arduino.h>
#include "led.h"


/* Pin declarations */
int ledRedPin    = 12,
    ledOrangePin = 9,
    ledGreenPin  = 10,
    ledBluePin   = 11,
    switchPin    = 6,   
    buttonPinA   = 7, 
    buttonPinB   = 8, 
    buttonPinC   = 9;


led red(ledRedPin);
led orange(ledOrangePin);
led green(ledGreenPin);
led blue(ledBluePin);


/* Parameter for number of flashes in DIAG mode */
int numProbs = 5;


/* Declare types for the FSM */
enum state_t {
	OFF,
	STBY,
	RUN,
	SLP,
	DIAG
} state = OFF; // Makes a globabl called state, init. to OFF


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void testFSM() {
	switch (state) {
	
		// no leds on
		case OFF:
			if (digitalRead(switchPin)) {
				state = STBY;
				ledStby();
			}
			break;
		
		// can move to run, sleep, or off state
		case STBY:
			if (not digitalRead(switchPin)) {
				state = OFF;
				allStop();
			} else if (not digitalRead(buttonPinA)) {
				state = RUN;
				ledRun();
			} else if (not digitalRead(buttonPinB)) {
				state = SLP;
				ledSlp();
			} else
				ledStby();
			break;
		
		// run state solid green led
		// can move to sleep, diagnostic, or off state
		case RUN:
			if (not digitalRead(switchPin)) {
				state = OFF;
				allStop();
			} else if (not digitalRead(buttonPinB)) {
				state = SLP;
				ledSlp();
			} else if (not digitalRead(buttonPinC)) {
				state = DIAG;
				ledDiag(numProbs);
			} else
				ledRun();
			break;
		
		// sleep state breathing blue led
		// can move to run state or off state
		case SLP:
			if (not digitalRead(switchPin)) {
				state = OFF;
				allStop();
			} else if (not digitalRead(buttonPinA)) {
				state = RUN;
				ledRun();
			} else
				ledSlp();
			break;
		
		// diagnostic state blinks led for number of problems
		// can only move to off state
		case DIAG:
			if (not digitalRead(switchPin)) {
				state = OFF;
				allStop();
			} else
				ledDiag(numProbs);
			break;
			
	} // switch
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void allStop() {
	red.setOff();
	orange.setOff();
	blue.setOff();
	green.setOff();
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ledStby() {
	allStop();
	red.setMode(BLINK, 1000);
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ledRun() {
	allStop();
	green.setMode(SOLID);
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ledSlp() {
	allStop();
	blue.setMode(PULSE, 1000);
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ledDiag(int numProbs) {
	allStop();
	orange.setMode(FLASH, 300, numProbs, 1000);
}


#endif
