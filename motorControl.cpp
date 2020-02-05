#include <math.h>
#include "Arduino.h"
#include "motorControl.h"


/* Constructor sets direction to FWD and speed to 0
 * and sets pin modes.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
motorControl::motorControl(const int PINS_ARR[2]) {

  for (int i = FWD; i <= REV; i++) {
    PINS[i] = PINS_ARR[i];
    pinMode(PINS[i], OUTPUT);
  }
  setVelocity(0, FWD);
}


/* Speed control: Set the active pin to spd, set the other to 0.
 * If velocity setpoint changes, reset the acceleration ramp timer
 * and update the deltas 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void motorControl::setVelocity(int spd, spin_t spin) {
  if (spin != curSpin or spd != tgtPwms[FWD] and spd != tgtPwms[REV]) {
  	accelTimer = millis();
   	for (int i = FWD; i <= REV; i++)
      deltas[i] = curPwms[i] - tgtPwms[i];
  }
    
  tgtPwms[FWD] = spd * (int)(not curSpin); 
  tgtPwms[REV] = spd * (int)(curSpin);
}


/* Uses a cosine to ramp between one velocity and the next.
 * If deltaT is 0, outputs tgt - (delta / 2) * 2, i.e. just the previous tgt.
 * If deltaT is RAMP_TIME, outputs tgt - 0,       i.e. just the current tgt.
 * Everything in between is handled appropriately.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void motorControl::loop() {
  static unsigned long deltaT;
  deltaT = millis() - accelTimer;

  /*
  if (deltaT <= RAMP_TIME) 
  	for (int i = FWD; i <= REV; i++)
  	  curPwms[i] = tgtPwms[i] - (deltas[i] / 2) 
                   * (cos(deltaT * PI / RAMP_TIME) + 1);
  */

  analogWrite(PINS[FWD], tgtPwms[FWD]);
  analogWrite(PINS[REV], tgtPwms[REV]);
}
