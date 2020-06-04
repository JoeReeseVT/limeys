const uint8_t L1 = 2;
const uint8_t L2 = 3;
const uint8_t R1 = 4;
const uint8_t R2 = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
}

void loop() {
static unsigned long timer = 0;

timer = millis();

if (millis() - timer < 1000)
  setPwm(0,0,0,0);

if (millis() - timer < 1000)
  setPwm(100,0,100,0);

timer = millis();

if (millis() - timer < 500)
  setPwm(0,0,0,0);

if (millis() - timer < 1000)
  setPwm(0,100,0,100);

timer = millis();

if (millis() - timer < 500)
  setPwm(0,0,0,0);
  
timer = millis();

//left?
if (millis() - timer < 1000)
  setPwm(100,0,0,100);

timer = millis();

if (millis() - timer < 500)
  setPwm(0,0,0,0);

timer = millis();

//right?
if (millis() - timer < 1000)
  setPwm(0,100,100,0);
 
if (millis() - timer < 3000)
  setPwm(0,0,0,0);
}

void setPwm(int a, int b, int c, int d) {
 //  String str;
  // send data only when you receive data:
//  if (Serial.available() > 0) {
//    // read the incoming byte:
//    str = Serial.readString();
//     
//    a = (str.substring(0, 3)).toInt();
//    b = (str.substring(4, 7)).toInt();
//    c = (str.substring(8, 11)).toInt();
//    d = (str.substring(12)).toInt();
//    
//    Serial.println("Left: ");
//    Serial.println(a);
//    Serial.println(b);
//    Serial.println("Right: ");
//    Serial.println(c);
//    Serial.println(d);
//    Serial.println();
//    
//    
//  }
  analogWrite(L1, a); // on
  analogWrite(L2, b); // off
  analogWrite(R1, c); // off
  analogWrite(R2, d); // on
}
