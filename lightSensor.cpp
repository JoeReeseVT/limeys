#include "lightSensor.h"
#include "led.h"

extern unsigned long MILLIS;

#include <limits.h>


lightSensor::lightSensor(int sensor, int red, int blu) 
  : redLed(red, 255), bluLed(blu, 255) {
  SENSOR   = sensor;
      
    redLed.setMode(BLINK, BLINK_PERIOD);
    bluLed.setMode(BLINK, BLINK_PERIOD);
    bluLed.phaseInvert();
    pinMode(25, OUTPUT); // DBG
}

/* There is an array called int duties[2] that can hold pwm values for each pin */
void lightSensor::loop() { 
  redLed.loop();
  bluLed.loop();


  static unsigned long timer = 0;
  static int quarterWaves = 0;
  
  if (MILLIS - timer >= BLINK_PERIOD >> 2) {
    timer = MILLIS;
    quarterWaves++;
    if (quarterWaves % 2) {// if Odd {
      redLed.isOn() ? calcDeltaV(RED_SENS) : calcDeltaV(BLU_SENS); 
 //     digitalWrite(25, !digitalRead(25)); // DBG
      detectTrack();

/*
  static unsigned long toglTimer = 0;
  static unsigned long sensTimer = ULONG_MAX; //BLINK_PERIOD / 2;

  static bool indicator = true; // DBG

  if (MILLIS - toglTimer >= BLINK_PERIOD) {
      toglTimer = MILLIS;
      sensTimer = MILLIS;
  } else if (MILLIS - sensTimer >= BLINK_PERIOD >> 1) {
      redLed.isOn() ? calcDeltaV(RED_SENS) : calcDeltaV(BLU_SENS); 
      detectTrack();
      indicator = not indicator; // DBG
      digitalWrite(25, indicator);
      //analogWrite(8, 255 * indicator); // DBG
      sensTimer = ULONG_MAX;
  }
*/

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
  Serial.print(curVolt[BLU_SENS]);
  Serial.print("\tRed volt: ");
  Serial.println(curVolt[RED_SENS]);
#endif
    }
  }

}


track_t lightSensor::getCurTrack() {
  return curTrack;
}


void lightSensor::detectTrack() { //This will output and int/index number to light up the specific LED
    if (curVolt[RED_SENS] < RED_THRESH )
      curVolt[BLU_SENS] < BLU_THRESH ? curTrack = YLW_TK : curTrack = RED_TK;
    else if (curVolt[BLU_SENS] < BLU_THRESH)
      curTrack = BLU_TK;
    else if (curVolt[RED_SENS] > BLK_THRESH and curVolt[BLU_SENS] > BLK_THRESH)
      curTrack = BLK_TK;
    else
      curTrack = ERR_TK;
}


/* Track moving derivative of the intensity coming into the light sensor
 * * * * * */
void lightSensor::calcDeltaV(sensor_t clr) {
//    int oldVolt    = curVolt[clr];
    curVolt[clr]  = analogRead(SENSOR);
//    deltaVolt[clr] = oldVolt - curVolt[clr]; 
}
