/*
 * driveControl class interface
 *  
 * This class instantiates two motorControl objects to be able to
 * coordinate the movement of a two-wheel-drive robot. It declares some
 * shorthand functions to make movement control simpler for the user.
 * 
 * motor{Left|Right}
 *     motorControl object for the each motor
 *
 * speed{Left|Right}
 *     Current speed of each motor (PWM voltage 0-255)
 *
 * dir{Left|Right}
 *     The current direction of motion for each motor, either FWD or REV
 *      
 * duration
 *     Number of milliseconds to perform the given move for
 *
 * timer
 *     Tracks milliseconds since start of the current move
 *
 * isIdle
 *     Whether the previous move has completed. Always set true when
 *     starting a move, set to false when the move's  duration elapses or
 *     halt() is called with no arguments.
 */

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

        motorControl motorLeft;
        motorControl motorRight;
        
        int speedLeft;
        int speedRight;
        
        spin_t dirLeft;
        spin_t dirRight;
                    
        uint32_t duration;
        uint32_t timer;
        
        bool isIdle;
};


#endif
