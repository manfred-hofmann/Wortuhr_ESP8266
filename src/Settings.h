//******************************************************************************
// Settings.h
//******************************************************************************

#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <EEPROM.h>
#include "Colors.h"
#include "Configuration.h"
#include "Languages.h"
#include "Modes.h"

#define SETTINGS_MAGIC_NUMBER 0x12
#define SETTINGS_VERSION 1


class Settings
{
public:
    Settings();
    ~Settings();

    struct MySettings
    {
        uint8_t magicNumber;                          // techn. Zahl 
        uint8_t version;                              // EEPROM Version
        char systemname[30] = {};                     // Systemname der Wortuhr
        boolean useAbc;                               // Automatische Helligkeitsregelung mit dem LDR aktiv
        int16_t brightness;                           // (max./aktuelle) Helligkeit
        uint8_t color;                                // Aktuelle Farbe der LEDs
        uint8_t colorChange;                          // Farbwechsel der LEDs: 0 kein Wechsel, 1: alle 5Min, 2: Stunde, 3: Tag
        uint8_t transition;                           // Transitions siehe Modes.h
        boolean modeChange;                           // AutoModeChange
        boolean itIs;                                 // Anzeige "Es ist"
        boolean alarm1;                               // Alarm1 aktiv
        time_t  alarm1Time;                           // Alarm1 Zeit
        uint8_t alarm1Weekdays;                       // Alarm1 Wochentage
        boolean alarm2;                               // Alarm2 aktiv
        time_t  alarm2Time;                           // Alarm2 Zeit
        uint8_t alarm2Weekdays;                       // Alarm2 Wochentage 
        time_t  nightOffTime;                         // Ausschaltezeit der Uhr
        time_t  dayOnTime;                            // Einschaltezeit der Uhr
        boolean hourBeep;                             // Stundensound: false = kein Sound, true = aktiv
        int16_t volume;                               // Lautstärke:10 - 100
        boolean sprecher;                             // Sprecher: true = vicki, false = hans        
        boolean randomsound;                          // Flag für Zufallssound
        uint8_t weekdaysoundfile[8] = {};             // Soundfilenr pro Tag (0 = Sonntag)
        boolean weekendlater;                         // Amwochenende 2h später lauter
        boolean vickihans24h;                         // Ausgabeformat false:12h true:24h wenn Vicki oder Hans die Stunde ansagen
        char ntphost[50] = {};                        // Zeitserver
        uint8_t corner_color;                         // Aktuelle Farbe der Minuten LEDs
        uint8_t corner_colorChange;                   // Farbwechsel der Minuten LEDs: 0 kein Wechsel, 1: alle 5Min, 2: Stunde, 3: Tag
        uint32_t bg_color;                            // Hintergrundfarbe
        uint8_t  enable_bg_color;                     // Hintergrundfarbe 0 = aus 1 = zeit ein 2 = immer
        char openweatherapikey[35] = {};              // OpenWeather API-Key
        char openweatherlocation[40] = {};            // Standort für OpenWeather z.B.: Baden-Baden,de
        int16_t highscore[9] = {};                    // Highscore Werte
        int16_t standort_hoehe;                       // Höhe über NN
        uint8_t auto_mode_change;                     // Minuten bis zum nächsten AutoModeChange
        boolean ani_sunrise;                          // Sonnenaufgang Ankündigung
        boolean ani_sunset;                           // Sonnenuntergang Ankündigung
        double latitude;                              // Standort Latitude
        double longitude;                             // Standort Longitude
    } mySettings;

    void saveToEEPROM();

private:
    void resetToDefault();
    void loadFromEEPROM();
};

#endif
