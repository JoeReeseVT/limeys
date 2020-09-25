#ifndef GOBEYOND_H
#define GOBEYOND_H

#include <Arduino.h> 
#include <WiFiNINA.h> 

class goBeyond {
    public:
        void setup(); 
        void loop(); 
        
    private:
        const char* ssid; 
        const char* password;

        String header; 
        
        unsigned long currentTime; 
        unsigned long previousTime; 
        const long timeoutTime = 2000; 

        void motorSetup(); 
        void wifiSetup(); 
        
        void adjustAction(String header);  
        void disableAction(String header); 
        void enableAction(String header); 
        void shutdownAction(); 

        void displayServer(WiFiClient client); 
        void displayAction(WiFiClient client);
};


#endif
