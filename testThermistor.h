/*
 *
 */

#ifndef TESTTHERMISTOR_H
#define TESTTHERMISTOR_H

#include <Arduino.h>
#include <limits.h>  // for ULONG_MAX

const int  sensorPin      = A5;
const int  outLedPin      = 7;

int currThermValue;
float currThermVoltage;
float firstThermVoltage;
float thermThreshold = 0.05; // (V)

void testThermistor() {

	//Init
	pinMode(sensorPin, INPUT_PULLUP);
	pinMode(outLedPin, OUTPUT);

  //Save first value
	currThermValue = analogRead(sensorPin);
	firstThermVoltage = currThermValue * (5.0 / 1023);

  //Loop, checking values
  while(true)
  {
    currThermValue = analogRead(sensorPin);
    currThermVoltage = currThermValue * (5.0 / 1023);
    
    if ((currThermVoltage - firstThermVoltage) > thermThreshold)
    {
      digitalWrite(outLedPin, HIGH);
    }
  }

}

#endif
