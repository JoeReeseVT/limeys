#ifndef BOTWIFI_H
#define BOTWIFI_H


#include <Arduino.h>
#include <WiFiNINA.h>

enum status_t {
    ERR, // message holds error
    VLD, // message holds valid data
    UNK  // message data is not valid
};

class botWifi {
    public:
        void setup();
        void printWifiStatus();
        void POST(String hexIdLocal, String hexIdRemote, String message);
        void GET(String hexIdLocal, String hexIdRemote);
        status_t parseMessage(char c);
        void shutdown();
        
    private:
        const char * ssid;
        const char * pass;
        const char * server;
        WiFiClient client;
        status_t msgStatus;
        String message;
};


#endif
