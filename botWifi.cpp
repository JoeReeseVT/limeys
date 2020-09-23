/**
 * Wifi Class
 */

 #include <Arduino.h>
 #include "botWifi.h"
 #include <SPI.h>
 #include <WiFiNINA.h>
 #include "arduino_secrets.h"

 void botWifi::setup() {

   ssid = SECRET_SSID;
   pass = SECRET_PASS;
   server = "ee31.ece.tufts.edu"; //TODO - make not hardcoded for email communications?

  //Initialize status
  int status = WL_IDLE_STATUS;
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();
  
  const String DATASTR = "testing";
  
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
  }
}

void botWifi::printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void botWifi::POST(String hexIdLocal, String hexIdRemote, String message){
  String POSTstring = "";
  POSTstring = "POST /" + hexIdLocal + "/" + hexIdRemote + " HTTP/1.1";

  client.println(POSTstring);
  client.println("Host: ee31.ece.tufts.edu");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(message.length());
  client.println();
  client.println(message);
  client.println();
  
}

String botWifi::GET(String hexIdLocal, String hexIdRemote){
  String GETstring = "";
  GETstring = "GET /" + hexIdLocal + "/" + hexIdRemote + " HTTP/1.1";
  
  client.println(GETstring);
  client.println("Host: ee31.ece.tufts.edu");
  client.println("Content-Type: application/x-www-form-urlencoded");

  static String messageIn = "";
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
    messageIn += c;
  }

  String parsedMessage = parseMessage(messageIn);
  return parsedMessage;
}

String botWifi::parseMessage(String messageReceived){
  //STUB
  return messageReceived;
}
