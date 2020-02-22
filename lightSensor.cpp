#include "lightSensor.h"
#include <limits.h>

//lightSensor::lightSensor() {
  
//}

lightSensor::lightSensor(int sensor, int red, int blue) {
  SENSOR   = sensor;
  ledPins[RED_SENS] = red;
  ledPins[BLU_SENS] = blue;
  curTrack = ERR_TK; 
  duties[RED_SENS]  = 0;
  duties[BLU_SENS]  = BLU_PWM;
}

/* There is an array called int duties[2] that can hold pwm values for each pin */
void lightSensor::loop() {
  static       unsigned long toglTimer  = 0;
  static       unsigned long sensTimer  = ULONG_MAX;
  static const unsigned long LED_PERIOD = 500; // milliseconds
  
  if (millis() - toglTimer >= LED_PERIOD) {
      toglTimer = millis();
      sensTimer = millis();
      duties[RED_SENS] = RED_PWM - duties[RED_SENS];
      duties[BLU_SENS] = BLU_PWM - duties[BLU_SENS];
      analogWrite(ledPins[RED_SENS], duties[RED_SENS]);
      analogWrite(ledPins[BLU_SENS], duties[BLU_SENS]);
  } else if (millis() - sensTimer >= LED_PERIOD >> 1) {
      sensTimer = ULONG_MAX;
      duties[RED_SENS] ? calcDeltaV(RED_SENS) : calcDeltaV(BLU_SENS);
  }
  
  detectTrack();

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

  #if 0
  Serial.print("Blue volt: ");
  Serial.print(curVolt[BLU_SENS]);
  Serial.print("\tRed volt: ");
  Serial.println(curVolt[RED_SENS]);
  #endif
  
  #if 0
  if (abs(deltaVolt[BLU_SENS]) > 100 or abs(deltaVolt[RED_SENS]) > 10) {
    Serial.print("Blue delta: ");
    Serial.print(deltaVolt[BLU_SENS]);
    Serial.print("\tRed delta: ");
    Serial.println(deltaVolt[RED_SENS]);
  }
  #endif
}


/* CASES:
 * Black to red:    blue should have small delta, red should have very negative
 * Black to blue:   blue should have negative delta, red should have small delta
 * Black to yellow: blue and red should both have negative delta
 * * * * * * * * * */ 
void lightSensor::detectTrack() { //This will output and int/index number to light up the specific LED
    if (curVolt[RED_SENS] < 500 )
      curVolt[BLU_SENS] < 500 ? curTrack = YLW_TK : curTrack = RED_TK;
    else if (curVolt[BLU_SENS] < 500)
      curTrack = BLU_TK;
    else if (curVolt[RED_SENS] > 800 and curVolt[BLU_SENS] > 800)
      curTrack = BLK_TK;
    else
      curTrack = ERR_TK;
    /*
    if (deltaVolt[RED_SENS] < RED_THRESH and deltaVolt[BLU_SENS] < BLU_THRESH) { // Yellow 
        curTrack = YLW_TK;
    } else if (deltaVolt[RED_SENS] < RED_THRESH and deltaVolt[BLU_SENS] >= BLU_THRESH) {  // Red
        curTrack = RED_TK;
    } else if (deltaVolt[RED_SENS] >= RED_THRESH and deltaVolt[BLU_SENS] < BLU_THRESH) {  // Blue  
        curTrack = BLU_TK;
    } else if (deltaVolt[RED_SENS] >= RED_THRESH and deltaVolt[BLU_SENS] >= BLU_THRESH) { // Neither
        ; // do nothing!
    } else
        curTrack = ERR_TK;
    */
}


/* Track moving derivative of the intensity coming into the light sensor
 * 
 * * * * * */
void lightSensor::calcDeltaV(sensor_t clr) {
    int oldVolt    = curVolt[clr];
    curVolt[clr]  = analogRead(SENSOR);
    deltaVolt[clr] = oldVolt - curVolt[clr]; 
}
