#include "led.h"
#include "motorControl.h"
#include "lightSensor.h"
#include "globalTimer.h"

#pragma GCC optimize ("O3")

extern unsigned long MILLIS;

// Pin declarations
const int MTR_L_PINS[] = {4, 5};
const int MTR_R_PINS[] = {2, 3};
const int SENSOR_PIN = A0;
const int SWCH0  = 6; // switch port
const int BTN[3] = {7, 8, 9}; // array of button ports


// For diagnostic mode
int numProbs = 5;


// State variable declarations
enum state_t {
	OFF,
	STBY,
	RUN,
	SLP,
	DIAG
} state = OFF; // Makes a globabl called state, init. to OFF


// CLASS INSTANTIATIONS
led          redTkLed(6, 127);
led          bluTkLed(7, 127);
led          ylwTkLed(8, 127);

motorControl leftMotor(MTR_L_PINS);
motorControl rightMotor(MTR_R_PINS);
lightSensor  myLightSensors(SENSOR_PIN, 12, 11);


void setup() { 
  MILLIS = millis();
//  TESTLED.setMode(BLINK, 500);

	Serial.begin(9600);
	for (int k = 6; k <= 9; k++)
		pinMode(k, INPUT_PULLUP); // setup pins to pull up
}


void loop() {
  MILLIS = micros() / 1000;
  static unsigned long speedLimiter = MILLIS;
  
  if (MILLIS - speedLimiter >= 1) {
  //stateMachine();
  //fsmUI.loop();  

  //leftMotor.loop();
  //rightMotor.loop();

  switch (myLightSensors.getCurTrack()) {
    case RED_TK: 
      ylwTkLed.setOff();
      bluTkLed.setOff();
      redTkLed.setMode(SOLID);
      break;
    case BLU_TK:
      ylwTkLed.setOff();
      bluTkLed.setMode(SOLID);
      redTkLed.setOff();
      break;
    case YLW_TK:
      ylwTkLed.setMode(SOLID);
      bluTkLed.setOff();
      redTkLed.setOff();
      break;
    default:
      ylwTkLed.setOff();
      bluTkLed.setOff();
      redTkLed.setOff();
  } // switch
  
  myLightSensors.loop();
  ylwTkLed.loop();
  bluTkLed.loop();
  redTkLed.loop();
  
  
  //testing();
  } // if
}


void testing() {
	static int testNum = 0;

	switch (testNum) {
		/* Straight FWD */
		case 0:
			leftMotor.setVelocity(70, FWD);
			rightMotor.setVelocity(70, FWD);
			if (wait(1000)) {
				Serial.println("Switching to 1");
        leftMotor.halt();
        rightMotor.halt();
				testNum++;
			}
			break;
			
		/* Straight back */
		case 1:
			if (wait(500)) {
				Serial.println("Switching to 2");
				leftMotor.setVelocity(70, REV);
				rightMotor.setVelocity(70, REV);
				testNum++;
			}
			break;
		
		case 2:
			if (wait(1000)) {
				Serial.println("Switching to 3");
				leftMotor.halt();
				rightMotor.halt();
				testNum++;
			}
			break;
		
		/* Turn left */
		case 3:
			if (wait(500)) {
				Serial.println("Switching to 4");
				leftMotor.setVelocity(70, FWD);
				rightMotor.setVelocity(70, REV);
				testNum++;
			}
			break;
		case 4:
			if (wait(1000)) {
				Serial.println("Switching to 5");
        leftMotor.halt();
        rightMotor.halt();
				testNum++;
			}
			break;
		
		/* Turn right */
		case 5:
			if (wait(500)) {
				Serial.println("Switching to 6");
				leftMotor.setVelocity(70, REV);
				rightMotor.setVelocity(70, FWD);
				testNum++;
			}
			break;
		case 6:
			if (wait(1000)) {
				Serial.println("Switching to 7");
        leftMotor.halt();
        rightMotor.halt();
				testNum++;
			}
			break;
		
		case 7:
			if (wait(500)) {
				Serial.println("Switching to 0");
				testNum = 0;
			}
			break;
	} // switch

}


bool wait(unsigned long delay_ms) {
	static unsigned long  timer = MILLIS;

	if (MILLIS - timer >= delay_ms) {
		timer = MILLIS;
		return true;
	}
	else
		return false;
}









#if 0
// State machine for part 1A
void stateMachine() {
	switch (state) {
	
		// no leds on
		case OFF:
			if (digitalRead(SWCH0)) {
				state = STBY;
				ledStby();
			}
			break;
		
		// can move to run, sleep, or off state
		case STBY:
			if (not digitalRead(SWCH0)) {
				state = OFF;
				fsmUI.allStop();
			} else if (not digitalRead(BTN[0])) {
				state = RUN;
				ledRun();
			} else if (not digitalRead(BTN[1])) {
				state = SLP;
				ledSlp();
			} else
				ledStby();
			break;
		
		// run state solid green led
		// can move to sleep, diagnostic, or off state
		case RUN:
			if (not digitalRead(SWCH0)) {
				state = OFF;
				fsmUI.allStop();
			} else if (not digitalRead(BTN[1])) {
				state = SLP;
				ledSlp();
			} else if (not digitalRead(BTN[2])) {
				state = DIAG;
				ledDiag(numProbs);
			} else
				ledRun();
			break;
		
		// sleep state breathing blue led
		// can move to run state or off state
		case SLP:
			if (not digitalRead(SWCH0)) {
				state = OFF;
				fsmUI.allStop();
			} else if (not digitalRead(BTN[0])) {
				state = RUN;
				ledRun();
			} else
				ledSlp();
			break;
		
		// diagnostic state blinks led for number of problems
		// can only move to off state
		case DIAG:
			if (not digitalRead(SWCH0)) {
				state = OFF;
				fsmUI.allStop();
			} else
				ledDiag(numProbs);
			break;
	} // switch
}


void ledStby() {
	fsmUI.allStop();
	fsmUI.setMode(RED, BLINK, 1000);
}


void ledRun() {
	fsmUI.allStop();
	fsmUI.setMode(GRN, SOLID);
}


void ledSlp() {
	fsmUI.allStop();
	fsmUI.setMode(BLU, PULSE, 1000);
}


void ledDiag(int numProbs) {
  fsmUI.allStop();
	fsmUI.setMode(ORN, FLASH, 300, numProbs, 1000);
}
#endif
