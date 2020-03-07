/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef HALLSENSOR_H
#define HALLSENSOR_H


#include <Arduino.h>


/*
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
enum hallMode_t {
  ACTIVE_HIGH,
  ACTIVE_LOW
};


class hallSensor {
  public:
    hallSensor(int sensorPin, hallMode_t mode);

    void loop();
    
    bool detectField();

    bool getDetected();
  
  private:
    int sensorPin;
    bool detected;
    hallMode_t mode;
};


#endif
