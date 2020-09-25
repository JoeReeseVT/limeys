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
  
    bool loop();

  private:

    int sensorPin;
    int outputPin;
    
    int currThermValue;
    int firstThermValue;
    int thermThreshold;
  
};

#endif
