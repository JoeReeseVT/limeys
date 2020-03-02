#include "led.h"
#include "driveControl.h"
#include "motorControl.h"
#include "lightSensor.h"

//#include "testMotor.h"
//#include "testDrive.h"
//#include "testFSM.h"
#include "testPathFollow.h"


void setup() {
  Serial.begin(9600);
}


void loop() {
//  driveTest();
//  motorTest();
pathFollowTest();
}
