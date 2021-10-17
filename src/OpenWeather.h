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

    String description;
    String weathericon1;
    String weathericon2;
    uint16_t weatherid1;
    uint16_t weatherid2;
    double temperature;
    double windspeed;
    uint8_t humidity;
    uint8_t clouds;
    uint16_t pressure;
    time_t sunrise;
    time_t sunset;

    uint16_t getOutdoorConditions(String location, String apiKey);

private:

};

#endif
