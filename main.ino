/*
 * Tufts University Spring 2020 Junior Design Project, Team Smaragdine
 *
 * This code is to control a small 'Swarmbot' consisting of DC motors,
 * photosensors, hall effect sensors, collision detection switches, and
 * a 2 MHz radio communication system.
 *
 * Notes
 *     The bot's features are divided up into classes. Some classes encompass
 *     others, such as driveControl containing two instances of motorControl.
 *
 *     Each class has three basic elements: a loop() function that executes
 *     repeatedly, state variables that determine what loop() is doing, and
 *     public functions to modify the state.
 *
 *     The main loop() function is simply here to call the loop() functions
 *     of each of the bot's modules. Various test functions have also been
 *     written to verify correct behavior.
 *
 *     The various loop() functions are all kept synchronized by a global
 *     timer MILLIS, which is updated once per main loop(). That way each
 *     loop() is guaranteed to execute in the correct sequence. Without a
 *     global timer, it is possible for the millis() function to roll
 *     over before the end of the main loop() is reached.
 *
 * Known issues
 *     For some reason, the timing seems to be much more consistent when
 *     doing micros() / 1000, rather than millis(). The downside is that
 *     micros() rolls over after about 70 minutes, whereas micros() rolls
 *     over after about 50 days. The risk of timer overflow is ignored here,
 *     as the bot is not expected to perform for more than a few minutes at
 *     a time.
 *
 *     Because of the structure outlined in the notes above, the CPU is
 *     constantly crunching as fast as it can. The number of things that have
 *     to run on each loop() is quite high, and this limits the maximum
 *     frequency of a given function. For example, at the time of writing,
 *     the LEDs in the lightSensor class have a minimum period of about 50 ms.
 *
 *     There's also nothing protecting MILLIS from being modified erroneously,
 *     but given its unique purpose in the program, this is not so heinous.
 */

#include <Arduino.h>
#include "globalTimer.h"

extern uint32_t MILLIS;
extern const int selectionPin;

/* For each test you include, add the corresponding test from loop() */
#include "testMotor.h"
#include "testDrive.h"
#include "testPathFollow.h"
#include "testThermistor.h"
#include "testBrightSensor.h"

#include "testGoBeyond.h"
#include "goBeyond.h"

void (*scriptFunc)(void) = NULL;

/* High baud rate -> fast printing, to minimize timing impact */
void setup() {
    Serial.begin(115200);

    int script = analogRead(selectionPin) / 100;
    
    Serial.print("Executing Script: ");
    
    switch (script) {
        case 10:
            Serial.println("testGoBeyond"); 
            goBeyond connection; 
            connection.setup(); 
            scriptFunc = testGoBeyond; 
            break;
            
        case  9:
            Serial.println("testMotor");
            scriptFunc = testMotor;
            break;
            
        case 8: 
        case 7:
            Serial.println("testDrive");
            scriptFunc = testDrive;
            break;

        case 6: 
        case 5:
            Serial.println("testPathFollow");
            scriptFunc = testPathFollow;
            break;

        case 4:
        case 3:
            Serial.println("testThermistor");
            scriptFunc = testThermistor;
            break;

        case 2:
        case 1:
            Serial.println("testBrightSensor");
            scriptFunc = testBrightSensor;
            break;

        case 0:
        default:
            Serial.println("<NO TEST>");
            scriptFunc = NULL;
    }
}

/* Update MILLIS and call any test function(s) */
void loop() {
    MILLIS = micros() / 1000;
     
    if (scriptFunc != NULL) { scriptFunc(); }
}
