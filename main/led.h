/*
 *
 *
 */

#ifndef LED_H
#define LED_H


#include <Arduino.h>


/*
 * Enumerates the different kinds of patterns for LED control.
 */
enum mode_t {
    BLINK,  // Simple ON/OFF cycle
    FLASH,  // Blink a certain number of times, pause, then repeat
    PULSE,  // Gradually 'breathe' ON/OFF
    SOLID,  // Continuous ON
    STOP    // Continuous OFF
};


class led {
    public:
        led(int ledPin);
        led(int ledPin, int pwmMax);

        void loop();

        bool isOn();
        void setMode(mode_t mode);
        void setMode(mode_t mode, uint32_t period);
        void setMode(mode_t mode, uint32_t period,
                     int flashes, uint32_t wait);
        void setOff();
        void phaseInvert();

    private:
        void ledInit(int ledPin, int pwmMax);

        uint32_t period;
        uint32_t timer;
        uint32_t wait;

        mode_t mode;

        int ledPin;
        int pwmMax;
        int flashes;
        int duty;
};


#endif
