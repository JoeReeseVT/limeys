#include "botUI.h"
#include "driveControl.h"
#include "motorControl.h"
#include "lightSensor.h"

//#include "testMotor.h"
//#include "testDrive.h"
//#include "testFSM.h"
#include "testPathFollow.h"


void setup() {
  Serial.begin(9600);
  for (int k = 6; k <= 9; k++)
    pinMode(k, INPUT_PULLUP); // setup pins to pull up
}


void loop() {
//  driveTest();
//  motorTest();
pathFollowTest();
}
