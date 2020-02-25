#ifndef TESTPATHFOLLOW_H
#define TESTPATHFOLLOW_H

#include "Arduino.h"
#include "driveControl.h"
#include "lightSensor.h"
#include <limits.h> // for ULONG_MAX

const int MTR_L_PINS[] = {4, 5};
const int MTR_R_PINS[] = {2, 3};

lightSensor  botSense(A0, 12, 11);
driveControl botDrive(MTR_L_PINS, MTR_R_PINS);

/* SCRIPT:
 * Start forward on black
 * When you hit blue, turn about 90 degrees right (about 1 sec)
 * When you hit yellow, turn a little right
 * When you hit red, stop
 * * * * * * * * * * * * * * * * * * * */
void pathFollowTest() {
  static int testNum = 0;

  botDrive.loop();
  botSense.loop();

  switch (testNum) {

    case 0: // 5-second stop
      botDrive.stop(5000);
      testNum++;
      break;
    
    case 1: // Go forward until you hit blue
      botDrive.forward(ULONG_MAX, 45);
      if (botSense.detectTrack() == BLU_TK) {
        botDrive.stop();
        testNum++;
      }
      break;    
        
    case 2: // Turn 90 deg right
      botDrive.turnRight(1000, 70);
      testNum++;
      break;
      
    case 3: // Forward until yellow, then stop
      botDrive.forward(ULONG_MAX, 45);
      if (botSense.detectTrack() == YLW_TK) {
        botDrive.stop();
        testNum++;
      }
      break;
      
    case 4: // Turn a little right
      botDrive.turnRight(250, 70); // DBG TEST THIS!!
      testNum++;
      break;
      
    case 5: // Forward till red, then stop FINALLY
      botDrive.forward(ULONG_MAX, 45);
      if (botSense.detectTrack() == RED_TK) {
        botDrive.stop();
        testNum++;
      }
      break;
      
    default:
      ; // NULL
      break;

  } // switch
}

#endif
