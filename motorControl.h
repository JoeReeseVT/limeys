/*
 * motorControl class interface
 *
 * Given a speed (0-255) and direction of rotation (CW or CCW), output
 * proper signals to an L293D H-Bridge IC for controlling a DC motor.
 *
 * tgtPwms
 *     The desired (target) PWM value for each pin
 *
 * curPwms
 *     What PWM value is actually being driven at the moment
 *
 * deltas
 *     Difference b/t current tgtPwm value and the prev one
 *
 * curSpin
 *     Are we currently trying to go forward or backward?
 *
 * NOTE
 *     Pin numbers should be given in ther order {FWD, REV}, where FWD
 *     indicates the pin that moves the wheel forward when driven HIGH,
 *     and likewise for REV.
 */

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H


/*
 * Forward output corresponds to the pin that pushes that motor forward
 * e.g. the motor on the starboard side has clockwise being forward
 */
enum spin_t {
    FWD,
    REV
};


class motorControl {
    public:
        /* Instantiating a motor without scaling value is a deprecated feature */
        //motorControl(int fwdPin, int revPin);
        motorControl(int fwdPin, int revPin, float scalar);

        void loop();

        void setVelocity(int speed, spin_t spin);
        void halt();

    private:
        void initMotor(int fwdPin, int revPin, float scalar);

        const uint32_t RAMP_TIME = 5;  // ms to go from speed A to speed B

        uint32_t accelTimer;

        spin_t spin;

        float scalar;  // Usually 1.0

        int fwdPin,    revPin,
            tgtPwmFwd, tgtPwmRev,
            curPwmFwd, curPwmRev,
            deltaFwd,  deltaRev;
};


#endif
