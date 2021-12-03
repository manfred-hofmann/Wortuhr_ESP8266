//******************************************************************************
// OpenWeather.h - Get weather data from OpenWeather
//******************************************************************************

#ifndef OPENWEATHER_H
#define OPENWEATHER_H

#include <Arduino_JSON.h>
#include <ESP8266WiFi.h>
#include "Configuration.h"
#include <TimeLib.h>

class OpenWeather
{
public:
    OpenWeather();
    ~OpenWeather();

    String owfehler = "";
    String description = "";
    String weathericon1 = "";
    String weathericon2 = "";
    uint16_t weatherid1 = 0;
    uint16_t weatherid2 = 0;
    double temperature = 0;
    double windspeed = 0;
    uint8_t humidity = 0;
    uint8_t clouds = 0;
    uint16_t pressure = 0;
    time_t sunrise;
    time_t sunset;

    uint16_t getOutdoorConditions(String location, String apiKey);

private:

};

#endif
