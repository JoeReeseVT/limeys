/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <limits.h>
#include "lightSensor.h"
#include "led.h"

extern uint32_t MILLIS;


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
lightSensor::lightSensor(int sensorPin, int redPin, int bluePin) 
	: red(redPin, 255), blue(bluePin, 255) {
	this->sensorPin = sensorPin;
			
	red.setMode(BLINK, BLINK_PERIOD);
	blue.setMode(BLINK, BLINK_PERIOD);
	blue.phaseInvert();
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void lightSensor::loop() { 
	red.loop();
	blue.loop();

	static uint32_t timer = 0;
	static int quarterWaves = 0;
	
	if (MILLIS - timer >= BLINK_PERIOD >> 2) {
		timer = MILLIS;
		quarterWaves++;
		if (quarterWaves % 2) { // if Odd quarterwave
			red.isOn() ? measureRed() : measureBlue(); 
			detectTrack();

/* DEBUGGING CODE */
#if 0
	if (curTrack == BLU_TK)
		Serial.println("BLUE");
	else if (curTrack == RED_TK)
		Serial.println("RED");
	else if (curTrack == YLW_TK)
		Serial.println("YELLOW");
	else if (curTrack == BLK_TK)
		Serial.println("BLACK");
	else if (curTrack == ERR_TK)
		Serial.println("ERROR");
#elif 0
	Serial.print("Blue volt: ");
	Serial.print(blueVoltage);
	Serial.print("\tRed volt: ");
	Serial.println(redVoltage);
#endif
		}
	}
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
track_t lightSensor::detectTrack() {
		if (redVoltage < YR_THRESH and blueVoltage < YB_THRESH)
			curTrack = YLW_TK;
		else if (redVoltage < RED_THRESH and blueVoltage >= BLK_THRESH)
			curTrack = RED_TK;
		else if (blueVoltage < BLU_THRESH and redVoltage >= BLK_THRESH)
			curTrack = BLU_TK;
		else if (redVoltage > BLK_THRESH and blueVoltage >= BLK_THRESH)
			curTrack = BLK_TK;
		else
			curTrack = ERR_TK;

		return curTrack;
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void lightSensor::measureRed() {
		redVoltage = analogRead(sensorPin);
}


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void lightSensor::measureBlue() {
		blueVoltage = analogRead(sensorPin);
}
