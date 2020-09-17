#ifndef BOTPINOUT_H
#define BOTPINOUT_H


/* Thermistor module */
const int   thermPin           = A0;
const int   thermLedPin        =  2;
const float thermDefaultThresh =  0.1; // (V)

/* Light sensing module */
const int brightSensePin    =  7;
const int brightSenseLedPin = 12;

/* Motor control pins */
const int mtrSpeed        = 80;  // Motor base speed. Effective max is 255
const int mtrLeftFwdPin   =  9;
const int mtrLeftRevPin   = 10;
const int mtrRightFwdPin  =  5;
const int mtrRightRevPin  =  6;
const float mtrLeftScale  =  1.0;  // NOTE Scaling may change bot-to-bot
const float mtrRightScale =  1.0;

/* Path sensing */
const int pathSensePin = A1;


#endif
