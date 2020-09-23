/*
 *
 */

#ifndef TESTWIFI_H
#define TESTWIFI_H

#include <Arduino.h>
#include "botWifi.h"

 //Define constant strings for all of our HEX IDs
 const String MELISSA = "64E4E8B782CC";
 const String KEVIN = "46B426BD88FB";
 const String MELVIN = "D969A9704429";
 const String COLE = "0E229ED13C38";
 const String ALEJANDRO = "981C14F46BD0";
 const String JOE = "20ABD7AE9A5E";

//Declare botWifi object
botWifi connection;

void testWifi(){
  connection.setup();

  //test POST
  connection.POST(MELISSA, COLE, "hello");

  //test GET
  String messageReceived = connection.GET(MELISSA, COLE);
  Serial.println(messageReceived);
}

#endif
