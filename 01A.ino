// port constant declorations
const uint8_t NONE     = 1; // allOffExcept(NONE) to turn all leds off
const uint8_t REDLED   = 2; // red led port
const uint8_t GRNLED   = 3; // green led port
const uint8_t BLUELED  = 4; // blue led port
const uint8_t ORNGLED  = 5; // orange led port
const uint8_t SWCH0    = 6; // switch port
const uint8_t BTN[3]   = {7, 8, 9}; // array of button ports

// for diagnostic mode
int numProbs = 5;

// state variable declorations
int state = 0;
const int OFF  = 0;
const int STBY = 1;
const int RUN  = 2;
const int SLP  = 3;
const int DIAG = 4;

const unsigned long DEBOUNCE_DELAY = 5; // milliseconds
unsigned long debounceTimer = 0;

void setup() {
  for (int i = 2; i <= 5; i++)
    pinMode(i, OUTPUT); // setup LED pins to output
  for (int k = 6; k <= 9; k++)
    pinMode(k, INPUT_PULLUP); // setup pins to pull up
  allOffExcept(NONE);
}

void loop() {
  stateMachine();
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
    // standby state blinking red led
    // can move to run, sleep, or off state
    case STBY: 
      if (not digitalRead(SWCH0)) {
        state = OFF;
        allOffExcept(NONE);
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
        allOffExcept(NONE);
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
        allOffExcept(NONE);
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
        allOffExcept(NONE);
      } else 
        ledDiag(numProbs);
      break;
  }
}

void allOffExcept(uint8_t pinOn) { // pinOn is the port for the led in use
  for (int i = 2; i < pinOn; i++)
    analogWrite(i, 0);

  for (int k = pinOn + 1; k < 5; k++)
    analogWrite(k, 0);
}
void ledStby() {
  allOffExcept(REDLED);
  static unsigned long timer = 0;
  static const unsigned long HALF_CYCLE = 500; // milliseconds
  static bool isOn = true;
  
  if (millis() - timer >= HALF_CYCLE) {
    timer = millis();
    isOn = not isOn;
  }
  
  analogWrite(REDLED, 127 * isOn); // 50% duty cycle
}

void ledRun() {
  allOffExcept(GRNLED);
  analogWrite(GRNLED, 127); // 50% duty cycle
}

void ledSlp() {
  allOffExcept(BLUELED);
  
  static unsigned long timer = 0;
  static const unsigned long DELAY_TIME = 75; // milliseconds
  static unsigned long fadeAmount = 4;
  static uint8_t brightness = 0;

  // delay
  if (millis() - timer >= DELAY_TIME) {
    timer = millis();
    brightness = brightness + fadeAmount;
    // reverse direction of count
    if (brightness < 4 || brightness >= 127) {
    fadeAmount = -fadeAmount;
    }
  }
  
  analogWrite(BLUELED, brightness);
}

// blinks led for "numProbs" number of times
// then turns off for a period of time
// then repeats
void ledDiag(int numProbs) {
  allOffExcept(ORNGLED);
  static unsigned long timer[2] = {0, 0};
  static const unsigned long BLINK = 300; // milliseconds
  static const unsigned long SOLID = BLINK * (2 * numProbs); // milliseconds
  static bool isOn    = true;
  static bool isOff = true;
  
  // toggles if led is off or blinking
  if (millis() - timer[0] >= SOLID) {
    timer[0] = millis();
    isOff = not isOff;
  }
  
  if (not isOff) {
    // toggles led in blink mode
    if (millis() - timer[1] >= BLINK) {
      timer[1] = millis();
      isOn = not isOn;
    }
    analogWrite(ORNGLED, 127 * isOn); // 50% duty cycle
  } else
    analogWrite(ORNGLED, 0); // off when not blinking
}
