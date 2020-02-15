#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include "Arduino.h"

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
    lightSensor();
    lightSensor(int sensor, int red, int blue);   // Constructor
    void loop();
    void detectTrack();            // All this does is report the current detected colors
    void calcDeltaV(sensor_t clr); // Find the differrence between the new voltage and old voltage
  
  private:
    const   int RED_THRESH = -1;
    const   int BLU_THRESH = -1;
    const   unsigned long BLINK_PERIOD = 500;   // milliseconds
    const   unsigned long WAIT_TIME    = 100;   // milliseconds
    int     ledPins[2];
    int     duties[2];
    int     SENSOR;
    track_t curTrack;
    int     curVolt[2];
    int     deltaVolt[2];
};

#endif
