#ifndef PATHFOLLOW_H
#define PATHFOLLOW_H
#include "Arduino.h"

class driveControl {
  public:
 	driveControl();
  	void loop();
  	void turnLeft(unsigned long time);
  	void turnRight(unsigned long time);
  	void forward(unsigned long time, int speed);
  	void reverse(unsigned long time, int speed);
  	void stop()
  	bool getIsMoving()
  
  private:
    void move(unsigned long time, int spd0, int spd1 spin_t dir0, spin_t dir1) // spd0 = left, spd1 = right, dir0 = left, dir1 = right
  	bool isMoving;
    int state;
  	unsigned long delay;
  	unsigned long timer;
  	int spd[2];
	spin_t dir[2];
};
#endif

