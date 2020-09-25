/*
 * driveControl class implementation
 *
 * Notes
 *     Each different movement function is just a shorthand that calls
 *     move() with set arguments. At the moment, a given move() will not
 *     begin until the previous one completes, i.e. if not idle, further
 *     calls to move() will do nothing.
 *
 *     The solution is to first call halt() if we need to move immediately.
 */

#include <Arduino.h>
#include "driveControl.h"

extern uint32_t MILLIS;


/*
 * Initialize data members to sane values. Attach pin numbers to the
 * motorControl objects and instantiate them.
 *
 * mtr{Left|Right}{Fwd|Rev}Pin
 *     Arduino pin number corresp. to FWD/+, REV/- of each motor
 *
 * scale{Left|Right}
 *     Scaling factor for PWM of each motor. Usually one will be 1.0
 *     and the other will be different.
 *
 * Effects
 *     Calls motorControl constructor when instantiating the objects.
 */
driveControl::driveControl(int   mtrLeftFwdPin,  int   mtrLeftRevPin,
                           float scaleLeft,      int   mtrRightFwdPin,
                           int   mtrRightRevPin, float scaleRight)
    : motorLeft(mtrLeftFwdPin,   mtrLeftRevPin,  scaleLeft),
      motorRight(mtrRightFwdPin, mtrRightRevPin, scaleRight) {

    isIdle     = true;
    duration   = 0;
    timer      = 0;
    speedLeft  = 0;
    speedRight = 0;
    dirLeft    = FWD;
    dirRight   = FWD;
}


/*
 * Call the loop() function of each motorControl object to drive correct
 * PWM values etc. Also tracks whether the given move has completed;
 * if so, calls halt() to end the move.
 *
 * Effects
 *     halt() modifies data members
 */
void driveControl::loop() {
    motorLeft.loop();
    motorRight.loop();

    if (not isIdle and MILLIS - timer >= duration) {
        halt();
    }
}


/*
 * Tell whether the most recent valid move has completed.
 *
 * Returns
 *     isIdle, which is false unless a move() is in progress.
 */
bool driveControl::getIsIdle() {
    return isIdle;
}


/*
 * Configure the motorControl state for a desired type of motion.
 *
 * duration
 *     How many milliseconds should this move last for?
 *
 * speed{Left|Right}
 *     Motor PWM will be set to this for the duration
 *
 * dir{Left|Right}
 *     If FWD, speed is applied to the FWD motor pin. If REV, speed
 *     is applied to the REV motor pin.
 *
 * Effects
 *     Resets state values to reflect the situation at the time move()
 *     is called. Also changes states of the motorControl objects by
 *     calling setVelocity().
 */
void driveControl::move(uint32_t duration, int speedLeft, int speedRight,
                        spin_t dirLeft, spin_t dirRight) {
    if (isIdle) {
        timer    = MILLIS;
        isIdle = false;

        this->duration   = duration;
        this->speedLeft  = speedLeft;
        this->speedRight = speedRight;
        this->dirLeft    = dirLeft;
        this->dirRight   = dirRight;

        motorLeft.setVelocity(speedLeft, dirLeft);
        motorRight.setVelocity(speedRight, dirRight);
    }
}


/*
 * When called by the user, trigger the appropriate move().
 *
 * duration
 *     How many milliseconds should this move last for?
 *
 * speed
 *     How fast should the motors spin during this move?
 *
 * Effects
 *     move() modifies data members.
 */
void driveControl::forward(uint32_t duration, int speed) {
    move(duration, speed, speed, FWD, FWD);
}

void driveControl::reverse(uint32_t duration, int speed) {
    move(duration, speed, speed, REV, REV);
}

void driveControl::turnLeft(uint32_t duration, int speed) {
    move(duration, speed, speed, REV, FWD);
}

void driveControl::turnRight(uint32_t duration, int speed){
    move(duration, speed, speed, FWD, REV);
}


/*
 * Instantly stop any motor motion, cancelling any active move.
 *
 * Effects
 *     Resets duration to its initial value, sets isIdle to true. Also
 *     modifies state of the motorControl objects by calling setVelocity().
 */
void driveControl::halt() {
    duration = 0;
    isIdle   = true;

    motorLeft.setVelocity(0, dirLeft);
    motorRight.setVelocity(0, dirRight);
}


/*
 * Halt for a given duration, WITHOUT cancelling the active move.
 *
 * duration
 *     How long to stay halted before the next move is allowed to proceed
 *
 * Effects: move() modifies data members.
 */
void driveControl::halt(uint32_t duration) {
    move(duration, 0, 0, FWD, FWD);
}
