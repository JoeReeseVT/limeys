/*
 *
 *
 */

#ifndef THERMISTOR_H
#define THERMISTOR_H


#include <Arduino.h>

class thermistor{
  public:

    thermistor(int sensorPinIn, int outputPinIn);
  
    void init();
    void loop();
    void checkFirstValue();
    void checkCurrentValue();

  private:

    int sensorPin;
    int outputPin;
    
    int currThermValue;
    float currThermVoltage;
    float firstThermVoltage;
    float thermThreshold;
  
};

#endif
