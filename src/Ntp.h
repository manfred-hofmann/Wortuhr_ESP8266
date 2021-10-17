//******************************************************************************
// Ntp.h - Get UTC time from NTP
//******************************************************************************

#ifndef NTP_H
#define NTP_H

#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <WiFiUDP.h>

class Ntp
{
public:
    Ntp();
    ~Ntp();

    time_t getTime(char* server);

private:

};

#endif
