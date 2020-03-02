/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H


#include <Arduino.h>
#include "led.h"


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
enum track_t {
	BLK_TK,
	RED_TK,
	BLU_TK,
	YLW_TK,
	ERR_TK,
};


class lightSensor {
	public:
		lightSensor(int sensor, int red, int blu);

		void loop();
		
		track_t detectTrack();
	
	private:
		void measureRed();
		void measureBlue();

		const uint32_t BLINK_PERIOD = 128; // milliseconds
		
		const int RED_THRESH = 620,
		          BLU_THRESH = 470,
		          YR_THRESH  = 450,
		          YB_THRESH  = 390,
		          BLK_THRESH = 800;

		track_t curTrack;
		
		led red, blue;

		int sensorPin,
		    redDuty, blueDuty,
		    redVoltage, blueVoltage;
};


#endif
