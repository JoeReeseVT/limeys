const uint8_t TL = 9;
const uint8_t BL = 11;
const uint8_t TR = 10;
const uint8_t BR = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(TL, OUTPUT);
  pinMode(BL, OUTPUT);
  pinMode(TR, OUTPUT);
  pinMode(BR, OUTPUT);
  
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
}

void loop() {
  String str;
  int a, b, c, d;
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    str = Serial.readString();
    
    a = (str.substring(0, 3)).toInt();
    b = (str.substring(4)).toInt();
    if(a) {
      d = 1;
    } else
      d = 0; 
    
    if(b) {
      c = 1;
    } else
      c = 0; 
    Serial.print("CW: ");
    Serial.println(a);
    Serial.print("CCW: ");
    Serial.println(b);
    Serial.println();
    
    
  }
  analogWrite(TL, 255 - a); // on
  analogWrite(TR, 255 - b); // off
  digitalWrite(BL, c); // off
  digitalWrite(BR, d); // on
}
