/* driveControl class interface
 *  
 * Purpose: This class instantiates two motorControl objects to be able to
 *     coordinate the movement of a two-wheel-drive robot. It declares a few
 *     shorthand functions to make movement control simpler for the user.
 * 
 * Data members:
 *     motor[Left|Right] : motorControl object for the each motor
 *     speed[Left|Right] : Current speed of each motor (PWM voltage 0-255)
 *     dir[Left|Right]   : The current direction of motion for each motor,
 *                         either FWD or REV (as per spin_t)
 *      
 *     duration : Number of milliseconds to perform the given move for
 *     timer    : Tracks milliseconds since start of the current move
 *     isIdle   : Whether the previous move has completed. Always set to true 
 *                when starting a move, set to false when the move's duration
 *                elapses or when halt() is called with no arguments.
 *                  
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef DRIVECONTROL_H
#define DRIVECONTROL_H


#include <Arduino.h>
#include "motorControl.h"


class driveControl {
	public:
		driveControl(int mtrLeftFwdPin,  int mtrLeftRevPin,  float scaleLeft,
                     int mtrRightFwdPin, int mtrRightRevPin, float scaleRight); 
		
		void loop();

		bool getIsIdle();
		void forward(uint32_t duration, int speed);
		void reverse(uint32_t duration, int speed);
		void turnLeft(uint32_t duration, int speed);
		void turnRight(uint32_t duration, int speed);
		void halt();
		void halt(uint32_t duration);
		
	private:
		void move(uint32_t duration, int speedLeft, int speedRight, 
		          spin_t dirLeft, spin_t dirRight); 

		motorControl motorLeft,
		             motorRight;
		
		int speedLeft, 
		    speedRight;
		
		spin_t dirLeft, 
		       dirRight;
		       		
		uint32_t duration, 
		         timer;
		
		bool isIdle;
};


#endif
