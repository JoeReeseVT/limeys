#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "Arduino.h"


/* Forward output corresponds to the pin that pushes that motor forward
 * e.g. the motor on the starboard side has clockwise being forward
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
enum spin_t {
  FWD, 
  REV
};

/* motorControl class
 * 
 * Purpose: given a speed (0-255) and direction of rotation (CW or CCW), 
 *   output proper signals to an L293D H-Bridge IC for controlling a
 *   single DC motor.
 * 
 * NOTE: Pin numbers should be given in ther order {FWD, REV}, where FWD
 *   indicates the pin that moves the wheel forward when driven HIGH,
 *   and likewise for REV.
 *     
 * Data members:
 *   tgtPwms : The desired (target) PWM value for each pin
 *   curPwms : What PWM value is actually being driven at the moment
 *   deltas  :  Difference b/t current tgtPwm value and the prev one
 *   curSpin : Are we currently trying to go forward or backward?
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class motorControl {
  public:
  	motorControl(const int PINS_ARR[2]);
    void loop();
  	void setVelocity(int spd, spin_t spin);

  private:
    const unsigned long RAMP_TIME  = 5; // ms to go from A to B
 	  unsigned long accelTimer;
  	int PINS[2];
    
  	int    tgtPwms[2];
  	int    curPwms[2];
    int    deltas[2];
  	spin_t curSpin;
};

#endif
