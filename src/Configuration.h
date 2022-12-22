//******************************************************************************
// Configuration.h
//******************************************************************************

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

//******************************************************************************
// Software settings
//******************************************************************************
//die mit "//*" gekennzeichneten Zeilen nicht verändern!

#define WIFIHOSTNAME "WORTUHR"                 // Das ist der default Hostname/Systemname. Der eigentliche Systemname wird in Settings eingestellt.
#define WIFI_SETUP_TIMEOUT 300                 // So lange ist der AP (AccessPoint) zum eingeben der WiFi Parameter an
#define WIFI_AP_PASS "12345678"                // Wifi Pass für den AP
#define OTA_PASS "1234"                        // Passwort für den OTA (Over the Air) Update
#define NTP_SERVER "time.google.com"           // Das ist der default Name des Zeitservers. Der eigentliche Zeitserver wird in Settings eingestellt.
//#define SHOW_IP                              // Zeigt die IP-Adresse beim Start. Nach Neueingabe der Wlan Parameter wird die IP immer angezeigt!
#define WIFI_BEEPS                             // ob die WLAN Verbunden Meldung kommt
//#define ESP_LED                                // OnBoard LED blinkt im Sekundentakt

//#define NONE_TECHNICAL_ZERO                  // ob die Null bei Feed mit oder ohne Schrägstrich angezeigt wird.
#define AUTO_MODECHANGE_TIME 420               //* Default AutoMode Change Periode. Die eigentliche Periode wird in Settings eingestellt.
#define SHOW_MODE_TIMEOUT 3500                 //* Timer bis es im Mode Modus zum nächsten Mode geht
#define FEED_SPEED 120                         //* wie schnell die Buchstaben über die Uhr huschen
#define TRANSITION_SPEED 90                    //* wie schnell die Transitions laufen

#define MAXEVENTS  40                          //* wie viele Events maximal angelegt werden können                           
#define EVENT_TIME 1800                        //* Das ist die default Event Intervall. Der eigentliche Intervall wird am Event definiert

#define ALARM_LED_COLOR RED                    // Farbe der Alarm LED
//#define ABUSE_CORNER_LED_FOR_ALARM             // Rechte obere Minuten LED wird zur Alarm LED

//#define POWERON_SELFTEST                     // LEDs werden beim anschalten mit versch. Farben getestet. Der Test kann auch im Mode Modus bei nochmalige betätigen des ModeButtons während der Sekunden Ausgabe gestartet werden. 
//* welche Modes gibt es:
#define SHOW_MODE_ANSAGE                       
#define SHOW_MODE_SECONDS
#define SHOW_MODE_WEEKDAY
#define SHOW_MODE_DATE
#define SHOW_MODE_MOONPHASE
#define SHOW_MODE_WETTER
#define SHOW_MODE_TEST

//https://openweathermap.org/
// Test: http://api.openweathermap.org/data/2.5/weather?q=Baden-Baden,de&lang=de&units=metric&appid=<APIKEY>
#define APIKEY                                          // Zum abschalten von Openweather auskommentieren.
#define DEFAULTAPIKEY "OpenWeather APIKEY"              // Hier kann dein default APIKEY von openweathermap rein. Die eigentliche APIKey wird in Settings eingestellt.
#define LOCATION "Baden-Baden,de"                       // Hier kann dein default openweathermap Location rein. Die eigentliche LOCATION wird in Settings eingestellt.
//#define LOCATION "Zurich, CH"
//#define LOCATION "Hong Kong, HK"
#define OPENWEATHER_PERIODE 1800                        //* wie oft in Sekunden openweather.org aufgerufen wird
#define OPENWEATHER_MAX_ERROR 20                        //* bei Fehler: wie oft es pro Tag versucht wird bis es aufgegeben wird

#define SunRiseLib                                      // falls kein API Key vorhanden ist kann Sonnenaufgang/Sonnenuntergang über die Lib SunRise.h berechnet werden.
#define LONGITUDE 8.244                                 // Die RunRise Lib ist in der Bibliotheksverwaltung zu finden.
#define LATITUDE 48.766                                 // Dafür wird der Standort benötigt. Kann z.B. über google maps erfolgen. Die eigentliche Standort wird in Settings eingestellt.

// SunRise/SunSet Animationen
#define ANI_SUNRISE "SUNRISE"                           // Name der Sonnenaufgangsanimation
#define ANI_SUNSET "SUNSET"                             // Name der Sonnenuntergangsanimation

//#define FRONTCOVER_EN
#define FRONTCOVER_DE_DE
//#define FRONTCOVER_DE_SW
//#define FRONTCOVER_DE_BA
//#define FRONTCOVER_DE_SA
//#define FRONTCOVER_DE_MKF_DE
//#define FRONTCOVER_DE_MKF_SW
//#define FRONTCOVER_DE_MKF_BA
//#define FRONTCOVER_DE_MKF_SA
//#define FRONTCOVER_D3
//#define FRONTCOVER_CH
//#define FRONTCOVER_CH_AG                              // Aargau ohne L
//#define FRONTCOVER_CH_AL                              // Aargau mit L
//#define FRONTCOVER_ES
//#define FRONTCOVER_FR
//#define FRONTCOVER_IT
//#define FRONTCOVER_NL
//#define FRONTCOVER_BINARY

//******************************************************************************
// Timezone
//******************************************************************************

//#define TIMEZONE_IDLW  // IDLW  International Date Line West UTC-12
//#define TIMEZONE_SST   // SST   Samoa Standard Time UTC-11
//#define TIMEZONE_HST   // HST   Hawaiian Standard Time UTC-10
//#define TIMEZONE_AKST  // AKST  Alaska Standard Time UTC-9
//#define TIMEZONE_USPST // USPST Pacific Standard Time (USA) UTC-8
//#define TIMEZONE_USMST // USMST Mountain Standard Time (USA) UTC-7
//#define TIMEZONE_USAZ  // USAZ  Mountain Standard Time (USA) UTC-7 (no DST)
//#define TIMEZONE_USCST // USCST Central Standard Time (USA) UTC-6
//#define TIMEZONE_USEST // USEST Eastern Standard Time (USA) UTC-5
//#define TIMEZONE_AST   // AST   Atlantic Standard Time UTC-4
//#define TIMEZONE_BST   // BST   Eastern Brazil Standard Time UTC-3
//#define TIMEZONE_VTZ   // VTZ   Greenland Eastern Standard Time UTC-2
//#define TIMEZONE_AZOT  // AZOT  Azores Time UTC-1
//#define TIMEZONE_GMT   // GMT   Greenwich Mean Time UTC
#define TIMEZONE_CET     // CET   Central Europe Time UTC+1
//#define TIMEZONE_EST   // EST   Eastern Europe Time UTC+2
//#define TIMEZONE_MSK   // MSK   Moscow Time UTC+3 (no DST)
//#define TIMEZONE_GST   // GST   Gulf Standard Time UTC+4
//#define TIMEZONE_PKT   // PKT   Pakistan Time UTC+5
//#define TIMEZONE_BDT   // BDT   Bangladesh Time UTC+6
//#define TIMEZONE_JT    // JT    Java Time UTC+7
//#define TIMEZONE_CNST  // CNST  China Standard Time UTC+8
//#define TIMEZONE_HKT   // HKT   Hong Kong Time UTC+8
//#define TIMEZONE_PYT   // PYT   Pyongyang Time (North Korea) UTC+8.5
//#define TIMEZONE_CWT   // CWT   Central West Time (Australia) UTC+8.75
//#define TIMEZONE_JST   // JST   Japan Standard Time UTC+9
//#define TIMEZONE_ACST  // ACST  Australian Central Standard Time UTC+9.5
//#define TIMEZONE_AEST  // AEST  Australian Eastern Standard Time UTC+10
//#define TIMEZONE_LHST  // LHST  Lord Howe Standard Time UTC+10.5
//#define TIMEZONE_SBT   // SBT   Solomon Islands Time UTC+11
//#define TIMEZONE_NZST  // NZST  New Zealand Standard Time UTC+12

//******************************************************************************
// Hardware settings
//******************************************************************************

#define SERIAL_SPEED 115200

//#define ONOFF_BUTTON
#define MODE_BUTTON
//#define SHOW_TIME_BUTTON


// Einstellen der min/max Helligkeiten
#define MIN_BRIGHTNESS 5                             // Minimale Helligkeit
#define MAX_BRIGHTNESS 255                           // Maximale Helligkeit
#define TEST_BRIGHTNESS 80                           // Helligkeit beim LED Test

// Ist ein BME280 an Board
#define SENSOR_BME280
#define SEALEVELPRESSURE_HPA (1013.25)               //* Luftdruck auf Meereshöhe
#define BME_TEMPERATURE_OFFSET -0.1                  // Temperaturkorrektur
#define BME_HUMIDITY_OFFSET +0.1                     // Luftfeuchtekorrektur


#define HOEHE_UEBER_0 130                            // Hier die default Höhe über NN des Wohnortes eintragen.Der eigentliche Wert wird in Settings eingestellt.

#define LUFTDRUCKMIN 975                             //* Hier den zu erwartenden minimalen Luftdruck eintragen (Baseline im Diagramm)
//* Parameter für die Berechnung des Luftdrucks auf Meeresniveau:
#define FALLBESCHLEUNIGUNG 9.80665
#define GASKONSTANTE 287.05
#define KELVIN_0 273.15
#define TEMPERATURGRADIENT 0.00325
#define EULERSCHE_ZAHL 2.7183

// Schwellen für steigend/fallender Luftdruck:
#define LUFTDRUCK_DIFF_STEIGEND 30
#define LUFTDRUCK_DIFF_LEICHTSTEIGEND 15
#define LUFTDRUCK_DIFF_LEICHTFALLEND -15
#define LUFTDRUCK_DIFF_FALLEND -30

//#define RTC_BACKUP
#define RTC_TEMPERATURE_OFFSET -0.1

// Lichtabhängiger Widerstand an Board?
#define LDR
//#define LDR_IS_INVERSE                      // Falls LDR Wert gegen Masse angeschlossen wurde
#define MIN_LDR_STARTVALUE 30                 // LDR Startwert bei Dunkelheit (1-1023) (Wert siehe Infoseite)
#define MAX_LDR_STARTVALUE 100                // LDR Startwert bei Tageslicht (1-1023) (Wert muss größer als MIN_LDR_STARTVALUE sein!)

//#define BUZZER
//#define BUZZTIME_ALARM_1 10
//#define BUZZTIME_ALARM_2 10
//#define BUZZTIME_TIMER 10

// MP3 Spieler vorhanden:
#define AUDIO_SOUND

#ifdef AUDIO_SOUND

//#define CHECK_MP3                             // prüft jede Stunde zur Random Minute den MP3 Player

#define SINGLEMODE_MIT_SOUND                  // Wenn z.B. der Mond im Webinterface angeklickt wird kommt die Mondanimation mit oder ohne Ansage 

#define STARTUPSOUNDLEVEL 30                  // Startlautstärke 1-100
#define AUDIO_EQUALIZER DFPLAYER_EQ_NORMAL    // Einstellungen Equalizer: DFPLAYER_EQ_NORMAL,DFPLAYER_EQ_POP,DFPLAYER_EQ_ROCK,DFPLAYER_EQ_JAZZ,DFPLAYER_EQ_CLASSIC,DFPLAYER_EQ_BASS

#define BUZZTIME_ALARM_1 10                   // wie lange der Alarm1 an ist
#define BUZZTIME_ALARM_2 10                   // wie lange der Alarm2 an ist
#define BUZZTIME_TIMER 5                      // wie lange der Timeralarm an ist

// Basiswerte der Soundfiles
#define AUDIO_BASENR0 0                      //* 0 s1
#define AUDIO_BASENR1 20                     //* 1 s2
#define AUDIO_BASENR2 40                     //* 2 s3
#define AUDIO_BASENR3 60                     //* 3 s4
#define AUDIO_BASENR4 80                     //* 4 kuckuck
#define AUDIO_BASENR5 120                    //* 5 bing
#define AUDIO_BASENR6 140                    //* 6 kirche
#define AUDIO_BASENR7 100                    //* 7 westminster 1
#define AUDIO_BASENR8 160                    //* 8 westminster 2
#define AUDIO_BASENR9 180                    //* 9 alte Uhr
#define AUDIO_BASENR10 200                   //* 10 ding
#define AUDIO_BASENR11 220                   //* 11 Hund und Katz
#define AUDIO_BASENR12 240                   //* 12 Tod

#define AUDIO_BASENR_VICKI 1000              //* 13 vicki
#define AUDIO_BASENR_HANS  2000              //* 14 hans
#define AUDIO_BASENR_VICKI_HANS 9999         //* 15 vicki und hans im wechsel
#define AUDIO_BASENR_RANDOM  0               //* 16 Random

// Lautstärke Level pro Stunde in Prozent:
#define AUDIO_H00 30
#define AUDIO_H01 20
#define AUDIO_H02 10
#define AUDIO_H03 10
#define AUDIO_H04 10
#define AUDIO_H05 20
#define AUDIO_H06 30
#define AUDIO_H07 50
#define AUDIO_H08 80
#define AUDIO_H09 90
#define AUDIO_H10 100
#define AUDIO_H11 100
#define AUDIO_H12 100
#define AUDIO_H13 100
#define AUDIO_H14 100
#define AUDIO_H15 100
#define AUDIO_H16 100
#define AUDIO_H17 100
#define AUDIO_H18 100
#define AUDIO_H19 100
#define AUDIO_H20 100
#define AUDIO_H21 90
#define AUDIO_H22 80
#define AUDIO_H23 60
#define AUDIO_H24 30

#ifdef SINGLEMODE_MIT_SOUND
 #define SMODE_SOUND "1"
#else
 #define SMODE_SOUND "0"
#endif

#else
 #define SMODE_SOUND "0"
#endif //Ende AUDIO_SOUND

// IR-Receiver vorhanden:
//#define IR_RECEIVER
#ifdef IR_RECEIVER
//###################################################################
//##################              KTS017            #################
//###################################################################
//#define IR_CODE_ONOFF         16728765 // On/Off
//#define IR_CODE_TIME          16712445 // Enter
//#define IR_CODE_MODE          16732845 // Stop/mode
//#define IR_CODE_LEISER        16754775 // Vol-
//#define IR_CODE_LAUTER        16736925 // Vol+
//#define IR_CODE_DUNKLER       16720605 // <
//#define IR_CODE_HELLER        16761405 // >
//#define IR_CODE_SECONDS       16730805 // 0/10+
//#define IR_CODE_WEEKDAY       16738455 // 1
//#define IR_CODE_DATE          16750695 // 2
//#define IR_CODE_MOND          16756815 // 3
//#define IR_CODE_TEMP          16724175 // 4
//#define IR_CODE_HUMIDITY      16718055 // 5
//#define IR_CODE_LUFTDRUCK     16743045 // 6
//#define IR_CODE_WETTER        16716015 // 7
//#define IR_CODE_EXT_TEMP      16726215 // 8
//#define IR_CODE_EXT_HUMIDITY  16734885 // 9

//#define IR_RECEIVER_GAME                                   // IR-Ferbedienung zur Spielesteuerung (experimentell)
//#ifdef IR_RECEIVER_GAME
//  #define IR_CODE_LEFT          16720605 // <
//  #define IR_CODE_UP            16736925 // ^
//  #define IR_CODE_RIGHT         16761405 // >
//  #define IR_CODE_DOWN          16754775 // v
//  #define IR_CODE_MIDDLE        16712445 // Enter
//  #define IR_CODE_STOP          16732845 // Stop/Mode
//#endif
//###################################################################
//##################        CLT2 V1.1 Remote        #################
//###################################################################
// CLT2 V1.1 Remote
//#define IR_CODE_ONOFF 0xFFE01F // CLT2 V1.1 Remote Power
//#define IR_CODE_TIME  0xFFA05F // CLT2 V1.1 Remote Time
//#define IR_CODE_MODE  0xFF20DF // CLT2 V1.1 Remote Region
// Liste muss noch ergänzt werden!

//###################################################################
//##################           BerryBase            #################
//##(https://www.berrybase.de/infrarot-fernbedienung-mit-21-tasten)##
//###################################################################
#define IR_CODE_ONOFF         0xFD807F // On/Off
#define IR_CODE_TIME          0xFD906F // Enter
#define IR_CODE_MODE          0xFD609F // Stop/mode
#define IR_CODE_LEISER        0xFD00FF // Vol-
#define IR_CODE_LAUTER        0xFD40BF // Vol+
#define IR_CODE_DUNKLER       0xFD10EF // <
#define IR_CODE_HELLER        0xFD50AF // >
#define IR_CODE_SECONDS       0xFD30CF // 0/10+
#define IR_CODE_WEEKDAY       0xFD08F7 // 1
#define IR_CODE_DATE          0xFD8877 // 2
#define IR_CODE_MOND          0xFD48B7 // 3
#define IR_CODE_TEMP          0xFD28D7 // 4
#define IR_CODE_HUMIDITY      0xFDA857 // 5
#define IR_CODE_LUFTDRUCK     0xFD6897 // 6
#define IR_CODE_WETTER        0xFD18E7 // 7
#define IR_CODE_EXT_TEMP      0xFD9867 // 8
#define IR_CODE_EXT_HUMIDITY  0xFD58A7 // 9

#define IR_RECEIVER_GAME                                     // IR-Ferbedienung zur Spielesteuerung (experimentell)
#ifdef IR_RECEIVER_GAME
  #define IR_CODE_LEFT          0xFD10EF // <
  #define IR_CODE_UP            0xFDA05F // ^
  #define IR_CODE_RIGHT         0xFD50AF // >
  #define IR_CODE_DOWN          0xFDB04F // v
  #define IR_CODE_MIDDLE        0xFD906F // Enter
  #define IR_CODE_STOP          0xFD609F // Stop/Mode
#endif
//###################################################################
//#define IR_LETTER_OFF
#define IR_LETTER_X 8
#define IR_LETTER_Y 10

#endif  // Ende IR_RECEIVER
//###################################################################


#define NUMPIXELS 115                       // mit Alarm LED
//#define NUMPIXELS 114                       // ohne Alarm LED

// Das LED Layout (Siehe in LedDriver.cpp):
//#define LED_LAYOUT_HORIZONTAL_1
//#define LED_LAYOUT_HORIZONTAL_2         // B
#define LED_LAYOUT_HORIZONTAL_3          // C (260x260)
//#define LED_LAYOUT_VERTICAL_1
//#define LED_LAYOUT_VERTICAL_2
//#define LED_LAYOUT_VERTICAL_3           // A (390x390)

//******************************************************************************
// Einstellungen LED Type
//******************************************************************************
//#define LED_LIBRARY_LPD8806RGBW              // https://github.com/bracci/LPD8806RGBW for download Lib
//-------------------------------

#define LED_LIBRARY_NEOPIXEL

#define NEOPIXEL_TYPE NEO_GRB + NEO_KHZ800     // see Adafruit_NeoPixel.h for help

//#define NEOPIXEL_TYPE NEO_GRBW + NEO_KHZ800

//#define NEOPIXEL_TYPE NEO_WRGB + NEO_KHZ800

// Um den Weißanteil bzw. die Farbtemperatur zu verändern (nur für sk6812 LEDs mit weißer LED)
//#define NEOPIXEL_FARBTEMPERATUR

#ifdef NEOPIXEL_FARBTEMPERATUR
#define whiteboost 3 //1-10 default 4 
//Je kleiner der whiteboost, desto höher der Weißanteil (heller aber weniger starke Farben). 
//Je größer der whiteboost, desto kleiner der Weißanteil (dunkler aber intensivere Farben).

//Ändern der Farbtemperatur. Nur für sk6812 LEDs
//Laut Datenblatt = RGBW (WW 2700-3000K; CW 6000-6500K; NW 4000-4500K)
//https://andi-siess.de/rgb-to-color-temperature/
// WW K2800: (255, 173, 94)
// CW K6300: (255, 246, 247)
// NW K4200: (255, 213, 173)
//Beispiel K4500: (255, 219, 186),
#define temp_red 255 //default 255 
#define temp_green 255 //default 255
#define temp_blue 255 //default 255
#endif


//******************************************************************************
// Misc
//******************************************************************************

// Debug Schalter:
// Im Normalbetrieb immer alle DEBUG Schalter aus!

//#define DEBUG 1
//#define DEBUG_EVENTS
//#define DEBUG_ANIMATION
//#define DEBUG_GAME
//#define DEBUG_WEB
//#define DEBUG_IR
//#define DEBUG_MATRIX
//#define DEBUG_FPS
//#define DEBUG_OW
//#define DEBUG_AUDIO


#define __NAME__ (strrchr(__FILE__,'\\')?strrchr(__FILE__,'\\')+1:__FILE__)
//******************************************************************************
//#define SYSLOGSERVER_SERVER "192.168.0.1"
//#define SYSLOGSERVER_PORT 514


//******************************************************************************
// ESP8266 / WeMos Anschlüsse:
//******************************************************************************

//                                 V1      KELLY
//#define PIN_IR_RECEIVER  D6     //                          wird für IR-Receiver benötigt
#define PIN_WIRE_SCL     SCL    // D1,SCL  D1,SCL             SCL
#define PIN_WIRE_SDA     SDA    // D2,SDA  D2,SDA             SDA
#define PIN_MODE_BUTTON  D7     // D7      D3,mode/flash
#define PIN_LED          D4     // D4      D4,LED Data        LED_BUILTIN
#define PIN_AUDIO_RX     D5     // D5      D5,14
#define PIN_AUDIO_TX     D3     // D3      D7,13
#define PIN_AUDIO_BUSY   D0     // D0      D0,16              kein Interrupt!
//#define PIN_BUZZER       D4     //
//#define PIN_LEDS_CLOCK   D6     //       D6,12              wird für LPD8806RGBW benötigt D6
#define PIN_LEDS_DATA    D8     // D8      D8,Data            (z.B. WS2812B)
#define PIN_LDR          A0     // A0      A0,LDR             ADC
#define PIN_SHOW_TIME_BUTTON RX //         RX,time
#define PIN_ONOFF_BUTTON TX     //         TX,on/off
// GPIO 06 to GPIO 11 are
// used for flash memory databus

#endif
