#include "driveControl.h"
#include "Arduino.h"

driveControl::driveControl(const int L_PINS[2], const int R_PINS[2]) 
  : leftMotor(L_PINS, 1.2), rightMotor(R_PINS, 1.0) {
  isMoving = false;
  state = 0;
  delay = 0;
  timer = 0;
  spd[0] = 0;
  spd[1] = 0;
  dir[0] = FWD;
  dir[1] = FWD;
}

void driveControl::loop() {
  leftMotor.loop();
  rightMotor.loop();
  
  switch (state) {
    /* stopped */
    case 0:
      leftMotor.setVelocity(0, dir[0]);
      rightMotor.setVelocity(0, dir[1]);
    break;
		
    /* moving */
    case 1:
      leftMotor.setVelocity(spd[0], dir[0]);
      rightMotor.setVelocity(spd[1], dir[1]);
      if (millis() - timer >= delay) {
        isMoving = false;
        state = 0;
      }
  } //switch
}
  
void driveControl::stop() {
  state = 0;
  delay = 0;
  isMoving = false;
}
void driveControl::stop(unsigned long time) {
  move(time, 0, 0, FWD, FWD);
}
void driveControl::turnLeft(unsigned long time, int speed) {
  move(time, speed, speed, REV, FWD);
}
void driveControl::turnRight(unsigned long time, int speed){
  move(time, speed, speed, FWD, REV);
}
void driveControl::forward(unsigned long time, int speed) {
  move(time, speed, speed, FWD, FWD);
} 
void driveControl::reverse(unsigned long time, int speed) {
  move(time, speed, speed, REV, REV); 
}
 void driveControl::move(unsigned long time, int spd0, int spd1, spin_t dir0, spin_t dir1) {
  if (!isMoving) {
    timer    = millis();
    isMoving = true;
    state    = 1;
    delay    = time;
    spd[0]   = spd0;
    spd[1]   = spd1;
    dir[0]   = dir0;
    dir[1]   = dir1;
  }
 }

bool driveControl::getIsMoving() {
  return isMoving;
  }
