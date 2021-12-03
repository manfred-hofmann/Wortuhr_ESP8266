//******************************************************************************
// Settings.cpp
//******************************************************************************

#include "Settings.h"

Settings::Settings()
{
    loadFromEEPROM();
}

Settings::~Settings()
{
}

// Set all defaults
void Settings::resetToDefault()
{
    mySettings.magicNumber = SETTINGS_MAGIC_NUMBER;
    mySettings.version = SETTINGS_VERSION;
    strcpy (mySettings.systemname,WIFIHOSTNAME);
    mySettings.useAbc = true;
    mySettings.brightness = 70;
    mySettings.color = WHITE;
    mySettings.colorChange = COLORCHANGE_FIVE;
    mySettings.transition = TRANSITION_ALLE_NACHEINANDER;
    mySettings.modeChange = true;
    mySettings.itIs = true;
    mySettings.alarm1 = false;
    mySettings.alarm1Time = 0;
    mySettings.alarm1Weekdays = 0b11111110;
    mySettings.alarm2 = false;
    mySettings.alarm2Time = 0;
    mySettings.alarm2Weekdays = 0b11111110;
    mySettings.nightOffTime = 10860;
    mySettings.dayOnTime = 18000;
    mySettings.hourBeep = true;
    mySettings.volume = 100;
    mySettings.sprecher = true;          //vicki
    mySettings.randomsound = false;
    mySettings.weekdaysoundfile[0] = 8; //Sonntag
    mySettings.weekdaysoundfile[1] = 0;
    mySettings.weekdaysoundfile[2] = 1;
    mySettings.weekdaysoundfile[3] = 2;
    mySettings.weekdaysoundfile[4] = 3;
    mySettings.weekdaysoundfile[5] = 4;
    mySettings.weekdaysoundfile[6] = 5;  //Samstag
    mySettings.weekendlater = true;
    mySettings.vickihans24h = true;
    strcpy (mySettings.ntphost,NTP_SERVER);
    mySettings.corner_color = ORANGE;
    mySettings.corner_colorChange = COLORCHANGE_FIVE;
    mySettings.bg_color = 0x320032;
    mySettings.enable_bg_color = 0;
    strcpy (mySettings.openweatherapikey,DEFAULTAPIKEY);
    strcpy (mySettings.openweatherlocation,LOCATION);
    mySettings.highscore[0] = 0;
    mySettings.highscore[1] = 40;
    mySettings.highscore[2] = 163;
    mySettings.highscore[3] = 176;
    mySettings.highscore[4] = 0;
    mySettings.highscore[5] = 0;
    mySettings.highscore[6] = 0;
    mySettings.highscore[7] = 0;
    mySettings.highscore[8] = 0;
    mySettings.standort_hoehe = HOEHE_UEBER_0;
    mySettings.auto_mode_change = AUTO_MODECHANGE_TIME / 60;
    mySettings.ani_sunrise = true;
    mySettings.ani_sunset = true;
    mySettings.latitude = LATITUDE;
    mySettings.longitude = LONGITUDE;
    saveToEEPROM();
}

// Load settings from EEPROM
void Settings::loadFromEEPROM()
{
    EEPROM.begin(sizeof(mySettings)+8);
    EEPROM.get(0, mySettings);
    if ((mySettings.magicNumber != SETTINGS_MAGIC_NUMBER) || (mySettings.version != SETTINGS_VERSION))
        resetToDefault();
    EEPROM.end();
}

// Write settings to EEPROM
void Settings::saveToEEPROM()
{
#ifdef DEBUG
    Serial.println("Settings saved to EEPROM.");
#endif
    EEPROM.begin(sizeof(mySettings)+8);
    EEPROM.put(0, mySettings);
    //EEPROM.commit();
    EEPROM.end();
}
