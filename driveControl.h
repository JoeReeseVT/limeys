#ifndef PATHFOLLOW_H
#define PATHFOLLOW_H
#include "Arduino.h"
#include "motorControl.h"

class driveControl {
  public:
 	  driveControl(const int L_PINS[2], const int R_PINS[2]); 
  	void loop();
  	void turnLeft(unsigned long time, int speed);
  	void turnRight(unsigned long time, int speed);
  	void forward(unsigned long time, int speed);
  	void reverse(unsigned long time, int speed);
  	void stop();
    void stop(unsigned long time);
  	bool getIsMoving();
  
  private:
    // spd0 = left, spd1 = right, dir0 = left, dir1 = right
    void move(unsigned long time, int spd0, int spd1, spin_t dir0, spin_t dir1); 
  	bool isMoving;
    int state;
  	unsigned long delay;
  	unsigned long timer;
  	int spd[2];
	  spin_t dir[2];
    motorControl leftMotor;
    motorControl rightMotor;
};
#endif
