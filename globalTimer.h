/*
 * Global timer variable definition
 *
 * Instead of using millis() directly everywhere, it seems like a good idea
 * to have every module running on the same global count. That way (a) you
 * make sure that everything in one loop cycle agrees about the time, even
 * if the number of milliseconds since the top of the loop has actually
 * changed, (b) you slightly reduce overhead by removing the need for a
 * function call every time millis() is needed (which is frequently!).
 *
 * To use MILLIS in new files, don't #include this file, but do add the 
 * line 'extern uint32_t MILLIS;'
 */

#ifndef GLOBALTIMER_H
#define GLOBALTIMER_H


#include <Arduino.h>


uint32_t MILLIS;


#endif
