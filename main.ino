#include "botUI.h"
#include "motorControl.h"

// Pin declarations
const int LED_PINS[] = {7, 8, 9, 10};
const int MTR_L_PINS[] = {2, 3};
const int MTR_R_PINS[] = {4, 6};

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


botUI        myBotUI(LED_PINS, 4);
motorControl leftMotor(MTR_L_PINS);
motorControl rightMotor(MTR_R_PINS);


void setup() {
  for (int k = 6; k <= 9; k++)
    pinMode(k, INPUT_PULLUP); // setup pins to pull up  
}


void loop() {
  stateMachine(); 
  myBotUI.loop();
  leftMotor.loop();
  rightMotor.loop();
}


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
        myBotUI.allStop();
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
        myBotUI.allStop();
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
        myBotUI.allStop();
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
        myBotUI.allStop();
      } else 
        ledDiag(numProbs);
      break;
  } // switch
}


void ledStby() {
  myBotUI.allStop();
  myBotUI.setMode(RED, BLINK, 1000);
}


void ledRun() {
  myBotUI.allStop();
  myBotUI.setMode(GRN, SOLID);
}


void ledSlp() {
  myBotUI.allStop();
  myBotUI.setMode(BLU, PULSE, 1000);
}


void ledDiag(int numProbs) {
  myBotUI.allStop();
  myBotUI.setMode(ORN, FLASH, 300, numProbs, 1000);
}
