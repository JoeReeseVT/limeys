
const uint8_t REDLED   = 2;
const uint8_t GREENLED = 3;
const uint8_t BLUELED  = 4;
const uint8_t ORANGE   = 5;
const uint8_t SWCH0    = 6;
const uint8_t BTN[3]   = {7, 8, 9}; 
int brightness = 0;
int state = 0;
const int OFF  = 0;
const int STBY = 1;
const int RUN  = 2;
const int SLP  = 3;
const int DIAG = 4;

const unsigned long DEBOUNCE_DELAY = 5; // milliseconds
unsigned long debounceTimer = 0;

void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i <= 5; i++)
    pinMode(i, OUTPUT); // setup LED pins to output
  for (int k = 6; k <= 7; k++)
    pinMode(k, INPUT_PULLUP); // setup pins to pull up
  allOff();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  stateMachine();
}

#if 0
void switchISR_() {
  static const unsigned long DELAY = 5; // ms
  static unsigned long timer = 0;

  static bool curState;
  static bool prvState = false;
  static bool output;

  curState = digitalRead(pin);

  if (curState ^ prvState)
    timer = millis();
   
  if (millis() - timer >= DELAY)
    output = curState;   
  
  prvState = curState;

  return output;
}
#endif

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
    case STBY: 
      if (not digitalRead(SWCH0)) {
        state = OFF;
        allOff();
      } else if (not digitalRead(BTN[0])) {
        state = RUN;
        ledRun();
      }else if (not digitalRead(BTN[1])) {
        
      } else 
        ledStby(); 
      break;
    // run state solid green led
    case RUN:
      if (not digitalRead(SWCH0)) {
        state = OFF;
        allOff();
      else
      }
      break;
    case SLP:
      if (not digitalRead(SWCH0)) {
        state = OFF;
        allOff();
      }
  }
}

void allOff() {
  for (int i = 2; i < 5; i++)
    analogWrite(i, 0);
}
void ledStby() {
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
  analogWrite(REDLED, 0); // turn off green led
  analogWrite(GREENLED, 127); // 50% duty cycle
}
