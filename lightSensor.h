#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include "Arduino.h"
#include "led.h"

enum track_t {
  BLK_TK, // TK for "track"
  RED_TK,
  BLU_TK,
  YLW_TK,
  ERR_TK,
};


enum sensor_t {
  RED_SENS,
  BLU_SENS
};


class lightSensor {
  public:
    lightSensor(int sensor, int red, int blu);   // Constructor
    void loop();
    track_t getCurTrack();
    void detectTrack();            // All this does is report the current detected colors
    void calcDeltaV(sensor_t clr); // Find the differrence between the new voltage and old voltage
  
  private:
    led redLed;
    led bluLed;
    
    const   int RED_THRESH = 750;
    const   int BLU_THRESH = 800;
    const   int BLK_THRESH = 900;
    const   unsigned long BLINK_PERIOD = 128;   // milliseconds
    int     ledPins[2];
    int     duties[2];
    int     SENSOR;
    track_t curTrack;
    int     curVolt[2];
    int     deltaVolt[2];
};

#endif
