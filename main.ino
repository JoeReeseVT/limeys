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
#include "config.h"

extern uint32_t MILLIS;

#include "testPathFollow.h"
#include "testBrightSensor.h"
#include "thermistor.h"


/*
 *  Select which bot this is:
 *      1: Thermistor start, path follow, sends POST message at end of path
 *      2: Receive BOT_1's message, flashlight tracking, POST at end of path
 *      3: Receive BOT_2's message, Go Beyond demo
 */
#define BOTNUM 1


/* High baud rate -> fast printing, to minimize timing impact */
void setup() {
    Serial.begin(115200);

    /* Make sure Serial is started before anything else tries to execute */
    while (not Serial) {;}

    #if BOTNUM == 1
    /* Loop until thermistor reaches required temperature */
    {
        extern const int thermPin;
        extern const int thermLedPin;
        extern const int thermDefaultThresh;

        thermistor thermObject(thermPin, thermLedPin, thermDefaultThresh);
        while (not thermObject.loop()) {;}
    }

    #elif BOTNUM == 2
    /* Set up wifi */
    // STUB

    /* Loop until we receive the correct message from BOT 1 */
    // STUB

    #elif BOTNUM == 3
    /* Set up wifi */
    // STUB

    /* Loop until we receive the correct message from BOT 2 */
    // STUB

    #endif
} 

/* Update MILLIS and call any test function(s) */
void loop() {
    MILLIS = micros() / 1000;

    static int state = 0;

    switch (state) {

        #if BOTNUM == 1
        case 0:
            if (testPathFollow()) { state = 1; }
            break;
        case 1:
            // STUB: SEND POST FOR COLE/MELISSA TO PICK UP
            break;

        #elif BOTNUM == 2
        case 0:
            if (testBrightSensor()) { state = 1; }
            break;
        case 1:
            // STUB: SEND POST FOR MELVIN/ALE
            break;

        #elif BOTNUM == 3
        case 0:
            testGoBeyond();
            break;

        #endif

        default:
            {;}
    }
}
