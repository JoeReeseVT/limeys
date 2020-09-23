#ifndef BOTWIFI_H
#define BOTWIFI_H


#include <Arduino.h>
#include <WiFiNINA.h>

class botWifi {
    public:
        void setup();
        void printWifiStatus();
        
    private:
        const char * ssid;
        const char * pass;
        const char * server;
        WiFiClient client;

};


#endif
