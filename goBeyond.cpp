#include <Arduino.h> 
#include <SPI.h> 
#include <WiFiNINA.h> 

#include "goBeyond.h"
#include "arduino_secrets.h"
#include "config.h"

extern const int   mtrLeftFwdPin;
extern const int   mtrLeftRevPin;
extern const int   mtrRightFwdPin;
extern const int   mtrRightRevPin;

// Auxiliary variables to store the current output state
String mtrLeftFwdState = "off";
String mtrLeftRevState = "off";
String mtrRightFwdState = "off";
String mtrRightRevState = "off";

String fwdState = "off";
String revState = "off";
String leftState = "off"; 
String rightState = "off"; 

// Variable to store the HTTP request
WiFiServer server(80); 

void goBeyond::setup() {
  ssid = SECRET_SSID; 
  password = SECRET_PASS; 

  currentTime = millis(); 
  previousTime = 0; 

  Serial.begin(115200); 

  motorSetup(); 
  wifiSetup(); 
}

// Initialize the output variables as outputs
void goBeyond::motorSetup() {    
  pinMode(mtrLeftFwdPin,OUTPUT);
  pinMode(mtrLeftRevPin,OUTPUT);
  pinMode(mtrRightFwdPin,OUTPUT);
  pinMode(mtrRightRevPin,OUTPUT);

  digitalWrite(mtrLeftFwdPin,LOW);
  digitalWrite(mtrLeftRevPin,LOW);
  digitalWrite(mtrRightFwdPin,LOW);
  digitalWrite(mtrRightRevPin,LOW);
}

// Initializes the WiFi settings
void goBeyond::wifiSetup() {
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

// Enables or disables an action based on the button
void goBeyond::adjustAction(String header) {
  if (header.indexOf("off") >= 0) {
    disableAction(header); 
  } else if (header.indexOf("on") >= 0) {
    enableAction(header); 
  }
}

void goBeyond::disableAction(String header) {
  if (header.indexOf("GET /Forward/") >= 0) {
    Serial.println("GPIO 10 and 5 off");
    fwdState = "off";
    digitalWrite(mtrLeftRevPin, LOW);
    digitalWrite(mtrRightFwdPin, LOW); 
  } else if (header.indexOf("GET /LeftTurn/") >= 0) {
    Serial.println("GPIO 9 and 5 off");
    leftState = "off";
    digitalWrite(mtrLeftFwdPin, LOW);
    digitalWrite(mtrRightFwdPin, LOW);
  } else if (header.indexOf("GET /Reverse/") >= 0) {
    Serial.println("GPIO 9 and 6 off");
    revState = "off";
    digitalWrite(mtrLeftFwdPin, LOW);
    digitalWrite(mtrRightRevPin, LOW);
  } else if (header.indexOf("GET /RightTurn/") >= 0) {  //Backwards
    Serial.println("GPIO 10 and 6 on");
    rightState = "off";
    digitalWrite(mtrLeftRevPin, LOW);
    digitalWrite(mtrRightRevPin, LOW);
  }
}

void goBeyond::enableAction(String header) {
  if (header.indexOf("GET /Forward/") >= 0) {
    Serial.println("GPIO 10 and 5 off");
    fwdState = "on";
    digitalWrite(mtrLeftRevPin, HIGH);
    digitalWrite(mtrRightFwdPin, HIGH); 
  } else if (header.indexOf("GET /LeftTurn/") >= 0) {
    Serial.println("GPIO 9 and 5 on");
    leftState = "on";
    digitalWrite(mtrLeftFwdPin, HIGH);
    digitalWrite(mtrRightFwdPin, HIGH);
  } else if (header.indexOf("GET /Reverse/") >= 0) {
    Serial.println("GPIO 9 and 6 off");
    revState = "on";
    digitalWrite(mtrLeftFwdPin, HIGH);
    digitalWrite(mtrRightRevPin, HIGH);
  } else if (header.indexOf("GET /RightTurn/") >= 0) {  //Backwards
    Serial.println("GPIO 10 and 6 on");
    rightState = "on";
    digitalWrite(mtrLeftRevPin, HIGH);
    digitalWrite(mtrRightRevPin, HIGH);
  }
}

// Responsible for how the server is displayed 
void goBeyond::displayServer(WiFiClient client) {
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  // CSS to style the on/off buttons 
  // Feel free to change the background-color and font-size attributes to fit your preferences
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #417DC1; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #8B4513;}</style></head>");
  
  client.println("<body><h1>Corbeau & Smaragdine Junior Design Team</h1>");

  displayAction(client);

  client.println("</body></html>");
  client.println();
}

void goBeyond::displayAction(WiFiClient client) {
  client.println("<p>Drive Forward - State " + fwdState + "</p>");     
  if (fwdState=="off") {
    client.println("<p><a href=\"/Forward/on\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("<p><a href=\"/Forward/off\"><button class=\"button button2\">OFF</button></a></p>");
  } 
  client.println("<p>Turn Left - State " + leftState + "</p>");     
  if (leftState=="off") {
    client.println("<p><a href=\"/LeftTurn/on\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("<p><a href=\"/LeftTurn/off\"><button class=\"button button2\">OFF</button></a></p>");
  }
  client.println("<p>Turn Right - State " + rightState + "</p>");
  if (rightState=="off") {
    client.println("<p><a href=\"/RightTurn/on\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("<p><a href=\"/RightTurn/off\"><button class=\"button button2\">OFF</button></a></p>");
  } 
  client.println("<p>Drive in Reverse - State " + revState + "</p>");     
  if (revState=="off") {
    client.println("<p><a href=\"/Reverse/on\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("<p><a href=\"/Reverse/off\"><button class=\"button button2\">OFF</button></a></p>");
  }
}

void goBeyond::loop() {
  WiFiClient client = server.available(); 

  if (client) {
     currentTime = millis(); 
     previousTime = currentTime;

     Serial.println("New Client.");         
     String currentLine = "";                
     while (client.connected() && currentTime - previousTime <= timeoutTime) {  
        currentTime = millis();
        if (client.available()) {             
          char c = client.read();             
          Serial.write(c);                   
          header += c;
          if (c == '\n') {                    
            if (currentLine.length() == 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();

              adjustAction(header);
              displayServer(client); 
         
              break;
            } else { 
              currentLine = "";
            }
          } else if (c != '\r') {  
            currentLine += c;      
          }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
