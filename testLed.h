/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TESTLED_H
#define TESTLED_H

#include <Arduino.h>
#include "led.h"

extern uint32_t MILLIS;


int ledPin = 13; 

led l(ledPin, 127);


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void testLed() {
    static uint32_t timer = MILLIS;
	static bool     init  = true;
	if (init) {
		l.setMode(SIGNAL, 100, 5);
		init = false;
	}
		
    if (MILLIS - timer >= 3000) {
        timer = MILLIS;
        l.setMode(SIGNAL, 100, 5); // 500 ms period, 3 flashes
    }

    l.loop();
}


#endif
