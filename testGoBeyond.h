#ifndef TESTGOBEYOND_H
#define TESTGOBEYOND_H

#include <Arduino.h>
#include "goBeyond.h"

goBeyond connection; 

void testGoBeyond() { 
  connection.loop(); 
}

#endif
