#ifndef DRIVETEST_H
#define DRIVETEST_H

#include "Arduino.h"
#include "driveControl.h"

const int MTR_L_PINS[] = {4, 5};
const int MTR_R_PINS[] = {2, 3};

driveControl botDrive(MTR_L_PINS, MTR_R_PINS);

void driveTest() {
  static int testNum = 0;

  botDrive.loop();

  switch (testNum) {
    /* Straight FWD */
    case 0:
      if (!botDrive.getIsMoving()) {
        Serial.println("Switching to 1");
        botDrive.stop(500);
        testNum++;
      }
      break;
      
    /* Straight back */
    case 1:
      if (!botDrive.getIsMoving()) {
        Serial.println("Switching to 2");
        botDrive.reverse(1000, 70);
        testNum++;
      }
      break;
    
    case 2:
      if (!botDrive.getIsMoving()) {
        Serial.println("Switching to 3");
        botDrive.stop(500);
        testNum++;
      }
      break;
    
    /* Turn left */
    case 3:
      if (!botDrive.getIsMoving()) {
        Serial.println("Switching to 4");
        botDrive.turnLeft(1000, 70);
        testNum++;
      }
      break;
      
    case 4:
      if (!botDrive.getIsMoving()) {
        Serial.println("Switching to 5");
        botDrive.stop(500);
        testNum++;
      }
      break;
    
    /* Turn right */
    case 5:
      if (!botDrive.getIsMoving()) {
        Serial.println("Switching to 6");
        botDrive.turnRight(1000, 70);
        testNum++;
      }
      break;
      
    case 6:
      if (!botDrive.getIsMoving()) {
        Serial.println("Switching to 7");
        botDrive.stop(500);
        testNum++;
      }
      break;
    case 7:
      if (!botDrive.getIsMoving()) {
        Serial.println("Switching to 0");
        botDrive.forward(1000, 70);
        testNum = 0;
      }

  } // switch
}

#endif
