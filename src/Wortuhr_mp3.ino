// ******************************************************************************
// WORTUHR_MP3
// An advanced firmware for a DIY "word-clock"
//
// @mc ESP8266 Version 2.6.3
// @created 12.03.2017
//
// This source file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This source file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// ******************************************************************************
// ******************************************************************************

// Einstellungen für das Board: (LOLIN(WEMOS) D1 R2 & mini)
// CPU Frequenz auf 160 MHz
// Flash Size 4MB ( FS:2MB OTA~1019KB)
// SLL Support Basic

// oder für ESP8266 EX: Board LOLIN(WEMOS) D1 pro
// CPU Frequenz auf 160 MHz
// Flash Size: 16MB ( FS:14MB OTA~1019KB)
// Flash Mode: "DOUT(compatible)"
// SLL Support Basic

// wichtig: Board Version 2.6.3 bis 2.7.4

// Im Normalbetrieb immer alle DEBUG Schalter aus. (configuration.h ab Zeile 305!)

// folgende Libraries werden benötigt:

//Software Serial für ESP8266:
//https://circuits4you.com/2016/12/14/software-serial-esp8266/ 
// Link zur Library: https://circuits4you.com/wp-content/uploads/2016/11/SoftwareSerial.zip --> SoftwareSerial.h

// MP3-Player:
//https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299
// Link zur Library: https://github.com/DFRobot/DFRobotDFPlayerMini/archive/1.0.3.zip -->DFRobotDFPlayerMini.h

//BME280:
//Open your Arduino IDE and go to Sketch > Include Library > Manage Libraries. The Library Manager should open.
//Search for “adafruit bme280 ” on the Search box and install the library. --> Adafruit_BME280.h
//To use the BME280 library, you also need to install the Adafruit_Sensor library. Follow the next steps to install the library in your Arduino IDE:
//Go to Sketch > Include Library > Manage Libraries and type “Adafruit Unified Sensor” in the search box. 
//Scroll all the way down to find the library and install it. --> Adafruit_Sensor.h

// Adfruit Neopixel:
//In the Arduino IDE, navigate to Sketch > Include Library > Manage Libraries
//Then the Library Manager will open and you will find a list of libraries that are already installed or ready for installation.
//Then search for Neopixel strip using the search bar.
//Click on the text area and then select the specific version and install it.

// SunRise Library:
//In the Arduino IDE, navigate to Sketch > Include Library > Manage Libraries
//Then the Library Manager will open and you will find a list of libraries that are already installed or ready for installation.
//Then search for SunRise using the search bar.
//Click on the text area SunRise by Cyrus Rahman and then select the specific Version 2.0.2 and install it.

#define FIRMWARE_VERSION 20220603 

#include <Arduino.h>
#include <Arduino_JSON.h>
#include <ArduinoHttpClient.h>
#include <ArduinoOTA.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//#include <DS3232RTC.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <TimeLib.h>
#include <Ticker.h>
#include <FS.h>

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>


#include "Colors.h"
#include "Configuration.h"
#include "Events.h"
#include "spiel_main.h"
#include "Languages.h"
#ifdef LED_LIBRARY_NEOPIXEL
#include "LedDriver.h"
#endif
#ifdef LED_LIBRARY_LPD8806RGBW
#include "LedDriver_LPD8806RGBW.h"
#endif
#include "Modes.h"
#include "Ntp.h"
#include "OpenWeather.h"
#include "Renderer.h"
#include "Settings.h"
#include "Syslog.h"
#include "Timezone.h"
#include "Timezones.h"
#include "WiFiManager.h"
#include "Audio.h"
#include "Animation.h"

#ifdef SunRiseLib
#include <SunRise.h>
#endif

//******************************************************************************
// Init
//******************************************************************************
// Servers
ESP8266WebServer webServer(80);

ESP8266HTTPUpdateServer httpUpdater;

//Audio Sound
#ifdef AUDIO_SOUND
SoftwareSerial SoftSer(PIN_AUDIO_TX, PIN_AUDIO_RX, false, 128); 

DFRobotDFPlayerMini Mp3Player;
int16_t SOUNDBASENR[17] = {AUDIO_BASENR0,AUDIO_BASENR1,AUDIO_BASENR2,AUDIO_BASENR3,AUDIO_BASENR4,AUDIO_BASENR5, 
                           AUDIO_BASENR6,AUDIO_BASENR7,AUDIO_BASENR8,AUDIO_BASENR9,AUDIO_BASENR10,AUDIO_BASENR11,
                           AUDIO_BASENR12,AUDIO_BASENR_VICKI, AUDIO_BASENR_HANS, AUDIO_BASENR_VICKI_HANS, AUDIO_BASENR_RANDOM};

Ticker BusyPinCheck;
                     
int AUDIO_HOUR = -1;
bool AUDIO_TEST = false;
int16_t volume_test_bck = 10;
bool vickihans24h_bck = false;
bool vicki_hans_switch = false;
uint8_t testsoundfile = 0;
uint16_t soundbase = 0;
int AUDIO_FILENR = 0;
int ANSAGEBASE = AUDIO_BASENR_VICKI; //vicki
uint8_t VOLUME_ALT = 0;
uint8_t myIPidx = 0;
uint8_t PABStatus = 1;
#endif
int hny = 0;

//BME280 (Temp Sensor)
#ifdef SENSOR_BME280
Adafruit_BME280 bme;
bool bme_status;
float luftdruck_hist[15] = {};
float lufdruck_hour[3] = {};
struct  temperatur_hist_struct
{
  String stundeminute;
  float innentemp;
  float aussentemp;
};
temperatur_hist_struct temperatur_hist[74];
#endif

// IR receiver
#ifdef IR_RECEIVER
IRrecv irrecv(PIN_IR_RECEIVER);
decode_results irDecodeResult;
#endif

// Syslog
#ifdef SYSLOGSERVER_SERVER
WiFiUDP wifiUdp;
Syslog syslog(wifiUdp, SYSLOGSERVER_SERVER, SYSLOGSERVER_PORT, HOSTNAME, "WORTUHR", LOG_INFO);
#endif

// RTC
#ifdef RTC_BACKUP
DS3232RTC RTC(true);
#endif

// LED driver 
//LedDriver_NeoPixel ledDriver;
#ifdef LED_LIBRARY_NEOPIXEL
LedDriver ledDriver;
#endif
// LPD8806RGBW ledDriver
#ifdef LED_LIBRARY_LPD8806RGBW
LedDriver_LPD8806RGBW ledDriver;
#endif

// Renderer
Renderer renderer;

// Settings
Settings settings;
uint8_t akt_transition = 1;
uint8_t akt_transition_old = 1;

// NTP
Ntp ntp;
char ntpServer[50] {};
uint8_t errorCounterNTP = 0;
bool aktntptime = false;

// Screenbuffer
uint16_t matrix[10] = {};
uint16_t matrixOld[10] = {};
boolean screenBufferNeedsUpdate = true;
bool wortuhrinit = true;

// Mode
Mode mode = MODE_TIME;
Mode lastMode = mode;
unsigned long modeTimeout = 0;
uint32_t autoModeChangeTimer = settings.mySettings.auto_mode_change * 60;
boolean runTransitionOnce = false;
uint8_t autoMode = 0;
boolean autoModeChangeFlag = false;
bool MODE_BUTTON_BOOL = false;
bool SHOW_TIME_BUTTON_BOOL = false;
unsigned long show_off_on_time = 0;
int ModeSequenz = 0;
int modeExtraTime = 0;
int Modecount = 0;


// Time
uint8_t lastDay = 0;
uint8_t lastHour = 0;
uint8_t lastMinute = 0;
uint8_t lastSecond = 0;

uint8_t aktDay = 0;
uint8_t aktHour = 0;
uint8_t aktMinute = 0;
uint8_t aktSecond = 0;

int esptimedrift = 0;
int maxesptimedrift = 0;

uint32_t last500Millis = 0;
uint32_t last50Millis = 0;
time_t upTime = 0;
time_t startTime = 0;
uint8_t randomHour = 0;
uint8_t randomMinute = 0;
uint8_t randomSecond = 0;
int moonphase = 0;
int ani_moonphase = 0;
uint8_t web_moonphase = 0;


#ifdef SunRiseLib
time_t sunRiseTime;
time_t sunSetTime;
SunRise sr;
#endif


// Feed
String feedText = "";
uint8_t feedColor = WHITE;
uint8_t feedPosition = 0;
bool audio_stop_nach_feed = true;

// OpenWeather
#ifdef APIKEY
OpenWeather outdoorWeather;
int errorCounterOutdoorWeather = 0;
uint16_t retcodeOutdoorWeather = 0;
time_t LastOutdoorWeatherTime = 0;
uint16_t WetterSequenz = 0; 
uint8_t WetterAnsageSchritt = 0;

#endif

// BME280
float roomTemperature = 0;
float roomHumidity = 0;
float Pressure = 0;
float Pressure_red = 0;
float info_luftdruckdiff = 0;
int luftdrucktendenz_soundbase;
int luftdrucktendenz_web = 0;
uint8_t errorCounterBME = 0;
uint8_t Tempcolor;

// Brightness and LDR
uint8_t brightness = map(settings.mySettings.brightness, 10, 100, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
uint8_t abcBrightness = brightness;
uint16_t ldrValue = 0;
#ifdef LDR
uint16_t lastLdrValue = 0;
uint16_t minLdrValue = 120; // The ESP will crash if minLdrValue and maxLdrValue are equal due to an error in map()
uint16_t maxLdrValue = 400;
#endif
bool ldr_update = false;

//Animationen
s_myanimation myanimation;
uint32_t anipalette[] = { 0xFF0000,0xFFAA00,0xFFFF00,0x00FF00,0x00FFFF,0x0000FF,0xAA00FF,0xFF00FF,0x000000,0xFFFFFF };
String myanimationslist[MAXANIMATION+1];
uint8_t akt_aniframe = 0;
uint8_t akt_aniloop = 0;
uint8_t frame_fak = 1;        // Animationsrichtung
String animation;
bool playanimation = false;


// Alarm
#if defined(BUZZER) || defined(AUDIO_SOUND)
boolean alarmTimerSet = false;
uint8_t alarmTimer = 0;
uint8_t alarmTimerSecond = 0;
uint8_t alarmOn = false;
#endif

// Events
#ifdef EVENT_TIME
uint32_t showEventTimer = EVENT_TIME;
s_event events[MAXEVENTS+1];
#endif
bool post_event_ani = false;

//Sunrise
uint8_t sunriseHour = 0;
uint8_t sunriseMinute = 0;
uint8_t sunriseSecond = 0;
boolean ani_sunrise_done = false;

uint8_t sunsetHour = 0;
uint8_t sunsetMinute = 0;
uint8_t sunsetSecond = 0;
boolean ani_sunset_done = false;

// Misc
uint8_t testColumn = 0;
int updateInfo = 0;
IPAddress myIP = { 0,0,0,0 };
unsigned long lastButtonPress = 0;
boolean transitionInProgress = false;
uint8_t colorsaver = 0;
uint8_t colorold = 0;
uint8_t cornercolorold = 0;
String WEB_Uhrtext = "Es ist ...";

uint16_t minFreeBlockSize = 10000;
uint16_t codeline = 0;

int WLAN_reconnect = 0;

//******************************************************************************
// Setup()
//******************************************************************************

void setup()
{
	// init serial port
	Serial.begin(SERIAL_SPEED);
	while (!Serial);
	delay(1000);
  setTime(12,0,0,1,2,2003);
	
	Serial.println();
	Serial.println("****** " + String(settings.mySettings.systemname) + " ******");
	Serial.println("Firmware: " + String(FIRMWARE_VERSION));
#ifdef DEBUG
  Serial.printf("Size of Settings: %i byte\n",sizeof(settings));
  Serial.printf("ESP BoardVersion: %s\n",ESP.getCoreVersion().c_str());
#endif

#ifdef POWERON_SELFTEST
	renderer.setAllScreenBuffer(matrix);
  cornercolorold = settings.mySettings.corner_color;
	Serial.println(F("Set all LEDs to red.")); 
  settings.mySettings.corner_color = RED;
  writeScreenBuffer(matrix, RED, TEST_BRIGHTNESS);
	delay(2500);
	Serial.println(F("Set all LEDs to green."));
  settings.mySettings.corner_color = GREEN;
	writeScreenBuffer(matrix, GREEN, TEST_BRIGHTNESS);
	delay(2500);
	Serial.println(F("Set all LEDs to blue."));
 settings.mySettings.corner_color = BLUE;
	writeScreenBuffer(matrix, BLUE, TEST_BRIGHTNESS);
	delay(2500);
	Serial.println(F("Set all LEDs to white."));
  settings.mySettings.corner_color = WHITE;
	writeScreenBuffer(matrix, WHITE, TEST_BRIGHTNESS);
	delay(2500);
  settings.mySettings.corner_color = cornercolorold;
#endif

#ifdef ESP_LED
	Serial.println(F("Setting up ESP-LED."));
	pinMode(PIN_LED, OUTPUT);
	digitalWrite(PIN_LED, HIGH);
#endif

#ifdef MODE_BUTTON
	Serial.println(F("Setting up Mode-Button."));
	pinMode(PIN_MODE_BUTTON, INPUT); 
	attachInterrupt(digitalPinToInterrupt(PIN_MODE_BUTTON), buttonModeInterrupt, RISING);
#endif

#ifdef ONOFF_BUTTON
	Serial.println(F("Setting up Back-Button."));
	pinMode(PIN_ONOFF_BUTTON, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(PIN_ONOFF_BUTTON), buttonOnOffInterrupt, FALLING);
#endif

#ifdef SHOW_TIME_BUTTON
	Serial.println(F("Setting up Time-Button."));
	pinMode(PIN_SHOW_TIME_BUTTON, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(PIN_SHOW_TIME_BUTTON), buttonShowTimeInterrupt, FALLING);
#endif


#ifdef SENSOR_BME280
  Serial.println(F("Setting up BME280."));
  bme_status = bme.begin();
  if (!bme_status) {
    bme_status = bme.begin(0x76);
    if (!bme_status) {
      Serial.println(F("Could not find a valid BME280 sensor, check wiring, address, sensor ID!"));
      Serial.print(F("SensorID was: 0x")); Serial.println(bme.sensorID(),16);
      Serial.print(F("   ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n"));
      Serial.print(F("   ID of 0x56-0x58 represents a BMP 280,\n"));
      Serial.print(F("        ID of 0x60 represents a BME 280.\n"));
      Serial.print(F("        ID of 0x61 represents a BME 680.\n"));
    }
  }
#endif

#ifdef BUZZER
	Serial.println(F("Setting up Buzzer."));
	pinMode(PIN_BUZZER, OUTPUT);
#endif

  colorsaver = settings.mySettings.color;
  if ( settings.mySettings.corner_colorChange == COLORCHANGE_MAIN) settings.mySettings.corner_color = settings.mySettings.color;

#ifdef AUDIO_SOUND
  Serial.print(F("Setting up Audio Sound."));
  pinMode(PIN_AUDIO_BUSY, INPUT);
  SoftSer.begin(9600);  // Einstellen der Baudrate auf 9600
//  SoftSer.begin(9600,SWSERIAL_8N1,PIN_AUDIO_TX, PIN_AUDIO_RX,false, 128);
  delay(500);
  Mp3Player.begin(SoftSer); // Starten der seriellen Kommunikation zwischen dem D1 Mini und dem MP3 Modul.
  Serial.print(F("."));
  delay(500);
  Serial.print(F("."));
  delay(500);
  Serial.print(F("."));
  delay(500);
  Serial.print(F("."));
  delay(500);
  Serial.println(F(". fertig!"));

  if ( settings.mySettings.sprecher )
  {
    ANSAGEBASE = AUDIO_BASENR_VICKI; //vicki
  }
  else
  {
    ANSAGEBASE = AUDIO_BASENR_HANS; //hans
  }
  Serial.printf("Ansagebase = %i \r\n", ANSAGEBASE);
  Mp3Player.volume(1);
  delay(100);
  Mp3Player.EQ(AUDIO_EQUALIZER);
  delay(100);
  Play_MP3(703,false,STARTUPSOUNDLEVEL); //Spiele mp3 Startup  
#endif
  delay (500);
  renderer.clearScreenBuffer(matrix);
  renderer.setSmallText("WI", TEXT_POS_TOP, matrix);
  renderer.setSmallText("FI", TEXT_POS_BOTTOM, matrix);
  farbenmeer(matrixOld, matrix, WHITE, brightness);
  wortuhrinit = false;
  spiffs();
// Load Events
  if ( loadEvents()) Serial.println(F("Events erfolgreich geladen!"));
  else Serial.println(F("Events konnten nicht geladen werden!"));
// Load Animationsliste
  getAnimationList();
  
#ifdef LDR
	Serial.print("Setting up LDR. ABC: ");
	settings.mySettings.useAbc ? Serial.println("enabled") : Serial.println("disabled");
	pinMode(PIN_LDR, INPUT);
#endif

#ifdef IR_RECEIVER
	Serial.println(F("Setting up IR-Receiver."));
	irrecv.enableIRIn();
#endif

	// Start WiFi and services
	writeScreenBuffer(matrix, WHITE, brightness);
  WiFi.hostname(String(settings.mySettings.systemname));    //
	WiFiManager wifiManager;
	//wifiManager.resetSettings();
	wifiManager.setTimeout(WIFI_SETUP_TIMEOUT);
	wifiManager.autoConnect(settings.mySettings.systemname, WIFI_AP_PASS);
	WiFi.setAutoReconnect(true);
	if (!WiFi.isConnected())
	{
//		WiFi.mode(WIFI_AP);
		Serial.println(F("No WLAN connected. Staying in AP mode."));
		writeScreenBuffer(matrix, RED, brightness);
#if defined(BUZZER) && defined(WIFI_BEEPS)
		digitalWrite(PIN_BUZZER, HIGH);
		delay(1500);
		digitalWrite(PIN_BUZZER, LOW);
#endif
#if defined(AUDIO_SOUND) && defined(WIFI_BEEPS)
  Play_MP3(ANSAGEBASE + 51,false,STARTUPSOUNDLEVEL); //Wlan nicht OK
#endif
    WiFi.mode(WIFI_AP);
		delay(3000);
		myIP = WiFi.softAPIP();
	}
	else
	{
		WiFi.mode(WIFI_STA);
		Serial.println(F("WLAN connected. Switching to STA mode."));
    Serial.print(F("Aktuelle IP ist : "));
    Serial.println(WiFi.localIP());
		writeScreenBuffer(matrix, GREEN, brightness);
#if defined(BUZZER) && defined(WIFI_BEEPS)
		for (uint8_t i = 0; i <= 2; i++)
		{
#ifdef DEBUG
			Serial.println(F("Beep!"));
#endif
			digitalWrite(PIN_BUZZER, HIGH);
			delay(100);
			digitalWrite(PIN_BUZZER, LOW);
			delay(100);
		}
#endif
#if defined(AUDIO_SOUND) && defined(WIFI_BEEPS)
  Serial.println(F("sprich: WLAN-verbunden."));
  Play_MP3(ANSAGEBASE + 50,true,STARTUPSOUNDLEVEL); 
#endif
		delay(500);
// Highscores aus EPROM holen
    highscore[SNAKE] = settings.mySettings.highscore[SNAKE];
    highscore[TETRIS] = settings.mySettings.highscore[TETRIS];
    highscore[BRICKS] = settings.mySettings.highscore[BRICKS];
    highscore[VIERGEWINNT] = settings.mySettings.highscore[VIERGEWINNT];
    delay(500);
    
		myIP = WiFi.localIP();

		// mDNS is needed to see HOSTNAME in Arduino IDE
		Serial.println(F("Starting mDNS responder."));
		MDNS.begin(String(settings.mySettings.systemname));
		//MDNS.addService("http", "tcp", 80);

		Serial.println(F("Starting OTA service."));
#ifdef DEBUG
		ArduinoOTA.onStart([]()
			{
				Serial.println(F("Start OTA update."));
			});
		ArduinoOTA.onError([](ota_error_t error)
			{
				Serial.println("OTA Error: " + String(error));
				if (error == OTA_AUTH_ERROR) Serial.println("Auth failed.");
				else if (error == OTA_BEGIN_ERROR) Serial.println("Begin failed.");
				else if (error == OTA_CONNECT_ERROR) Serial.println("Connect failed.");
				else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive failed.");
				else if (error == OTA_END_ERROR) Serial.println("End failed.");
			});
		ArduinoOTA.onEnd([]()
			{
				Serial.println(F("End OTA update."));
			});
#endif
#ifdef OTA_PASS
		ArduinoOTA.setPassword(OTA_PASS);
#endif
		ArduinoOTA.begin();

#ifdef SYSLOGSERVER_SERVER
		Serial.println(F("Starting syslog."));
#ifdef APIKEY
		syslog.log(LOG_INFO, ";#;dateTime;roomTemperature;roomHumidity;outdoorTemperature;outdoorHumidity;ldrValue;errorCounterNTP;errorCounterBME;errorCounterOutdoorWeather;freeHeapSize;upTime");
#else
		syslog.log(LOG_INFO, ";#;dateTime;roomTemperature;roomHumidity;ldrValue;errorCounterNTP;errorCounterBME;freeHeapSize;upTime");
#endif
#endif

	}

#ifdef SHOW_IP
	WiFi.isConnected() ? feedText = "  IP: " : feedText = "  AP-IP: ";
	feedText += String(myIP[0]) + '.' + String(myIP[1]) + '.' + String(myIP[2]) + '.' + String(myIP[3]) + "   ";
	feedPosition = 0;
	feedColor = WHITE;
	mode = MODE_FEED;
#endif

	Serial.println(F("Starting webserver."));
	setupWebServer();
  delay (500);
	Serial.println(F("Starting updateserver."));
	httpUpdater.setup(&webServer);

	renderer.clearScreenBuffer(matrix);

#ifdef RTC_BACKUP
	setSyncProvider(RTC.get);
	Serial.print(F("RTC Sync."));
	if (timeStatus() != timeSet) Serial.print(F(" FAIL!"));
	Serial.println();
#ifdef DEBUG
	time_t tempRtcTime = RTC.get();
	Serial.printf("Time (RTC): %02u:%02u:%02u %02u.%02u.%04u\r\n", hour(tempRtcTime), minute(tempRtcTime), second(tempRtcTime), day(tempRtcTime), month(tempRtcTime), year(tempRtcTime));
#endif
#endif

	// Get the time!
	if (WiFi.isConnected())
	{
		// Set ESP (and RTC) time from NTP
    strcpy(ntpServer,settings.mySettings.ntphost);
		time_t tempNtpTime = ntp.getTime(ntpServer);
		if (tempNtpTime)
		{
			errorCounterNTP = 0;
      startTime = tempNtpTime;
			setTime(timeZone.toLocal(tempNtpTime));
#ifdef DEBUG
			Serial.printf("Time (NTP): %02u:%02u:%02u %02u.%02u.%04u (UTC)\r\n", hour(tempNtpTime), minute(tempNtpTime), second(tempNtpTime), day(tempNtpTime), month(tempNtpTime), year(tempNtpTime));
			Serial.printf("Drift (ESP): %d sec.\r\n", tempNtpTime - timeZone.toUTC(now()));
#endif
#ifdef RTC_BACKUP
			RTC.set(timeZone.toLocal(tempNtpTime));
#ifdef DEBUG
			Serial.printf("Drift (RTC): %d sec.\r\n", tempNtpTime - timeZone.toUTC(RTC.get()));
#endif
#endif
      if ( ausperiode() ) 
      {
#ifdef DEBUG
      Serial.println(F("AusPeriode -> ModeBlank"));
#endif        
        setMode(MODE_BLANK);
      }
		}
		else
		{
      startTime = timeZone.toUTC(now());  // setze Startzeit auf dummy Zeit 1.2.2003 12:00 (UTC)
			if (errorCounterNTP < 255) errorCounterNTP++;
#ifdef DEBUG
			Serial.printf("Error (NTP): %u\r\n", errorCounterNTP);
#endif
		}
#ifdef DEBUG
      Serial.printf("StartTime: %02u:%02u:%02u %02u.%02u.%04u\r\n", hour(startTime), minute(startTime), second(startTime), day(startTime), month(startTime), year(startTime));
#endif
	}

	// Define a random time
	randomSeed(analogRead(A0));
	randomHour = random(9, 16);
  for (uint8_t i = 0; i <= 20; i++)
  {
	  randomMinute = random(23, 37);           // eine Zufallsminute die nicht auf eine volle 5 Minute fällt
    if ( randomMinute % 5 != 0 ) break;
  }
	randomSecond = random(5, 56);

  if (WiFi.isConnected())
  {
// Get weather from OpenWeather
#ifdef APIKEY
#ifdef DEBUG_OW
      Serial.println(F("Getting outdoor weather (INIT):"));
#endif
      delay(1000); 
      retcodeOutdoorWeather = outdoorWeather.getOutdoorConditions(String(settings.mySettings.openweatherlocation), String(settings.mySettings.openweatherapikey));
      if ( retcodeOutdoorWeather > 0 ) 
      {
#ifdef DEBUG_OW
       Serial.println(F("OpenWeather Error"));
#endif
       errorCounterOutdoorWeather++;
       LastOutdoorWeatherTime = 0;
      }
      else
      {
        LastOutdoorWeatherTime = startTime;
      }
#ifdef DEBUG_OW
      Serial.println(outdoorWeather.description);
      Serial.println(outdoorWeather.temperature);
      Serial.println(outdoorWeather.humidity);
      Serial.println(outdoorWeather.pressure);
#endif
    sunriseset();
#endif
  }

// Update room conditions
#ifdef SENSOR_BME280
	getRoomConditions();
// Initialisierung der Luftdruck Werte mit dummy Werte
  for (uint8_t ze = 0; ze <= 10; ze++) 
  {
    if ( Pressure_red < LUFTDRUCKMIN ) Pressure_red = LUFTDRUCKMIN + 30;
    luftdruck_hist[ze] = Pressure_red+float(0.17*(ze*ze)-0.95*ze-2.5);
  }
   luftdruck_hist[0] = Pressure_red;
//  luftdruck_hist[1] = 997.5;
//  luftdruck_hist[2] = 1000;
//  luftdruck_hist[3] = 1002.5;
//  luftdruck_hist[4] = 1005;
//  luftdruck_hist[5] = 1007.5;
//  luftdruck_hist[6] = 1010;
//  luftdruck_hist[7] = 1007.5;
  luftdruck_hist[8] = Pressure_red;
  luftdruck_hist[9] = Pressure_red;
  luftdruck_hist[10] = Pressure_red;
  lufdruck_hour[0] = Pressure_red;
  lufdruck_hour[1] = Pressure_red;
  lufdruck_hour[2] = Pressure_red;

// Initialisierung der Temperatur Werte mit dummy Werte
  int stunde = hour();
  int temp_init_z = 0;
  for (int s = 0 ; s < 24; s++) 
  {
    if ( stunde > 23) stunde = 0;
    for (int m = 0 ; m < 60; m = m + 20) 
    {
      
      temperatur_hist[temp_init_z].stundeminute = String(stunde);
      if ( stunde < 10 ) temperatur_hist[temp_init_z].stundeminute = "0" + temperatur_hist[temp_init_z].stundeminute;
      String c_minuten = String(m);
      if ( m < 10 ) c_minuten = "0" + c_minuten;
      temperatur_hist[temp_init_z].stundeminute = temperatur_hist[temp_init_z].stundeminute + ":" + c_minuten;
      temperatur_hist[temp_init_z].innentemp = roomTemperature + random(1,4) - 1.5;
      temperatur_hist[temp_init_z].aussentemp = 0;
#ifdef APIKEY
      temperatur_hist[temp_init_z].aussentemp = stunde * 2.5 - 15;
#endif
      temp_init_z++;
    }
    stunde++;
  }
  temperatur_hist[72].stundeminute = "SS:MM";
  temperatur_hist[72].innentemp = roomTemperature;
  temperatur_hist[72].aussentemp = 0;
  temperatur_hist[73].stundeminute = "SS:MM";
  temperatur_hist[73].innentemp = roomTemperature;
  temperatur_hist[73].aussentemp = 0;
#ifdef APIKEY
  temperatur_hist[72].aussentemp = outdoorWeather.temperature;
  temperatur_hist[73].aussentemp = outdoorWeather.temperature;
#endif

#endif

	// print some infos
#ifdef DEBUG
	Serial.printf("Day on: %02u:%02u:00\r\n", hour(settings.mySettings.dayOnTime), minute(settings.mySettings.dayOnTime));
	Serial.printf("Night off: %02u:%02u:00\r\n", hour(settings.mySettings.nightOffTime), minute(settings.mySettings.nightOffTime));
	Serial.printf("Alarm1: %02u:%02u:00 ", hour(settings.mySettings.alarm1Time), minute(settings.mySettings.alarm1Time));
	settings.mySettings.alarm1 ? Serial.print("on ") : Serial.print("off ");
	Serial.println(settings.mySettings.alarm1Weekdays, BIN);
	Serial.printf("Alarm2: %02u:%02u:00 ", hour(settings.mySettings.alarm2Time), minute(settings.mySettings.alarm2Time));
	settings.mySettings.alarm2 ? Serial.print("on ") : Serial.print("off ");
	Serial.println(settings.mySettings.alarm2Weekdays, BIN);
	Serial.printf("Random time: %02u:%02u:%02u\r\n", randomHour, randomMinute, randomSecond);
	Serial.println("DEBUG is on.");
#else
	Serial.println("DEBUG is off.");
#endif

	lastDay = day() - 1;
	lastHour = hour();
	lastMinute = minute();
	lastSecond = second();

#ifdef FRONTCOVER_BINARY
	settings.setTransition(TRANSITION_NORMAL);
#endif
} // setup()

// ******************************************************************************##################################################################
// Loop()
// ******************************************************************************##################################################################

void loop()
{
  ESP.wdtFeed(); //Setzt den Timer beider Watchdogs (Hardware+Software) zurück 
  aktDay = day();
  aktHour = hour();
  aktMinute = minute();
  aktSecond = second();
  
// ************************************************************************
// Run once a day
// ************************************************************************
	if (aktDay != lastDay)
	{
		lastDay = aktDay;
		screenBufferNeedsUpdate = true;

#ifdef SHOW_MODE_MOONPHASE
		moonphase = getMoonphase(year(), month(), day());
#endif

// SunRise
#ifdef SunRiseLib
  sr.calculate(settings.mySettings.latitude,settings.mySettings.longitude, timeZone.toUTC(now()) );
  sunRiseTime = timeZone.toLocal(sr.riseTime);
  sunSetTime = timeZone.toLocal(sr.setTime);
  sunriseset();
#ifdef DEBUG
      Serial.printf("Sunrise: %02u:%02u:%02u %02u.%02u.%04u\r\n", sunriseHour , sunriseMinute, sunriseSecond, day(sunRiseTime), month(sunRiseTime), year(sunRiseTime));
      Serial.printf("Sunset : %02u:%02u:%02u %02u.%02u.%04u\r\n", sunsetHour, sunsetMinute, sunsetSecond, day(sunSetTime), month(sunSetTime), year(sunSetTime));
#endif
#endif
    
    ani_sunrise_done = false;
    ani_sunset_done = false;
    
		// Reset URL event 0
    events[0].aktiv=false;
    events[0].year=0;
    events[0].month=0;
    events[0].day=0;
    events[0].text = "";
    events[0].color=0;
    events[0].audio_file=0;
    events[0].preani="";
    events[0].postani="";
    events[0].intervall=0;
    showEventTimer = 20;

#ifdef DEBUG
    Serial.printf("Date: %02u.%02u.%02u  %02u:%02u:%02u\r\n", aktDay, month(), year(),aktHour,aktMinute,aktSecond);
		Serial.printf("Uptime: %u days, %02u:%02u\r\n", int(upTime / 86400), hour(upTime), minute(upTime));
		Serial.printf("Free RAM: %u bytes\r\n", system_get_free_heap_size());
		Serial.printf("Moonphase: %u\r\n", moonphase);
#endif

		// Change color
		if (settings.mySettings.colorChange == COLORCHANGE_DAY)
		{
      changecolor();
#ifdef DEBUG
			Serial.printf("Color changed to: %u\r\n", settings.mySettings.color);
#endif
		}
     // Change cornercolor
      if (settings.mySettings.corner_colorChange == COLORCHANGE_DAY)
      {
        changecornercolor();

#ifdef DEBUG
        Serial.printf("Corner Color changed to: %u\r\n", settings.mySettings.corner_color);
#endif
      }
   
    Modecount = 0;
    for ( uint8_t gc = 0; gc <9;gc++) gamecount[gc] = 0;  // löschen der Spiele pro Tag
#ifdef APIKEY
    errorCounterOutdoorWeather = 0;
#endif
    WLAN_reconnect = 0;
    maxesptimedrift = 0;
    minFreeBlockSize = ESP.getMaxFreeBlockSize();
    codeline = __LINE__;
#ifdef DEBUG
      Serial.printf("minFreeBlockSize: %i Codezeile: %u\n", minFreeBlockSize,codeline); 
#endif   
	}

	// ************************************************************************
	// Run once every hour
	// ************************************************************************

	if (aktHour != lastHour)
	{
		lastHour = aktHour;
		screenBufferNeedsUpdate = true;

		// Change color
		if (settings.mySettings.colorChange == COLORCHANGE_HOUR)
		{
      changecolor();

#ifdef DEBUG
			Serial.printf("Color changed to: %u\r\n", settings.mySettings.color);
#endif
		}
     // Change cornercolor
      if (settings.mySettings.corner_colorChange == COLORCHANGE_HOUR)
      {
        changecornercolor();

#ifdef DEBUG
        Serial.printf("Corner Color changed to: %u\r\n", settings.mySettings.corner_color);
#endif
      }
   

		// Hourly beep
#ifdef BUZZER
		if ((settings.mySettings.hourBeep == true) && (mode == MODE_TIME) && minute() < 2 )
		{
			digitalWrite(PIN_BUZZER, HIGH);
			delay(25);
			digitalWrite(PIN_BUZZER, LOW);
#ifdef DEBUG
			Serial.println(F("Beep!"));
#endif
		}
#endif

#ifdef AUDIO_SOUND
    if ((settings.mySettings.hourBeep == true) && (mode == MODE_TIME) && minute() < 2 )
    {
      AUDIO_HOUR = aktHour;
#ifdef DEBUG
      Serial.println(F("Set AUDIO_HOUR"));
#endif
    }
#endif


		// ************************************************************************
		// Run once every random hour (once a day)
		// ************************************************************************

	}

	// ************************************************************************
	// Run once every minute
	// ************************************************************************

	if (aktMinute != lastMinute)
	{
// Check ob wir nach einem Neustart ab 5 Minuten die aktuelle Zeit haben. Wenn nicht dann Neustart.
    if ( millis()/1000 > 300 && millis()/1000 < 600 && year() < 2010 ) 
    {
      Serial.println(F("Nach 5 Minuten konnte keine aktuelle Zeit geholt werden! "));
      Serial.println(F("Wir versuchen einen Neustart.... "));
      ESP.restart();
    }
    
		lastMinute = aktMinute;
		screenBufferNeedsUpdate = true;
    myIP = WiFi.localIP();
    if (WiFi.status() != WL_CONNECTED || ( myIP[0] == 0 && myIP[1] == 0 && myIP[2] == 0 && myIP[3] == 0))
    {
#ifdef DEBUG
      Serial.print(F("Aktuelle IP ist : "));
      Serial.println(WiFi.localIP());
      Serial.println (F("WLAN-Reconnect!"));
#endif
      WiFi.reconnect();
      WLAN_reconnect++;
      delay(100);
#ifdef DEBUG
      Serial.print(F("Aktuelle IP nach Reconnect ist : "));
      Serial.println(WiFi.localIP());
#endif
    }
#if defined(RTC_BACKUP) || defined(SENSOR_BME280)
		// Update room conditions
		getRoomConditions();
#endif

#if defined(BUZZER) || defined(AUDIO_SOUND)
		// Switch on buzzer for alarm 1
		if (settings.mySettings.alarm1 && (aktHour == hour(settings.mySettings.alarm1Time)) && (aktMinute == minute(settings.mySettings.alarm1Time)) && bitRead(settings.mySettings.alarm1Weekdays, weekday()))
		{
			alarmOn = BUZZTIME_ALARM_1 * 4;
#ifdef DEBUG
			Serial.println(F("Alarm1 on."));
#endif
		}

		// Switch on buzzer for alarm 2
		if (settings.mySettings.alarm2 && (aktHour == hour(settings.mySettings.alarm2Time)) && (aktMinute == minute(settings.mySettings.alarm2Time)) && bitRead(settings.mySettings.alarm2Weekdays, weekday()))
		{
			alarmOn = BUZZTIME_ALARM_2 * 4;
#ifdef DEBUG
			Serial.println(F("Alarm2 on."));
#endif
		}
#endif

#ifdef DEBUG
		time_t tempEspTime = now();
		Serial.printf("Time (ESP): %02u:%02u:%02u %02u.%02u.%04u\r\n", hour(tempEspTime), minute(tempEspTime), second(tempEspTime), day(tempEspTime), month(tempEspTime), year(tempEspTime));
#ifdef RTC_BACKUP
		time_t tempRtcTime = RTC.get();
		Serial.printf("Time (RTC): %02u:%02u:%02u %02u.%02u.%04u\r\n", hour(tempRtcTime), minute(tempRtcTime), second(tempRtcTime), day(tempRtcTime), month(tempRtcTime), year(tempRtcTime));
#endif
#endif

		// Set night- and daymode
		if ((aktHour == hour(settings.mySettings.nightOffTime)) && (aktMinute == minute(settings.mySettings.nightOffTime)))
		{
#ifdef DEBUG
			Serial.println(F("Night off."));
#endif
			setMode(MODE_BLANK);
		}
		if ((aktHour == hour(settings.mySettings.dayOnTime)) && (aktMinute == minute(settings.mySettings.dayOnTime)))
		{
#ifdef DEBUG
			Serial.println(F("Day on."));
#endif
			setMode(lastMode);
		}

    //*************************************************************************
    // Prüfen ob es zur aktuellen Minute eine Animation gibt
    //*************************************************************************
    if ( mode == MODE_TIME )
    {
      animation = "Z";
      if ( aktHour <= 9 ) animation += "0";
      animation += String(aktHour);
      if ( aktMinute <= 9 ) animation += "0";
      animation += String(aktMinute);
  //    Serial.println ( animation);
      playanimation = false;
      if ( not ( month() == 1 && day() == 1 && hour() == 0 && minute() <= 9 ))  // An Neujahr die ersten 9 Minuten keine Animation zulassen!
      {
        for ( int aninr=0; aninr <= MAXANIMATION; aninr++ )
        {
          if ( myanimationslist[aninr].length() == 0 || myanimationslist[aninr] == "neu" ) continue;
          if ( myanimationslist[aninr] == animation)
          {
            playanimation = true;
            break;
          }
        }
      }
    }
    
		// ************************************************************************
		// Run once every random minute (once an hour) or if NTP has an error
		// ************************************************************************

		if ((aktMinute == randomMinute) || aktntptime || ((errorCounterNTP > 0) && (errorCounterNTP < 30)))
		{
      aktntptime = false;
			if (WiFi.isConnected())
			{
				// Set ESP (and RTC) time from NTP
				time_t tempNtpTime = ntp.getTime(ntpServer);
				if (tempNtpTime && year(tempNtpTime) > 2010)
				{
					errorCounterNTP = 0;
          if ( year(timeZone.toUTC(now())) > 2010) esptimedrift = tempNtpTime - timeZone.toUTC(now());
          if ( abs(esptimedrift) > abs(maxesptimedrift) ) maxesptimedrift = esptimedrift;
					
#ifdef DEBUG
					Serial.printf("Time (NTP): %02u:%02u:%02u %02u.%02u.%04u (UTC)\r\n", hour(tempNtpTime), minute(tempNtpTime), second(tempNtpTime), day(tempNtpTime), month(tempNtpTime), year(tempNtpTime));
					Serial.printf("Drift (ESP): %d sec.\r\n", esptimedrift);
#endif
          setTime(timeZone.toLocal(tempNtpTime));
#ifdef RTC_BACKUP
					RTC.set(timeZone.toLocal(tempNtpTime));
#ifdef DEBUG
					Serial.printf("Drift (RTC): %d sec.\r\n", tempNtpTime - timeZone.toUTC(RTC.get()));
#endif
#endif
				}
				else
				{
					if (errorCounterNTP < 255) errorCounterNTP++;
#ifdef DEBUG
					Serial.printf("Error (NTP): %u\r\n", errorCounterNTP);
#endif
				}
			}
      else
      {
        if (errorCounterNTP < 255) errorCounterNTP++;
#ifdef DEBUG
          Serial.printf("Error (NTP): %u\r\n", errorCounterNTP);
#endif
      }
      
		}

		if (aktMinute == randomMinute)
		{
      if (errorCounterNTP > 53) // = 30 Minuten + 24 Stunden
      {
#ifdef AUDIO_SOUND
        AUDIO_FILENR = ANSAGEBASE + 29;  // Zeitserver Meldung
        Play_MP3(AUDIO_FILENR,true,0);
        delay(3000);
#endif
        settings.mySettings.color = RED;
        colorsaver = settings.mySettings.color;
        settings.mySettings.colorChange = COLORCHANGE_NO;
      }
		}

#ifdef APIKEY
    // ************************************************************************
    // Alle 10 minutes +4 neue Wetterdaten holen
    // ************************************************************************
    if ( aktMinute % 10 == 4 && timeZone.toUTC(now()) > LastOutdoorWeatherTime + OPENWEATHER_PERIODE && errorCounterOutdoorWeather < OPENWEATHER_MAX_ERROR )  
    {
      if (WiFi.isConnected())
      {
#ifdef DEBUG_OW
    Serial.println(F("Getting outdoor weather:"));
#endif
        // Get weather from OpenWeather
        retcodeOutdoorWeather = outdoorWeather.getOutdoorConditions(String(settings.mySettings.openweatherlocation), String(settings.mySettings.openweatherapikey));
        if ( retcodeOutdoorWeather > 0 ) 
        {
#ifdef DEBUG_OW
     Serial.println(F("OpenWeather Error"));
#endif
          errorCounterOutdoorWeather++;
        }
        else
        {
          LastOutdoorWeatherTime = timeZone.toUTC(now());
        }
        sunriseset();
#ifdef DEBUG_OW
        Serial.println(F( "Request Outdoor Weather :"));
        Serial.println(outdoorWeather.description);
        Serial.println(outdoorWeather.temperature);
        Serial.println(outdoorWeather.humidity);
        Serial.println(outdoorWeather.pressure);
#endif
      }
    }
#endif


// SunRise
#ifdef SunRiseLib
    if (aktMinute == randomMinute + 1 )
    {
      sr.calculate(settings.mySettings.latitude,settings.mySettings.longitude, timeZone.toUTC(now()) );
      sunRiseTime = timeZone.toLocal(sr.riseTime);
      sunSetTime = timeZone.toLocal(sr.setTime);
    #ifdef DEBUG
          Serial.printf("Sunrise: %02u:%02u:%02u %02u.%02u.%04u\r\n", hour(sunRiseTime), minute(sunRiseTime), second(sunRiseTime), day(sunRiseTime), month(sunRiseTime), year(sunRiseTime));
          Serial.printf("Sunset : %02u:%02u:%02u %02u.%02u.%04u\r\n", hour(sunSetTime), minute(sunSetTime), second(sunSetTime), day(sunSetTime), month(sunSetTime), year(sunSetTime));
    #endif
    }
#endif

		// ************************************************************************
		// Run once every 5 minutes
		// ************************************************************************

		if (aktMinute % 5 == 0)
		{
    
#ifdef SYSLOGSERVER_SERVER
			// Write some data to syslog
			if (WiFi.isConnected())
			{
				time_t tempEspTime = now();
#ifdef APIKEY
				syslog.log(LOG_INFO, ";D;" + String(tempEspTime) + ";" + String(roomTemperature) + ";" + String(roomHumidity) + ";" + String(outdoorWeather.temperature) + ";" + String(outdoorWeather.humidity) + ";" + String(ldrValue)\
					+ ";" + String(errorCounterNTP) + ";" + String(errorCounterBME) + ";" + String(errorCounterOutdoorWeather) + ";" + String(ESP.getFreeHeap()) + ";" + String(upTime));
#else
				syslog.log(LOG_INFO, ";D;" + String(tempEspTime) + ";" + String(roomTemperature) + ";" + String(roomHumidity) + ";" + String(ldrValue)\
					+ ";" + String(errorCounterNTP) + ";" + String(errorCounterBME) + ";" + String(ESP.getFreeHeap()) + ";" + String(upTime));
#endif
#ifdef DEBUG
				Serial.println(F("Data written to syslog."));
#endif
			}
#endif
			// Change color
			if (settings.mySettings.colorChange == COLORCHANGE_FIVE)
			{
        changecolor();

#ifdef DEBUG
				Serial.printf("Color changed to: %u\r\n", settings.mySettings.color);
#endif
			}
      // Change cornercolor
      if (settings.mySettings.corner_colorChange == COLORCHANGE_FIVE)
      {
        changecornercolor();

#ifdef DEBUG
        Serial.printf("Corner Color changed to: %u\r\n", settings.mySettings.corner_color);
#endif
      }
		}
	}

	// ************************************************************************
	// Run once every second
	// ************************************************************************

	if (aktSecond != lastSecond)
	{
		lastSecond = aktSecond;

    if ( year(startTime) > 2010 )         // Startzeit passt
    {
		  upTime = timeZone.toUTC(now()) - startTime;
    }
    else
    {
      if ( year(timeZone.toUTC(now())) > 2010 )  // Wenn die aktuelle Zeit passt kann daraus jetzt die Startzeit ermittelt werden
      {
        startTime = timeZone.toUTC(now()) - millis()/1000;
        upTime = timeZone.toUTC(now()) - startTime;
#ifdef DEBUG
      Serial.printf("Neue StartTime: %02u:%02u:%02u %02u.%02u.%04u\r\n", hour(startTime), minute(startTime), second(startTime), day(startTime), month(startTime), year(startTime));
#endif
      }
      else
      {
        upTime = millis()/1000;
      }
    }

#ifdef AUDIO_SOUND
//Silvester Countdown
    if ( mode == MODE_TIME && month() == 12 && aktDay == 31 && aktHour == 23 && aktMinute == 59 && aktSecond == 49 )
    {
      delay (100);
      AUDIO_FILENR = ANSAGEBASE + 170;  //Countdown
      Play_MP3(AUDIO_FILENR,false,450);
    }
#endif  
 

#ifdef BUZZER
		// Make some noise
		if (alarmOn)
		{
			alarmOn--;
			digitalRead(PIN_BUZZER) == LOW ? digitalWrite(PIN_BUZZER, HIGH) : digitalWrite(PIN_BUZZER, LOW);
			if (!alarmOn)
			{
#ifdef DEBUG
				Serial.println(F("Alarm: off"));
#endif
				digitalWrite(PIN_BUZZER, LOW);
				screenBufferNeedsUpdate = true;
			}
		}
#endif
#ifdef AUDIO_SOUND
    // Make some noise
    if (alarmOn)
    {
      alarmOn--;
      if ( digitalRead(PIN_AUDIO_BUSY) ) Play_MP3(705,false,200);  //Alarm

      if (!alarmOn)
      {
#ifdef DEBUG
        Serial.println(F("Alarm: off"));
#endif
        screenBufferNeedsUpdate = true;
      }
    }
    if (alarmOn && mode != MODE_ALARMANIMATION && year() > 2010 )
    {
      animation = "ALARM";
      for ( int aninr=0; aninr <= MAXANIMATION; aninr++ )
      {
        if ( myanimationslist[aninr].length() == 0 || myanimationslist[aninr] == "neu" ) continue;
        if ( myanimationslist[aninr] == animation)
        {
          if ( loadAnimation(animation) ) 
          {
            akt_aniframe = 0;
            akt_aniloop = 0;
            frame_fak = 0;
            mode = MODE_ALARMANIMATION;
          }
          break;
        }
      }
      if ( mode != MODE_ALARMANIMATION ) delay (100);
    }
#endif

		// Set brightness from LDR
#ifdef LDR
		if (settings.mySettings.useAbc) setBrightnessFromLdr();
#endif

#ifdef FRONTCOVER_BINARY
		if (mode != MODE_BLANK) screenBufferNeedsUpdate = true;
#else
		// Running displayupdate in MODE_TIME or MODE_BLANK every second will lock the ESP due to TRANSITION_FADE
		if ((mode != MODE_TIME) && (mode != MODE_BLANK) && (mode != MODE_MAKEANIMATION) ) screenBufferNeedsUpdate = true;
#endif

		// Flash ESP LED
#ifdef ESP_LED
		digitalWrite(PIN_LED, !digitalRead(PIN_LED));
#endif

		// Countdown timeralarm by one minute in the second it was activated
#if defined(BUZZER) || defined(AUDIO_SOUND)
		if (alarmTimer && alarmTimerSet && (alarmTimerSecond == aktSecond))
		{
			alarmTimer--;
#ifdef DEBUG
			if (alarmTimer) Serial.printf("Timeralarm in %u min.\r\n", alarmTimer);
#endif
		}
		// Switch on buzzer for timer
		if (!alarmTimer && alarmTimerSet)
		{
			alarmTimerSet = false;
			alarmOn = BUZZTIME_TIMER * 4;
#ifdef DEBUG
			Serial.println(F("Timeralarm: on"));
#endif
		}
#endif

// *********************************************************************************
// ************************** Sunrise/Sunset  **************************************
// *********************************************************************************
// SunRise
    if ( mode == MODE_TIME && sunriseHour > 0 )
    {
      if ( settings.mySettings.ani_sunrise && !ani_sunrise_done && sunriseHour == aktHour && sunriseMinute == aktMinute && aktSecond > sunriseSecond )
      {
        ani_sunrise_done = true;
        animation = String(ANI_SUNRISE);
        if ( loadAnimation(animation) ) 
        {
          akt_aniframe = 0;
          akt_aniloop = 0;
          frame_fak = 0;
#ifdef DEBUG
          Serial.println("Starte SunRise Animation: " + animation );
#endif 
#ifdef AUDIO_SOUND 
          Zeitansage(ANSAGEBASE,0);
#endif
          while ( showAnimation(brightness) ) 
          {
#ifdef AUDIO_SOUND
            if ( akt_aniframe == 1 ) 
            {
              
              AUDIO_FILENR = ANSAGEBASE + 165;
              Play_MP3(AUDIO_FILENR,false,0);
            }
#endif           
          }
          screenBufferNeedsUpdate = true;
          if (autoModeChangeTimer < 10 ) autoModeChangeTimer + 10;
          if (showEventTimer < 10 ) showEventTimer + 10;
        }
      }
    }
// SunSet   
    if ( mode == MODE_TIME && sunsetHour > 0 )
    {
      if ( settings.mySettings.ani_sunset && !ani_sunset_done && sunsetHour == aktHour && sunsetMinute == aktMinute && aktSecond > sunsetSecond )
      {
        ani_sunset_done = true;
        animation = String(ANI_SUNSET);
        if ( loadAnimation(animation) ) 
        {
          akt_aniframe = 0;
          akt_aniloop = 0;
          frame_fak = 0;
#ifdef DEBUG
          Serial.println("Starte SunSet Animation: " + animation );
#endif
#ifdef AUDIO_SOUND 
          Zeitansage(ANSAGEBASE,0);
#endif
          while ( showAnimation(brightness) )
          {
#ifdef AUDIO_SOUND
            if ( akt_aniframe == 1 ) 
            {
              AUDIO_FILENR = ANSAGEBASE + 166;
              Play_MP3(AUDIO_FILENR,false,0);          
            }
#endif           
          }
          screenBufferNeedsUpdate = true;
          if (autoModeChangeTimer < 10 ) autoModeChangeTimer + 10;
          if (showEventTimer < 10 ) showEventTimer + 10;
        }
      }
    }

// *********************************************************************************
// ************************** Auto switch modes  ***********************************
// *********************************************************************************
		if (settings.mySettings.modeChange && (mode == MODE_TIME))
		{
			autoModeChangeTimer--;
  			if (!autoModeChangeTimer)
        {
          if ( aktSecond > 45 ) 
          {
            autoModeChangeTimer = autoModeChangeTimer + 30;
          }
          else if ( aktSecond < 15 )
          {
            autoModeChangeTimer = autoModeChangeTimer + 15;
          }
          else
    			{
    #ifdef DEBUG
    				Serial.println("Auto modechange. (" + String(autoMode) + ")");
    #endif
    				autoModeChangeTimer = settings.mySettings.auto_mode_change * 60;
            autoModeChangeFlag = true;
            colorsaver = settings.mySettings.color;
    				switch (autoMode)
    				{
    				case 0:
    #ifdef APIKEY
    					if (WiFi.isConnected() && strlen(settings.mySettings.openweatherapikey) > 25 ) setMode(MODE_EXT_TEMP);
    #endif
    					autoMode = 1;
    					break;
              
    				case 1:
    #if defined(RTC_BACKUP) || defined(SENSOR_BME280)
    					setMode(MODE_TEMP);
    #else
    #ifdef APIKEY
    					if (WiFi.isConnected() && strlen(settings.mySettings.openweatherapikey) > 25 ) setMode(MODE_EXT_TEMP);
    #else
    #ifdef SHOW_MODE_DATE
              setMode(MODE_DATE);
    #endif
    #endif
    #endif
    					autoMode = 2;
    					break;
              
            case 2:
     #ifdef SHOW_MODE_MOONPHASE
              setMode(MODE_MOONPHASE);
     #endif
              autoMode = 3;
              break;
              
            case 3:
     #ifdef SHOW_MODE_DATE
              setMode(MODE_DATE);
     #endif
              autoMode = 4;
              break;
              
            case 4:
    #ifdef APIKEY
    #ifdef SHOW_MODE_WETTER
              if ( strlen(settings.mySettings.openweatherapikey) > 25 ) setMode(MODE_WETTER);
    #endif
    #else
    #ifdef SHOW_MODE_MOONPHASE
              setMode(MODE_MOONPHASE);
    #endif
    #endif
              autoMode = 0;
              break;
    				}
    			}
        }
		  }  
// *********************************************************************************
// ************************** Ende Auto switch modes  ******************************
// *********************************************************************************		

		// Show event in feed
#ifdef EVENT_TIME
		if (mode == MODE_TIME)
		{
			showEventTimer--;
			if (!showEventTimer )
      {
        showEventTimer = EVENT_TIME;
        if ( year() > 2010 )
  			{
          Eventcheck();
  			}
      }
		}
#endif
	}

	// ************************************************************************
	// Run always
	// ************************************************************************

// schaltet für ca. 3 sek die LEDs an
  if (SHOW_TIME_BUTTON_BOOL && millis() > show_off_on_time + 3000 && mode != MODE_BLANK) {
#ifdef DEBUG
    Serial.println(F("Wieder aus nach 3 sek."));
#endif
    setMode(MODE_BLANK);
    SHOW_TIME_BUTTON_BOOL = false;
  }

  
  if (MODE_BUTTON_BOOL) {
    MODE_BUTTON_BOOL = false;
    if ( SHOW_TIME_BUTTON_BOOL ) {
      SHOW_TIME_BUTTON_BOOL = false;
    }
    else
    {
      if ( !SHOW_TIME_BUTTON_BOOL && mode == MODE_BLANK ) 
      {
        show_off_on_time = millis();
        SHOW_TIME_BUTTON_BOOL = true;
      }
      if ( mode != MODE_TIME && mode < MODE_SECONDS ) 
      {
        buttonTimePressed();
      }
      else
      {
        buttonModePressed();
      }
    }
  }

#ifdef SHOW_TIME_BUTTON
  if (SHOW_TIME_BUTTON_BOOL && mode == MODE_BLANK) {
    setMode(MODE_TIME);
  }
#endif

	if (mode == MODE_FEED) screenBufferNeedsUpdate = true;

#ifdef AUDIO_SOUND
// Happy New Ansage
  if ( hny > 0 ) 
  {
    hny++;
    delay (10);
  }
  
  if ( hny == 75 ) 
  {
    screenBufferNeedsUpdate = true;
    Play_MP3(571,false,450); // hans Frohes neues Jahr!
    hny++;
  }
  if ( hny == 150 )
  {
    Play_MP3(271,false,450); // vicki Frohes neues Jahr!
    screenBufferNeedsUpdate = true;
  }
  if ( hny > 150 )
  {
    hny = 0;
  }

// *********************************************************************
// Stundenschlag
// *********************************************************************
  if ( AUDIO_HOUR >= 0 )
  {
 // Happy New Year
    if ( year() > 2010 && month() == 1 && day() == 1 && hour() == 0 && minute() == 0 ) 
    {
      hny = 1;
      setMode(MODE_TIME);
      showEventTimer = 30;
    }
    else
    {
  
// Soundtest
     if ( AUDIO_TEST ) {
        soundbase = SOUNDBASENR[testsoundfile];
      }
//Random Sound:
      else if ( settings.mySettings.randomsound ) {  
         soundbase = SOUNDBASENR[random(0, 13)];
      }
      else
      {
// Sound pro Wochentag: 
        soundbase = SOUNDBASENR[settings.mySettings.weekdaysoundfile[weekday() - 1]]; // 0 = Sonntag
      }
// Vicki und Hans im Wechsel
      if ( soundbase == AUDIO_BASENR_VICKI_HANS ) 
      {
        if (vicki_hans_switch) 
        {
          soundbase = AUDIO_BASENR_VICKI;
          vicki_hans_switch = false;
        }
        else
        {
          soundbase = AUDIO_BASENR_HANS;
          vicki_hans_switch = true;
        }
      }
// 12h oder 24h Ansage
      if ( !( (soundbase == AUDIO_BASENR_VICKI || soundbase == AUDIO_BASENR_HANS ) && settings.mySettings.vickihans24h))
      {
        if ( AUDIO_HOUR > 12 ) {
          AUDIO_HOUR = AUDIO_HOUR - 12;
        }
      }
      
      AUDIO_FILENR = soundbase + AUDIO_HOUR;

#ifdef DEBUG
      Serial.printf("AudioHourSound: %i AUDIO_FILENR: %i\r\n", AUDIO_HOUR,AUDIO_FILENR);
#endif
      Play_MP3(AUDIO_FILENR,false,0);
    }
    AUDIO_HOUR = -1;
    if ( AUDIO_TEST ) {
      AUDIO_TEST = false;
      settings.mySettings.volume = volume_test_bck;
      settings.mySettings.vickihans24h = vickihans24h_bck;
    }
  }
// *********************************************************************
// Stundenschlag Ende
// *********************************************************************
#endif

#ifdef IR_RECEIVER
	// Look for IR commands
	if (irrecv.decode(&irDecodeResult))
	{
#ifdef DEBUG_IR
		Serial.print(F("IR signal: 0x"));
		serialPrintUint64(irDecodeResult.value, HEX);
		Serial.println();
#endif
		switch (irDecodeResult.value)
		{
		case IR_CODE_ONOFF:
			buttonOnOffPressed();
			break;
		case IR_CODE_TIME:
			buttonTimePressed();
			break;
		case IR_CODE_MODE:
			buttonModePressed();
			break;
		}
		irrecv.resume();
	}
#endif

// *********************************************************************
// *********************************************************************
	// Render a new screenbuffer if needed

	if (screenBufferNeedsUpdate)
	{
		screenBufferNeedsUpdate = false;
		// Save old screenbuffer
		for (uint8_t i = 0; i <= 9; i++) matrixOld[i] = matrix[i];
    if ( mode != MODE_TIME ) ModeSequenz++;
    modeExtraTime = 0;
		switch (mode)
		{
		case MODE_TIME:
			renderer.clearScreenBuffer(matrix);

#ifdef FRONTCOVER_BINARY
			matrix[0] = 0b1111000000000000;
			matrix[1] = aktHour << 5;
			matrix[2] = aktMinute << 5;
			matrix[3] = aktSecond << 5;
			matrix[5] = 0b1111000000000000;
			matrix[6] = aktDay << 5;
			matrix[7] = month() << 5;
			matrix[8] = year() - 2000 << 5;
#else
// Hier wird die Uhrzeit gesetzt:
			renderer.setTime(aktHour, aktMinute, matrix);
			renderer.setCorners(aktMinute, matrix);
			if (!settings.mySettings.itIs && ((aktMinute / 5) % 6)) renderer.clearEntryWords(matrix);
#endif
#ifdef ALARM_LED_COLOR  // <----- hier einfügen
#if defined(BUZZER) || defined(AUDIO_SOUND)
			if (settings.mySettings.alarm1 || settings.mySettings.alarm2 || alarmTimerSet) renderer.setAlarmLed(matrix);
#endif
#endif
			break;
#ifdef SHOW_MODE_ANSAGE
		case MODE_ANSAGE:
#ifdef DEBUG
     if ( ModeSequenz == 1 ) Serial.println(F("************ Mode Ansage"));
#endif
      modeExtraTime = -200;
      renderer.clearScreenBuffer(matrix);
        matrix[0] = 0b0000111000000000;
        matrix[1] = 0b0011111110000000;
        matrix[2] = 0b0111111111000000;
        matrix[3] = 0b0110111011000000;
        matrix[4] = 0b1110111011100000;
        matrix[5] = 0b1111111111100000;
        matrix[6] = 0b0101111101000000;
        matrix[7] = 0b0110000011000000;
        matrix[8] = 0b0011000110000000;
        matrix[9] = 0b0000111000000000;
#ifdef AUDIO_SOUND
        if ( ModeSequenz == 3 ) {
          Zeitansage(ANSAGEBASE,0);
        }
#endif
			break;
#endif
#ifdef SHOW_MODE_SECONDS
		case MODE_SECONDS:
#ifdef DEBUG
     if ( ModeSequenz == 1 ) Serial.println(F("************ Mode Sekunden"));
#endif
      modeExtraTime = 5000;
#ifdef AUDIO_SOUND
      if ( ModeSequenz == 2 ) {
        AUDIO_FILENR = ANSAGEBASE + 30;
        Play_MP3(AUDIO_FILENR,false,0);
      }
#endif
			renderer.clearScreenBuffer(matrix);
			renderer.setCorners(aktMinute, matrix);
			for (uint8_t i = 0; i <= 6; i++)
			{
        uint8_t b = pgm_read_byte(&numbersBig[aktSecond / 10][i]);
        matrix[1 + i] |= b << 11;
        b = pgm_read_byte(&numbersBig[aktSecond % 10][i]);
        matrix[1 + i] |= b << 5;
//				matrix[1 + i] |= numbersBig[aktSecond / 10][i] << 11;
//				matrix[1 + i] |= numbersBig[aktSecond % 10][i] << 5;
			}
			break;
#endif
#ifdef SHOW_MODE_WEEKDAY
		case MODE_WEEKDAY:
#ifdef DEBUG
     if ( ModeSequenz == 1 ) Serial.println(F("************ Mode Wochentag"));
#endif
      modeExtraTime = -500;
#ifdef AUDIO_SOUND
      if ( ModeSequenz == 2 ) {
        Wochentagansage(ANSAGEBASE,0);
      }
#endif
			renderer.clearScreenBuffer(matrix);
			renderer.setSmallText(String(sWeekday[weekday()][0]) + String(sWeekday[weekday()][1]), TEXT_POS_MIDDLE, matrix);
			break;
#endif
#ifdef SHOW_MODE_DATE
		case MODE_DATE:
#ifdef DEBUG
     if ( ModeSequenz == 1 ) Serial.println(F("************ Mode Datum"));
#endif
#ifdef AUDIO_SOUND
      if ( ModeSequenz == 2 && !autoModeChangeFlag ) {
        Datumsansage(ANSAGEBASE,0);
      }
#endif
      modeExtraTime = 2000;
			renderer.clearScreenBuffer(matrix);
			if (aktDay < 10)
				renderer.setSmallText(("0" + String(aktDay)), TEXT_POS_TOP, matrix);
			else
				renderer.setSmallText(String(aktDay), TEXT_POS_TOP, matrix);
			if (month() < 10)
				renderer.setSmallText(("0" + String(month())), TEXT_POS_BOTTOM, matrix);
			else
				renderer.setSmallText(String(month()), TEXT_POS_BOTTOM, matrix);
//			renderer.setPixelInScreenBuffer(5, 4, matrix); // hier ein Punkt nochmal am Ende ??
//			renderer.setPixelInScreenBuffer(5, 9, matrix); // hier ein Punkt nochmal am Ende ??

			break;
#endif

#ifdef SHOW_MODE_MOONPHASE
		case MODE_MOONPHASE:
#ifdef DEBUG
     if ( ModeSequenz == 1 ) Serial.println(F("************ Mode Mondphase"));
#endif
    modeExtraTime = 3000;
#ifdef AUDIO_SOUND
      if ( ModeSequenz == 1 && !autoModeChangeFlag ) {
        AUDIO_FILENR = ANSAGEBASE + 33;
        Play_MP3(AUDIO_FILENR,false,0);
      }
      if ( ModeSequenz == 3 && !autoModeChangeFlag ) {
        if ( moonphase == 0 ) AUDIO_FILENR = ANSAGEBASE + 70; // Neumond
        if ( moonphase == 11 ) AUDIO_FILENR = ANSAGEBASE + 72; // Vollmond
        if ( moonphase > 0 && moonphase < 11 ) AUDIO_FILENR = ANSAGEBASE + 71; // zunehmend
        if ( moonphase > 11 && moonphase < 22 ) AUDIO_FILENR = ANSAGEBASE + 73; // abnehmend
        Play_MP3(AUDIO_FILENR,false,0);
      }
#endif
		 if ( ModeSequenz == 1 ) renderer.clearScreenBuffer(matrix);
     if ( ModeSequenz <= 5 ) {
       ani_moonphase = moonphase - 5 + ModeSequenz;
     
       if ( ani_moonphase < 0 ) ani_moonphase = 22 + ani_moonphase;
#ifdef DEBUG
     Serial.println("ani_moonphase: " + String(ani_moonphase));
#endif
       for (uint8_t i = 0; i <= 9; i++) 
       {
         matrixOld[i] = matrix[i];
//         matrix[i] = MONDMATRIX[ani_moonphase][i];
         matrix[i] = pgm_read_word(&MONDMATRIX[ani_moonphase][i]);
       }
     }
			break;
#endif

#if defined(RTC_BACKUP) || defined(SENSOR_BME280)
		case MODE_TEMP:
#ifdef DEBUG
    if ( ModeSequenz == 1 ) 
    { 
      Serial.println(F("************ Mode Raumtemperatur"));
      Serial.println("Raumtemperatur:" + String(roomTemperature));
    }
#endif
#ifdef AUDIO_SOUND
      if ( ModeSequenz == 2 && !autoModeChangeFlag ) {
        Temperaturansage(ANSAGEBASE,true,roomTemperature,0);
      }
#endif
			renderer.clearScreenBuffer(matrix);
			if (roomTemperature == 0)
			{
				matrix[0] = 0b0000000001000000;
				matrix[1] = 0b0000000011100000;
				matrix[2] = 0b0000000010100000;
				matrix[3] = 0b0000000011100000;
			}
			if (roomTemperature > 0)
			{
				matrix[0] = 0b0000000001000000;
				matrix[1] = 0b0100000011100000;
				matrix[2] = 0b1110000010100000;
				matrix[3] = 0b0100000011100000;
			}
			if (roomTemperature < 0)
			{
				matrix[0] = 0b0000000001000000;
				matrix[1] = 0b0000000011100000;
				matrix[2] = 0b1110000010100000;
				matrix[3] = 0b0000000011100000;
			}
			renderer.setSmallText(String(int(abs(roomTemperature) + 0.5)), TEXT_POS_BOTTOM, matrix);
			break;
#ifdef SENSOR_BME280
		case MODE_HUMIDITY:
#ifdef DEBUG
    if ( ModeSequenz == 1 ) 
    { 
      Serial.println(F("************ Mode Luftfeuchtigkeit innen"));
		  Serial.println("Luftfeuchtigkeit innen:" + String(roomHumidity));
    }
#endif
#ifdef AUDIO_SOUND
      if ( ModeSequenz == 2 ) {
        Humidityansage(ANSAGEBASE,true,roomHumidity,0);
      }
#endif
			renderer.clearScreenBuffer(matrix);
			renderer.setSmallText(String(int(roomHumidity + 0.5)), TEXT_POS_TOP, matrix);
			matrix[6] = 0b0100100001000000;
			matrix[7] = 0b0001000011100000;
			matrix[8] = 0b0010000010100000;
			matrix[9] = 0b0100100011100000;
			break;
#endif
#endif


#ifdef APIKEY
// #################### WETTER START #################
#ifdef SHOW_MODE_WETTER
  if ( strlen(settings.mySettings.openweatherapikey) > 25 )
  {
    case MODE_WETTER:
      
    if ( ModeSequenz == 1 ) 
    {
      WetterSequenz = ModeSequenz;
      WetterAnsageSchritt = ModeSequenz; // Start
    }
#ifdef DEBUG
    if ( ModeSequenz == 1 ) 
    { 
      Serial.println(F("************ Mode Wetter"));
    }
#endif

// ############# Wetteransage Start
#ifdef AUDIO_SOUND

    if ( ModeSequenz == 2 && !autoModeChangeFlag ) {
      AudioBufferClear();
      AudioBufferIn(ANSAGEBASE + 400); // Wetter
      PABStatus = PlayAudioBuffer(0);
      AUDIO_FILENR = ANSAGEBASE + getWeatherSound(outdoorWeather.weatherid1); // Wetterlage 1
      AudioBufferIn(AUDIO_FILENR);
      WetterAnsageSchritt = 2; //Start Ansage Wetterlage
    }
//#ifdef DEBUG
//      if ( digitalRead(PIN_AUDIO_BUSY) ) Serial.printf("BusyPin! %i\n",millis() - wetteransagets);
//#endif   
    if ( WetterAnsageSchritt == 2 && PlayAudioBuffer(0) == 2 && !autoModeChangeFlag ) {
      if ( outdoorWeather.weatherid1 != 771 && outdoorWeather.weatherid1 != 781 && outdoorWeather.weatherid2 != 771 && outdoorWeather.weatherid2 != 781 )
      {
        if ( outdoorWeather.windspeed <= 0.5 )                                     AUDIO_FILENR = ANSAGEBASE + WETTERSOUNDBASE + 80;      //windstill
        if ( outdoorWeather.windspeed > 0.5 && outdoorWeather.windspeed <= 4.0 )   AUDIO_FILENR = ANSAGEBASE + WETTERSOUNDBASE + 81;      //leichte Brise
        if ( outdoorWeather.windspeed > 4.0 && outdoorWeather.windspeed <= 8.0 )   AUDIO_FILENR = ANSAGEBASE + WETTERSOUNDBASE + 82;      //mäßiger-schwacher Wind
        if ( outdoorWeather.windspeed > 8.0 && outdoorWeather.windspeed <= 14.0 )  AUDIO_FILENR = ANSAGEBASE + WETTERSOUNDBASE + 83;      //starker Wind
        if ( outdoorWeather.windspeed > 14.0 && outdoorWeather.windspeed <= 18.0 ) AUDIO_FILENR = ANSAGEBASE + WETTERSOUNDBASE + 84;      //stürmischer Wind
        if ( outdoorWeather.windspeed > 18 )                                       AUDIO_FILENR = ANSAGEBASE + WETTERSOUNDBASE + 85;      //Sturm
        AudioBufferIn(AUDIO_FILENR);
      }
      WetterAnsageSchritt = 3;  //Start Ansage Wetterlage Load Ansage Wind
    }

    if ( WetterAnsageSchritt == 3 && PlayAudioBuffer(0) == 2 && !autoModeChangeFlag  &&  WetterSequenz < 2000 )
    {
      WetterAnsageSchritt = 4; // Start Ansage Wind
    }
    if ( WetterAnsageSchritt == 4 && !Soundaktiv() )
    {
      WetterAnsageSchritt = 5; // Ende Ansage Wind
    }
    
    if ( WetterSequenz == 2005 && !autoModeChangeFlag ) {
      AUDIO_FILENR = ANSAGEBASE + getWeatherSound(outdoorWeather.weatherid2); 
      AudioBufferIn(AUDIO_FILENR);             // Wetterlage 2 (wenn vorhanden)
      PABStatus = PlayAudioBuffer(0);
      WetterAnsageSchritt = 11; //Start Ansage Wetterlage2
    }
    if ( WetterAnsageSchritt == 11 && !Soundaktiv() && !autoModeChangeFlag ) 
    {
      WetterAnsageSchritt = 12; //Ende Ansage Wetterlage2
    }

#endif
// ############# Wetteransage Ende

    if ( WetterSequenz == 1 || WetterSequenz == 2001 ) 
    {
      animation = F("WETTER_");
      if ( WetterSequenz == 1 ) animation += getWeatherIcon(outdoorWeather.weathericon1);
      if ( WetterSequenz == 2001 ) animation += getWeatherIcon(outdoorWeather.weathericon2);
      animation.toUpperCase();
#ifdef DEBUG
      Serial.printf("Wetteranimantion: %s ",animation.c_str());
#endif
      if ( loadAnimation(animation) )
      {
        WetterSequenz++;
        akt_aniframe = 0;
        akt_aniloop = 0;
        frame_fak = 0;
      }
      else            // Wetteranimation wurde nicht gefunden - sollte eigentlich nicht vorkommen!
      {
        WetterSequenz = 9999;  //Ende
        modeExtraTime = SHOW_MODE_TIMEOUT * -1;
#ifdef AUDIO_SOUND
        Play_MP3(99,true,0); //Stop
#endif
      }
    }  
#ifdef DEBUG
    if ( !autoModeChangeFlag ) Serial.printf("WetterAnsageSchritt: %i\n", WetterAnsageSchritt);
#endif
    if ( ( WetterSequenz > 1 && WetterSequenz < 2000 )  ||  ( WetterSequenz > 2001 && WetterSequenz < 9999 ) ) 
    {
      if ( showAnimation(brightness) && ( WetterAnsageSchritt < 5 || WetterAnsageSchritt == 10 || WetterAnsageSchritt == 11) )
      {
        modeExtraTime = 500;
        modeTimeout = millis();
        WetterSequenz++;
      }
      else
      { 
        delay(100);
        if ( WetterSequenz < 2000 && !autoModeChangeFlag && outdoorWeather.weathericon2.length() > 1 && outdoorWeather.weathericon1 != outdoorWeather.weathericon2  ) 
        {
#ifdef DEBUG
        Serial.println(F("2.WetterLage"));
#endif
          WetterAnsageSchritt = 10;  // 2. Wetterlage
          WetterSequenz = 2001;
        }
        else
        {
#ifdef DEBUG
        Serial.println(F("Ende Wetter"));
#endif
          modeExtraTime = SHOW_MODE_TIMEOUT * -1;
          modeTimeout = millis();
          delay(10);
          WetterSequenz = 0;
          WetterAnsageSchritt = 0;
        }
      }
    }
   break;
  }
#endif
// ######################## WETTER ENDE ##############
		case MODE_EXT_TEMP:
#ifdef DEBUG
     if ( ModeSequenz == 1 ) 
     { 
       Serial.println(F("************ Mode Aussentemperatur"));
		   Serial.println("Aussentemperatur: " + String(outdoorWeather.temperature));
     }
#endif
#ifdef AUDIO_SOUND
      if ( ModeSequenz == 2 && !autoModeChangeFlag ) {
        Temperaturansage(ANSAGEBASE,false,outdoorWeather.temperature,0);
      }
#endif
			renderer.clearScreenBuffer(matrix);
			if (outdoorWeather.temperature > 0)
			{
				matrix[1] = 0b0100000000000000;
				matrix[2] = 0b1110000000000000;
				matrix[3] = 0b0100000000000000;
			}
			if (outdoorWeather.temperature < 0)
			{
				matrix[2] = 0b1110000000000000;
			}
			renderer.setSmallText(String(int(abs(outdoorWeather.temperature) + 0.5)), TEXT_POS_BOTTOM, matrix);
			break;
		case MODE_EXT_HUMIDITY:
      modeExtraTime = 2000;
#ifdef DEBUG
    if ( ModeSequenz == 1 ) 
    { 
      Serial.println(F("************ Mode Luftfeuchtigkeit aussen"));
			Serial.println("Luftfeuchtigkeit aussen: " + String(outdoorWeather.humidity));
    }
#endif
#ifdef AUDIO_SOUND
      if ( ModeSequenz == 2 ) {
        Humidityansage(ANSAGEBASE,false,outdoorWeather.humidity,0);
      }
#endif
			renderer.clearScreenBuffer(matrix);
			if (outdoorWeather.humidity < 100)
				renderer.setSmallText(String(outdoorWeather.humidity), TEXT_POS_TOP, matrix);
			else
			{
				matrix[0] = 0b0010111011100000;
				matrix[1] = 0b0110101010100000;
				matrix[2] = 0b0010101010100000;
				matrix[3] = 0b0010101010100000;
				matrix[4] = 0b0010111011100000;
			}
			matrix[6] = 0b0100100000000000;
			matrix[7] = 0b0001000000000000;
			matrix[8] = 0b0010000000000000;
			matrix[9] = 0b0100100000000000;
			break;
#endif

#ifdef SENSOR_BME280
    case MODE_LUFTDRUCK:
#ifdef DEBUG
      if ( ModeSequenz == 1 ) Serial.println(F("************ Mode Luftdruckverlauf"));
#endif
      modeExtraTime = 2000;
      renderer.clearScreenBuffer(matrix);
      Luftdruckverlauf(matrix);
#ifdef AUDIO_SOUND
      AUDIO_FILENR = ANSAGEBASE + 64;   //Luftdruckverlauf
      if ( ModeSequenz == 3 ) {
          Play_MP3(AUDIO_FILENR,true,0);
          AUDIO_FILENR = ANSAGEBASE + luftdrucktendenz_soundbase;
          Play_MP3(AUDIO_FILENR,true,0);
      }
#endif

      break;
#endif

#if defined(BUZZER) || defined(AUDIO_SOUND)
		case MODE_TIMER:                      // Timer
#ifdef AUDIO_SOUND
      AUDIO_FILENR = ANSAGEBASE + 38;  //Timer
      if ( ModeSequenz == 1 ) {
        Play_MP3(AUDIO_FILENR,false,0);
      }
#endif
			renderer.clearScreenBuffer(matrix);
			renderer.setSmallText("TI", TEXT_POS_TOP, matrix);
			renderer.setSmallText(String(alarmTimer), TEXT_POS_BOTTOM, matrix);
			break;
#endif

#ifdef SHOW_MODE_TEST
		case MODE_TEST:
			renderer.clearScreenBuffer(matrix);
			if (testColumn == 10)
				testColumn = 0;
			matrix[testColumn] = 0b1111111111110000;
			testColumn++;
			break;
		case MODE_RED:
		case MODE_GREEN:
		case MODE_BLUE:
		case MODE_WHITE:
			renderer.setAllScreenBuffer(matrix);
			break;
#endif
		case MODE_BLANK:
			renderer.clearScreenBuffer(matrix);
			break;
      
    case MODE_IP:
      if ( ModeSequenz == 1 ) 
      {
          WiFi.isConnected() ? feedText = "  IP: " : feedText = "  AP-IP: ";
          
          feedText += String(myIP[0]) + '.' + String(myIP[1]) + '.' + String(myIP[2]) + '.' + String(myIP[3]) + "   ";

          feedPosition = 0;
          feedColor = WHITE;
#ifdef AUDIO_SOUND
          myIPidx = 0;
#endif
      }
#ifdef AUDIO_SOUND
      if ( feedPosition == 0 ) {
        AudioBufferClear();
        AUDIO_FILENR = ANSAGEBASE + 47;  //IP-Adresse
        Play_MP3(AUDIO_FILENR,false,0);
        myIPidx = 0;
      }
#ifdef DEBUG
      Serial.printf("FeedPos: %i  FeedPosChar: ", feedPosition);
      Serial.println(feedText[feedPosition]);
#endif      
      if ( feedText[feedPosition] == ':' ) ZahltoAudioBuffer(ANSAGEBASE, myIP[myIPidx]);
      
      if ( feedText[feedPosition+2] == '.' ) 
      {
        AudioBufferIn(ANSAGEBASE + 57); // Punkt
        myIPidx++;
        ZahltoAudioBuffer(ANSAGEBASE, myIP[myIPidx]);
      }
      PABStatus = PlayAudioBuffer(0) ;
     
#endif       

		case MODE_FEED:
        if ( feedPosition == 0 ) {
          
#ifdef DEBUG
      Serial.println(feedText);
#endif
          feedText.replace("\xC3\x84","\x7F"); // Ä
          feedText.replace("\xC3\xA4","\x80"); // ä
          feedText.replace("\xC3\x9C","\x81"); // Ü
          feedText.replace("\xC3\xBC","\x82"); // ü
          feedText.replace("\xC3\x96","\x83"); // Ö
          feedText.replace("\xC3\xB6","\x84"); // ö
          feedText.replace("\xC3\x9F","\x85"); // ß
        }
#ifdef DEBUG_EVENTS
      Serial.printf("Eventzeichen: %c : %x\n",feedText[feedPosition],feedText[feedPosition]);
#endif
      if ( feedText[feedPosition] < 32     || feedText[feedPosition]     > 133 ) feedText[feedPosition]     = '.';
      if ( feedText[feedPosition + 1] < 32 || feedText[feedPosition + 1] > 133 ) feedText[feedPosition + 1] = '.';
      if ( feedText[feedPosition + 2] < 32 || feedText[feedPosition + 2] > 133 ) feedText[feedPosition + 2] = '.';

			for (uint8_t y = 0; y <= 5; y++)
			{
				renderer.clearScreenBuffer(matrix);
				for (uint8_t z = 0; z <= 6; z++)
				{
          uint8_t b = pgm_read_byte(&lettersBig[feedText[feedPosition] - 32][z]);
//					matrix[2 + z] |= (lettersBig[feedText[feedPosition] - 32][z] << 11 + y) & 0b1111111111100000;
          matrix[2 + z] |= (b << 11 + y) & 0b1111111111100000;
          b = pgm_read_byte(&lettersBig[feedText[feedPosition + 1] - 32][z]);
//					matrix[2 + z] |= (lettersBig[feedText[feedPosition + 1] - 32][z] << 5 + y) & 0b1111111111100000;
          matrix[2 + z] |= (b << 5 + y) & 0b1111111111100000;
          b = pgm_read_byte(&lettersBig[feedText[feedPosition + 2] - 32][z]);
//					matrix[2 + z] |= (lettersBig[feedText[feedPosition + 2] - 32][z] << y - 1) & 0b1111111111100000;
          matrix[2 + z] |= (b << y - 1) & 0b1111111111100000;
				}
				writeScreenBuffer(matrix, feedColor, brightness);
				delay(FEED_SPEED);
        handle_Webserver(__LINE__);
        if ( mode == MODE_IP ) 
        {
          delay(FEED_SPEED/2);
#ifdef AUDIO_SOUND
          if ( PABStatus > 0 ) PABStatus = PlayAudioBuffer(0);
#endif
        }
			}
			feedPosition++;
			if (feedPosition == feedText.length() - 2)
			{
				feedPosition = 0;
        if ( post_event_ani ) 
        {
          post_event_ani = false;
          while ( showAnimation(brightness) ) 
          {
#ifdef DEBUG_EVENTS
           Serial.println("Starte Event Post Animation: " + String(myanimation.name) + " Loop: " +  String(akt_aniloop) + " Frame: " + String(akt_aniframe) );
#endif           
          }         
        }

#ifdef AUDIO_SOUND
        if ( audio_stop_nach_feed ) Play_MP3(99,false,0); //Stop
        audio_stop_nach_feed = true;
#endif
        if ( events[0].aktiv ) events[0].aktiv  = false;  // Setze Event 0 inaktiv.
				if ( mode != MODE_IP ) setMode(MODE_TIME);
			}
			break;
      case MODE_SHOWANIMATION:
      break;
      case MODE_MAKEANIMATION:
      break;
      case MODE_ALARMANIMATION:
      break;
		}

		// turn off LED behind IR-sensor
#ifdef IR_LETTER_OFF
		renderer.unsetPixelInScreenBuffer(IR_LETTER_X, IR_LETTER_Y - 1, matrix);
#endif

		//debugScreenBuffer(matrixOld);
#ifdef DEBUG_MATRIX
		debugScreenBuffer(matrix);
#endif

		// write screenbuffer to display
 
		switch (mode)
		{
    case MODE_BLANK:
      writeScreenBufferFade(matrixOld, matrix, settings.mySettings.color, brightness);
    break;
		case MODE_TIME:
      if ( ldr_update )
      {
        writeScreenBuffer(matrix, settings.mySettings.color, brightness);
      }
//#ifdef SHOW_TIME_BUTTON
      else if (SHOW_TIME_BUTTON_BOOL )
      {         
        renderer.clearScreenBuffer(matrixOld);
//        writeScreenBuffer(matrix, settings.mySettings.color, brightness);
        writeScreenBufferFade(matrixOld, matrix, settings.mySettings.color, brightness);
      }
//#endif
      else if ( playanimation )
      {
        if ( loadAnimation(animation) ) 
        {
           akt_aniframe = 0;
           akt_aniloop = 0;
           frame_fak = 0;
#ifdef DEBUG
             Serial.println("Starte StundeMinute Animation: " + String(myanimation.name) );
#endif 
           while ( showAnimation(brightness) ) {}
        }
        playanimation = false;
        if ( settings.mySettings.colorChange == COLORCHANGE_FIVE || settings.mySettings.colorChange == COLORCHANGE_HOUR ) settings.mySettings.color = aktHour;
        if ( settings.mySettings.corner_colorChange == COLORCHANGE_MAIN ) settings.mySettings.corner_color = settings.mySettings.color;
        renderer.clearScreenBuffer(matrixOld);
        writeScreenBuffer(matrix, settings.mySettings.color, brightness);
        runTransitionOnce = false;
        screenBufferNeedsUpdate = false;  
      }
      else if ( hny > 0 )
      {
        farbenmeer(matrixOld, matrix, settings.mySettings.color, brightness);
      }
      else if ( lastMode == MODE_ALARMANIMATION ) 
      {
        writeScreenBuffer(matrix, settings.mySettings.color, brightness);
      }
      else
      {
        if (aktMinute % 5 != 0 )
        {
          writeScreenBufferFade(matrixOld, matrix, settings.mySettings.color, brightness);
        }
        else
        {
          akt_transition = settings.mySettings.transition;
          if ( settings.mySettings.transition == TRANSITION_RANDOM ) 
          {
            akt_transition_old = akt_transition;
            for (uint8_t i = 0; i <= 20; i++)
            {
              akt_transition = random(TRANSITION_NORMAL+1, TRANSITION_MAX);
              if ( akt_transition != akt_transition_old ) break;
            }
          }
          if ( settings.mySettings.transition == TRANSITION_ALLE_NACHEINANDER ) 
          {
            akt_transition_old++;
            if ( akt_transition_old >= TRANSITION_MAX ) akt_transition_old = TRANSITION_NORMAL+1;
            akt_transition = akt_transition_old;
          }
       
          if (akt_transition == TRANSITION_NORMAL) 
            writeScreenBuffer(matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_MOVEUP)
            moveScreenBufferUp(matrixOld, matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_MOVEDOWN)
            moveScreenBufferDown(matrixOld, matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_MOVELEFT)
            moveScreenBufferLeft(matrixOld, matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_MOVERIGHT)
            moveScreenBufferRight(matrixOld, matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_MOVELEFTDOWN)
            moveScreenBufferLeftDown(matrixOld, matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_MOVERIGHTDOWN)
            moveScreenBufferRightDown(matrixOld, matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_MOVECENTER)
            moveScreenBufferCenter(matrixOld, matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_FADE)
            writeScreenBufferFade(matrixOld, matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_FARBENMEER)
            farbenmeer(matrixOld, matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_MATRIX)
            matrix_regen(matrixOld, matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_SPIRALE_LINKS)
            moveSeriell(matrixOld, matrix, settings.mySettings.color, brightness, SPIRALE_LINKS);
          else if (akt_transition == TRANSITION_ZEILENWEISE)
            moveSeriell(matrixOld, matrix, settings.mySettings.color, brightness, ZEILENWEISE);
          else if (akt_transition == TRANSITION_SPIRALE_RECHTS)
            moveSeriell(matrixOld, matrix, settings.mySettings.color, brightness, SPIRALE_RECHTS);
          else if (akt_transition == TRANSITION_MITTE_LINKSHERUM)
            moveSeriell(matrixOld, matrix, settings.mySettings.color, brightness, MITTE_LINKSHERUM);
          else if (akt_transition == TRANSITION_REGENBOGEN)
            regenbogen(matrixOld, matrix, settings.mySettings.color, brightness);
          else if (akt_transition == TRANSITION_QUADRATE)
            quadrate(matrixOld, matrix, settings.mySettings.color, brightness);
          else 
          {
            writeScreenBuffer(matrix, settings.mySettings.color, brightness);
          }
        }
      }
      
			break;
    case MODE_ANSAGE:
//      writeScreenBufferFade(matrixOld, matrix, YELLOW, brightness);
      writeScreenBuffer(matrix, YELLOW, brightness);
      break;
#ifdef APIKEY

    case MODE_WETTER:
    break;
    case MODE_EXT_TEMP:
      if ( strlen(settings.mySettings.openweatherapikey) > 25 )
      {
        if (outdoorWeather.temperature < -10 ) Tempcolor = VIOLET;
        else if (outdoorWeather.temperature >= -10  && outdoorWeather.temperature < -5) Tempcolor = BLUE;
        else if (outdoorWeather.temperature >= -5  && outdoorWeather.temperature < 0) Tempcolor = LIGHTBLUE;
        else if (outdoorWeather.temperature >= 0  && outdoorWeather.temperature < 5) Tempcolor = CYAN;
        else if (outdoorWeather.temperature >= 5  && outdoorWeather.temperature < 10) Tempcolor = MINTGREEN;
        else if (outdoorWeather.temperature >= 10  && outdoorWeather.temperature < 15) Tempcolor = GREEN;
        else if (outdoorWeather.temperature >= 15  && outdoorWeather.temperature < 20) Tempcolor = GREENYELLOW;
        else if (outdoorWeather.temperature >= 20  && outdoorWeather.temperature < 25) Tempcolor = YELLOW;
        else if (outdoorWeather.temperature >= 25  && outdoorWeather.temperature < 30) Tempcolor = ORANGE;
        else if (outdoorWeather.temperature >= 30  && outdoorWeather.temperature < 40) Tempcolor = RED;
        else if (outdoorWeather.temperature >= 40  ) Tempcolor = RED_50;
        writeScreenBuffer(matrix, Tempcolor, brightness);
      }
      break;
#endif
#ifdef SENSOR_BME280     
    case MODE_TEMP:
      if (roomTemperature < 10 ) Tempcolor = VIOLET;
      else if (roomTemperature >= 10  && roomTemperature < 12) Tempcolor = BLUE;
      else if (roomTemperature >= 12  && roomTemperature < 15) Tempcolor = LIGHTBLUE;
      else if (roomTemperature >= 15  && roomTemperature < 17) Tempcolor = CYAN;
      else if (roomTemperature >= 17  && roomTemperature < 19) Tempcolor = MINTGREEN;
      else if (roomTemperature >= 19  && roomTemperature < 20) Tempcolor = GREEN;
      else if (roomTemperature >= 20  && roomTemperature < 22) Tempcolor = GREENYELLOW;
      else if (roomTemperature >= 22  && roomTemperature < 24) Tempcolor = YELLOW;
      else if (roomTemperature >= 24  && roomTemperature < 27) Tempcolor = ORANGE;
      else if (roomTemperature >= 27  && roomTemperature < 30) Tempcolor = RED;
      else if (roomTemperature >= 30  ) Tempcolor = RED_50;
      writeScreenBuffer(matrix, Tempcolor, brightness);
      break;
#endif
    case MODE_WEEKDAY:
      if ( weekday() == 1 ) writeScreenBuffer(matrix, RED_25, brightness); //Sonntag
      if ( weekday() == 7 ) writeScreenBuffer(matrix, GREEN_25, brightness); //Samstag
      if ( weekday() > 1 && weekday() < 7 ) writeScreenBuffer(matrix, YELLOW_50, brightness); //Wochentag
      
      break;
    case MODE_DATE:
      writeScreenBuffer(matrix, YELLOW, brightness);
      break;
    case MODE_MOONPHASE:
      writeScreenBufferFade(matrixOld, matrix, ORANGE, brightness);
//      writeScreenBuffer(matrix, ORANGE, brightness);
      break;
      
#ifdef SHOW_MODE_TEST
    case MODE_TEST:
#ifdef DEBUG
      if ( ModeSequenz == 1 ) Serial.println(F("************ Mode Matrixtest"));
#endif
#ifdef AUDIO_SOUND   
      AUDIO_FILENR = ANSAGEBASE + 39; //Matrixtest
      if ( ModeSequenz == 1 ) {
        Play_MP3(AUDIO_FILENR,false,0);
      }
#endif
      cornercolorold = settings.mySettings.corner_color;
      settings.mySettings.corner_color = WHITE;
      writeScreenBuffer(matrix, WHITE, TEST_BRIGHTNESS);
      settings.mySettings.corner_color = cornercolorold;
    break;
    
		case MODE_RED:
#ifdef DEBUG
      if ( ModeSequenz == 1 ) Serial.println(F("************ Mode rot"));
#endif
#ifdef AUDIO_SOUND
      AUDIO_FILENR = ANSAGEBASE + 43;  //Alles rot
      if ( ModeSequenz == 2 ) { 
        Play_MP3(AUDIO_FILENR,false,0);
      }
#endif
      cornercolorold = settings.mySettings.corner_color;
      settings.mySettings.corner_color = RED;
			writeScreenBuffer(matrix, RED, TEST_BRIGHTNESS);
      settings.mySettings.corner_color = cornercolorold;
			break;
      
		case MODE_GREEN:
#ifdef DEBUG
      if ( ModeSequenz == 1 ) Serial.println(F("************ Mode grün"));
#endif
#ifdef AUDIO_SOUND
      AUDIO_FILENR = ANSAGEBASE + 44; //Alles grün
      if ( ModeSequenz == 2 )  {
        Play_MP3(AUDIO_FILENR,false,0);
      }
#endif
      cornercolorold = settings.mySettings.corner_color;
      settings.mySettings.corner_color = GREEN;
			writeScreenBuffer(matrix, GREEN, TEST_BRIGHTNESS);
      settings.mySettings.corner_color = cornercolorold;
			break;
      
		case MODE_BLUE:
#ifdef DEBUG
      if ( ModeSequenz == 1 ) Serial.println(F("************ Mode blau"));
#endif
#ifdef AUDIO_SOUND
      AUDIO_FILENR = ANSAGEBASE + 45; //Alles blau
      if ( ModeSequenz == 2 ) {
        Play_MP3(AUDIO_FILENR,false,0);
      }
#endif
      cornercolorold = settings.mySettings.corner_color;
      settings.mySettings.corner_color = BLUE;
			writeScreenBuffer(matrix, BLUE, TEST_BRIGHTNESS);
      settings.mySettings.corner_color = cornercolorold;
			break;
      
		case MODE_WHITE:
#ifdef DEBUG
      if ( ModeSequenz == 1 ) Serial.println(F("************ Mode weiss"));
#endif
#ifdef AUDIO_SOUND
      AUDIO_FILENR = ANSAGEBASE + 46;  //Alles weiss
      if ( ModeSequenz == 2 ) {
        Play_MP3(AUDIO_FILENR,false,0);
      }
#endif
      cornercolorold = settings.mySettings.corner_color;
      settings.mySettings.corner_color = WHITE;
			writeScreenBuffer(matrix, WHITE, TEST_BRIGHTNESS);
      settings.mySettings.corner_color = cornercolorold;
			break;
      
#endif
    case MODE_IP:
#ifdef DEBUG
      if ( ModeSequenz == 1 ) Serial.println(F("************ Mode IP"));
#endif
		case MODE_FEED:
			writeScreenBuffer(matrix, feedColor, brightness);
			break;
    case MODE_SHOWANIMATION:
      if ( !showAnimation(brightness) )
      {
        akt_aniframe = 0;
        akt_aniloop = 0;
        screenBufferNeedsUpdate = true;
      }
    break;
    case MODE_MAKEANIMATION:
      showMakeAnimation(brightness);
    break;
    case MODE_ALARMANIMATION:
        if ( !showAnimation(brightness) )
        {
          akt_aniframe = 0;
          akt_aniloop = 0;
          setMode(MODE_TIME);
        }        
    break;
		default:
			if (runTransitionOnce)
			{
        writeScreenBuffer(matrix, settings.mySettings.color, brightness);
				runTransitionOnce = false;
				testColumn = 0;
			}
			else
				writeScreenBuffer(matrix, settings.mySettings.color, brightness);
			break;
		}
    ldr_update = false;
	}
  
	// Wait for mode timeout then switch back to time

  if ((millis() > (modeExtraTime + modeTimeout + SHOW_MODE_TIMEOUT)) && modeTimeout ) 
	{
  
    ModeSequenz = 0;
    if ( mode < MODE_SECONDS && !autoModeChangeFlag ) {
      setMode(mode++);
    }
    else
    {
#ifdef DEBUG
    Serial.println(F("Mode TIME"));
#endif  
      settings.mySettings.color = colorsaver;
#ifdef DEBUG
        Serial.printf("Color changed to: %u\r\n", settings.mySettings.color);
#endif
  	  setMode(MODE_TIME);
      autoModeChangeFlag = false;
    }
      #ifdef DEBUG
        Serial.printf("2576: Mode: %i\n",mode);
     #endif
	}

#ifdef DEBUG_FPS
	debugFps();
#endif

  delay(5);
  // Call HTTP- and OTA-handle
  handle_Webserver(__LINE__);
  delay(5);
  ArduinoOTA.handle();
} // loop()

//*****************************************************************************
//*************************** ENDE LOOP ***************************************
//*****************************************************************************

/******************************************************************************
  Transitions
******************************************************************************/

void moveScreenBufferUp(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
	for (uint8_t z = 0; z <= 9; z++)
	{
    ledDriver.clear();
		for (uint8_t i = 0; i <= 9; i++) 
		{
      if ( i == 9 ) 
      {
        screenBufferOld[i] = screenBufferNew[z]&0b1111111111100000;
      }
      else
      {
        screenBufferOld[i] = screenBufferOld[i + 1]&0b1111111111100000;
      }
      for (uint8_t x = 0; x <= 10; x++)
      {
        if ( 8-z >= i ) {
          if (bitRead(screenBufferOld[i], 15 - x)) ledDriver.setPixel(x, i, colorold, brightness);
        }
        else
        {
          if (bitRead(screenBufferOld[i], 15 - x)) ledDriver.setPixel(x, i, color, brightness);
        }
      }
    }
    ledDriver.show();
		handle_Webserver(__LINE__);
		delay(TRANSITION_SPEED);
	}
  writeScreenBuffer(screenBufferNew, color, brightness);
}

void moveScreenBufferDown(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
  for (int z = 9; z >= 0; z--)
  {
    ledDriver.clear();
    for (int i = 9; i >= 0; i--) 
    {
     if ( i == 0 ) 
      {
        screenBufferOld[i] = screenBufferNew[z]&0b1111111111100000;
      }
      else
      {
        screenBufferOld[i] = screenBufferOld[i - 1]&0b1111111111100000;
      }
      for (uint8_t x = 0; x <= 10; x++)
      {
        if ( 8-z >= i ) {
          if (bitRead(screenBufferOld[i], 15 - x)) ledDriver.setPixel(x, i, color, brightness);
        }
        else
        {
          if (bitRead(screenBufferOld[i], 15 - x)) ledDriver.setPixel(x, i, colorold, brightness);
        }
      }      
    }
    ledDriver.show();
    handle_Webserver(__LINE__);
    delay(TRANSITION_SPEED);
  }
  writeScreenBuffer(screenBufferNew, color, brightness);
}

void moveScreenBufferLeft(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
  uint16_t m_old[10] = {};
  uint16_t m_new[10] = {};
  for (uint8_t ze = 0; ze <= 9; ze++)
  {
    m_old[ze] = screenBufferOld[ze];
    m_new[ze] = screenBufferNew[ze];
  }
  for (uint8_t z = 0; z <= 10; z++)
  {
    ledDriver.clear();
    for (uint8_t i = 0; i <= 9; i++) 
    {
      m_old[i] = (( m_old[i]&0b1111111111100000 )<<1  | (( m_new[i]>>10 ) & 0b0000000000100000 )) & 0b1111111111100000;
      m_new[i] = (m_new[i]<<1)&0b1111111111100000;
      
      for (uint8_t x = 0; x <= 10; x++)
      {
        if ( x > 9-z  ) 
        {
          if (bitRead(m_old[i], 15 - x)) ledDriver.setPixel(x, i, color, brightness);
        }
        else
        {
           if (bitRead(m_old[i], 15 - x)) ledDriver.setPixel(x, i, colorold, brightness);
        }
      }
    }      
    ledDriver.show();
    handle_Webserver(__LINE__);
    delay(TRANSITION_SPEED);
  }
  writeScreenBuffer(screenBufferNew, color, brightness);
}

void moveScreenBufferRight(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
  uint16_t m_old[10] = {};
  uint16_t m_new[10] = {};
  for (uint8_t ze = 0; ze <= 9; ze++)
  {
    m_old[ze] = screenBufferOld[ze];
    m_new[ze] = screenBufferNew[ze];
  }
  for (uint8_t z = 0; z <= 10; z++)
  {
    ledDriver.clear();
    for (uint8_t i = 0; i <= 9; i++) 
    {
      m_old[i] = (m_old[i]>>1|m_new[i]<<10)&0b1111111111100000;
      m_new[i] = (m_new[i]>>1)&0b1111111111100000;

      for (uint8_t x = 0; x <= 10; x++)
      {
        if ( x > z  ) 
        {
          if (bitRead(m_old[i], 15 - x)) ledDriver.setPixel(x, i, colorold, brightness);
        }
        else
        {
           if (bitRead(m_old[i], 15 - x)) ledDriver.setPixel(x, i, color, brightness);
        }
      }
    }
    ledDriver.show();
    handle_Webserver(__LINE__);
    delay(TRANSITION_SPEED);
  }
  writeScreenBuffer(screenBufferNew, color, brightness);
}

void moveScreenBufferLeftDown(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
    for (int z = 0; z <= 9; z++)
    {
      ledDriver.clear();
      for (int i = 0; i <= 8 ; i++) 
      {
        screenBufferOld[9-i] = (screenBufferOld[8-i]&0b1111111111100000)<<1;
      }   
      for (int i = 0; i <= z ; i++) 
      {
        screenBufferOld[i] = ((screenBufferNew[9+i-z]>>(14-z))<<5)&0b1111111111100000;
      }

      for (int y = 0; y <= 9; y++)
      {
        for (uint8_t x = 0; x <= 10; x++)
        {
          if ( y <= z ) {
            if (bitRead(screenBufferOld[y], 15 - x)) ledDriver.setPixel(x, y, color, brightness);
          }
          else
          {
            if (bitRead(screenBufferOld[y], 15 - x)) ledDriver.setPixel(x, y, colorold, brightness);
          }
        }    
      }  

      ledDriver.show();
      handle_Webserver(__LINE__);
      delay(TRANSITION_SPEED);
    }
    writeScreenBuffer(screenBufferNew, color, brightness);
}

void moveScreenBufferRightDown(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
    for (int z = 0; z <= 9; z++)
    {
      ledDriver.clear();
      for (int i = 0; i <= 8 ; i++) 
      {
        screenBufferOld[9-i] = screenBufferOld[8-i]>>1&0b1111111111100000;
      }   
      for (int i = 0; i <= z ; i++) 
      {
        screenBufferOld[i] = (screenBufferNew[9+i-z]<<(9-z))&0b1111111111100000;
      }

      for (int y = 0; y <= 9; y++)
      {
        for (uint8_t x = 0; x <= 10; x++)
        {
          if ( y <= z ) {
            if (bitRead(screenBufferOld[y], 15 - x)) ledDriver.setPixel(x, y, color, brightness);
          }
          else
          {
            if (bitRead(screenBufferOld[y], 15 - x)) ledDriver.setPixel(x, y, colorold, brightness);
          }
        }    
      }  

      ledDriver.show();
      handle_Webserver(__LINE__);
      delay(TRANSITION_SPEED);
    }
    writeScreenBuffer(screenBufferNew, color, brightness);
}

void moveScreenBufferCenter(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
    uint16_t mask[5] = {};
    mask[0] = 0b1000000000100000;
    mask[1] = 0b1100000001100000;
    mask[2] = 0b1110000011100000;
    mask[3] = 0b1111000111100000;
    mask[4] = 0b1111101111100000;
    uint16_t m_old[10] = {};
    uint16_t m_new[10] = {};
    for (uint8_t ze = 0; ze <= 9; ze++)
    {
      m_old[ze] = screenBufferOld[ze]&0b1111111111100000;
      m_new[ze] = screenBufferNew[ze];
    }    
//##################### Old zur Mitte #########################################
    for (int i = 0; i <= 4; i++) 
    {
      for (int z = 0; z <= 4; z++)
      {
        m_old[z] = ((m_old[z]&0b1111110000000000)>>1)|((m_old[z]&0b0000001111110000)<<1);
        m_old[9-z] = ((m_old[9-z]&0b1111110000000000)>>1)|((m_old[9-z]&0b0000001111110000)<<1);
      }
      for (int z = 0; z <= 3; z++)
      {
        m_old[z+5] = m_old[z+6];
        m_old[4-z] = m_old[3-z];
      }
      m_old[9] = 0;
      m_old[0] = 0;
      writeScreenBuffer(m_old, colorold, brightness);
      handle_Webserver(__LINE__);
      delay(TRANSITION_SPEED);
    }
//###################### New aus der Mitte ########################################
  for (int i = 4; i >= 0 ; i--)
  {
    for (int z = 0; z <= 4-i; z++)
    {
       m_old[i+z] =   ((m_new[z]  &mask[4-i])>>(i+1)&0b1111110000000000)|((m_new[z]  &mask[4-i])<<(i+1)&0b0000011111100000);
       m_old[9-i-z] = ((m_new[9-z]&mask[4-i])>>(i+1)&0b1111110000000000)|((m_new[9-z]&mask[4-i])<<(i+1)&0b0000011111100000); 
    }
    writeScreenBuffer(m_old, color, brightness);
    handle_Webserver(__LINE__);
    delay(TRANSITION_SPEED);   
  }

  handle_Webserver(__LINE__);
  writeScreenBuffer(screenBufferNew, color, brightness);
}




void matrix_regen(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
  uint16_t mline[11] = {0};
  uint16_t wline[11] = {0};
  uint16_t sline[11] = {0};
  uint8_t aktline;
  uint16_t mleer = 0;  // zu prüfen ob wir fertig sind

  uint8_t mstep = 0;
  uint16_t mline_max[11] = {0};
  uint16_t brightnessBuffer[11][12] = {0};
  uint16_t brightness_16 = brightness;

  uint16_t zufallszeile[11] = {0,1,2,3,4,5,6,7,8,9,10};
  uint16_t zufallsbuffer;
  uint16_t zufallsindex;
// Zufälliges Vertauschen von jeweils 2 Zeilenwerten:
   for (uint8_t i = 0; i <= 10; i++)
   {
     zufallsindex = random(0,11);
     zufallsbuffer = zufallszeile[zufallsindex];
     zufallszeile[zufallsindex] = zufallszeile[i];
     zufallszeile[i] = zufallsbuffer;
     
   }
// Variablen init
   for (uint8_t line = 0; line <= 10; line++) 
   {
     sline[line] = (11 - (zufallszeile[line] % 11 )) * 5 / 2;
     mline_max[line] = 0;
     mline[line] = 0;
     wline[line] = 0;
   }

   for (uint16_t i = 0; i <= 1200; i++)
   {
     aktline = zufallszeile[i % 11];

     if ( sline[aktline] > 0 ) sline[aktline]--;
     if ( sline[aktline] == 0 ) 
     {
       sline[aktline] = 3 - (aktline % 2);
       
       if ( mline[aktline] == 0 && mline_max[aktline] < 10)
       {
         mline[aktline] = 1;
         mline_max[aktline]++;
       }
       else 
       {
         if ( mline_max[aktline] < 11 )  // solange grün hinzu bis unten erreicht ist
         {
           if ( random(0,7) == 0 ) 
           {
             mline[aktline] = mline[aktline]<<1;
             mline[aktline] = mline[aktline]|1;
             wline[aktline] = wline[aktline]<<1;
           }
           else
           {
             wline[aktline] = wline[aktline]<<1;
             wline[aktline] = wline[aktline]|1;
             mline[aktline] = mline[aktline]<<1;
           } 
           mline_max[aktline]++;
         }
         else
         {
           mline[aktline] = mline[aktline]<<1;
           wline[aktline] = wline[aktline]<<1;
           if ( (mline[aktline]&0x3FF)  == 0 && (wline[aktline]&0x3FF) == 0 ) mleer = mleer | 1<<aktline;  
         }
       }
       ledDriver.clear();
       for ( uint16_t y = 0; y <= 9; y++ )
       {
         for ( uint16_t x = 0; x <= 10; x++ )
         {
           if ( y > mline_max[x]-1 ) 
           {
             if (bitRead(screenBufferOld[y], 15 - x)) ledDriver.setPixel(x, y, colorold, brightness);
           }
           else
           {
             if (bitRead(screenBufferNew[y], 15 - x)) ledDriver.setPixel(x, y, color, brightness);
           }
           brightnessBuffer[y][x] = 0;
           if ( wline[x] & (1<<y) )
           {
             brightnessBuffer[y][x] = brightness_16 / 9;
             if ( brightnessBuffer[y][x] < 3) brightnessBuffer[y][x] = 2;
           } 
           if ( mline[x] & (1<<y) )
           {
             brightnessBuffer[y][x] =  brightness_16 * 10 / 9;
             if ( brightnessBuffer[y][x] > 254 ) brightnessBuffer[y][x] = 255;
           } 
           
           if ( brightnessBuffer[y][x] > 0 ) 
           {
             ledDriver.setPixel(x, y, GREEN, brightnessBuffer[y][x]);
           }
         } // x
       }  // y 
       ledDriver.show();
       delay (int(TRANSITION_SPEED / 9)); 
       delay (1);
     }  
     handle_Webserver(__LINE__);
     if ( i > 100 && mleer == 0x7FF) break;
   }

   writeScreenBuffer(screenBufferNew, color, brightness);
   colorold = color;
}

void moveSeriell(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness, uint8_t sertype)
{
  uint16_t pointerbuffer;
  uint16_t xold_dest;
  uint16_t yold_dest;
  uint16_t xold_source;
  uint16_t yold_source;
  uint16_t xnew_dest;
  uint16_t ynew_dest;
  uint16_t xnew_source;
  uint16_t ynew_source;
  int s_old;
  int c;
  int s_new;

  int aquad;
  int adelay;

  for (int a = 0; a <= 109; a++)
  {
    ledDriver.clear();
    for (int b = 0; b <= 109; b++)
    {
      s_old = a + b +1;
      pointerbuffer = pgm_read_word(&seriellpointer[sertype][b]);
      xold_dest=pointerbuffer%11;             //seriellpointer ist in Modes.h definiert
      yold_dest=pointerbuffer/11;
      pointerbuffer = pgm_read_word(&seriellpointer[sertype][s_old]);
      xold_source=pointerbuffer%11;
      yold_source=pointerbuffer/11;

      c = 109 - b;
      s_new = a - c;
      
      xnew_dest=xold_dest;
      ynew_dest=yold_dest;
      pointerbuffer = pgm_read_word(&seriellpointer[sertype][s_new]);
      xnew_source=pointerbuffer%11;
      ynew_source=pointerbuffer/11;
      
      if (  c > a ) 
      {
        if (bitRead(screenBufferOld[yold_source],15-xold_source)) ledDriver.setPixel(xold_dest, yold_dest, colorold, brightness);
      }
      else
      {
        if (bitRead(screenBufferNew[ynew_source],15-xnew_source)) ledDriver.setPixel(xnew_dest, ynew_dest, color, brightness);
      }
    }
    
    ledDriver.show();
    handle_Webserver(__LINE__);
    aquad = (130-a)*(130-a);   // damit wir am Ende quadratisch immer langsamer werden
//    delay(2*TRANSITION_SPEED/(1+((120-a)/10)));
    adelay = 5 + ( 360 * TRANSITION_SPEED / aquad);
    delay(adelay);
  }   
  writeScreenBuffer(screenBufferNew, color, brightness);
  colorold = color;
}

void farbenmeer(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
  uint16_t zufallszeile[10] = {0,1,2,3,4,5,6,7,8,9};
  uint16_t zufallsbuffer;
  uint16_t zufallsspalte[11] = {0,1,2,3,4,5,6,7,8,9,10};
//  uint16_t zufallsspalte[11] = {0x20,0x40,0x80,0x100,0x200,0x400,0x800,0x1000,0x2000,0x4000,0x8000};
  uint16_t zufallsindex;
// Zufälliges Vertauschen von jeweils 2 Zeilenwerten:
  for (uint8_t i = 0; i <= 9; i++)
  {
    zufallsindex = random(0,10);
    zufallsbuffer = zufallszeile[zufallsindex];
    zufallszeile[zufallsindex] = zufallszeile[i];
    zufallszeile[i] = zufallsbuffer;
  }
// Zufälliges Vertauschen von jeweils 2 Spaltennwerten:
  for (uint8_t i = 0; i <= 10; i++)
  {
    zufallsindex = random(0,11);
    zufallsbuffer = zufallsspalte[zufallsindex];
    zufallsspalte[zufallsindex] = zufallsspalte[i];
    zufallsspalte[i] = zufallsbuffer;
  }
// Farben füllen
  for (uint8_t x = 0; x <= 10; x++)
  {
    for (uint8_t y = 0; y <= 9; y++)
    {
      zufallsindex = y + x;
      if ( zufallsindex > 10) zufallsindex = zufallsindex - 11;
               screenBufferOld[zufallszeile[y]] = screenBufferOld[zufallszeile[y]] | zufallsspalte[zufallsindex];
      ledDriver.setPixel(zufallsspalte[zufallsindex], zufallszeile[y], random(1,COLOR_COUNT+1) , brightness);
      ledDriver.show();
      handle_Webserver(__LINE__);
      if ( wortuhrinit ) {
        delay (60-5*x);
      } 
      else
      {
        delay (11-x);
      }
    }
  }
// Farben leeren
  for (uint8_t x = 0; x <= 10; x++)
  {
    for (uint8_t y = 0; y <= 9; y++)
    {
      zufallsindex = y + x;
      if ( zufallsindex > 10) zufallsindex = zufallsindex - 11;
      if ( bitRead(screenBufferNew[zufallszeile[y]], 15 - zufallsspalte[zufallsindex]))
      {
        ledDriver.setPixel(zufallsspalte[zufallsindex], zufallszeile[y], color , brightness);
      }
      else
      {
        ledDriver.setPixel(zufallsspalte[zufallsindex], zufallszeile[y], color , 0);
      }
      ledDriver.show();
      handle_Webserver(__LINE__);
      if ( wortuhrinit ) {
        delay (5+4*x);
      } 
      else
      {
        delay (1+x);
      }
      
    }
  }  
  writeScreenBuffer(screenBufferNew, color, brightness);
  colorold = color;
}


void regenbogen(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
  int startbogen = 0;
  int bogenidx = 0;

  uint8_t bogen[10][12] = {
             {0      ,0      ,0      ,0      ,RED    ,RED    ,RED    ,0      ,0      ,0      ,0     },
             {0      ,RED    ,RED    ,RED    ,ORANGE ,ORANGE ,ORANGE ,RED    ,RED    ,RED    ,0     },
             {RED    ,ORANGE ,ORANGE ,ORANGE ,YELLOW ,YELLOW ,YELLOW ,ORANGE ,ORANGE ,ORANGE ,RED   },
             {ORANGE ,YELLOW ,YELLOW ,YELLOW ,GREEN  ,GREEN  ,GREEN  ,YELLOW ,YELLOW ,YELLOW ,ORANGE},
             {YELLOW ,GREEN  ,GREEN  ,GREEN  ,BLUE   ,BLUE   ,BLUE   ,GREEN  ,GREEN  ,GREEN  ,YELLOW},
             {GREEN  ,BLUE   ,BLUE   ,BLUE   ,MAGENTA,MAGENTA,MAGENTA,BLUE   ,BLUE   ,BLUE   ,GREEN },
             {BLUE   ,MAGENTA,MAGENTA,MAGENTA,99     ,99     ,99     ,MAGENTA,MAGENTA,MAGENTA,BLUE  },
             {MAGENTA,99     ,99     ,99     ,99     ,99     ,99     ,99     ,99     ,99     ,MAGENTA},
             {99     ,99     ,99     ,99     ,99     ,99     ,99     ,99     ,99     ,99     ,99},
             {99     ,99     ,99     ,99     ,99     ,99     ,99     ,99     ,99     ,99     ,99    }
            };
            
  for (uint8_t d = 0; d < 19; d++)
  {      
    ledDriver.clear();
    for (uint8_t y = 0; y <= 9; y++)
    {
      startbogen = 9 - d;
      bogenidx=y-startbogen;
      if ( startbogen < 0 ) startbogen = 0;
      for (uint8_t x = 0; x <= 10; x++)
      {
        if (bitRead(screenBufferOld[y], 15 - x)) ledDriver.setPixel(x, y, colorold, brightness);
        if ( y >= startbogen && bogenidx >= 0 && bogenidx <= 9)                                                                // Regenbogenbereich
        {
          if ( bogen[bogenidx][x] != 0 && bogen[bogenidx][x] != 99 ) ledDriver.setPixel(x, y, bogen[bogenidx][x], brightness); // Farbe aus Regenbogen
          if ( bogen[bogenidx][x] == 99 )                                                                                      // Prüfen ob hier kein Regenbogen ist
          {
            if (bitRead(screenBufferNew[y], 15 - x)) ledDriver.setPixel(x, y, color, brightness);                              // Farbe aus color (neue Farbe)
            else ledDriver.setPixel(x, y, color, 0);                                                                           // Pixel löschen (brightness = 0)
          }
        }
        if ( y >= startbogen && bogenidx > 9 )                                                                         // Regenbogen ist vorbei
        {
          if (bitRead(screenBufferNew[y], 15 - x)) ledDriver.setPixel(x, y, color, brightness);                        // Neues Pixel gesetzt dann neue Farbe
          else ledDriver.setPixel(x, y, color, 0);                                                                     // ansonsten Pixel löschen (brightness = 0)
        }
      }
    }
    ledDriver.show();
    handle_Webserver(__LINE__);
    delay(TRANSITION_SPEED*15/10);
  }
  writeScreenBuffer(screenBufferNew, color, brightness);
  colorold = color;
}

void quadrate (uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
  uint8_t lpx = random(3,9);
  uint8_t lpy = random(3,8);
  uint8_t spx = random(3,9);
  uint8_t spy = random(3,8);
  uint8_t dl = 0;
  uint16_t xbuff;
  uint16_t m_old[10] = {};
  uint16_t m_new[10] = {};
  uint16_t lquad_old[10] = {};
  uint16_t lquad_new[10] = {};
  uint16_t lquad_disp[10] = {};
  uint16_t squad_old[10] = {};
  uint16_t squad_new[10] = {};
  uint16_t squad_disp[10] = {};
  uint16_t mask = 0b1111111111100000;
  bool q2 = false;
  bool work = true;
  
// Init
  for (uint8_t ze = 0; ze <= 9; ze++)
  {
    m_old[ze] = screenBufferOld[ze];
    m_new[ze] = screenBufferNew[ze];
    if (ze==lpy) lquad_old[ze]=1<<(16-lpx); 
    lquad_new[ze]=lquad_old[ze];
    lquad_disp[ze] = lquad_old[ze];
    
    if (ze==spy) squad_old[ze]=1<<(16-spx); 
    squad_new[ze]=squad_old[ze];
    squad_disp[ze] = squad_old[ze];
  } 
  
//  Work
  while (work)
  {
    dl++;
    work = false;
    ledDriver.clear();
    for (uint8_t y = 0; y <= 9; y++) 
    {
      lquad_old[y] = lquad_new[y];
      m_old[y] = m_old[y] & ~lquad_disp[y];
      for (uint8_t x = 0; x <= 10; x++)
      {      
        if (bitRead( lquad_disp[y], 15 - x )) ledDriver.setPixel(x, y, RED, brightness);
        if (bitRead( m_old[y], 15 - x )) ledDriver.setPixel(x, y, colorold, brightness);
        if ( q2 )
        {
          if (bitRead( squad_disp[y], 15 - x )) ledDriver.setPixel(x, y, GREEN, brightness);
          if (bitRead( m_new[y] & squad_old[y], 15 - x )) ledDriver.setPixel(x, y, color, brightness);
        }
      }
      if ( q2 ) squad_old[y] = squad_new[y];
      if ( squad_disp[y] > 0 ) work = true;
    }
    
    ledDriver.show();
    handle_Webserver(__LINE__);
    delay(TRANSITION_SPEED);
// Löschquadrat nach oben und unten kopieren
    for (uint8_t yc = 0 ;yc<= lpy-1; yc++)
    {
      lquad_new[yc] = lquad_old[yc+1];
    }
    for (uint8_t yc = 9 ;yc>= lpy+1; yc--)
    {
      lquad_new[yc] = lquad_old[yc-1];
    }
// Löschquadrat nach links und rechts erweitern
    for (uint8_t ye = 0; ye <= 9; ye++) 
      {
    xbuff=lquad_new[ye];
    lquad_new[ye] = lquad_new[ye]*2 | lquad_new[ye];
    xbuff=xbuff/2;
    lquad_new[ye] = lquad_new[ye] | xbuff;
        lquad_disp[ye] = lquad_new[ye] & ~lquad_old[ye] & mask;
      }
// Start Setzquadrat
      if ( q2 )
      {
// Setzquadrat nach oben und unten kopieren
        for (uint8_t yc = 0 ;yc<= spy-1; yc++)
      {
        squad_new[yc] = squad_old[yc+1];
      }
      for (uint8_t yc = 9 ;yc>= spy+1; yc--)
      {
        squad_new[yc] = squad_old[yc-1];
      }
// Setzquadrat nach links und rechts erweitern    
      for (uint8_t ye = 0; ye <= 9; ye++) 
        {
      xbuff=squad_new[ye];
      squad_new[ye] = squad_new[ye]*2 | squad_new[ye];
      xbuff=xbuff/2;
      squad_new[ye] = squad_new[ye] | xbuff;
          squad_disp[ye] = squad_new[ye] & ~squad_old[ye] & mask;           
        }
    }
// Prüfen ob Setzquadrat starten kann ( xdiff und ydiff müssen größer als die Anzahl der Durchläufe +1 sein)
    if ( dl > abs(lpx - spx)+1 && dl > abs(lpy - spy)+1) q2=true;
  }
  writeScreenBuffer(screenBufferNew, color, brightness);
  colorold = color;
}


void writeScreenBufferFade(uint16_t screenBufferOld[], uint16_t screenBufferNew[], uint8_t color, uint8_t brightness)
{
#ifdef DEBUG
  Serial.printf("Color: %i CornerColor: %i\n",color,settings.mySettings.corner_color );
#endif
	transitionInProgress = true;
	ledDriver.clear();
	uint8_t brightnessBuffer[10][12] = {};

	for (uint8_t y = 0; y <= 9; y++)
	{
		for (uint8_t x = 0; x <= 11; x++)
		{
			if (bitRead(screenBufferOld[y], 15 - x)) brightnessBuffer[y][x] = brightness;
		}
	}
	for (uint8_t i = 0; i < brightness; i++)
	{
		for (uint8_t y = 0; y <= 9; y++)
		{
      if ( lastMode == MODE_DATE && mode == MODE_TIME )
      {
        if ( y > 4 ) colorold = LIGHTBLUE; else colorold = YELLOW;
      }
			for (uint8_t x = 0; x <= 11; x++)
			{
//        if (!(bitRead(screenBufferOld[y], 15 - x)) && (bitRead(screenBufferNew[y], 15 - x))) brightnessBuffer[y][x]++;
//        if ((bitRead(screenBufferOld[y], 15 - x)) && !(bitRead(screenBufferNew[y], 15 - x))) brightnessBuffer[y][x]--;
//        ledDriver.setPixel(x, y, color, brightnessBuffer[y][x]);
				if (!(bitRead(screenBufferOld[y], 15 - x)) && (bitRead(screenBufferNew[y], 15 - x))) 
				{
          if ( i  >=    brightness / 3 && brightnessBuffer[y][x] < 255 ) brightnessBuffer[y][x]++;
          if ( i  > 2 * brightness / 3 && brightnessBuffer[y][x] < 255 ) brightnessBuffer[y][x]++;
          if ( x < 11 ) ledDriver.setPixel(x, y, color, brightnessBuffer[y][x]);
				}
				else if ((bitRead(screenBufferOld[y], 15 - x)) && !(bitRead(screenBufferNew[y], 15 - x))) 
				{
				  if ( brightnessBuffer[y][x] > 0 ) brightnessBuffer[y][x]--;
          if ( i < brightness / 3 && brightnessBuffer[y][x] > 0 ) brightnessBuffer[y][x]--;
          if ( x < 11 ) ledDriver.setPixel(x, y, colorold, brightnessBuffer[y][x]);
				}
        else
        {
          if ( x < 11 )
          {
            if ( i < brightness / 2 ) 
            {
               ledDriver.setPixel(x, y, colorold, brightnessBuffer[y][x]);
            }
            else
            {
               ledDriver.setPixel(x, y, color, brightnessBuffer[y][x]);
            }
          }
        }
			}
		}

		// Corner LEDs
		for (uint8_t y = 0; y <= 3; y++) 
    {
      if (!(bitRead(screenBufferOld[y], 4)) && (bitRead(screenBufferNew[y], 4))) 
      {
        ledDriver.setPixel(110 + y, settings.mySettings.corner_color, brightnessBuffer[y][11]);
      }
      else if ((bitRead(screenBufferOld[y], 4)) && !(bitRead(screenBufferNew[y], 4))) 
      {
        ledDriver.setPixel(110 + y, cornercolorold, brightnessBuffer[y][11]);
      }
      else
      {
        if ( i < brightness / 2 ) 
        {
           ledDriver.setPixel(110 + y, cornercolorold, brightnessBuffer[y][11]);
        }
        else
        {
           ledDriver.setPixel(110 + y, settings.mySettings.corner_color, brightnessBuffer[y][11]);
        }        
      }
    }
		   
		// Alarm LED
#if defined(BUZZER) || defined(AUDIO_SOUND)
#ifdef ALARM_LED_COLOR
#ifdef ABUSE_CORNER_LED_FOR_ALARM
		if (settings.mySettings.alarm1 || settings.mySettings.alarm2 || alarmTimerSet) 
		{
		  ledDriver.setPixel(111, ALARM_LED_COLOR, brightnessBuffer[4][11]);
		}
#else
		ledDriver.setPixel(114, ALARM_LED_COLOR, brightnessBuffer[4][11]);
#endif
#else
		ledDriver.setPixel(114, color, brightnessBuffer[4][11]);
#endif
#endif
		handle_Webserver(__LINE__);
    if ( mode == MODE_MOONPHASE )
    {
      delay(int((900 - brightness*3) / brightness ));
    }
		else
		{
		  delay(int((12 * TRANSITION_SPEED + 350 - brightness*2) / brightness));
		}
		ledDriver.show();
	}
	transitionInProgress = false;
  colorold = color;
  cornercolorold = settings.mySettings.corner_color;
  if ( lastMode == MODE_DATE && mode == MODE_TIME )
  {
    lastMode = MODE_TIME;
  }
}

void writeScreenBuffer(uint16_t screenBuffer[], uint8_t color, uint8_t brightness)
{
#ifdef DEBUG
  Serial.printf("Color: %i CornerColor: %i\n",color,settings.mySettings.corner_color );
#endif
  ledDriver.clear();
  for (uint8_t y = 0; y <= 9; y++)
  {
    if ( mode == MODE_DATE && y > 4 ) color = LIGHTBLUE;
    for (uint8_t x = 0; x <= 10; x++)
    {
      if (bitRead(screenBuffer[y], 15 - x)) ledDriver.setPixel(x, y, color, brightness);
    }
  }

  // Corner LEDs
  for (uint8_t y = 0; y <= 3; y++)
  {
    if (bitRead(screenBuffer[y], 4)) ledDriver.setPixel(110 + y, settings.mySettings.corner_color, brightness);
  }

  // Alarm LED
#if defined(BUZZER) || defined(AUDIO_SOUND)
  if (bitRead(screenBuffer[4], 4))
  {
#ifdef ALARM_LED_COLOR
#ifdef ABUSE_CORNER_LED_FOR_ALARM
    if (settings.mySettings.alarm1 || settings.mySettings.alarm2 || alarmTimerSet) ledDriver.setPixel(111, ALARM_LED_COLOR, brightness);
    else if (bitRead(screenBuffer[1], 4)) ledDriver.setPixel(111, settings.mySettings.corner_color, brightness);
#else
    ledDriver.setPixel(114, ALARM_LED_COLOR, brightness);
#endif
#else
    ledDriver.setPixel(114, color, brightness);
#endif
  }
#endif

  ledDriver.show();
  colorold = color;
  cornercolorold = settings.mySettings.corner_color;
}

void changecolor()
{
  uint8_t newcolor;
  int8_t diffcolor;
  int bghue;
  int bghue_min;
  int bghue_max;
  int colorhue;
  color_s bgcolor;
  colorold = settings.mySettings.color;
#define HUERANGE 60
  if ( settings.mySettings.enable_bg_color )
  {
    bgcolor = num_to_color(settings.mySettings.bg_color);
    bghue = rgbtoheu(bgcolor.red,bgcolor.green,bgcolor.blue);
    if ( bghue-HUERANGE < 0) bghue_min = bghue-HUERANGE+360; else bghue_min = bghue-HUERANGE;
    if ( bghue+HUERANGE >360) bghue_max = bghue+HUERANGE-360; else bghue_max = bghue+HUERANGE;
#ifdef DEBUG
  Serial.printf("BGColor HUE: %i Min/Max: %i/%i\n",bghue,bghue_min,bghue_max );
#endif
  }
  for (uint8_t i = 0; i <= 20; i++)
  {
     newcolor = random(0, COLOR_COUNT + 1);
     if ( brightness < 90 and newcolor == BLUE ) newcolor = WHITE;  // wenn es zu dunkel ist, kann man blau nicht mehr gut erkennen!
     if ( settings.mySettings.enable_bg_color )
     {
        colorhue = rgbtoheu(defaultColors[newcolor].red,defaultColors[newcolor].green,defaultColors[newcolor].blue);
#ifdef DEBUG
  Serial.printf("Color: %i Hue: %i\n",newcolor,colorhue );
#endif 
        if ( bghue == -2 && newcolor == WHITE) break;
        if ( bghue_max > bghue_min )
        {
          if ( colorhue < bghue_max && colorhue > bghue_min ) 
          {
#ifdef DEBUG
  Serial.println("Color zu nahe an Background -> verworfen");
#endif 
            continue;
          }

        }
        else
        {
          if ( (colorhue < bghue_max && colorhue > 0) || ( colorhue >bghue_min && colorhue < 360 ))
          {
#ifdef DEBUG
  Serial.println("Color zu nahe an Background -> verworfen");
#endif 
            continue;
          }
        }
     }
     diffcolor = newcolor - settings.mySettings.color;
     if ( abs(diffcolor) > 4 ) break;
  }
  settings.mySettings.color = newcolor;
  colorsaver = settings.mySettings.color;
  if (settings.mySettings.corner_colorChange == COLORCHANGE_MAIN) settings.mySettings.corner_color = settings.mySettings.color;
}

void changecornercolor()
{
  uint8_t newcornercolor;
  int8_t diffcolor;
  cornercolorold = settings.mySettings.corner_color;
  for (uint8_t i = 0; i <= 20; i++)
  {
     newcornercolor = random(0, COLOR_COUNT + 1);
     if ( brightness < 90 and newcornercolor == BLUE ) newcornercolor = WHITE;  // wenn es zu dunkel ist, kann man blau nicht mehr gut erkennen!
#if defined(BUZZER) || defined(AUDIO_SOUND)
#ifdef ALARM_LED_COLOR
#ifdef ABUSE_CORNER_LED_FOR_ALARM
    if (settings.mySettings.alarm1 || settings.mySettings.alarm2 || alarmTimerSet)
    {
      if (newcornercolor == ALARM_LED_COLOR ) newcornercolor = GREEN;
    } 
#endif
#endif
#endif
     diffcolor = newcornercolor - settings.mySettings.color;
     if ( abs(diffcolor) > 5  && newcornercolor != cornercolorold ) break;
  }
  settings.mySettings.corner_color = newcornercolor;
}

int rgbtoheu(uint8_t red, uint8_t green, uint8_t blue)
{ 
  int h;
  uint8_t rgbMin, rgbMax;
 
  rgbMax = max(max(red,green), blue);
  rgbMin = min(min(red,green), blue);
  if (rgbMax == 0 ) return -1;
  if (rgbMax == rgbMin ) return -2;
  
  if (rgbMax == red)
        h =        60 * (green - blue) / (rgbMax - rgbMin);
    else if (rgbMax == green)
        h =  120 + 60 * (blue - red)   / (rgbMax - rgbMin);
    else
        h =  240 + 60 * (red - green)  / (rgbMax - rgbMin);
    if ( h < 0 ) h += 360;
    return h;
}

/******************************************************************************
  "On/off" pressed
******************************************************************************/

void buttonOnOffPressed()
{
#ifdef DEBUG
	Serial.println(F("On/off pressed."));
#endif

	mode == MODE_BLANK ? setLedsOn() : setLedsOff();
}

/******************************************************************************
  "Time" pressed
******************************************************************************/

void buttonTimePressed()
{
#ifdef DEBUG
	Serial.println(F("Time pressed."));
#endif
#ifdef AUDIO_SOUND
  Play_MP3(700,true,0);  // OK Sound blub
#endif
	// Switch off alarm
#ifdef BUZZER
	if (alarmOn)
	{
#ifdef DEBUG
		Serial.println(F("Alarm: off"));
#endif
		digitalWrite(PIN_BUZZER, LOW);
		alarmOn = false;
	}
#endif
#ifdef AUDIO_SOUND
  if (alarmOn)
  {
#ifdef DEBUG
    Serial.println(F("Alarm: off"));
#endif
    alarmOn = false;
  }
#endif
  if (mode != MODE_TIME ) {
    settings.mySettings.color = colorsaver;
	  modeTimeout = 0;
#ifdef DEBUG
        Serial.printf("Color changed to: %u\r\n", settings.mySettings.color);
#endif
  }
  if ( mode == MODE_WHITE ) renderer.clearScreenBuffer(matrix);  
	setMode(MODE_TIME);
 #ifdef DEBUG
   Serial.printf("modeTimeout: %i\r\n", modeTimeout);
#endif
}

/******************************************************************************
  "Mode" pressed
******************************************************************************/

void buttonModePressed()
{
#ifdef DEBUG
	Serial.println(F("Mode pressed."));
#endif

#ifdef AUDIO_SOUND
    Play_MP3(700,false,0); // OK Sound blub
#endif
	// Switch off alarm
#ifdef BUZZER
	if (alarmOn)
	{
#ifdef DEBUG
		Serial.println(F("Alarm: off"));
#endif
		digitalWrite(PIN_BUZZER, LOW);
		alarmOn = false;
		setMode(MODE_TIME);
		return;
	}
#endif

#ifdef AUDIO_SOUND
  if (alarmOn)
  {
#ifdef DEBUG
    Serial.println(F("Alarm: off"));
#endif
    alarmOn = false;
    setMode(MODE_TIME);
    return;
  }
#endif
  if (mode == MODE_TIME ) {
    colorsaver = settings.mySettings.color;
    settings.mySettings.color = WHITE;
#ifdef DEBUG
    Serial.println(F("Mode Color White"));
#endif
  }
  if ( mode == MODE_WHITE ) { 
    renderer.clearScreenBuffer(matrix);
  }
  if ( mode > MODE_COUNT || SHOW_TIME_BUTTON_BOOL ) { 
    renderer.clearScreenBuffer(matrix);
    setMode(MODE_TIME);
  }
  else
  {
	  setMode(mode++);
  }
  Modecount++;
}

/******************************************************************************
  Set mode
******************************************************************************/

void setMode(Mode newMode)
{
	screenBufferNeedsUpdate = true;
  ModeSequenz = 0;
	runTransitionOnce = true;
	lastMode = mode;
	mode = newMode;

	// set timeout
	switch (mode)
	{
#ifdef SHOW_MODE_ANSAGE
	case MODE_ANSAGE:
#endif
#ifdef SHOW_MODE_SECONDS
	case MODE_SECONDS:
#endif
#ifdef SHOW_MODE_WEEKDAY
	case MODE_WEEKDAY:
#endif
#ifdef SHOW_MODE_DATE
	case MODE_DATE:
#endif
#ifdef SHOW_MODE_MOONPHASE
	case MODE_MOONPHASE:
#endif
#if defined(RTC_BACKUP) && !defined(SENSOR_BME280)
	case MODE_TEMP:
#endif
#ifdef SENSOR_BME280
	case MODE_TEMP:
	case MODE_HUMIDITY:
  case MODE_LUFTDRUCK:
#endif
#ifdef APIKEY
  case MODE_WETTER:
	case MODE_EXT_TEMP:
	case MODE_EXT_HUMIDITY:
#endif
		modeTimeout = millis();
		break;
	default:
		modeTimeout = 0;
		break;
	}
}

//******************************************************************************
// get brightness from LDR
//******************************************************************************
#ifdef LDR
void setBrightnessFromLdr()
{
#ifdef LDR_IS_INVERSE
	ldrValue = 1024 - analogRead(PIN_LDR);
#else
	ldrValue = analogRead(PIN_LDR);
#endif
	if (ldrValue < minLdrValue) minLdrValue = ldrValue;
	if (ldrValue > maxLdrValue) maxLdrValue = ldrValue;
	if ((ldrValue >= (lastLdrValue + 30)) || (ldrValue <= (lastLdrValue - 30))) // Hysteresis ist 30 (vorher 40)
	{
		lastLdrValue = ldrValue;
		brightness = map(ldrValue, minLdrValue, maxLdrValue, MIN_BRIGHTNESS, abcBrightness);
    if ( !screenBufferNeedsUpdate )
    {
      screenBufferNeedsUpdate = true;
      ldr_update = true;      
    }

#ifdef DEBUG
		Serial.printf("Brightness: %u (min: %u, max: %u)\r\n", brightness, MIN_BRIGHTNESS, abcBrightness);
		Serial.printf("LDR: %u (min: %u, max: %u)\r\n", ldrValue, minLdrValue, maxLdrValue);
#endif
	}
}
#endif

//******************************************************************************
// Luftdruckverlauf
//******************************************************************************
#ifdef SENSOR_BME280
void Luftdruckverlauf(uint16_t screenBuffer[])
{
    uint16_t matrixstartwert = 0b1000000000000000;
    float luftdruck_max = 0;
    float luftdruckdiff = 0;
    uint16_t matrixwert;
    int startzeile;
    int druckzeile;
    for (uint8_t ze = 0; ze <= 9; ze++)
    {
      screenBuffer[ze]=0;
      if ( luftdruck_hist[ze+1] > luftdruck_max ) luftdruck_max = luftdruck_hist[ze+1];
    }   
    if (luftdruck_hist[0] > 0 )
    {
      startzeile = 4 - (luftdruck_hist[0] - luftdruck_max) / 3;
    } 
    else 
    {
      startzeile = 4;
    }

    screenBuffer[startzeile] = matrixstartwert;
    for (uint8_t sp = 1; sp <= 10; sp++)
    {
      matrixwert = matrixstartwert>>sp;
      if (luftdruck_hist[0] == 0) luftdruck_hist[0] = luftdruck_hist[sp];
      if (luftdruck_hist[sp] > 0 )
      {
        druckzeile = startzeile - (luftdruck_hist[sp] - luftdruck_hist[0]) / 2;
      }
      else
      {
        druckzeile = 4;
      }
      if (druckzeile < 0 ) druckzeile = 0;
      if (druckzeile > 10 ) druckzeile = 10;
      screenBuffer[druckzeile] = screenBuffer[druckzeile] | matrixwert;
      }
// Soundfile für Luftdrucktendenz
      for (int i = 1;i<11;i++) {
        luftdruckdiff = luftdruckdiff + (luftdruck_hist[i] - luftdruck_hist[i-1]) * i;
      }
      if ( luftdruckdiff <= LUFTDRUCK_DIFF_FALLEND ) luftdrucktendenz_soundbase = 69; // fallend
      if ( luftdruckdiff > LUFTDRUCK_DIFF_FALLEND and luftdruckdiff <= LUFTDRUCK_DIFF_LEICHTFALLEND  ) luftdrucktendenz_soundbase = 68; // leicht fallend
      if ( luftdruckdiff > LUFTDRUCK_DIFF_LEICHTFALLEND and luftdruckdiff <= LUFTDRUCK_DIFF_LEICHTSTEIGEND  ) luftdrucktendenz_soundbase = 67; // gleichbleibend
      if ( luftdruckdiff > LUFTDRUCK_DIFF_LEICHTSTEIGEND and luftdruckdiff <= LUFTDRUCK_DIFF_STEIGEND  ) luftdrucktendenz_soundbase = 66; // leicht steigend
      if ( luftdruckdiff > LUFTDRUCK_DIFF_STEIGEND ) luftdrucktendenz_soundbase = 65; //steigend
}

#endif
//******************************************************************************
// Get room conditions
//******************************************************************************
#if defined(RTC_BACKUP) || defined(SENSOR_BME280)
void getRoomConditions()
{
  int stunde = hour();
  String c_stunden;
  String c_minuten;

#if defined(RTC_BACKUP) && !defined(SENSOR_BME280)
	roomTemperature = RTC.temperature() / 4.0 + RTC_TEMPERATURE_OFFSET;
#ifdef DEBUG
	Serial.println("Temperature (RTC): " + String(roomTemperature) + "C");
#endif
#endif
#ifdef SENSOR_BME280
  float luftdruckdiff = 0;
	float bmeTemperature = bme.readTemperature();
	float bmeHumidity = bme.readHumidity();
  float bmePressure = bme.readPressure() / 100.0F;
#ifdef DEBUG
  Serial.print(F("BME SensorID was: 0x")); Serial.println(bme.sensorID(),16);
#endif
	if ( bme.sensorID() != 255 )
	{
		errorCounterBME = 0;
		roomTemperature = bmeTemperature + BME_TEMPERATURE_OFFSET;
		roomHumidity = bmeHumidity + BME_HUMIDITY_OFFSET;
    Pressure = bmePressure;
#ifdef APIKEY
    if ( strlen(settings.mySettings.openweatherapikey) > 25 )
    {
      Pressure_red = Pressure * pow ( EULERSCHE_ZAHL ,(( FALLBESCHLEUNIGUNG / ( GASKONSTANTE * ( KELVIN_0 + outdoorWeather.temperature + TEMPERATURGRADIENT * float(settings.mySettings.standort_hoehe) ))) * float(settings.mySettings.standort_hoehe) ));
    }
    else
    {
      Pressure_red = Pressure * pow ( EULERSCHE_ZAHL ,(( FALLBESCHLEUNIGUNG / ( GASKONSTANTE * ( KELVIN_0 + 20 + TEMPERATURGRADIENT * float(settings.mySettings.standort_hoehe) ))) * float(settings.mySettings.standort_hoehe) ));
    }
#else
    Pressure_red = Pressure * pow ( EULERSCHE_ZAHL ,(( FALLBESCHLEUNIGUNG / ( GASKONSTANTE * ( KELVIN_0 + 20 + TEMPERATURGRADIENT * float(settings.mySettings.standort_hoehe) ))) * float(settings.mySettings.standort_hoehe) ));
#endif
// Historisierung Luftdruck
    lufdruck_hour[stunde%3] = Pressure_red;
    luftdruck_hist[10]=(lufdruck_hour[0]+lufdruck_hour[1]+lufdruck_hour[2])/3; // Mittwelwert der letzten 3 Stunden
    
    if ( minute() == 1 ) // Historisierung der Luftdruckwerte
    { 
      if ( stunde%3 == 0 )
      {
        for (int hist = 0 ; hist <= 9; hist++)
          luftdruck_hist[hist]=luftdruck_hist[hist+1];
        luftdruck_hist[10]=(lufdruck_hour[0]+lufdruck_hour[1]+lufdruck_hour[2])/3; // Mittwelwert der letzten 3 Stunden
      }
    }
// Luftdrucktendenz für Web
      for (int i = 1;i<11;i++) {
        luftdruckdiff = luftdruckdiff + (luftdruck_hist[i] - luftdruck_hist[i-1]) * i;
      }
      if ( luftdruckdiff <= LUFTDRUCK_DIFF_FALLEND ) luftdrucktendenz_web = 1; // fallend
      if ( luftdruckdiff > LUFTDRUCK_DIFF_FALLEND and luftdruckdiff <= LUFTDRUCK_DIFF_LEICHTFALLEND  ) luftdrucktendenz_web = 2; // leicht fallend
      if ( luftdruckdiff > LUFTDRUCK_DIFF_LEICHTFALLEND and luftdruckdiff <= LUFTDRUCK_DIFF_LEICHTSTEIGEND  ) luftdrucktendenz_web = 3; // gleichbleibend
      if ( luftdruckdiff > LUFTDRUCK_DIFF_LEICHTSTEIGEND and luftdruckdiff <= LUFTDRUCK_DIFF_STEIGEND  ) luftdrucktendenz_web = 4; // leicht steigend
      if ( luftdruckdiff > LUFTDRUCK_DIFF_STEIGEND ) luftdrucktendenz_web = 5; //steigend
      info_luftdruckdiff = luftdruckdiff;
// Historisierung Temperatur
    c_stunden = String(stunde);
    if ( stunde < 10 ) c_stunden = "0" + c_stunden;
    c_minuten = String(minute());
    if ( minute() < 10 ) c_minuten = "0" + c_minuten;
    if ( (minute()%20) - 1  == 0 ) // Werte alle 20 Minuten (01,21,41)
    {
#ifdef DEBUG
  Serial.println("Historisierung Temp. Werte: " + c_stunden + ":" + c_minuten);
#endif
      for (int hist = 0 ; hist <= 71; hist++)
      {
        temperatur_hist[hist]=temperatur_hist[hist+1];
      }
    }
    temperatur_hist[72].stundeminute =  c_stunden + ":" + c_minuten;
    temperatur_hist[72].innentemp = roomTemperature;
    temperatur_hist[72].aussentemp = 0;
#ifdef APIKEY
    temperatur_hist[72].aussentemp = outdoorWeather.temperature;
#endif
#ifdef DEBUG
		Serial.println("Temperature (BME): " + String(roomTemperature) + "C");
		Serial.println("Humidity (BME): " + String(roomHumidity) + "%");
    Serial.println("Pressure (BME): " + String(Pressure) + " hPa");
#endif
	}
	else
	{
		if (errorCounterBME < 250) errorCounterBME++;
#ifdef DEBUG
    Serial.println(F("Could not find a valid BME280 sensor, check wiring, address, sensor ID!"));
		Serial.printf("Error (BME): %u\r\n", errorCounterBME);
#endif
	}
#endif
}
#endif

//******************************************************************************
// Sunrise/Sunset
//******************************************************************************
void sunriseset()
{
  sunriseHour = 0;
  sunriseMinute = 0;
  sunriseSecond = 0;
  sunsetHour = 0;
  sunsetMinute = 0;
  sunsetSecond = 0;

#ifdef APIKEY
  if ( strlen(settings.mySettings.openweatherapikey) > 25 )
  {
    if ( hour(outdoorWeather.sunrise) > 0 ) 
    {
      sunriseHour = hour(outdoorWeather.sunrise);
      sunriseMinute = minute(outdoorWeather.sunrise);
      sunriseSecond = second(outdoorWeather.sunrise);
      if ( sunriseSecond > 40 ) sunriseSecond = 40;
      if ( sunriseSecond < 10 ) sunriseSecond = 10;
    }
    if ( hour(outdoorWeather.sunset) > 0 ) 
    {
      sunsetHour = hour(outdoorWeather.sunset);
      sunsetMinute = minute(outdoorWeather.sunset);
      sunsetSecond = second(outdoorWeather.sunset);
      if ( sunsetSecond > 40 ) sunsetSecond = 40;
      if ( sunsetSecond < 10 ) sunsetSecond = 10;
    }
  }
  else
  {
#endif // APIKEY
#ifdef SunRiseLib
    if ( hour(sunRiseTime) > 0 ) 
    {
      sunriseHour = hour(sunRiseTime);
      sunriseMinute = minute(sunRiseTime);
      sunriseSecond = second(sunRiseTime);
      if ( sunriseSecond > 40 ) sunriseSecond = 40;
      if ( sunriseSecond < 10 ) sunriseSecond = 10;
    }
    if ( hour(sunSetTime) > 0 ) 
    {
      sunsetHour  = hour(sunSetTime);
      sunsetMinute  = minute(sunSetTime);
      sunsetSecond  = second(sunSetTime);
      if ( sunsetSecond > 40 ) sunsetSecond = 40;
      if ( sunsetSecond < 10 ) sunsetSecond = 10;
    }
#endif  // SunRiseLib
#ifdef APIKEY
  }
#endif

//  sunriseHour = 14;
//  sunriseMinute = 18;
//  sunsetHour = 18;
//  sunsetMinute = 13;
}

//******************************************************************************
// Misc
//******************************************************************************

#ifdef MODE_BUTTON
ICACHE_RAM_ATTR void buttonModeInterrupt()
{
	if (millis() > lastButtonPress + 250)
	{
		lastButtonPress = millis();
//		buttonModePressed();
    MODE_BUTTON_BOOL = true;
	}
}
#endif

#ifdef ONOFF_BUTTON
ICACHE_RAM_ATTR void buttonOnOffInterrupt()
{
	if (millis() > lastButtonPress + 250)
	{
		lastButtonPress = millis();
		buttonOnOffPressed();
	}
}
#endif

#ifdef SHOW_TIME_BUTTON
ICACHE_RAM_ATTR void buttonShowTimeInterrupt()
{
	if (millis() > lastButtonPress + 250)
	{
		lastButtonPress = millis();
		show_off_on_time = millis();
    SHOW_TIME_BUTTON_BOOL = true;
	}
}
#endif

// AusPhase
bool ausperiode()
{

  uint16_t offts = hour(settings.mySettings.nightOffTime) * 60 + minute(settings.mySettings.nightOffTime);
  uint16_t onts = hour(settings.mySettings.dayOnTime) * 60 + minute(settings.mySettings.dayOnTime);
  uint16_t aktts = hour() * 60 + minute();
  bool retval = false;
  
  if ( offts <= onts )
  {
    if ( aktts >= offts && aktts < onts ) retval =  true;
  }
  else
  {
    if ( ( aktts >= offts && aktts < 1440 ) || (aktts >= 0 && aktts < onts)) retval = true;
  }
  return retval;
}

// Switch off LEDs
void setLedsOff()
{
#ifdef DEBUG
	Serial.println(F("LEDs: off"));
#endif
	setMode(MODE_BLANK);
#ifdef AUDIO_SOUND
  Play_MP3(ANSAGEBASE+40,false,0); // Aus
#endif
}

// Switch on LEDs
void setLedsOn()
{
#ifdef DEBUG
	Serial.println(F("LEDs: on"));
#endif
	setMode(lastMode);
#ifdef AUDIO_SOUND
  Play_MP3(ANSAGEBASE+41,false,0); // Ein
#endif
}

// Calculate moonphase
#ifdef SHOW_MODE_MOONPHASE
int getMoonphase(int y, int m, int d)
{
	int b;
	int c;
	int e;
	double jd;
	if (m < 3)
	{
		y--;
		m += 12;
	}
	++m;
	c = 365.25 * y;
	e = 30.6 * m;
	jd = c + e + d + 0.8 - 694039.09; // jd is total days elapsed
	jd /= 29.5306;                // divide by the moon cycle (29.53 days)
	b = jd;                     // int(jd) -> b, take integer part of jd
	jd -= b;                    // subtract integer part to leave fractional part of original jd
	b = jd * 22 + 0.2 ;                // scale fraction from 0-22
  web_moonphase = jd * 8 + 0.5 ; // scale fraction from 0-9 and round by adding 0.5
  web_moonphase = web_moonphase & 7;
  if (b >= 22 ) b = 0;
	return b;
}
#endif


// finde den passenden Sound zur Wetter-Id
uint16_t getWeatherSound(uint16_t wetterid)
{
  uint8_t soundmapidx = 0;
  uint16_t soundidx = 0;
  uint16_t soundnr = 0;
  uint16_t wettermapid = 0;
  
  do
  {
    soundnr = pgm_read_word(&wettersoundmapping[soundmapidx][0]);
    wettermapid = pgm_read_word(&wettersoundmapping[soundmapidx][1]);
    if ( wettermapid == wetterid ) 
    {
      soundidx = WETTERSOUNDBASE - 1 + soundnr;
      soundnr = 0;
    }
    soundmapidx++;
  } while ( soundnr != 0 );

  if ( soundidx == WETTERSOUNDBASE -1 || soundidx == 0 ) soundidx = 99; // kein Sound vorhanden
  return soundidx;
}


#ifdef APIKEY
String getWeatherIcon(String weathericonnummer)
{
  String tagnacht;
  String wnummer;
  uint8_t winummer;
  String icon = " ";
//  tagnacht = weathericonnummer.substring(weathericonnummer.length()-1,weathericonnummer.length());
  wnummer = weathericonnummer.substring(0,weathericonnummer.length()-1);
  winummer = wnummer.toInt();
  
  if ( now() > outdoorWeather.sunrise && now() < outdoorWeather.sunset ) tagnacht = "d";
  else tagnacht = "n";
 
  if ( winummer == 1 || winummer == 2 || winummer == 10 )
  {
    if ( tagnacht == "d" ) icon = wnummer + tagnacht;
    else
    {
      if ( moonphase > 9 && moonphase < 13 ) icon = wnummer + tagnacht + "a"; 
      else icon = wnummer + tagnacht + "b";
    }
    if ( winummer == 10 && outdoorWeather.clouds > 80 ) icon = "09";
  }
  else
  {
    icon = wnummer;
  }
#ifdef DEBUG_OW
  Serial.print(F( "Wetter Icon Nummer: "));
  Serial.print(wnummer);
  Serial.print(F( " Wolken: "));
  Serial.print(outdoorWeather.clouds);
  Serial.print(F( "% Tag/Nacht: "));
  Serial.print(tagnacht);
  Serial.print(F( " -> Icon: "));
  Serial.println(icon);
#endif
  return icon;
}

#endif

// Write screenbuffer to console
#ifdef DEBUG_MATRIX
void debugScreenBuffer(uint16_t screenBuffer[])
{
	const char buchstabensalat[][12] =
	{
	  { 'E', 'S', 'K', 'I', 'S', 'T', 'A', 'F', 'U', 'N', 'F', '1' },
	  { 'Z', 'E', 'H', 'N', 'Z', 'W', 'A', 'N', 'Z', 'I', 'G', '2' },
	  { 'D', 'R', 'E', 'I', 'V', 'I', 'E', 'R', 'T', 'E', 'L', '3' },
	  { 'V', 'O', 'R', 'F', 'U', 'N', 'K', 'N', 'A', 'C', 'H', '4' },
	  { 'H', 'A', 'L', 'B', 'A', 'E', 'L', 'F', 'U', 'N', 'F', 'A' },
	  { 'E', 'I', 'N', 'S', 'X', 'A', 'M', 'Z', 'W', 'E', 'I', ' ' },
	  { 'D', 'R', 'E', 'I', 'P', 'M', 'J', 'V', 'I', 'E', 'R', ' ' },
	  { 'S', 'E', 'C', 'H', 'S', 'N', 'L', 'A', 'C', 'H', 'T', ' ' },
	  { 'S', 'I', 'E', 'B', 'E', 'N', 'Z', 'W', 'O', 'L', 'F', ' ' },
	  { 'Z', 'E', 'H', 'N', 'E', 'U', 'N', 'K', 'U', 'H', 'R', ' ' }
	};
	//Serial.println("\033[0;0H"); // set cursor to 0, 0 position
	Serial.println(F(" -----------"));
	for (uint8_t y = 0; y <= 9; y++)
	{
		Serial.print('|');
		for (uint8_t x = 0; x <= 10; x++)
		{
			Serial.print((bitRead(screenBuffer[y], 15 - x) ? buchstabensalat[y][x] : ' '));
		}
		Serial.print('|');
		Serial.println((bitRead(screenBuffer[y], 4) ? buchstabensalat[y][11] : ' '));
	}
	Serial.println(F(" -----------"));
}
#endif

// Write FPS to console
#ifdef DEBUG_FPS
void debugFps()
{
	static uint16_t frames;
	static uint32_t lastFpsCheck;
	frames++;
	if ((millis() % 1000 == 0) && (millis() != lastFpsCheck))
	{
		lastFpsCheck = millis();
		Serial.printf("FPS: %u\r\n", frames);
		frames = 0;
	}
}
#endif

/******************************************************************************
  Events
 ******************************************************************************/
void Eventcheck()
{
  uint8_t aktevent[3];
  uint8_t eventidx = 0;
  uint8_t akteventidx = 0; 

  for (uint8_t i = 0; i <= MAXEVENTS; i++)
  {
    if ( events[i].aktiv && year() > 2010 && aktDay == events[i].day && month() == events[i].month )
    {
#ifdef DEBUG_EVENTS
    Serial.println("EventNr heute: \"" + String(i) + "\"");
    Serial.printf("EventNr heute: %i.%i.%i\n", aktDay,month(),year());
#endif
      aktevent[eventidx] = i;
      if ( eventidx < 2 ) eventidx++;
    }
  }
  if ( eventidx > 0 ) 
  {
    if ( events[0].aktiv ) akteventidx = 0;                // event 0 hat immer Vorrang
    else  akteventidx = aktevent[random(0,eventidx)];
#ifdef DEBUG_EVENTS
    Serial.println("EventNr heute ausgewählt: \"" + String(akteventidx) + "\"");
#endif
    showEventTimer = events[akteventidx].intervall*60;
    if ( showEventTimer == 0 ) showEventTimer = EVENT_TIME;
    
#ifdef AUDIO_SOUND
    audio_stop_nach_feed = false;
    if (events[akteventidx].audio_file > 0 ) {
      int audio_file_einer = events[akteventidx].audio_file%10;
      if ( audio_file_einer == 0 || events[akteventidx].audio_file < 710 || events[akteventidx].audio_file >= 800 ) {
        if ( hour() <= 3 && brightness > 40 )            // wenn es von 0 - 3 Uhr noch hell (Licht an) ist die Lautstärke erhöhen!
        {
          Play_MP3 (events[akteventidx].audio_file,false,450);
        }
        else
        {
          Play_MP3 (events[akteventidx].audio_file,false,0);
        }
      }
      else {
#ifdef DEBUG_EVENTS
        Serial.printf("Random-AudioFiles: %i - %i \r\n", (events[akteventidx].audio_file - audio_file_einer),(events[akteventidx].audio_file));
#endif
        int audio_file_random = random((events[akteventidx].audio_file - audio_file_einer), (events[akteventidx].audio_file + 1));
        if ( hour() <= 3 && brightness > 40 )            // wenn es von 0 - 3 Uhr noch hell (Licht an) ist die Lautstärke erhöhen!
        {
          Play_MP3 (audio_file_random,false,450);
        }
        else
        {
          Play_MP3 (audio_file_random,false,0);
        }
      }
    }
#endif

// Lade Pre Animation
    if ( events[akteventidx].preani != "KEINE" )
    {
      animation = events[akteventidx].preani;
      if ( loadAnimation(animation) ) 
      {
         akt_aniframe = 0;
         akt_aniloop = 0;
         frame_fak = 0;
         while ( showAnimation(brightness) ) 
         {
#ifdef DEBUG_EVENTS
           Serial.println("Starte Event Pre Animation: " + String(myanimation.name) + " Loop: " +  String(akt_aniloop) + " Frame: " + String(akt_aniframe) );
#endif          
         }
      }
    }
//    if (events[akteventidx].year > 1799 ) feedText = "  " + events[akteventidx].text + " (" + String(year() - events[akteventidx].year) + ")   ";
//    else feedText = "  " + events[akteventidx].text + "   ";
    
    feedText = "  " + events[akteventidx].text + "   ";
    String eventalter = String(year() - events[akteventidx].year);
    feedText.replace("YY",eventalter);
    
    feedPosition = 0;
    feedColor = events[akteventidx].color;    
#ifdef DEBUG_EVENTS
    Serial.println("Event: \"" + feedText + "\"");
#endif

// Lade Post Animation
    if ( events[akteventidx].postani != "KEINE" )
    {
      animation = events[akteventidx].postani;
      if ( loadAnimation(animation) ) 
      {
         akt_aniframe = 0;
         akt_aniloop = 0;
         frame_fak = 0;
         post_event_ani = true;
      }
    }
    setMode(MODE_FEED);
  }

}


/******************************************************************************
  Webserver
******************************************************************************/
void handle_Webserver(uint16_t codezeile)
{
  if ( ESP.getMaxFreeBlockSize() < minFreeBlockSize ) 
  {
    minFreeBlockSize = ESP.getMaxFreeBlockSize();
    codeline = codezeile;
#ifdef DEBUG
    Serial.printf("minFreeBlockSize: %i Codezeile: %u\n", minFreeBlockSize,codezeile); 
#endif   
  }
  webServer.handleClient();
  delay(0);
}


void setupWebServer()
{
//	webServer.onNotFound(handleNotFound);
 
	webServer.on("/", handleRoot);
	webServer.on("/handleButtonOnOff", []() { buttonOnOffPressed(); callRoot(); });
	webServer.on("/handleButtonSettings", handleButtonSettings);
  webServer.on("/handleButtonMode", []() { buttonModePressed(); webServer.send(200, "text/plain", "OK"); });
  webServer.on("/handleButtonTime", []() { buttonTimePressed(); webServer.send(200, "text/plain", "OK"); });
  webServer.on("/commitSettings", handleCommitSettings);
	webServer.on("/debugClock", debugClock);
#ifdef AUDIO_SOUND
  webServer.on("/AudioTest", AudioTest);
#endif
  webServer.on("/BackgroundColor", BackgroundColor);
	webServer.on("/reboot", handleReboot);
  webServer.on("/wifireset", handleWiFiReset);
	webServer.on("/setEvent", handleSetEvent);
	webServer.on("/showText", handleShowText);
	webServer.on("/control", handleControl);
  webServer.on("/back"   , handlebacktoMODE_TIME);           // zurück zum Hauptmenü +  MODE_TIME 

  webServer.on("/handleevents", HTTP_POST, handleevents);    // Eventseite
  
  webServer.on("/animationmenue", startAnimationsmenue);     //Starte Animationsmenü
  webServer.on("/myaniselect", HTTP_POST, handleaniselect);  //Verarbeitung Animationsauswahl
  webServer.on("/makeanimation", startmakeAnimation);        //Starte Animationsoberfläche
  webServer.on("/handlemakeanimation", handlemakeAnimation); //Verarbeite Animationsoberfläche

  webServer.on("/StartGame", startGame);     //Starte Game
  webServer.on("/game", handleGameControl);
  
	webServer.begin();
}

void callRoot()
{
	webServer.send(200, "text/html", "<!doctype html><html><head><script>window.onload=function(){window.location.replace('/');}</script></head></html>");
}



// Page /
void handleRoot()
{
  delay(0);
  webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
	String message;
	message = F("<!doctype html>");
	message += F("<html><head>");
	message +=	"<title>" + String(settings.mySettings.systemname) + "</title>";
	message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
		"<meta http-equiv=\"Cache-Control\" content=\"no-cache, no-store, must-revalidate\"\n>"
    "<meta http-equiv=\"refresh\" content=\"60\" charset=\"UTF-8\">\n"
    "<link rel=\"icon\" type=\"image/png\" sizes=\"192x192\"  href=\"/android-icon-192x192.png\">"
    "<link rel=\"icon\" type=\"image/png\" sizes=\"32x32\" href=\"/favicon-32x32.png\">"
    "<link rel=\"icon\" type=\"image/png\" sizes=\"96x96\" href=\"/favicon-96x96.png\">"
    "<link rel=\"icon\" type=\"image/png\" sizes=\"16x16\" href=\"/favicon-16x16.png\">"
    "<link rel=\"stylesheet\" href=\"/main.css\" >"
    "<script src=\"jquery-3.1.1.min.js\"></script>\n"
		"</head>"
		"<body>");
	message += "<h1>" + String(settings.mySettings.systemname) + "</h1>\n";
  message += "<h2>" + WEB_Uhrtext + "</h2>\n";
#ifdef DEDICATION
	message += DEDICATION;
	message += "<br><br>";
#endif
	if (mode == MODE_BLANK) message += F("<button title=\"LEDs an\" onclick=\"window.location.href='/handleButtonOnOff'\">&#9899;</button>\n");
	else message += F("<button title=\"LEDs aus\" onclick=\"window.location.href='/handleButtonOnOff'\">&#9898;</button>\n");
	message += F("<button title=\"Einstellungen\" onclick=\"window.location.href='/handleButtonSettings'\">&#128295;</button>\n");
  message += F("<button title=\"Animationen\" onclick=\"window.location.href='/animationmenue'\">&#127916;</button>\n");
  message += F("<button title=\"Events\" onclick=\"window.location.href='/events.html'\">&#128197;</button>\n"
  "<button title=\"Nachricht\" onclick=\"window.location.href='/nachricht.html'\">&#128172;</button>\n"
  "<button title=\"Spiele\" onclick=\"window.location.href='/Gamemenue.html'\">&#127922;</button>\n"
  "<button title=\"Infoanzeige\" id=\"button_mode\" type=\"button\" \">&#128512;</button>\n"
  "<button title=\"Zeitanzeige\" id=\"button_zeit\" type=\"button\" \">&#128344;</button>\n");

message += F("<hr>\n");

// Abschnitt Mondphase
#ifdef SHOW_MODE_MOONPHASE

  message += F("<table><tr>");
  message += F("<td style=\"width:30%\">");
  message += F("<img id=\"Sonnen\" title=\"Sonnenaufgang\" src=\"/web_sonnenaufgang.png\" alt=\"Sonnenaufgang\">");
  message += F("</td>\n");
  
  message += F("<td style=\"width:30%\">");
  message += F("<img id=\"Sonnen\" title=\"Sonnenuntergang\" src=\"/web_sonnenuntergang.png\" alt=\"Sonnenuntergang\">");
  message += F("</td>\n");
  
  message += F("<td style=\"padding-top: 17px;width:40%\">");
  message += F("<span id=\"Mond\" title=\"Mondphase\">");
  switch (web_moonphase)
  {
    case 0: message += F("&#127761;"); //Neumond
    break;
    case 1: message += F("&#127762;");
    break;
    case 2: message += F("&#127763;");
    break;
    case 3: message += F("&#127764;");
    break;
    case 4: message += F("&#127765;"); //Vollmond
    break;
    case 5: message += F("&#127766;");
    break;
    case 6: message += F("&#127767;");
    break;
    case 7: message += F("&#127768;");
  }
  message += F("</span>");
  message += F("</td>\n");
  message += F("</tr>\n");
  message += F("<tr>");
  message += F("<td>");
  
#if defined(SunRiseLib) || defined(APIKEY)
  message += F("<span id=\"Sonnenzeit\" title=\"Sonnenaufgang\">");
  message += String(sunriseHour) + ":";
  if (sunriseMinute < 10) message += F("0");
  message += String(sunriseMinute);
  message += F(" Uhr");
  message += F("</span></td>\n");
#endif

  message += F("<td>");
  
#if defined(SunRiseLib) || defined(APIKEY)
  message += F("<span id=\"Sonnenzeit\" title=\"Sonnenuntergang\">");
  message += String(sunsetHour) + ":";
  if (sunsetMinute < 10) message += F("0");
  message += String(sunsetMinute);
  message += F(" Uhr");
  message += F("</span></td>\n");
#endif
  
  message += F("<td>"); 
  message += F("<span id=\"Mondphase\" title=\"Mondphase\">");
  if ( moonphase == 0 )                   message += F("Neumond");     // Neumond
  if ( moonphase == 11 )                  message += F("Vollmond");    // Vollmond
  if ( moonphase > 0 && moonphase < 11 )  message += F("zunehmend");   // zunehmend
  if ( moonphase > 11 && moonphase < 22 ) message += F("abnehmend");   // abnehmend
  message += F("</span></td>\n");
  message += F("</tr></table>");
  message += F("<hr>\n");
#endif

// Abschnitt Innentemperatur + Luftfeuchtigkeit + Luftdruck

#if defined(RTC_BACKUP) || defined(SENSOR_BME280)
	message += F("<br><span style=\"font-size:30px;\">&#127968;</span>");  //Haus
	message += "<br><span style=\"font-size:24px;\">&#127777;</span> <span style=\"font-size:20px;\">" + String(roomTemperature) + "&deg;C / " + String(roomTemperature * 1.8 + 32.0) + "&deg;F</span>";
#endif

// ################### sende html Teil 1
webServer.sendHeader("Cache-Control", "no-cache");
webServer.send(200, "text/html", message);
message = "";
delay(0);

#ifdef SENSOR_BME280
	message += "<br><span style=\"font-size:18px;\">&#128167;</span> <span style=\"font-size:20px;\">" + String(roomHumidity) + "%RH</span>"
		"<br><span style=\"font-size:24px;\">";
	if (roomHumidity < 30) message += F("<span style=\"color:Red;\">&#9751;</span>");
	else message += F("<span style=\"color:Red;\">&#9750;</span>");
	if ((roomHumidity >= 30) && (roomHumidity < 40)) message += F("<span style=\"color:Orange;\">&#9751;</span>");
	else message += F("<span style=\"color:Orange;\">&#9750;</span>");
	if ((roomHumidity >= 40) && (roomHumidity <= 50)) message += F("<span style=\"color:MediumSeaGreen;\">&#9751;</span>");
	else message += F("<span style=\"color:MediumSeaGreen;\">&#9750;</span>");
	if ((roomHumidity > 50) && (roomHumidity < 60)) message += F("<span style=\"color:Lightblue;\">&#9751;</span>");
	else message += F("<span style=\"color:Lightblue;\">&#9750;</span>");
	if (roomHumidity >= 60) message += F("<span style=\"color:Blue;\">&#9751;</span>");
	else message += F("<span style=\"color:Blue;\">&#9750;</span>");
	message += F("</span>");
  message += "<br><span style=\"font-size:20px;\">&#128168;</span><span style=\"font-size:20px;\">rel. " + String(Pressure_red) + " hPa <br>(abs. " + String(Pressure) + " hPa) </span>" ;

//#####################
// Luftdruck Diagramm
//#####################
message += F("<br>\n");
message += F("<br><span style=\"font-size:14px;\">");
message += F("Luftdruck der letzten Stunden: (Tendenz:  </span>");
message += F("<span style=\"font-size:24px;\">");
  if ( luftdrucktendenz_web == 1 ) message += F(" &#8595;");
  if ( luftdrucktendenz_web == 2 ) message += F(" &#8600;");
  if ( luftdrucktendenz_web == 3 ) message += F(" &#8594;");
  if ( luftdrucktendenz_web == 4 ) message += F(" &#8599;");
  if ( luftdrucktendenz_web == 5 ) message += F(" &#8593;");
message += F("</span><span style=\"font-size:14px;\"> )</span>\n");
message += F("<div>\n");
message += F("<canvas id=\"canvas_druckdiagramm\" width=\"300\" height=\"270\" style=\"border:2px solid #d3d3d3;\">");
message += F("<script type=\"text/javascript\">");
message += F("var canvas = document.getElementById(\"canvas_druckdiagramm\");\n");
message += F("var canvasWidth = 300;\n");
message += F("var canvasHeight = 270;\n");
message += F("canvas.setAttribute('width', canvasWidth);\n");
message += F("canvas.setAttribute('height', canvasHeight);\n");
message += F("var cv = canvas.getContext(\"2d\");\n");

//Options Grid

message += F("var yAchse = { values:[\n");
for(uint8_t i=0; i<=65; i=i+5) {
  message += F("{Y:\"");
  if ( LUFTDRUCKMIN + i < 1000 ) message += F("  ");
  message += String(LUFTDRUCKMIN + i); 
  message += F("hPa\",C:\"#000000\"},{Y:\" \",C:\"#000000\"},\n");
}

message += F("]};\n");
message += F("var graphxoffset = 42;\n");
message += F("var graphyoffset = 15;\n");
message += F("var graphGridSize = (canvasHeight - graphyoffset) / yAchse.values.length;\n");
message += F("var graphGridY = (canvasHeight - graphyoffset) / graphGridSize;\n");
message += F("cv.lineWidth = 1;\n");
message += F("for(var i = 0; i < graphGridY; i++){\n");
message += F("cv.moveTo(canvasWidth,  canvasHeight - graphGridSize*i-graphyoffset);\n");
message += F("cv.lineTo(graphxoffset, canvasHeight - graphGridSize*i-graphyoffset);\n");
message += F("}\n");
message += F("cv.strokeStyle = \"#FFFFFF\";\n");
message += F("cv.stroke();\n");

message += F("cv.fillStyle = '#000000';\n");
message += F("cv.font = \"10px Arial\";\n");
message += F("for(var i = 0; i < graphGridY; i++){\n");
message += F("cv.fillStyle = yAchse.values[i].C;\n");
message += F("cv.fillText(yAchse.values[i].Y,0,canvasHeight - graphGridSize*i-graphyoffset+3,graphxoffset);\n");
message += F("}\n");

//Data Graph
message += F("var data = { values:[");
message += "{A:\"-30h\",B:" + String(luftdruck_hist[0]) + ",C:\"#353746\"},\n"
"{A:\"-27h\",B:" + String(luftdruck_hist[1]) + ",C:\"#353746\"},\n"
"{A:\"-24h\",B:" + String(luftdruck_hist[2]) + ",C:\"#353746\"},\n"
"{A:\"-21h\",B:" + String(luftdruck_hist[3]) + ",C:\"#353746\"},\n"
"{A:\"-18h\",B:" + String(luftdruck_hist[4]) + ",C:\"#353746\"},\n"
"{A:\"-15h\",B:" + String(luftdruck_hist[5]) + ",C:\"#353746\"},\n"
"{A:\"-12h\",B:" + String(luftdruck_hist[6]) + ",C:\"#353746\"},\n"
"{A:\" -9h\",B:" + String(luftdruck_hist[7]) + ",C:\"#353746\"},\n"
"{A:\" -6h\",B:" + String(luftdruck_hist[8]) + ",C:\"#353746\"},\n"
"{A:\" -3h\",B:" + String(luftdruck_hist[9]) + ",C:\"#353746\"},\n"
"{A:\" akt\",B:" + String(luftdruck_hist[10]) + ",C:\"#353746\"}\n"
"]};\n";

//Options Graph
message += F("var graphMinValue = "); message += String(LUFTDRUCKMIN) + ";\n";    // Value der Nulllinie
message += F("var graphXDiff = 2.5;\n");       // Value für eine Abschnittsdifferenz
message += F("var graphPadding = 5;\n");
message += F("var graphFaktor = graphGridSize / graphXDiff;\n");
message += F("var graphWidth = (canvasWidth-graphPadding-graphxoffset) / data.values.length;\n");
message += F("var graphTextcolor = '#000000';\n");

//Draw Graph
message += F("for(var i = 0; i < data.values.length; i ++){\n");
message += F("Value = data.values[i].B-graphMinValue;\n");
message += F("tmpTop = (canvasHeight-graphyoffset-(graphFaktor*Value)).toFixed();\n");
message += F("tmpHeight = ((Value*graphFaktor)).toFixed();\n");
message += F("cv.fillStyle = data.values[i].C;\n");
message += F("cv.fillRect(graphWidth+((i-1)*graphWidth)+graphPadding+graphxoffset, tmpTop, graphWidth-graphPadding, tmpHeight);\n");
message += F("cv.fillStyle = graphTextcolor;\n");
message += F("cv.font = \"10px Arial\";\n");
message += F("cv.fillText(data.values[i].A, graphWidth+((i-1)*graphWidth)+graphPadding-2+graphxoffset, canvasHeight-3, graphWidth);\n");
message += F("}\n");
message += F("</script>");
message += F("</div>\n");
message += F("<hr>\n");
//##################### sende Luftdruck Diagramm html Teil 2
webServer.sendContent(message); 
message = "";
delay(0);
#else
 message += F("<hr><br>\n");
#endif

// Abschnitt Außentemperatur + Luftfeuchtigkeit
#ifdef APIKEY
if ( strlen(settings.mySettings.openweatherapikey) > 25 )
{
  message += F("<br>");
  message += F("<span style=\"font-size:30px;\">&#127794;</span>");  //Baum
  message += F("<br><span style=\"font-size:24px;\">&#127777;</span><span style=\"font-size:20px;\">"); 
  message += String(outdoorWeather.temperature);
  message += F("&deg;C / ");
  message += String(outdoorWeather.temperature * 1.8 + 32.0);
  message += F("&deg;F</span><br><span style=\"font-size:18px;\">&#128167;</span> <span style=\"font-size:20px;\">"); 
  message += String(outdoorWeather.humidity);
  message += F("%RH</span><br><span style=\"font-size:20px;\">Windgeschwindigkeit ");
  message += String(outdoorWeather.windspeed);
  message += F(" &#13223;</span><br><span style=\"font-size:20px;\">");
  message += outdoorWeather.description;
  message += F("</span><br>");
  if ( outdoorWeather.weathericon1.length() > 1 ) 
  {
    message += F("<img id=\"Wettersymbole\" title=\"Wetter\" src=\"web_"); 
    message += getWeatherIcon(outdoorWeather.weathericon1);
    message += F(".png\" alt=\"Wetter\">");
  }
  if ( outdoorWeather.weathericon2.length() > 1 && outdoorWeather.weathericon1 != outdoorWeather.weathericon2 ) 
  {
    message += F("<img id=\"Wettersymbole\" title=\"Wetter\" src=\"web_"); 
    message += getWeatherIcon(outdoorWeather.weathericon2);
    message += F(".png\" alt=\"Wetter\">");
  }    

  message += F("<br><br><hr>\n");
  //##################### sende Außentemperatur + Luftfeuchtigkeit html Teil 3
webServer.sendContent(message); 
message = "";
delay(0);
}
#endif

#ifdef SENSOR_BME280
//#####################
// Temperatur Diagramm
//#####################
message += F("<br>\n");
message += F("<span style=\"font-size:14px;\">");
message += F("Temperaturverlauf der letzten 24 Stunden:");
message += F("</span>\n");
message += F("<div>\n");
message += F("<canvas id=\"canvas_tempdiagramm\" width=\"400\" height=\"200\" style=\"border:1px solid #d3d3d3;\">\n");
message += F("<script type=\"text/javascript\">\n");
message += F("var canvas = document.getElementById(\"canvas_tempdiagramm\");\n");
message += F("var canvasWidth = 330;\n");
message += F("var canvasHeight = 270;\n");
message += F("canvas.setAttribute('width', canvasWidth);\n");
message += F("canvas.setAttribute('height', canvasHeight);\n");
message += F("var cv = canvas.getContext(\"2d\");\n");
//Options Grid

message += F("var yAchse = { values:[\n"
"{Y:\" -20°C\",C:\"#990099\"},\n"
"{Y:\" -15°C\",C:\"#330099\"},\n"
"{Y:\" -10°C\",C:\"#0000aa\"},\n"
"{Y:\"  -5°C\",C:\"#0000bb\"},\n"
"{Y:\"   0°C\",C:\"#003399\"},\n"
"{Y:\"   5°C\",C:\"#005555\"},\n"
"{Y:\"  10°C\",C:\"#007733\"},\n"
"{Y:\"  15°C\",C:\"#777722\"},\n"
"{Y:\"  20°C\",C:\"#775522\"},\n"
"{Y:\"  25°C\",C:\"#995522\"},\n"
"{Y:\"  30°C\",C:\"#992222\"},\n"
"{Y:\"  35°C\",C:\"#771111\"},\n"
 "{Y:\"  40°C\",C:\"#770000\"}\n"
"]};\n");

//X-Grid:
message += F("var graphxoffset = 30;\n");
message += F("var graphyoffset = 15;\n");
message += F("var graphGridSize = (canvasHeight - graphyoffset) / yAchse.values.length;\n");
message += F("var graphGridY = (canvasHeight - graphyoffset) / graphGridSize;\n");

message += F("cv.lineWidth = 1;\n");
message += F("for(var i = 0; i < graphGridY; i++){\n");
message += F("cv.moveTo(canvasWidth,  canvasHeight - graphGridSize*i-graphyoffset);\n");
message += F("cv.lineTo(graphxoffset, canvasHeight - graphGridSize*i-graphyoffset);\n");
message += F("}\n");
message += F("cv.strokeStyle = \"#FFFFFF\";\n");
message += F("cv.stroke();\n");

//Y-Achse Text:
message += F("cv.fillStyle = '#000000';\n");
message += F("cv.font = \"10px Arial\";\n");
message += F("for(var i = 0; i < graphGridY; i++){\n");
message += F("cv.fillStyle = yAchse.values[i].C;\n");
message += F("cv.fillText(yAchse.values[i].Y,0,canvasHeight - graphGridSize*i-graphyoffset+3,graphxoffset);\n");
message += F("}\n");

//Data Graph:
message += "var data = { values:[\n";
  for ( int i = 0; i <=71; i++)
  {
    message += "{T:\"" + temperatur_hist[i].stundeminute + "\",GA:" + String(temperatur_hist[i].aussentemp) + ",GB:" + String(temperatur_hist[i].innentemp) + "},\n";
  }
  message += "{T:\"" + temperatur_hist[72].stundeminute + "\",GA:" + String(temperatur_hist[72].aussentemp) + ",GB:" + String(temperatur_hist[72].innentemp) + "}\n";
message += "]};\n";

//##################### sende Temp Diagramm html Teil 4.1
webServer.sendContent(message); 
message = "";
delay(0);
//Options Graph

message += F("var graphMinValue = -20;\n"             // Value der Nulllinie
 "var graphXDiff = 5;\n"                              // Value für eine Abschnittsdifferenz
 "var graphFaktor = graphGridSize/graphXDiff;\n"
 "var graphPadding = 1;\n"
 "var graphWidth = (canvasWidth-graphPadding-graphxoffset)/data.values.length;\n"
 "var graphTextcolor = '#000000';\n"
 "var gradient = cv.createLinearGradient(0,canvasHeight,0,0);\n");
message += F("gradient.addColorStop(\"0\",\"magenta\");"
 "gradient.addColorStop(\"0.3\",\"blue\");"
 "gradient.addColorStop(\"0.4\",\"green\");"
 "gradient.addColorStop(\"0.6\",\"yellow\");"
 "gradient.addColorStop(\"1.0\",\"red\");\n");

//Draw Graph
message += F("for(var i = 1; i < data.values.length; i ++){\n");
// Graph1
message += F("ValueA1 = data.values[i-1].GA-graphMinValue;\n");
message += F("ValueA2 = data.values[i].GA-graphMinValue;\n");
message += F("tmpTopA1 = (canvasHeight-graphyoffset-(graphFaktor*ValueA1)).toFixed();\n");
message += F("tmpTopA2 = (canvasHeight-graphyoffset-(graphFaktor*ValueA2)).toFixed();\n");

// Graph2
message += F("ValueB1 = data.values[i-1].GB-graphMinValue;\n");
message += F("ValueB2 = data.values[i].GB-graphMinValue;\n");
message += F("tmpTopB1 = (canvasHeight-graphyoffset-(graphFaktor*ValueB1)).toFixed();\n");
message += F("tmpTopB2 = (canvasHeight-graphyoffset-(graphFaktor*ValueB2)).toFixed();\n");

// Y-Grid + X-Beschriftung
message += F("if ( data.values[i-1].T.substr(-2) == \"00\" ) {\n");
message += F("cv.fillStyle = graphTextcolor;\n");
message += F("cv.font = \"9px Arial\";\n");
message += F("cv.fillText(data.values[i-1].T.substr(0,2), graphWidth+((i-1)*graphWidth)+graphPadding-5+graphxoffset, canvasHeight-2,graphWidth*3);\n");
message += F("cv.beginPath();\n");
message += F("cv.moveTo(graphWidth+((i-1)*graphWidth)+graphPadding+graphxoffset, canvasHeight - graphyoffset+4);\n");
message += F("cv.lineTo(graphWidth+((i-1)*graphWidth)+graphPadding+graphxoffset, 0);\n");
message += F("cv.lineWidth = 1;\n");
message += F("cv.strokeStyle = \"#FFFFFF\";\n");
message += F("cv.stroke();\n");
message += F("}\n");
message += F("cv.beginPath();\n");
message += F("cv.lineWidth = 3;\n");
message += F("cv.moveTo(graphWidth+((i-1)*graphWidth)+graphPadding+graphxoffset, tmpTopA1);\n");
message += F("cv.lineTo(graphWidth+((i)*graphWidth)+graphPadding+graphxoffset, tmpTopA2);\n");
message += F("cv.strokeStyle = gradient;\n");
message += F("cv.stroke();\n");
message += F("cv.beginPath();\n");
message += F("cv.lineWidth = 3;\n");
message += F("cv.moveTo(graphWidth+((i-1)*graphWidth)+graphPadding+graphxoffset, tmpTopB1);\n");
message += F("cv.lineTo(graphWidth+((i)*graphWidth)+graphPadding+graphxoffset, tmpTopB2);\n");
message += F("cv.strokeStyle = \"#000000\";\n");
message += F("cv.stroke();\n");
message += F("}\n");
message += F("</script></div><hr>\n");
//##################### sende Temp Diagramm html Teil 4.2
webServer.sendContent(message); 
message = "";
delay(0);
#endif

// Abschnitt Wortuhr und Uptime
message += F("<span style=\"font-size:12px;\">\n");
message += F("<br>Wortuhr");
message += "<br>\nUptime: " + String(int(upTime / 86400)) + " Tage, " + String(hour(upTime)) + " Stunden, " + String(minute(upTime)) + " Minuten, " + String(second(upTime)) + " Sekunden";
message += "<br>\nFirmware: " + String(FIRMWARE_VERSION);
message += "<br>\n";

// Abschnitt Info Button
message += F("<hr>\n");
message += F("<button id=\"Infobutton\" title=\"Info\" name=\"Info\" onclick=\"window.location.href='/debugClock'\">Info</button>");
message += F("</span>");

 message += F("\n<script>\n"
    "$(\"#button_zeit\").click(function() {"
      "$.post(\"/handleButtonTime\");"
    "});\n"
    "$(\"#button_mode\").click(function() {"
      "$.post(\"/handleButtonMode\");"
    "});\n"
    "document.addEventListener(\"visibilitychange\", function() {"
    "if (!document.hidden){"
    " location.reload();"
    "}"
    "});\n"

    "</script>\n");

// Ende Webserver
	message += F("</body></html>");
//##################### sende letzen html Teil 5
  webServer.sendContent(message);
  webServer.sendContent("");
//	webServer.send(200, "text/html", message);
  if ( ESP.getMaxFreeBlockSize() < minFreeBlockSize ) 
  {
    minFreeBlockSize = ESP.getMaxFreeBlockSize();
    codeline = __LINE__;
#ifdef DEBUG
    Serial.printf("minFreeBlockSize: %i Codezeile: %u\n", minFreeBlockSize,codeline); 
#endif   
  }
  message = "";
}

//debugClock
void debugClock()
{
#ifdef DEBUG
    Serial.println("Info Seite refresh!");
#endif
  delay(0);
  webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
  String message;
  message = F("<!doctype html>"
  "<html>"
  "<head>");
  message += "<title>" + String(settings.mySettings.systemname) + " Info</title>";  
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
  "<meta http-equiv=\"refresh\" content=\"30\" charset=\"UTF-8\">"
  "<link rel=\"icon\" type=\"image/png\" sizes=\"192x192\" href=\"/android-icon-192x192.png\">"
  "<link rel=\"icon\" type=\"image/png\" sizes=\"32x32\" href=\"/favicon-32x32.png\">"
  "<link rel=\"icon\" type=\"image/png\" sizes=\"96x96\" href=\"/favicon-96x96.png\">"
  "<link rel=\"icon\" type=\"image/png\" sizes=\"16x16\" href=\"/favicon-16x16.png\">"
  "<style>"
  "body{background-color:#FFFFFF;color:#333333;font-family:Sans-serif;font-size:16px;}"
  "</style>"
  "</head>\n"
  "<body>");
  // ################### sende html Teil 1
  webServer.send(200, "text/html", message);
  message = "";
  delay(0);
  
  message += "<h2>" + String(settings.mySettings.systemname) + " Info</h2>";
  message += F("<hr>\n"
    "<small><br></small>");
  message += F("<big><b>&bull;  Firmware: ");
  message += String(FIRMWARE_VERSION);
  message += F("</b></big>\n");
  message += F("<a href=\"https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/main/Bedienungsanleitung_Wortuhr_mp3.pdf\" target=\"_blank\" style=\"font-size:30px;\">&#128214;</a>\n");
  message += F("<ul>\n"
// ######################### WIFI/NETZWERK ##################
    "<li><b>WiFi/Netzwerk</b>\n"
    "<ul>\n");
  message += F("<li>WLan-SID: ");
  message += WiFi.SSID();
  message += F("</li>\n");
  message += F("<li>Signalst&auml;rke: ");
  message += WiFi.RSSI();
  message += F(" dBm (");
  if ( WiFi.RSSI() >= -50 ) message += F("ausgezeichnet");
  if ( WiFi.RSSI() >= -65 && WiFi.RSSI() < -50 ) message += F("sehr gut");
  if ( WiFi.RSSI() >= -70 && WiFi.RSSI() < -65 ) message += F("gut");
  if ( WiFi.RSSI() >= -75 && WiFi.RSSI() < -70 ) message += F("akzeptabel");
  if ( WiFi.RSSI() >= -80 && WiFi.RSSI() < -75 ) message += F("schlecht");
  if ( WiFi.RSSI() >= -90 && WiFi.RSSI() < -80 ) message += F("sehr schlecht");
  if ( WiFi.RSSI() < -90 ) message += F("ungen&uumlgend");
  message += F(")</li>\n");
  message += F("<li>WLAN Reconnect pro Tag: "); 
  message += String(WLAN_reconnect) + "</li>\n";
  message += F("<li>IP-Addresse: ");
  message += String(myIP[0]) + '.' + String(myIP[1]) + '.' + String(myIP[2]) + '.' + String(myIP[3]);
  message += F("</li>\n<li>Client IP-Addr: ");
  message += webServer.client().remoteIP().toString();
  message += F("</li>\n");
  message += F("</ul>\n</li>\n");

// ######################### ZEIT ##################
  message += F("<li><b>Zeit</b>\n"
     "<ul>\n"); 
  message += "<li>NTP-Server: " + String(settings.mySettings.ntphost) + "</li>\n"
    "<li>Error (NTP): " + String(errorCounterNTP) + "</li>\n" 
    "<li>ESP-Time Drift in sek: " + String(esptimedrift) + " <small>(max: " + String(maxesptimedrift) + ")</small></li>\n";  
  time_t tempEspTime = now();
  message += "<li>Zeit: " + String(hour(tempEspTime)) + ":";
  if (minute(tempEspTime) < 10) message += "0";
  message += String(minute(tempEspTime));
  message += ":";
  if (second(tempEspTime) < 10) message += "0";
  message += String(second(tempEspTime));
  if (timeZone.locIsDST(now())) message += " (Sommerzeit)";
  message += "<li>Datum:" + String(dayStr(weekday(tempEspTime))) + ", " + String(day(tempEspTime)) + ". " + String(monthStr(month(tempEspTime))) + " "  + String(year(tempEspTime)) + "</li>\n";
  message += "</li>\n<li>UTC-TST:" + String(timeZone.toUTC(tempEspTime)) + "</li>\n" +
   "<li>Uptime: " + String(int(upTime / 86400)) + " d, " + String(hour(upTime)) + " h, " + String(minute(upTime)) + " m, " + String(second(upTime)) + " s</li>\n";
  time_t lokalstartTime = timeZone.toLocal(startTime);
  message += "<li>Startzeit: " + String(hour(lokalstartTime)) + ":";
  if (minute(lokalstartTime) < 10) message += "0";
  message += String(minute(lokalstartTime));
  message += ":";
  if (second(lokalstartTime) < 10) message += "0";
  message += String(second(lokalstartTime));
  message += " " + String(day(lokalstartTime)) + "." + String(month(lokalstartTime)) + "." + String(year(lokalstartTime)) + "</li>\n";
  message +="<li>tgl. Stunde: " + String(randomHour) + ", stdl. Minute: " + String(randomMinute) + "</li>\n" +
   "<li>Mondphase Uhr: " + String(moonphase) + " Web: " + String(web_moonphase) + "</li>\n";
  message += F("</ul>\n"
    "</li>\n");

// ######################### SYSTEM ##################
  message += F("<li><b>System</b>\n"
     "<ul>\n");   
  message += "<li>ESP-BoardVersion: " + String(ESP.getCoreVersion()) + "</li>\n" + 
   "<li>Free RAM: " + String(ESP.getFreeHeap()) + " bytes</li>\n"
   "<li>MaxFreeBlockSize: " + String(ESP.getMaxFreeBlockSize()) + " bytes</li>\n"
   "<li><small>MinFreeBlockSize: " + String(minFreeBlockSize) + "bytes Codezeile: " + String(codeline) + "</small></li>\n"
   "<li>HeapFragmentation: " + String(ESP.getHeapFragmentation()) + " %</li>\n"
   "<li>CpuFreq: " + String(ESP.getCpuFreqMHz()) + " MHz</li>\n"
   "<li>FlashSize (real/ide): " + String(ESP.getFlashChipRealSize()/1024/1024) + "/" + String(ESP.getFlashChipSize()/1024/1024) + " MB</li>\n";
   
  message += "<li>Reset Grund: " + ESP.getResetReason() + "</li>\n";
  message += F("</ul>\n"
    "</li>\n");  
    
//##################### sende 2. html Teil
  webServer.sendContent(message);
  message = "";
  delay(0);
// ######################### AUDIO ##################
#ifdef AUDIO_SOUND
  message += F("<li><b>Audio</b>\n"
     "<ul>\n");   
  message += F("<li>Sprecher: ");
  if ( settings.mySettings.sprecher ) message += F("Vicki"); else message += F("Hans");
  message += F("</li>\n");
  message += F("<li>Lautst&auml;rke (0-30): ");  message += String(VOLUME_ALT);
  message += F("</li>\n");
  message += F("</ul>\n"
    "</li>\n");  
#endif

// ######################### LDR ##################
#ifdef LDR
  message += F("<li><b>LDR</b>\n"
     "<ul>\n");
  message += "<li>Helligkeit: " + String(brightness) +
  "<small> (min: " + String(MIN_BRIGHTNESS) + ", max : " + String(abcBrightness) + ")</small></li>\n<li>ABC: "; 
  settings.mySettings.useAbc ? message += "enabled" : message += "disabled";
  message += "</li>\n<li>LDR-Wert: " + String(ldrValue) + "<small> (min: " + String(minLdrValue) + ", max: " + String(maxLdrValue) + ")</small></li>\n";
  message += F("</ul>\n"
    "</li>\n");
#endif

// ######################### BME280 ##################
#ifdef SENSOR_BME280
  message += F("<li><b>BME280</b>\n"
     "<ul>\n");
  message += "<li>Error (BME): " + String(errorCounterBME) + "</li>\n";
  message += "<li>Temperatur: " + String(bme.readTemperature()) + "</li>\n";
  message += "<li>Luftfeuchte: " + String(bme.readHumidity()) + "</li>\n";
  message += "<li>Luftdruck: " + String(bme.readPressure() / 100.0F) + "</li>\n";
  message += "<li>Luftdruckdiff: " + String(info_luftdruckdiff) + "</li>\n";
  message += "<li>Druckschwellen: <small>(A: " + String(LUFTDRUCK_DIFF_LEICHTFALLEND) + "/" + String(LUFTDRUCK_DIFF_LEICHTSTEIGEND) + " B: " + String(LUFTDRUCK_DIFF_FALLEND) + "/" + String(LUFTDRUCK_DIFF_STEIGEND) + ")</small></li>\n";
  message += F("</ul>\n"
    "</li>\n");
#endif

// ######################### OPENWEATHER ##################
#ifdef APIKEY
 message += F("<li><b>OpenWeather</b>\n"
     "<ul>\n");
  message += "<li>OpenWeather Error: " + String(errorCounterOutdoorWeather) + " <small>(Code: " + String(retcodeOutdoorWeather,BIN) + ")</small></li>\n";
  message += "<li>Errortext: " + outdoorWeather.owfehler + "</li>\n";
  message += "<li>Letzter Update: " + String(hour(timeZone.toLocal(LastOutdoorWeatherTime))) + ":";
  if (minute(timeZone.toLocal(LastOutdoorWeatherTime)) < 10) message += "0";
  message += String(minute(timeZone.toLocal(LastOutdoorWeatherTime)));
  message += ":";
  if (second(timeZone.toLocal(LastOutdoorWeatherTime)) < 10) message += "0";
  message += String(second(timeZone.toLocal(LastOutdoorWeatherTime)));
  message += F("</li>\n");
  message += "<li>WetterInfo 1: <small>ID: " + String(outdoorWeather.weatherid1) + " ICON: " + outdoorWeather.weathericon1 + " CLOUDS: " + outdoorWeather.clouds + "</small></li>\n";
  message += "<li>WetterSound 1: <small>" + String(getWeatherSound(outdoorWeather.weatherid1)) + "</small></li>\n";
  message += "<li>WetterInfo 2: <small>ID: " + String(outdoorWeather.weatherid2) + " ICON: " + outdoorWeather.weathericon2 + "</small></li>\n";
  message += F("<li>Sonnenauf/untergang: ");
  if ( !ani_sunrise_done ) message += F("<b>");
  message += String(hour(outdoorWeather.sunrise)) + ":";
  if (minute(outdoorWeather.sunrise) < 10) message += "0"; 
  message += String(minute(outdoorWeather.sunrise)) + ":";
  if (second(outdoorWeather.sunrise) < 10) message += "0"; 
  message += String(second(outdoorWeather.sunrise));
  if ( !ani_sunrise_done ) message += F("</b>");
  
  message += F("/");
  if ( !ani_sunset_done ) message += F("<b>");
  message += String(hour(outdoorWeather.sunset)) + ":";
  if (minute(outdoorWeather.sunset) < 10) message += "0"; 
  message += String(minute(outdoorWeather.sunset)) + ":";
  if (second(outdoorWeather.sunset) < 10) message += "0";
  message += String(second(outdoorWeather.sunset));
  if ( !ani_sunset_done ) message += F("</b>");
  message += F("</li>\n");
  message += F("</ul>\n"
    "</li>\n");
#endif 

// ######################### SUNRISELIB ##################
#ifdef SunRiseLib
 message += F("<li><b>SunRiseLib</b>\n"
     "<ul>\n");
  message += F("<li>Sonnenauf/untergang: ");
  if ( !ani_sunrise_done ) message += F("<b>");
  message += String(hour(sunRiseTime)) + ":";
  if (minute(sunRiseTime) < 10) message += "0"; 
  message += String(minute(sunRiseTime)) + ":";
  if (second(sunRiseTime) < 10) message += "0"; 
  message += String(second(sunRiseTime));
  if ( !ani_sunrise_done ) message += F("</b>");
  
  message += F("/");
  if ( !ani_sunset_done ) message += F("<b>");
  message += String(hour(sunSetTime)) + ":";
  if (minute(sunSetTime) < 10) message += "0"; 
  message += String(minute(sunSetTime)) + ":";
  if (second(sunSetTime) < 10) message += "0";
  message += String(second(sunSetTime));
  if ( !ani_sunset_done ) message += F("</b>");
  message += F("</li>\n");
  message += F("</ul>\n"
    "</li>\n");
#endif      

// ######################### Events/Modes/Transitions ##################
 message += F("<li><b>Events/Mode/Transitions</b>\n"
     "<ul>\n");
  message += "<li>ModeCount pro Tag: " + String(Modecount) + "</li>\n"
  "<li>Event-Timer: " + String(showEventTimer) + "</li>\n"
  "<li>autoModeChange-Timer: " + String(autoModeChangeTimer) + "</li>\n"
  "<li>Letzte Trans: (" + String(akt_transition) + ")<small>";
  if      (akt_transition == TRANSITION_NORMAL)        message += F("normal");
  else if (akt_transition == TRANSITION_MOVEUP)        message += F("hoch");
  else if (akt_transition == TRANSITION_MOVEDOWN)      message += F("runter");
  else if (akt_transition == TRANSITION_MOVELEFT)      message += F("links");
  else if (akt_transition == TRANSITION_MOVERIGHT)     message += F("rechts");
  else if (akt_transition == TRANSITION_MOVELEFTDOWN)  message += F("links runter");   
  else if (akt_transition == TRANSITION_MOVERIGHTDOWN) message += F("rechts runter ");
  else if (akt_transition == TRANSITION_MOVECENTER)    message += F("mitte");
  else if (akt_transition == TRANSITION_FADE)          message += F("fade");
  else if (akt_transition == TRANSITION_FARBENMEER)    message += F("farbenmeer");
  else if (akt_transition == TRANSITION_MATRIX)        message += F("matrix");
  else if (akt_transition == TRANSITION_SPIRALE_LINKS) message += F("spirale links");
  else if (akt_transition == TRANSITION_SPIRALE_RECHTS) message += F("spirale rechts");
  else if (akt_transition == TRANSITION_ZEILENWEISE)   message += F("zeilenweise");
  else if (akt_transition == TRANSITION_REGENBOGEN)    message += F("regenbogen");
  else if (akt_transition == TRANSITION_MITTE_LINKSHERUM) message += F("mitte linksherum");
  else if (akt_transition == TRANSITION_QUADRATE)      message += F("quadrate");  
  else
  message += F("unbekannt");
  message += " </small></li>\n";
  message += F("</ul>\n"
    "</li>\n");
 
// ######################### Spiele ##################
  message += F("<li><b>Spiele</b>\n"
     "<ul>\n");
  message += "<li>Snake Count/Highscore: " + String(gamecount[SNAKE]) + "/" + String(highscore[SNAKE]) + "</li>\n";
  message += "<li>Tetris Count/Highscore: " + String(gamecount[TETRIS]) + "/" + String(highscore[TETRIS]) + "</li>\n";
  message += "<li>Bricks Count/Highscore: " + String(gamecount[BRICKS]) + "/" + String(highscore[BRICKS]) + "</li>\n";
  message += "<li>4gewinnt Count/Highscore: " + String(gamecount[VIERGEWINNT]) + "/" + String(highscore[VIERGEWINNT]) + "</li>\n";
  message += "<li>Tiermemory Count: " + String(gamecount[TIERMEMORY])  + "</li>\n";
  message += "<li>Musikmemory Count: " + String(gamecount[MUSIKMEMORY]) + "</li>\n";
  message += "<li>ABBAmemory Count: " + String(gamecount[ABBAMEMORY]) + "</li>\n";
  
  message += F("</ul>\n"
    "</li>\n");  

// ######################### Flags ##################
  message += F("<li><b>Flags</b>\n"
     "<ul>\n<li>");
#ifdef RTC_BACKUP
  message += F("RTC ");
#else
  message += F("<s>RTC</s> ");
#endif
#ifdef SENSOR_BME280
  message += F("BME ");
#else
  message += F("<s>BME280</s> ");
#endif
#ifdef LDR
  message += F("LDR ");
#else
  message += F("<s>LDR</s> ");
#endif
#ifdef BUZZER
  message += F("BUZZER ");
#else
  message += F("<s>BUZZER</s> ");
#endif
#ifdef AUDIO_SOUND
  message += F("AUDIO_SOUND ");
#else
  message += F("<s>AUDIO_SOUND</s>");
#endif
message += F("</li>\n<li>");
#ifdef IR_RECEIVER
  message += F("IR_RECEIVER ");
#else
  message += F("<s>IR_RECEIVER</s> ");
#endif
#ifdef ESP_LED
  message += F("ESP_LED ");
#else
  message += F("<s>ESP_LED</s> ");
#endif
#if defined(ONOFF_BUTTON) || defined(MODE_BUTTON) || defined(SHOW_TIME_BUTTON)
  message += F("BUTTONS ");
#else
  message += F("<s>BUTTONS</s> ");
#endif
  message += F("</li>\n"); 
  message += F("</ul>\n"
    "</li>\n"); 
    
  message += F("</ul>\n"); 
  
  message += F("</body></html>");
  //##################### sende letzen html Teil
  webServer.sendContent(message);
  webServer.sendContent("");
  message = "";
  delay(0);
}


//*********************************************************************************************************************************
// Page settings


void handleButtonSettings()
{
#ifdef DEBUG
  Serial.println("Settings pressed.");
#endif
  webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
  String message = F("<!doctype html>"
    "<html>"
    "<head>");
    message += F("<title>"); message += String(settings.mySettings.systemname); message += F(" Einstellung</title>");
    message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
    "<meta charset=\"UTF-8\">\n"
    "<link rel=\"icon\" type=\"image/png\" sizes=\"192x192\"  href=\"/android-icon-192x192.png\">\n"
    "<link rel=\"icon\" type=\"image/png\" sizes=\"32x32\" href=\"/favicon-32x32.png\">\n"
    "<link rel=\"icon\" type=\"image/png\" sizes=\"96x96\" href=\"/favicon-96x96.png\">\n"
    "<link rel=\"icon\" type=\"image/png\" sizes=\"16x16\" href=\"/favicon-16x16.png\">\n"
    "<style>\n"
    "body{background-color:#aaaaaa;text-align:center;color:#333333;font-family:Sans-serif;}\n"
    "button{background-color:#353746;text-align:center;line-height: 22px;color:#FFFFFF;width:150px;height:32px;margin:5px;padding:1px;border:2px solid #FFFFFF;font-size:14px;border-radius:15px;cursor: pointer;}\n"
    "h2 {color: #FFFFFF;text-shadow: 2px 2px 2px Black;}\n"
    "span {color: Black;}\n"
    "input[type=submit]{background-color:#1FA3EC;text-align:center;color:#FFFFFF;width:200px;padding:12px;border:5px solid #FFFFFF;font-size:20px;border-radius:10px;}\n"
    "table{border-collapse:collapse;margin:0px auto;} td{padding:12px;border-bottom:1px solid #ddd;} tr:first-child{border-top:1px solid #ddd;} td:first-child{text-align:right;} td:last-child{text-align:left;}\n"
    "select{font-size:16px;}\n"
    "#ssel{border-top:3px solid #aaaaaa;border-bottom:3px solid #aaaaaa;}"
    "#wt{padding:3px}"
    "</style>"
    "<script src=\"jquery-3.1.1.min.js\"></script>\n"
    "</head>"
    "<body>\n");
    message += F("<h2>"); message += String(settings.mySettings.systemname); message += F(" Settings</h2>");
// ################################################# sende html Teil 1
    webServer.send(200, "text/html", message);
    message = "";
    delay(0);
// ###################################################################
    message += F("<form action=\"/commitSettings\">\n"
    "<table>\n");
  // ------------------------------------------------------------------------
#if defined(BUZZER) || defined(AUDIO_SOUND)
  message += F("<tr><td>"
    "Alarm 1:"
    "</td><td>"
    "<input type=\"radio\" name=\"a1\" value=\"1\"");
  if (settings.mySettings.alarm1) message += F(" checked");
  message += F("> on "
    "<input type=\"radio\" name=\"a1\" value=\"0\"");
  if (!settings.mySettings.alarm1) message += F(" checked");
  message += F("> off&nbsp;&nbsp;&nbsp;"
    "<input type=\"time\" name=\"a1t\" value=\"");
  if (hour(settings.mySettings.alarm1Time) < 10) message += F("0");
  message += String(hour(settings.mySettings.alarm1Time)); message += F(":");
  if (minute(settings.mySettings.alarm1Time) < 10) message += F("0");
  message += String(minute(settings.mySettings.alarm1Time)); message += F("\">");
  message +=F(" h<br><br>"
    "<input type=\"checkbox\" name=\"a1w2\" value=\"4\"");
  if (bitRead(settings.mySettings.alarm1Weekdays, 2)) message += F(" checked");
  message += F("> Mo. "
    "<input type=\"checkbox\" name=\"a1w3\" value=\"8\"");
  if (bitRead(settings.mySettings.alarm1Weekdays, 3)) message += F(" checked");
  message += F("> Di. "
    "<input type=\"checkbox\" name=\"a1w4\" value=\"16\"");
  if (bitRead(settings.mySettings.alarm1Weekdays, 4)) message += F(" checked");
  message += F("> Mi. "
    "<input type=\"checkbox\" name=\"a1w5\" value=\"32\"");
  if (bitRead(settings.mySettings.alarm1Weekdays, 5)) message += F(" checked");
  message += F("> Do. "
    "<input type=\"checkbox\" name=\"a1w6\" value=\"64\"");
  if (bitRead(settings.mySettings.alarm1Weekdays, 6)) message += F(" checked");
  message += F("> Fr. "
    "<input type=\"checkbox\" name=\"a1w7\" value=\"128\"");
  if (bitRead(settings.mySettings.alarm1Weekdays, 7)) message += F(" checked");
  message += F("> Sa. "
    "<input type=\"checkbox\" name=\"a1w1\" value=\"2\"");
  if (bitRead(settings.mySettings.alarm1Weekdays, 1)) message += F(" checked");
  message += F("> So. "
    "</td></tr>\n");
  // ------------------------------------------------------------------------
  message += F("<tr><td>"
    "Alarm 2:"
    "</td><td>"
    "<input type=\"radio\" name=\"a2\" value=\"1\"");
  if (settings.mySettings.alarm2) message += F(" checked");
  message += F("> on "
    "<input type=\"radio\" name=\"a2\" value=\"0\"");
  if (!settings.mySettings.alarm2) message += F(" checked");
  message += F("> off&nbsp;&nbsp;&nbsp;"
    "<input type=\"time\" name=\"a2t\" value=\"");
  if (hour(settings.mySettings.alarm2Time) < 10) message += "0";
  message += String(hour(settings.mySettings.alarm2Time)) + ":";
  if (minute(settings.mySettings.alarm2Time) < 10) message += "0";
  message += String(minute(settings.mySettings.alarm2Time)) + "\">";
  message += F(" h<br><br>"
    "<input type=\"checkbox\" name=\"a2w2\" value=\"4\"");
  if (bitRead(settings.mySettings.alarm2Weekdays, 2)) message += F(" checked");
  message += F("> Mo. "
    "<input type=\"checkbox\" name=\"a2w3\" value=\"8\"");
  if (bitRead(settings.mySettings.alarm2Weekdays, 3)) message += F(" checked");
  message += F("> Di. "
    "<input type=\"checkbox\" name=\"a2w4\" value=\"16\"");
  if (bitRead(settings.mySettings.alarm2Weekdays, 4)) message += F(" checked");
  message += F("> Mi. "
    "<input type=\"checkbox\" name=\"a2w5\" value=\"32\"");
  if (bitRead(settings.mySettings.alarm2Weekdays, 5)) message += F(" checked");
  message += F("> Do. "
    "<input type=\"checkbox\" name=\"a2w6\" value=\"64\"");
  if (bitRead(settings.mySettings.alarm2Weekdays, 6)) message += F(" checked");
  message += F("> Fr. "
    "<input type=\"checkbox\" name=\"a2w7\" value=\"128\"");
  if (bitRead(settings.mySettings.alarm2Weekdays, 7)) message += F(" checked");
  message += F("> Sa. "
    "<input type=\"checkbox\" name=\"a2w1\" value=\"2\"");
  if (bitRead(settings.mySettings.alarm2Weekdays, 1)) message += F(" checked");
  message += F("> So. "
    "</td></tr>\n");
  // ------------------------------------------------------------------------
  message += F("<tr><td>"
    "Timer:"
    "</td><td>"
    "<select name=\"ti\">");
  for (int i = 0; i <= 10; i++)
  {
    message += F("<option value=\""); message += String(i) + "\">";
    if (i < 10) message += "0";
    message += String(i) + "</option>";
  }
  message += F("<option value=\"15\">15</option>"
    "<option value=\"20\">20</option>"
    "<option value=\"25\">25</option>"
    "<option value=\"30\">30</option>"
    "<option value=\"45\">45</option>"
    "<option value=\"60\">60</option>"
    "</select> minuten"
    "</td></tr>\n");
  // ------------------------------------------------------------------------
#ifndef AUDIO_SOUND
  message += F("<tr><td>"
    "Hourly beep:"
    "</td><td>"
    "<input type=\"radio\" name=\"hb\" value=\"1\"");
  if (settings.mySettings.hourBeep) message += F(" checked");
  message += F("> on "
    "<input type=\"radio\" name=\"hb\" value=\"0\"");
  if (!settings.mySettings.hourBeep) message += F(" checked");
  message += F("> off"
    "</td></tr>\n");
#endif
#endif

// ########################################################################### sende Settings html Teil 2
webServer.sendContent(message);
message = "";
delay(0);
// ########################################################################### sende Settings html Teil 2
  // ------------------------------------------------------------------------
#ifdef AUDIO_SOUND
  message += F("<tr><td>"
    "Stundenschlag:"
    "</td><td>"
    "<input type=\"radio\" name=\"hb\" value=\"1\"");
  if (settings.mySettings.hourBeep) message += F(" checked");
  message += F("> on "
    "<input type=\"radio\" name=\"hb\" value=\"0\"");
  if (!settings.mySettings.hourBeep) message += F(" checked");
  message += F("> off"
    "</td></tr>"
    "<tr><td>"
    "Lautst&auml;rke:"
    "</td><td>"
    "<select name=\"vol\" id=\"vol\">");
  for (int i = 10; i <= 100; i += 10)
  {
    message += F("<option value=\"");  message += String(i) + "\"";
    if (i == settings.mySettings.volume) message += F(" selected");
    message += F(">");
    message += String(i); message += F("</option>");
  }
  message += F("</select> %"
    "</td></tr>"
    "<tr><td>"
    "Stundensound:"
    "</td><td>"
    "zuf&auml;llig:"
    "<input type=\"radio\" id=\"srandon\" name=\"srand\" value=\"1\"");
    if (settings.mySettings.randomsound ) message += F(" checked");
    message += F("> on "
    "<input type=\"radio\" id=\"srandoff\" name=\"srand\" value=\"0\"");
    if (!settings.mySettings.randomsound ) message += F(" checked");
    message += F("> off"
    
    "<div id=\"wochentage\">"
    "<br>"
    "<table>");

    for ( uint8_t wti = 1; wti < 8; wti++)
    {
      uint8_t wt = wti;
      if ( wti == 7 ) wt = 0;
      message += F("<tr id=\"ssel\">"
      "<td id=\"wt\">");
      message += Wochentage[wt];
      message += F(":</td>"
      "<td id=\"wt\">"
      "<select name=\"wsf");
      message += String(wt);
      message += F("\" ");
      message += F(" id=\"soundfile");
      message += String(wt);
      message += F("\" >\n");
      message += F("<option value=\"0\"");
      if (settings.mySettings.weekdaysoundfile[wt] == 0) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME0;
      message += F("</option>\n"
      "<option value=\"1\"");  
      if (settings.mySettings.weekdaysoundfile[wt] == 1) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME1;
      message += F("</option>\n"
     
      "<option value=\"2\""); 
      if (settings.mySettings.weekdaysoundfile[wt] == 2) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME2;
      message += F("</option>\n"
    
      "<option value=\"3\"");   
      if (settings.mySettings.weekdaysoundfile[wt] == 3) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME3;
      message += F("</option>\n"

      "<option value=\"4\"");   
      if (settings.mySettings.weekdaysoundfile[wt] == 4) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME4;
      message += F("</option>\n"

      "<option value=\"5\"");   
      if (settings.mySettings.weekdaysoundfile[wt] == 5) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME5;
      message += F("</option>\n"
    
      "<option value=\"6\"");   
      if (settings.mySettings.weekdaysoundfile[wt] == 6) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME6;
      message += F("</option>\n"
     
      "<option value=\"7\""); 
      if (settings.mySettings.weekdaysoundfile[wt] == 7) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME7;
      message += F("</option>\n" 
    
      "<option value=\"8\""); 
      if (settings.mySettings.weekdaysoundfile[wt] == 8) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME8;
      message += F("</option>\n"
      
      "<option value=\"9\""); 
      if (settings.mySettings.weekdaysoundfile[wt] == 9) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME9;
      message += F("</option>\n"
      
      "<option value=\"10\""); 
      if (settings.mySettings.weekdaysoundfile[wt] == 10) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME10;
      message += F("</option>\n"

      "<option value=\"11\""); 
      if (settings.mySettings.weekdaysoundfile[wt] == 11) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME11;
      message += F("</option>\n"

      "<option value=\"12\""); 
      if (settings.mySettings.weekdaysoundfile[wt] == 12) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME12;
      message += F("</option>\n"

      "<option value=\"13\""); 
      if (settings.mySettings.weekdaysoundfile[wt] == 13) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME13;
      message += F("</option>\n"
    
      "<option value=\"14\""); 
      if (settings.mySettings.weekdaysoundfile[wt] == 14) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME14;
      message += F("</option>\n"

      "<option value=\"15\""); 
      if (settings.mySettings.weekdaysoundfile[wt] == 15) message += F(" selected");
      message += F(">");
      message += AUDIO_WEBNAME15;
      message += F("</option>\n"
          
      "</select>"
      "</td>");
      message += F("<td id=\"wt\">"
      "<input style=\"background-color:#353746; margin:3px; font-size:14px; border-radius:7px;\" title=\"Soundcheck\" id=\"soundcheck");
      message += String(wt);
      message += F("\" type=\"button\" value=\"&#128266\">"
      "</td>\n");       
      message += F("</tr>");
// ######################################################### sende html Wochentage Teile
      webServer.sendContent(message);
      message = "";
      delay(0);
// ###########################################################################
    }
  message += F("</table></div>\n");
  message += F("</td></tr>\n");

  message += F("<tr><td>"
    "am Wochenende 2h sp&auml;ter lauter:"
    "</td><td>"
    "<input type=\"radio\" name=\"wsl\" value=\"1\"");
  if (settings.mySettings.weekendlater) message += F(" checked");
  message += F("> on "
    "<input type=\"radio\" name=\"wsl\" value=\"0\"");
  if (!settings.mySettings.weekendlater) message += F(" checked");
  message += F("> off"
    "</td></tr>\n");

  message += F("<tr><td>"
    "Stundenansage Vicki/Hans Format:"
    "</td><td>"
    "<input type=\"radio\" name=\"vh24\" id=\"vh24on\" value=\"1\"");
  if (settings.mySettings.vickihans24h) message += F(" checked");
  message += F("> 24h "
    "<input type=\"radio\" name=\"vh24\" id=\"vh24off\" value=\"0\"");
  if (!settings.mySettings.vickihans24h) message += F(" checked");
  message += F("> 12h"
    "</td></tr>\n");

  message += F("<tr><td>"
    "Sprecher:"
    "</td><td>"
    "<input type=\"radio\" name=\"sprech\" value=\"1\"");
  if (settings.mySettings.sprecher) message += F(" checked");
  message += F("> Vicki "
    "<input type=\"radio\" name=\"sprech\" value=\"0\"");
  if (!settings.mySettings.sprecher) message += F(" checked");
  message += F("> Hans"
    "</td></tr>\n");
  
#endif
  // ------------------------------------------------------------------------
#if defined(RTC_BACKUP) || defined(SENSOR_BME280)
  message += F("<tr><td>"
    "Anzeige<br> Temperatur " 
#ifdef SHOW_MODE_MOONPHASE
    "Mondphase " 
#endif
#ifdef SHOW_MODE_WETTER 
    "Wetter " 
#endif
#ifdef SHOW_MODE_DATE
    "Datum "
#endif
    ":</td><td>"
    "<input type=\"radio\" id=\"mcon\" name=\"mc\" value=\"1\"");
  if (settings.mySettings.modeChange) message += F(" checked");
  message += F("> on "
    "<input type=\"radio\" id=\"mcoff\" name=\"mc\" value=\"0\"");
  if (!settings.mySettings.modeChange) message += F(" checked");
  message += F("> off");
  message += F( "<div id=\"amct\"> alle "
      "<input type=\"number\" style=\"width: 40px;\" value=\""); 
  message += String(settings.mySettings.auto_mode_change); 
  message += F("\" name=\"amct\" min=\"2\" max=\"180\">"  
    " min</div>");
  message += F("</td></tr>\n");
#endif
  // ------------------------------------------------------------------------
#if defined(SunRiseLib) || defined(APIKEY)
  message += F("<tr><td>"
    "Ank&uuml;ndigung - <br>"
    "Sonneaufgang:<br>"
    "Sonneuntergang:"
    "</td><td>"
    "<br><input type=\"radio\" name=\"sunr\" value=\"1\"");
  if (settings.mySettings.ani_sunrise) message += F(" checked");
  message += F("> on "
    "<input type=\"radio\" name=\"sunr\" value=\"0\"");
  if (!settings.mySettings.ani_sunrise) message += F(" checked");
  message += F("> off"
  "<br>"
    "<input type=\"radio\" name=\"suns\" value=\"1\"");
  if (settings.mySettings.ani_sunset) message += F(" checked");
  message += F("> on "
    "<input type=\"radio\" name=\"suns\" value=\"0\"");
  if (!settings.mySettings.ani_sunset) message += F(" checked");
  message += F("> off"  
    "</td></tr>\n");
#endif
  // ------------------------------------------------------------------------
#ifdef LDR
  message += F("<tr><td>"
    "autom. Helligkeit:"
    "</td><td>"
    "<input type=\"radio\" name=\"ab\" value=\"1\"");
  if (settings.mySettings.useAbc) message += F(" checked");
  message += F("> on "
    "<input type=\"radio\" name=\"ab\" value=\"0\"");
  if (!settings.mySettings.useAbc) message += F(" checked");
  message += F("> off"
    "</td></tr>\n");
#endif
  // ------------------------------------------------------------------------
  message += F("<tr><td>"
    "Helligkeit:"
    "</td><td>"
    "<select name=\"br\">");
  for (int i = 10; i <= 100; i += 10)
  {
    message += F("<option value=\"");  message += String(i) + "\"";
    if (i == settings.mySettings.brightness) message += F(" selected");
    message += F(">");
    message += String(i); 
    message += F("</option>");
  }
  message += F("</select> %"
    "</td></tr>\n");
  // ------------------------------------------------------------------------
  message += F("<tr><td>"
    "Farben:"
    "</td><td>"
    "<select name=\"co\">"
    "<option value=\"0\"");
  if (settings.mySettings.color == 0) message += F(" selected");
  message += F(">"
    "Weiss</option>"
    "<option value=\"1\"");
  if (settings.mySettings.color == 1) message += F(" selected");
  message += F(">"
    "Rot</option>"
    "<option value=\"2\"");
  if (settings.mySettings.color == 2) message += F(" selected");
  message += F(">"
    "Rot 75%</option>"
    "<option value=\"3\"");
  if (settings.mySettings.color == 3) message += F(" selected");
  message += F(">"
    "Rot 50%</option>"
    "<option value=\"4\"");
  if (settings.mySettings.color == 4) message += F(" selected");
  message += F(">"
    "Orange</option>"
    "<option value=\"5\"");
  if (settings.mySettings.color == 5) message += F(" selected");
  message += F(">"
    "Gelb</option>"
    "<option value=\"6\"");
  if (settings.mySettings.color == 6) message += F(" selected");
  message += F(">"
    "Gelb 75%</option>"
    "<option value=\"7\"");
  if (settings.mySettings.color == 7) message += F(" selected");
  message += F(">"
    "Gelb 50%</option>"
    "<option value=\"8\"");
  if (settings.mySettings.color == 8) message += F(" selected");
  message += F(">"
    "Gr&uuml;n-Gelb</option>"
    "<option value=\"9\"");
  if (settings.mySettings.color == 9) message += F(" selected");
  message += F(">"
    "Gr&uuml;n</option>"
    "<option value=\"10\"");
  if (settings.mySettings.color == 10) message += F(" selected");
  message += F(">"
    "Gr&uuml;n 75%</option>"
    "<option value=\"11\"");
  if (settings.mySettings.color == 11) message += F(" selected");
  message += F(">"
    "Gr&uuml;n 50%</option>"
    "<option value=\"12\"");
  if (settings.mySettings.color == 12) message += F(" selected");
  message += F(">"
    "Mintgr&uuml;n</option>"
    "<option value=\"13\"");
  if (settings.mySettings.color == 13) message += F(" selected");
  message += F(">"
    "Cyan</option>"
    "<option value=\"14\"");
  if (settings.mySettings.color == 14) message += F(" selected");
  message += F(">"
    "Cyan 75%</option>"
    "<option value=\"15\"");
  if (settings.mySettings.color == 15) message += F(" selected");
  message += F(">"
    "Cyan 50%</option>"
    "<option value=\"16\"");
  if (settings.mySettings.color == 16) message += F(" selected");
  message += F(">"
    "Leicht Blau</option>"
    "<option value=\"17\"");
  if (settings.mySettings.color == 17) message += F(" selected");
  message += F(">"
    "Blau</option>"
    "<option value=\"18\"");
  if (settings.mySettings.color == 18) message += F(" selected");
  message += F(">"
    "Blau 75%</option>"
    "<option value=\"19\"");
  if (settings.mySettings.color == 19) message += F(" selected");
  message += F(">"
    "Blau 50%</option>"
    "<option value=\"20\"");
  if (settings.mySettings.color == 20) message += F(" selected");
  message += F(">"
    "Violet</option>"
    "<option value=\"21\"");
  if (settings.mySettings.color == 21) message += F(" selected");
  message += F(">"
    "Magenta</option>"
    "<option value=\"22\"");
  if (settings.mySettings.color == 22) message += F(" selected");
  message += F(">"
    "Magenta 75%</option>"
    "<option value=\"23\"");
  if (settings.mySettings.color == 23) message += F(" selected");
  message += F(">"
    "Magenta 50%</option>"
    "<option value=\"24\"");
  if (settings.mySettings.color == 24) message += F(" selected");
  message += F(">"
    "Pink</option>"
    "</select>"
    "</td></tr>\n");
//-----------------------------------------------------------------------
//##################################### sende Settings html script Teil 3
webServer.sendContent(message); 
message = "";
delay(0);
// ######################################################################

  message += F("<tr><td>"
    "Minuten LED Farbe:"
    "</td><td>"
    "<select name=\"cco\">"
    "<option value=\"0\"");
  if (settings.mySettings.corner_color == 0) message += F(" selected");
  message += F(">"
    "Weiss</option>"
    "<option value=\"1\"");
  if (settings.mySettings.corner_color == 1) message += F(" selected");
  message += F(">"
    "Rot</option>"
    "<option value=\"2\"");
  if (settings.mySettings.corner_color == 2) message += F(" selected");
  message += F(">"
    "Rot 75%</option>"
    "<option value=\"3\"");
  if (settings.mySettings.corner_color == 3) message += F(" selected");
  message += F(">"
    "Rot 50%</option>"
    "<option value=\"4\"");
  if (settings.mySettings.corner_color == 4) message += F(" selected");
  message += F(">"
    "Orange</option>"
    "<option value=\"5\"");
  if (settings.mySettings.corner_color == 5) message += F(" selected");
  message += F(">"
    "Gelb</option>"
    "<option value=\"6\"");
  if (settings.mySettings.corner_color == 6) message += F(" selected");
  message += F(">"
    "Gelb 75%</option>"
    "<option value=\"7\"");
  if (settings.mySettings.corner_color == 7) message += F(" selected");
  message += F(">"
    "Gelb 50%</option>"
    "<option value=\"8\"");
  if (settings.mySettings.corner_color == 8) message += F(" selected");
  message += F(">"
    "Gr&uuml;n-Gelb</option>"
    "<option value=\"9\"");
  if (settings.mySettings.corner_color == 9) message += F(" selected");
  message += F(">"
    "Gr&uuml;n</option>"
    "<option value=\"10\"");
  if (settings.mySettings.corner_color == 10) message += F(" selected");
  message += F(">"
    "Gr&uuml;n 75%</option>"
    "<option value=\"11\"");
  if (settings.mySettings.corner_color == 11) message += F(" selected");
  message += F(">"
    "Gr&uuml;n 50%</option>"
    "<option value=\"12\"");
  if (settings.mySettings.corner_color == 12) message += F(" selected");
  message += F(">"
    "Mintgr&uuml;n</option>"
    "<option value=\"13\"");
  if (settings.mySettings.corner_color == 13) message += F(" selected");
  message += F(">"
    "Cyan</option>"
    "<option value=\"14\"");
  if (settings.mySettings.corner_color == 14) message += F(" selected");
  message += F(">"
    "Cyan 75%</option>"
    "<option value=\"15\"");
  if (settings.mySettings.corner_color == 15) message += F(" selected");
  message += F(">"
    "Cyan 50%</option>"
    "<option value=\"16\"");
  if (settings.mySettings.corner_color == 16) message += F(" selected");
  message += F(">"
    "Leicht Blau</option>"
    "<option value=\"17\"");
  if (settings.mySettings.corner_color == 17) message += F(" selected");
  message += F(">"
    "Blau</option>"
    "<option value=\"18\"");
  if (settings.mySettings.corner_color == 18) message += F(" selected");
  message += F(">"
    "Blau 75%</option>"
    "<option value=\"19\"");
  if (settings.mySettings.corner_color == 19) message += F(" selected");
  message += F(">"
    "Blau 50%</option>"
    "<option value=\"20\"");
  if (settings.mySettings.corner_color == 20) message += F(" selected");
  message += F(">"
    "Violet</option>"
    "<option value=\"21\"");
  if (settings.mySettings.corner_color == 21) message += F(" selected");
  message += F(">"
    "Magenta</option>"
    "<option value=\"22\"");
  if (settings.mySettings.corner_color == 22) message += F(" selected");
  message += F(">"
    "Magenta 75%</option>"
    "<option value=\"23\"");
  if (settings.mySettings.corner_color == 23) message += F(" selected");
  message += F(">"
    "Magenta 50%</option>"
    "<option value=\"24\"");
  if (settings.mySettings.corner_color == 24) message += F(" selected");
  message += F(">"
    "Pink</option>"
    "</select>"
    "</td></tr>\n");
  // ------------------------------------------------------------------------
  message += F("<tr><td>"
    "Farbenwechsel:"
    "</td><td>"
    "<input type=\"radio\" name=\"cc\" value=\"3\"");
  if (settings.mySettings.colorChange == 3) message += F(" checked");
  message += F("> tgl. "
    "<input type=\"radio\" name=\"cc\" value=\"2\"");
  if (settings.mySettings.colorChange == 2) message += F(" checked");
  message += F("> stdl. "
    "<input type=\"radio\" name=\"cc\" value=\"1\"");
  if (settings.mySettings.colorChange == 1) message += F(" checked");
  message += F("> 5 Min. "
    "<input type=\"radio\" name=\"cc\" value=\"0\"");
  if (settings.mySettings.colorChange == 0) message += F(" checked");
  message += F("> aus"
    "</td></tr>\n");
  // ------------------------------------------------------------------------
  message += F("<tr><td>"
    "Minuten Farbenwechsel:"
    "</td><td>"
    "<input type=\"radio\" name=\"ccc\" value=\"4\"");
  if (settings.mySettings.corner_colorChange == 4) message += F(" checked");
  message += F("> wie Hauptfarbe"
    "<br>"
    "<input type=\"radio\" name=\"ccc\" value=\"3\"");
  if (settings.mySettings.corner_colorChange == 3) message += F(" checked");
  message += F("> tgl. "
    "<input type=\"radio\" name=\"ccc\" value=\"2\"");
  if (settings.mySettings.corner_colorChange == 2) message += F(" checked");
  message += F("> stdl. "
    "<input type=\"radio\" name=\"ccc\" value=\"1\"");
  if (settings.mySettings.corner_colorChange == 1) message += F(" checked");
  message += F("> 5 Min. "
    "<input type=\"radio\" name=\"ccc\" value=\"0\"");
  if (settings.mySettings.corner_colorChange == 0) message += F(" checked");
  message += F("> aus"
    "</td></tr>\n");
// ------------------------------------------------------------------------    
  message += F("<tr><td>"
    "Hintergrundfarbe:"
    "</td><td>"
    "<input type=\"radio\" name=\"bgce\" id=\"bgce_off\" value=\"0\"");
  if (settings.mySettings.enable_bg_color == 0) message += F(" checked");
  message += F("> aus "
    "<input type=\"radio\" name=\"bgce\" id=\"bgce_zeit\" value=\"1\"");
  if (settings.mySettings.enable_bg_color == 1 ) message += F(" checked");
  message += F("> Zeit "
   "<input type=\"radio\" name=\"bgce\" id=\"bgce_immer\" value=\"2\"");
  if (settings.mySettings.enable_bg_color == 2 ) message += F(" checked");
  message += F("> immer  ");
  
  message += F("<input type=\"color\" color=\""); 
  message += num_to_string(settings.mySettings.bg_color); 
  message += F("\" value=\""); 
  message += num_to_string(settings.mySettings.bg_color); 
  message += F("\" name=\"bgc\" id=\"bgcolor\" >"
  
    "</td></tr>\n");
  // ------------------------------------------------------------------------

//######################################################### sende Settings html Teil 4
webServer.sendContent(message); 
message = "";
delay(0);
//#########################################################

#ifndef FRONTCOVER_BINARY
  message += F("<tr><td>"
   "&Uuml;bergang:"
   "</td><td>"
   "<select name=\"tr\">"
   "<optgroup label=\"Einzeln:\">"
    "<option value=\"0\"");
  if (settings.mySettings.transition == 0) message += F(" selected");
  message += F(">"
    "normal</option>" 
    "<option value=\"1\""); 
  if (settings.mySettings.transition == 1) message += F(" selected");
  message += F(">"
    "Farbenmeer</option>"
    "<option value=\"2\"");  
  if (settings.mySettings.transition == 2) message += F(" selected");
  message += F(">"
    "hoch</option>"  
    "<option value=\"3\""); 
  if (settings.mySettings.transition == 3) message += F(" selected");
  message += F(">"
    "runter</option>" 
    "<option value=\"4\"");   
  if (settings.mySettings.transition == 4) message += F(" selected");
  message += F(">"
    "links</option>"
    "<option value=\"5\"");   
  if (settings.mySettings.transition == 5) message += F(" selected");
  message += F(">"
    "rechts</option>"    
    "<option value=\"6\""); 
  if (settings.mySettings.transition == 6) message += F(" selected");
  message += F(">"
    "linksrunter</option>" 
    "<option value=\"7\""); 
  if (settings.mySettings.transition == 7) message += F(" selected");
  message += F(">"
    "rechtsrunter</option>"
    "<option value=\"8\""); 
  if (settings.mySettings.transition == 8) message += F(" selected");
  message += F(">"
    "zur Mitte</option>"
    "<option value=\"9\""); 
  if (settings.mySettings.transition == 9) message += F(" selected");
  message += F(">"
    "fade</option>"
    "<option value=\"10\""); 
  if (settings.mySettings.transition == 10) message += F(" selected");
  message += F(">"
    "Matrix</option>"
    "<option value=\"11\""); 
  if (settings.mySettings.transition == 11) message += F(" selected");
  message += F(">"
    "Spirale links</option>"
    "<option value=\"12\""); 
  if (settings.mySettings.transition == 12) message += F(" selected");
  message += F(">"
    "Spirale rechts</option>"
    "<option value=\"13\""); 
  if (settings.mySettings.transition == 13) message += F(" selected");
  message += F(">"
    "zeilenweise</option>"
    "<option value=\"14\""); 
  if (settings.mySettings.transition == 14) message += F(" selected");
  message += F(">"
    "Regenbogen</option>"
    "<option value=\"15\""); 
  if (settings.mySettings.transition == 15) message += F(" selected");
  message += F(">"
    "Mitte linksherum</option>"
  "<option value=\"16\""); 
  if (settings.mySettings.transition == 16) message += F(" selected");
  message += F(">"
    "Quadrate</option>"  
   "</optgroup>" 
   "<optgroup label=\"Alle:\">"
    "<option value=\"20\""); 
  if (settings.mySettings.transition == 20) message += F(" selected");
  message += F(">"
    "nacheinander</option>"
    "<option value=\"21\""); 
  if (settings.mySettings.transition == 21) message += F(" selected");
  message += F(">"
    "zuf&auml;llig</option>"
   "</optgroup>"
   
  "</select>"
  "</td></tr>\n");
#endif

  message += F("<tr><td>"
    "Nachts aus ab:"
    "</td><td>"
    "<input type=\"time\" name=\"no\" value=\"");
  if (hour(settings.mySettings.nightOffTime) < 10) message += "0";
  message += String(hour(settings.mySettings.nightOffTime)) + ":";
  if (minute(settings.mySettings.nightOffTime) < 10) message += "0";
  message += String(minute(settings.mySettings.nightOffTime)) + "\">"
    " h"
    "</td></tr>\n";
  // ------------------------------------------------------------------------
  message += F("<tr><td>"
    "Tags an ab:"
    "</td><td>"
    "<input type=\"time\" name=\"do\" value=\"");
  if (hour(settings.mySettings.dayOnTime) < 10) message += "0";
  message += String(hour(settings.mySettings.dayOnTime)) + ":";
  if (minute(settings.mySettings.dayOnTime) < 10) message += "0";
  message += String(minute(settings.mySettings.dayOnTime)) + "\">"
    " h"
    "</td></tr>\n";
  // ------------------------------------------------------------------------
  message += F("<tr><td>"
    "Zeige \"es ist\":"
    "</td><td>"
    "<input type=\"radio\" name=\"ii\" value=\"1\"");
  if (settings.mySettings.itIs) message += F(" checked");
  message += "> on "
    "<input type=\"radio\" name=\"ii\" value=\"0\"";
  if (!settings.mySettings.itIs) message += F(" checked");
  message += "> off"
    "</td></tr>\n";
  // ------------------------------------------------------------------------
  message += F("<tr><td>"
    "Setze Datum/Zeit:"
    "</td><td>"
    "<input type=\"datetime-local\" name=\"st\">"
    "</td></tr>\n");
  // ------------------------------------------------------------------------
  message += F("<tr><td>"
    "Zeitserver:"
    "</td><td>");
  message += F("<input type=\"search\" list=\"ntpserver\" placeholder=\""); message += String(settings.mySettings.ntphost) + "\" name=\"ntphost\">";
  message += F("<datalist id=\"ntpserver\">"
    "<option value=\"fritz.box\">"
    "<option value=\"pool.ntp.org\">"
    "<option value=\"ptbtime1.ptb.de\">"
    "<option value=\"ntp.web.de\">"
  "</datalist>"
    "</td></tr>\n");
  // ------------------------------------------------------------------------
  message += F("<tr><td>"
    "Systemname:"
    "</td><td>");
  message += F("<input type=\"text\" value=\""); 
  message += String(settings.mySettings.systemname); 
  message += F("\" name=\"sysname\" minlength=\"3\" maxlength=\"29\">"
    "</td></tr>\n");
  // ------------------------------------------------------------------------
#if defined(SunRiseLib) || defined(APIKEY)
  message += F("<tr><td>"
    "OpenWeather<br>ApiKey:<br>Location:<br>H&oumlhe Standort:");
#ifdef SunRiseLib
  message += F("<br>Latitude:<br>Longitude:");
#endif
  message += F("</td><td><br>");
  message += F("<input type=\"text\" value=\""); 
  message += String(settings.mySettings.openweatherapikey); 
  message += F("\" name=\"owkey\" minlength=\"9\" maxlength=\"34\" size=\"32\">"
             "<br><input type=\"text\" value=\""); 
  message += String(settings.mySettings.openweatherlocation); 
  message += F("\" name=\"owloc\" minlength=\"3\" maxlength=\"39\">"
            "<br><input type=\"number\" value=\""); 
  message += String(settings.mySettings.standort_hoehe); 
  message += F("\" name=\"hoehe\" min=\"0\" max=\"10000\">"  
            " m");
#ifdef SunRiseLib  
    message += F("<br><input type=\"number\" value=\""); 
    message += String(settings.mySettings.latitude); 
    message += F("\" name=\"latitude\" min=\"-90\" max=\"90\" step=0.01 >"
             "<br><input type=\"number\" value=\""); 
    message += String(settings.mySettings.longitude); 
    message += F("\" name=\"longitude\" min=\"-180\" max=\"180\" step=0.01 >");
#endif
  message += F("</td></tr>\n");
  
#endif
  // ------------------------------------------------------------------------
  // Highscore Reset
  message += F("<tr><td>"
    "Reset Highscores:"
    "</td><td>"
    "<input type=\"checkbox\" name=\"hsres\" value=\"1\">"
    "</td></tr>\n");
  // ------------------------------------------------------------------------
  
  message += F("</table>\n"
    "<br><button title=\"Explorer\" type=\"button\" onclick=\"window.location.href='/spiffs.html'\"><span style=\"color:White;font-size:14px;\">&#128193;SPIFFS</span></button>"
    "<hr>"
    "<br><button title=\"zur&uumlck\" type=\"button\" onclick=\"window.location.href='/'\"><span style=\"color:White;font-size:14px;\">&#128281; zur&uumlck</span></button>"
    "<button title=\"Save Settings.\"><span style=\"color:White;font-size:14px;\">&#128077; speichern</span></button>"
    "</form>\n");
//##################### sende Settings html script Teil
webServer.sendContent(message); 
message = "";
delay(0);
    message += F("<script>\n"
    "var urlBase = \"/\";");

    for ( uint8_t wti = 0; wti < 7; wti++)
    {

      message += F("$(\"#soundcheck");
      message += String(wti);
      message += F("\").click(function() {");
      message += F("if ( $(\"#vh24on\").prop('checked') ) vh24=1;");
      message += F("else  vh24=0;");
      message += F("var posturl = urlBase + \"AudioTest?soundfile=\" + $(\"#soundfile");
      message += String(wti);
      message += F("\").val() + \"&volume=\" + $(\"#vol\").val() + \"&vh24=\" + vh24;"
      "$.post(posturl);" 
      "});\n");
    }

    message +=F("$(\"#bgce_off\").click(function(){"
    "var posturl = urlBase + \"BackgroundColor?bgce=off\";\n"
    "$.post(posturl);" 
      "});\n");
    message +=F("$(\"#bgce_zeit\").click(function(){"
    "var posturl = urlBase + \"BackgroundColor?bgce=zeit\";\n"
    "$.post(posturl);" 
      "});\n");
    message +=F("$(\"#bgce_immer\").click(function(){"
    "var posturl = urlBase + \"BackgroundColor?bgce=immer\";\n"
    "$.post(posturl);" 
      "});\n");
    message +=F("$(\"#bgcolor\").change(function(){"
    "bgcolor = this.value;"
    "$(this).attr(\"color\",bgcolor);"
//    "console.log(\"bgcolor: \" + bgcolor);"
    "var posturl = urlBase + \"BackgroundColor?bgcolor=\" + bgcolor.slice(1, 7).toUpperCase();\n"
    "$.post(posturl);" 
      "});\n");
          
    message += F("$(\"#mcon\").click(function(){"
    "$(\"#amct\").show();"
    "});\n"
    "$(\"#mcoff\").click(function(){"
    "$(\"#amct\").hide();"
    "});\n"

    "$(\"#srandoff\").click(function(){"
    "$(\"#wochentage\").show();"
    "});\n"
    "$(\"#srandon\").click(function(){"
    "$(\"#wochentage\").hide();"
    "});\n"
    
    "document.addEventListener('DOMContentLoaded', function() {" 
    "if ( $(\"#mcoff\").prop('checked') )  $(\"#amct\").hide();"
    "else $(\"#amct\").show();"

    "if ( $(\"#srandon\").prop('checked') )  $(\"#wochentage\").hide();"
    "else $(\"#wochentage\").show();"
    
    "});\n"
    "</script>\n"
  "</body>\n</html>");
  //##################### sende letzen html Teil 5
  webServer.sendContent(message);
  webServer.sendContent("");
  if ( ESP.getMaxFreeBlockSize() < minFreeBlockSize ) 
  {
    minFreeBlockSize = ESP.getMaxFreeBlockSize();
    codeline = __LINE__;
#ifdef DEBUG
    Serial.printf("minFreeBlockSize: %i Codezeile: %u\n", minFreeBlockSize,codeline); 
#endif   
  }
  message = "";
}

void handleCommitSettings()
{
#ifdef DEBUG
	Serial.println("Commit settings pressed.");
#endif
	// ------------------------------------------------------------------------
#if defined(BUZZER) || defined(AUDIO_SOUND)
	time_t alarmTimeFromWeb = 0; 
//Alarm1
	if ( webServer.arg("a1") == "0" ) settings.mySettings.alarm1 = false;
	if ( webServer.arg("a1") == "1" ) settings.mySettings.alarm1 = true;

  if (webServer.arg("a1t")!= "" )
  {
  	alarmTimeFromWeb = webServer.arg("a1t").substring(0, 2).toInt() * 3600 + webServer.arg("a1t").substring(3, 5).toInt() * 60;
  	if (settings.mySettings.alarm1Time != alarmTimeFromWeb)
  		settings.mySettings.alarm1 = true;
  	settings.mySettings.alarm1Time = alarmTimeFromWeb;
  	settings.mySettings.alarm1Weekdays =
  		webServer.arg("a1w1").toInt() +
  		webServer.arg("a1w2").toInt() +
  		webServer.arg("a1w3").toInt() +
  		webServer.arg("a1w4").toInt() +
  		webServer.arg("a1w5").toInt() +
  		webServer.arg("a1w6").toInt() +
  		webServer.arg("a1w7").toInt();
  }
	// ------------------------------------------------------------------------
//Alarm2
	if ( webServer.arg("a2") == "0" ) settings.mySettings.alarm2 = false;
	if ( webServer.arg("a2") == "1" ) settings.mySettings.alarm2 = true;
  if (webServer.arg("a2t")!= "" )
  {
  	alarmTimeFromWeb = webServer.arg("a2t").substring(0, 2).toInt() * 3600 + webServer.arg("a2t").substring(3, 5).toInt() * 60;
  	if (settings.mySettings.alarm2Time != alarmTimeFromWeb)
  		settings.mySettings.alarm2 = true;
  	settings.mySettings.alarm2Time = alarmTimeFromWeb;
  	settings.mySettings.alarm2Weekdays =
  		webServer.arg("a2w1").toInt() +
  		webServer.arg("a2w2").toInt() +
  		webServer.arg("a2w3").toInt() +
  		webServer.arg("a2w4").toInt() +
  		webServer.arg("a2w5").toInt() +
  		webServer.arg("a2w6").toInt() +
  		webServer.arg("a2w7").toInt();
  }
	// ------------------------------------------------------------------------
// Stundenschlag
	if ( webServer.arg("hb") == "0" ) settings.mySettings.hourBeep = false;
	if ( webServer.arg("hb") == "1" ) settings.mySettings.hourBeep = true;
	// ------------------------------------------------------------------------
//Timer
	if (webServer.arg("ti") != "")
  {
    if ( webServer.arg("ti").toInt() ) 
  	{
  		alarmTimer = webServer.arg("ti").toInt();
  		alarmTimerSecond = second();
  		alarmTimerSet = true;
  		setMode(MODE_TIMER);
  	}
  }
#endif
#ifdef AUDIO_SOUND
// Lautstärke
  if ( webServer.arg("vol") != "" ) settings.mySettings.volume = webServer.arg("vol").toInt();
// Zufallssound
  if ( webServer.arg("srand") == "0" ) settings.mySettings.randomsound = false;
  if ( webServer.arg("srand") == "1" ) settings.mySettings.randomsound = true;

// Stundensound für Wochentage
  for ( uint8_t wti = 0; wti < 7; wti++)
  {
    if ( webServer.arg("wsf" + String(wti)) != "" ) settings.mySettings.weekdaysoundfile[wti] = webServer.arg("wsf" + String(wti)).toInt();
  }
//Sprecher  
  if ( webServer.arg("sprech") == "1" ) 
  {
    settings.mySettings.sprecher = true; 
    ANSAGEBASE = AUDIO_BASENR_VICKI;
  }
  if ( webServer.arg("sprech") == "0" ) 
  {
    settings.mySettings.sprecher = false;
    ANSAGEBASE = AUDIO_BASENR_HANS;
  }
#ifdef DEBUG
  Serial.printf("ANSAGEBASE: %i\r\n", ANSAGEBASE);
#endif

// Wochenend später lauter
  if ( webServer.arg("wsl") == "0" ) settings.mySettings.weekendlater = false;
  if ( webServer.arg("wsl") == "1" ) settings.mySettings.weekendlater = true;
// 12/24 Stunden Ansage
  if ( webServer.arg("vh24") == "0" ) settings.mySettings.vickihans24h = false; 
  if ( webServer.arg("vh24") == "1" ) settings.mySettings.vickihans24h = true;

#endif
// ------------------------------------------------------------------------
// AutoModeChange / AutoModeChange Timer
	if ( webServer.arg("mc") == "0" ) settings.mySettings.modeChange = false;
  if ( webServer.arg("mc") == "1" ) 
  { 
    settings.mySettings.modeChange = true;
    settings.mySettings.auto_mode_change = webServer.arg("amct").toInt();
    if ( autoModeChangeTimer > settings.mySettings.auto_mode_change * 60 ) autoModeChangeTimer = settings.mySettings.auto_mode_change * 60 ;
  }
// ------------------------------------------------------------------------
#if defined(SunRiseLib) || defined(APIKEY)
// Sunrise/ Sunset
  if ( webServer.arg("sunr") == "0" ) settings.mySettings.ani_sunrise = false;
  if ( webServer.arg("sunr") == "1" ) settings.mySettings.ani_sunrise = true;
  if ( webServer.arg("suns") == "0" ) settings.mySettings.ani_sunset = false;
  if ( webServer.arg("suns") == "1" ) settings.mySettings.ani_sunset = true;
#endif
// ------------------------------------------------------------------------
// Helligkeit in Prozent
  if ( webServer.arg("br") != "" ) settings.mySettings.brightness = webServer.arg("br").toInt();
  
  // ------------------------------------------------------------------------
#ifdef LDR
// ABC
	if (webServer.arg("ab") == "0")
	{
		settings.mySettings.useAbc = false;
    brightness = map(settings.mySettings.brightness, 10, 100, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	}
	if (webServer.arg("ab") == "1")
  {
    abcBrightness = map(settings.mySettings.brightness, 10, 100, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
		settings.mySettings.useAbc = true;
    if ( ldrValue <= 200 ) lastLdrValue = 400;
    if ( ldrValue > 200 ) lastLdrValue = 0;
  }
#else
  settings.mySettings.useAbc = false;
  abcBrightness = map(settings.mySettings.brightness, 10, 100, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
  brightness = abcBrightness;
#endif

// ------------------------------------------------------------------------
//Hauptfarbe
	if ( webServer.arg("co") != "" ) settings.mySettings.color = webServer.arg("co").toInt();
//Minutenfarbe
  if ( webServer.arg("cco") != "" ) settings.mySettings.corner_color = webServer.arg("cco").toInt();
// ------------------------------------------------------------------------
// Farbwechsel
  if ( webServer.arg("cc") != "")
  {
  	switch (webServer.arg("cc").toInt())
  	{
  	case 0: settings.mySettings.colorChange = COLORCHANGE_NO;   break;
  	case 1: settings.mySettings.colorChange = COLORCHANGE_FIVE; break;
  	case 2: settings.mySettings.colorChange = COLORCHANGE_HOUR; break;
  	case 3: settings.mySettings.colorChange = COLORCHANGE_DAY;  break;
  	}
  }
// ------------------------------------------------------------------------
// Farbwechsel Minutenfarbe
  if ( webServer.arg("ccc") != "")
  {
    switch (webServer.arg("ccc").toInt())
    {
    case 0: settings.mySettings.corner_colorChange = COLORCHANGE_NO;   break;
    case 1: settings.mySettings.corner_colorChange = COLORCHANGE_FIVE; break;
    case 2: settings.mySettings.corner_colorChange = COLORCHANGE_HOUR; break;
    case 3: settings.mySettings.corner_colorChange = COLORCHANGE_DAY;  break;
    case 4: settings.mySettings.corner_colorChange = COLORCHANGE_MAIN; break;
    }
    if ( settings.mySettings.corner_colorChange == COLORCHANGE_MAIN) settings.mySettings.corner_color = settings.mySettings.color;
  }
// ------------------------------------------------------------------------
// Hintergrundfarbe Modus
  if ( webServer.arg("bgce") == "0" ) settings.mySettings.enable_bg_color = 0; 
  if ( webServer.arg("bgce") == "1" ) settings.mySettings.enable_bg_color = 1; 
  if ( webServer.arg("bgce") == "2" ) settings.mySettings.enable_bg_color = 2;
// Hintergrundfarbe
  if ( webServer.arg("bgc") != "")
  {
    String farbwert = webServer.arg("bgc");
    farbwert.toUpperCase();
    settings.mySettings.bg_color = string_to_num(farbwert);
  }
// ------------------------------------------------------------------------
// Transitions
  if ( webServer.arg("tr") != "" )
  {
  	switch (webServer.arg("tr").toInt())
  	{
  	case 0: settings.mySettings.transition = TRANSITION_NORMAL; break;
  	case 1: settings.mySettings.transition = TRANSITION_FARBENMEER; break;
    case 2: settings.mySettings.transition = TRANSITION_MOVEUP;   break;
    case 3: settings.mySettings.transition = TRANSITION_MOVEDOWN; break;
  	case 4: settings.mySettings.transition = TRANSITION_MOVELEFT;   break;
    case 5: settings.mySettings.transition = TRANSITION_MOVERIGHT; break;
    case 6: settings.mySettings.transition = TRANSITION_MOVELEFTDOWN; break;
    case 7: settings.mySettings.transition = TRANSITION_MOVERIGHTDOWN; break;
    case 8: settings.mySettings.transition = TRANSITION_MOVECENTER;   break;
    case 9: settings.mySettings.transition = TRANSITION_FADE;   break;
    case 10: settings.mySettings.transition = TRANSITION_MATRIX;   break;
    case 11: settings.mySettings.transition = TRANSITION_SPIRALE_LINKS;   break;
    case 12: settings.mySettings.transition = TRANSITION_SPIRALE_RECHTS;   break;
    case 13: settings.mySettings.transition = TRANSITION_ZEILENWEISE;   break;
    case 14: settings.mySettings.transition = TRANSITION_REGENBOGEN;   break;
    case 15: settings.mySettings.transition = TRANSITION_MITTE_LINKSHERUM;   break;
    case 16: settings.mySettings.transition = TRANSITION_QUADRATE;   break;
    
    case 20: settings.mySettings.transition = TRANSITION_ALLE_NACHEINANDER;   break;
    case 21: settings.mySettings.transition = TRANSITION_RANDOM;   break;
    
  	}
  }
// ------------------------------------------------------------------------
// Nachts aus Zeit
  if ( webServer.arg("no") != "" )	settings.mySettings.nightOffTime = webServer.arg("no").substring(0, 2).toInt() * 3600 + webServer.arg("no").substring(3, 5).toInt() * 60;
// ------------------------------------------------------------------------
// Tag ein Zeit
	if ( webServer.arg("do") != "" ) settings.mySettings.dayOnTime = webServer.arg("do").substring(0, 2).toInt() * 3600 + webServer.arg("do").substring(3, 5).toInt() * 60;
// ------------------------------------------------------------------------
// Zeige "ES IST"
	if ( webServer.arg("ii") == "0" ) settings.mySettings.itIs = false;
	if ( webServer.arg("ii") == "1" ) settings.mySettings.itIs = true;
// ------------------------------------------------------------------------
// NTP-Server 
  if ( webServer.arg("ntphost").length() && webServer.arg("ntphost") != settings.mySettings.ntphost )
  {
    webServer.arg("ntphost").toCharArray(settings.mySettings.ntphost,webServer.arg("ntphost").length()+1);
    strcpy(ntpServer,settings.mySettings.ntphost);
    aktntptime = true;
  }
// ------------------------------------------------------------------------  
// Systemname
  if ( webServer.arg("sysname").length() && webServer.arg("sysname") != settings.mySettings.systemname )
  {
    webServer.arg("sysname").toCharArray(settings.mySettings.systemname,webServer.arg("sysname").length()+1);
  }
// ------------------------------------------------------------------------  
// openweatherapikey
  if ( webServer.arg("owkey").length() && webServer.arg("owkey") != settings.mySettings.openweatherapikey )
  {
    webServer.arg("owkey").toCharArray(settings.mySettings.openweatherapikey,webServer.arg("owkey").length()+1);
  }
//openweatherlocation
  if ( webServer.arg("owloc").length() && webServer.arg("owloc") != settings.mySettings.openweatherlocation )
  {
    webServer.arg("owloc").toCharArray(settings.mySettings.openweatherlocation,webServer.arg("owloc").length()+1);
  }
//hoehe_ueber_0
  if ( webServer.arg("hoehe").length() && webServer.arg("hoehe").toInt() != settings.mySettings.standort_hoehe )
  {
    settings.mySettings.standort_hoehe = webServer.arg("hoehe").toInt();
  }
// Standort
  if ( webServer.arg("latitude").length() )
  {
    settings.mySettings.latitude = webServer.arg("latitude").toDouble();
  }
  if ( webServer.arg("longitude").length() )
  {
    settings.mySettings.longitude = webServer.arg("longitude").toDouble();
  }
    
// ------------------------------------------------------------------------
// Setze /Datum/Uhrzeit
	if (webServer.arg("st").length())
	{
		Serial.println(webServer.arg("st"));
		setTime(webServer.arg("st").substring(11, 13).toInt(), webServer.arg("st").substring(14, 16).toInt(), 0, webServer.arg("st").substring(8, 10).toInt(), webServer.arg("st").substring(5, 7).toInt(), webServer.arg("st").substring(0, 4).toInt());
#ifdef RTC_BACKUP
		RTC.set(now());
#endif
	}
 // ------------------------------------------------------------------------
 // Highscores reset
  if (webServer.arg("hsres") == "1" ) 
  {
    highscore[SNAKE] = 0;
    highscore[TETRIS] = 0;
    highscore[BRICKS] = 0;
    highscore[VIERGEWINNT] = 0;
  
    settings.mySettings.highscore[SNAKE] = highscore[SNAKE];
    settings.mySettings.highscore[TETRIS] = highscore[TETRIS];
    settings.mySettings.highscore[BRICKS] = highscore[BRICKS];
    settings.mySettings.highscore[VIERGEWINNT] = highscore[VIERGEWINNT];
  }
  if ( webServer.args() < 10 )
  {
    webServer.send(200, "text/plain", "Parameter gesetzt!");
  }
  else
  {
// Sichern der Einstellungen
	  settings.saveToEEPROM();
	  callRoot();
  }
	screenBufferNeedsUpdate = true;
}
//------------------------------------------------------------------------
// Ende handleCommitSettings()
//------------------------------------------------------------------------


// Page reboot
void handleReboot()
{
	webServer.send(200, "text/plain", "OK. I'll be back!");
  delay (5000);
	ESP.restart();
}

// WiFi Reset
void handleWiFiReset()
{
  webServer.send(200, "text/plain", "OK. I'll be back as AP!");
  WiFi.disconnect(true);
  delay (1000);
  ESP.restart();
}

void BackgroundColor()
{
  webServer.send(200, "text/plain", "OK");
  if ( webServer.arg("bgcolor").length() == 6 ) 
  {
    String wert = "#" + webServer.arg("bgcolor");
    settings.mySettings.bg_color=string_to_num(wert);
    screenBufferNeedsUpdate = true;
    #ifdef DEBUG
      Serial.print("ändere Background: ");
      Serial.println(webServer.arg("bgcolor"));
    #endif  
  }
  if ( webServer.arg("bgce").length() > 2 ) 
  {
    #ifdef DEBUG
      Serial.print( "Background Enable: ");
      Serial.println(webServer.arg("bgce"));
    #endif  
    if ( webServer.arg("bgce") == "off" ) settings.mySettings.enable_bg_color = 0;
    if ( webServer.arg("bgce") == "zeit" ) settings.mySettings.enable_bg_color = 1; 
    if ( webServer.arg("bgce") == "immer" ) settings.mySettings.enable_bg_color = 2;
    if (settings.mySettings.enable_bg_color == 0 ) screenBufferNeedsUpdate = true; 
    else ledDriver.show();
  }
}

#ifdef AUDIO_SOUND
// AudioTest
void AudioTest()
{
  webServer.send(200, "text/plain", "OK");
  #ifdef DEBUG
      Serial.print( "Audiotest Volume: ");
      Serial.println(webServer.arg("volume"));
      Serial.print( "Audiotest Soundfilenr.: ");
      Serial.println(webServer.arg("soundfile"));
      Serial.print( "Vicki/Hans 24h: ");
      Serial.println(webServer.arg("vh24"));
  #endif
  
  volume_test_bck = settings.mySettings.volume;
  vickihans24h_bck = settings.mySettings.vickihans24h;
  if ( webServer.arg("vh24") == "0" ) settings.mySettings.vickihans24h = false; 
  else settings.mySettings.vickihans24h = true;
  settings.mySettings.volume = webServer.arg("volume").toInt();
  testsoundfile = webServer.arg("soundfile").toInt();
  AUDIO_TEST = true;
  AUDIO_HOUR = hour();
#ifdef DEBUG
  Serial.println("AudioTest...");
#endif
}
#endif

// Page setEvent
//http://wortuhr-ip/setEvent?text=Testevent&color=2&audio=700&preani=ALARM&postani=ALARM
void handleSetEvent()
{
  if ( events[0].aktiv ) 
  {
    webServer.send(202, "text/plain", "EVENT nicht aktiviert");
  }
  else
  {
    webServer.send(200, "text/plain", "EVENT gesetzt");
    events[0].aktiv = true;
    events[0].year = 9;
  	events[0].day = day();
  	events[0].month = month();
  	events[0].text = webServer.arg("text").substring(0, 80);
  	events[0].color = (eColor)webServer.arg("color").toInt();
    events[0].audio_file = webServer.arg("audio").toInt();
    events[0].preani=webServer.arg("preani").substring(0, 40);
    events[0].postani=webServer.arg("postani").substring(0, 40);
    events[0].intervall=(showEventTimer / 60 ) + 1;                // intervall in Minuten, showEventTimer in Sekunden
    showEventTimer = 2;
#ifdef DEBUG_EVENTS
	Serial.println("Event set: " + String(events[0].day) + "." + String(events[0].month) + ". " + events[0].text);
#endif
  }
}

// Page showText
//Beispiel: http://10.1.1.40/showText?buzzer=2&color=0&text=Das%20ist%20eine%20Nachricht%3A%20viel%20Spass%20mit%20der%20Wortuhr%2E
void handleShowText()
{
	uint8_t feedBuzzer = webServer.arg("buzzer").toInt();
	feedColor = webServer.arg("color").toInt();
	feedText = "  " + webServer.arg("text").substring(0, 80) + "   ";
	feedPosition = 0;
	webServer.send(200, "text/plain", "OK.");

#ifdef DEBUG
	Serial.println("Show text: " + webServer.arg("text").substring(0, 80));
#endif

#ifdef BUZZER
	for (uint8_t i = 0; i < feedBuzzer; i++)
	{
		digitalWrite(PIN_BUZZER, HIGH);
		delay(75);
		digitalWrite(PIN_BUZZER, LOW);
		delay(100);
	}
#endif
#ifdef AUDIO_SOUND
  for (uint8_t i = 0; i < feedBuzzer; i++)
  {
    Play_MP3(701,true,0); //Magical
  }

  AUDIO_FILENR = ANSAGEBASE + 42; // Eine Nachricht
  Play_MP3(AUDIO_FILENR,true,0);
  Play_MP3(706,false,0);
  
#endif

	setMode(MODE_FEED);
}

void handleControl()
{
	setMode((Mode)webServer.arg("mode").toInt());
	webServer.send(200, "text/plain", "OK.");
}

//################################################################################################################
// EVENTS
void handleevents()
{
  String webarg;
  uint8_t eventnr = 0;
  if ( webServer.arg("_action") == "0" ) callRoot();
  if ( webServer.arg("_action") == "1" )
  {
    showEventTimer = 10;  // nach Speichern nächste Prüfung in 10 Sek.
    for ( uint8_t eventnr = 1;eventnr <= MAXEVENTS;eventnr++)
    {
      events[eventnr].aktiv=false;
    }
    for (int i = 0; i < webServer.args(); i++) {
      webarg = String(i) + ": ";
      webarg += webServer.argName(i) + " : ";
      webarg += webServer.arg(i);
//      Serial.println(webarg);
      if ( webServer.argName(i).startsWith("t") )
      {
        eventnr++;
        if ( eventnr <= MAXEVENTS )
        {
          events[eventnr].aktiv=true;
          events[eventnr].text = webServer.arg(i);
          events[eventnr].text.trim();
        }
      }
      if ( eventnr <= MAXEVENTS )
      {
        if ( webServer.argName(i).startsWith("d") ) 
        { 
          events[eventnr].year = webServer.arg(i).substring(0,4).toInt();
          events[eventnr].month = webServer.arg(i).substring(5,7).toInt();
          events[eventnr].day = webServer.arg(i).substring(8).toInt();
        }
        if ( webServer.argName(i).startsWith("c") ) events[eventnr].color = webServer.arg(i).toInt();
        if ( webServer.argName(i).startsWith("a") ) events[eventnr].audio_file = webServer.arg(i).toInt();
        if ( webServer.argName(i).startsWith("v") ) {events[eventnr].preani = webServer.arg(i); events[eventnr].preani.trim();}
        if ( webServer.argName(i).startsWith("n") ) {events[eventnr].postani = webServer.arg(i);events[eventnr].postani.trim();}
        if ( webServer.argName(i).startsWith("i") ) events[eventnr].intervall = webServer.arg(i).toInt();
      }
    }
#ifdef DEBUG_EVENTS
    for ( uint8_t eventnr = 0;eventnr <= MAXEVENTS;eventnr++)
    {
      if ( events[eventnr].aktiv ) Serial.printf("Save Event: %i , Jahr: %i Monat: %i Tag: %i AudioNr: %i\n",eventnr, events[eventnr].year, events[eventnr].month,events[eventnr].day, events[eventnr].audio_file);
      if ( events[eventnr].aktiv ) Serial.println(events[eventnr].text);
    }
#endif
    bool save = saveEvents();
    callRoot();
  }
}

//################################################################################################################
// ANIMATIONEN
bool showAnimation(uint8_t brightness)
{
  uint8_t red;
  uint8_t green; 
  uint8_t blue;
//  unsigned long aktmillis = millis();
  
// beim ersten Frame in der ersten loop die Corner LEDs löschen
  if (  ! akt_aniframe && ! akt_aniloop ) 
  {
     for (uint8_t cp = 0; cp <= 3; cp++) 
     {
       ledDriver.setPixelRGB(110 + cp,0,0,0);
     }  
     if ( myanimation.laufmode < 2 ) frame_fak = 1;
  }
  
  if ( akt_aniloop >= myanimation.loops ) 
  {
    akt_aniloop = 0;
    akt_aniframe = 0;
    frame_fak = 1;
    return false;
  }
  else
  {
#ifdef  DEBUG_ANIMATION
  Serial.println("Start Animation: " + String(myanimation.name) + " Loop: " +  String(akt_aniloop) + " Frame: " + String(akt_aniframe) );
#endif
    
    for ( uint8_t z = 0;z <= 9;z++)
    {
      for ( uint8_t x = 0;x <= 10;x++)
      {
        red = myanimation.frame[akt_aniframe].color[x][z].red * brightness * 0.0039;
        green = myanimation.frame[akt_aniframe].color[x][z].green * brightness * 0.0039;
        blue = myanimation.frame[akt_aniframe].color[x][z].blue * brightness * 0.0039;
        ledDriver.setPixelRGB(x, z, red, green, blue);
      }
    }
    ledDriver.show();
    handle_Webserver(__LINE__);
    if ( myanimation.frame[akt_aniframe].delay > 200 ) 
    {
      delay (myanimation.frame[akt_aniframe].delay / 2);
      handle_Webserver(__LINE__);
      delay (myanimation.frame[akt_aniframe].delay / 2);
    }
    else
    {
      delay (myanimation.frame[akt_aniframe].delay);
    }
    if ( myanimation.laufmode == 0 ) 
    {
      akt_aniframe++;
      if (  (myanimation.frame[akt_aniframe].delay == 0 || akt_aniframe > MAXFRAMES )) 
      {
         akt_aniframe = 0;
         akt_aniloop++;
      }
    }
    if ( myanimation.laufmode == 1 ) 
    { 
      akt_aniframe=akt_aniframe + frame_fak;
      if (myanimation.frame[akt_aniframe].delay == 0 || akt_aniframe > MAXFRAMES ) 
      {
         frame_fak = -1;
         akt_aniframe=akt_aniframe - 2;
         akt_aniloop++;
      }
      if (akt_aniframe == 0 ) {
         frame_fak = 1;
         akt_aniloop++;        
      }
    }
    if ( myanimation.laufmode == 2 ) 
    {    
      frame_fak++;
      for ( uint8_t i = 0;i <= 20;i++)
      {
         akt_aniframe = random(0,MAXFRAMES);
         if (myanimation.frame[akt_aniframe].delay != 0 ) break;
      } 
      if ( frame_fak == 20 ) 
      {
        frame_fak = 0;
        akt_aniloop++;
      }
    }  
    if ( mode == MODE_MAKEANIMATION ) // falls der Editor gestartet wurde den aktuellen Frame + Loop + Richtung nochmal zurücksetzen
    {
      akt_aniframe = 0;
      akt_aniloop = 0;
      frame_fak = 1;
    }
    screenBufferNeedsUpdate = true;
    return true;
  }
  
}
// Set Corner Pixel 
void setCornerPixel(uint32_t colornum_in)
{
  uint8_t red;
  uint8_t green; 
  uint8_t blue;
  red = num_to_color(colornum_in).red * brightness * 0.0039;
  green = num_to_color(colornum_in).green * brightness * 0.0039;
  blue = num_to_color(colornum_in).blue * brightness * 0.0039;
  for (uint8_t cp = 0; cp <= 3; cp++) 
  {
     ledDriver.setPixelRGB(110 + cp,red,green,blue);
  }    
  ledDriver.show();
}

// Zeige den aktuellen Frame während MakeAnimation an.
void showMakeAnimation(uint8_t brightness)
{
  uint8_t red;
  uint8_t green; 
  uint8_t blue;
#ifdef  DEBUG_ANIMATION
  Serial.println("Make Animation: " + String(myanimation.name) + " Frame: " + String(akt_aniframe) );
#endif
   for ( uint8_t z = 0;z <= 9;z++)
    {
      for ( uint8_t x = 0;x <= 10;x++)
      {
        red = myanimation.frame[akt_aniframe].color[x][z].red * brightness * 0.0039;
        green = myanimation.frame[akt_aniframe].color[x][z].green * brightness * 0.0039;
        blue = myanimation.frame[akt_aniframe].color[x][z].blue * brightness * 0.0039;
        ledDriver.setPixelRGB(x, z, red, green, blue);
      }
    }
    ledDriver.show();
    handle_Webserver(__LINE__);  
}


//Verarbeitung Animationsauswahl
void handleaniselect()
{
  if ( webServer.arg("value") != "BACK" ) // wenn wir vom Editor zurückkommen
  {
    animation = webServer.arg("value");
    animation.toUpperCase();
  }
#ifdef  DEBUG_ANIMATION
  else
  {
    Serial.println("BACK");
  }
#endif
  akt_aniframe = 0;
  akt_aniloop = 0;
  bool load = loadAnimation(animation);
  mode = MODE_SHOWANIMATION;
  screenBufferNeedsUpdate = true;
  webServer.send(200, "text/plain", "OK"); 
}

// Zurück zum Hauptmenü + MODE_TIME
void handlebacktoMODE_TIME()
{
  curControl = BTN_EXIT;
  setMode(MODE_TIME);
  callRoot();
}

// Starte Animationsmenü
void startAnimationsmenue()
{
  getAnimationList(); 
  animation = myanimationslist[0];
  akt_aniframe = 0;
  akt_aniloop = 0;
  frame_fak = 1;
  bool load = loadAnimation(animation);
  
#ifdef  DEBUG_ANIMATION
  Serial.println("Start Animationsmenue: " + animation + " Frame: " + String(akt_aniframe) );
#endif
  mode = MODE_SHOWANIMATION;
  screenBufferNeedsUpdate = true;
//  webServer.send(200, "text/html", makeAnimationmenue());
  makeAnimationmenue();
}

//Starte Animationseditor
void startmakeAnimation()
{
  akt_aniframe = 0;
  akt_aniloop = 0;
  frame_fak = 1;
  mode = MODE_MAKEANIMATION;
  screenBufferNeedsUpdate = true;
  webServer.send(200, "text/html", "<!doctype html><html><head><script>window.onload=function(){window.location.replace('/animation.html?animation=" + String(animation) +"');}</script></head></html>");
}

//Verarbeite Animationsoberfläche
void handlemakeAnimation()
{
  String webargname;
  String webargvalue;
  String typ;
  String wert;
  uint8_t palidx;
  uint8_t x,y;
  mode = MODE_MAKEANIMATION;
  if ( webServer.arg("_action") == "save" )
  {
  //  print_Animation();
    if ( saveAnimation(animation) )
    {
      webServer.send(200, "text/plain", animation);
    }
    else
    {
      webServer.send(200, "text/plain", "E");
    }
//    webServer.send(200, "text/html", "<!doctype html><html><head><script>window.onload=function(){window.location.replace('/animationmenue');}</script></head></html>");
  }
  else
  {
    for (int i = 0; i < webServer.args(); i++) 
    {
      webargname += webServer.argName(i);
      webargvalue += webServer.arg(i);
#ifdef DEBUG_ANIMATION
      Serial.println(" WebArg: " + webargname + " = " + webargvalue );
#endif      
      if ( webargname == "aniname" ) 
      {
        webargvalue.trim();
        webargvalue.replace(" ","_");
        webargvalue.toUpperCase();
        webargvalue.toCharArray(myanimation.name, webargvalue.length()+1);
        animation = webargvalue;
      }
      if ( webargname == "frame" ) akt_aniframe = webargvalue.toInt();
      if ( webargname == "loops" ) myanimation.loops = webargvalue.toInt();
      if ( webargname == "laufmode" ) myanimation.laufmode = webargvalue.toInt();
      if ( webargname == "aktivfarbe" ) 
      {
        wert = "#" + webargvalue;
        setCornerPixel(string_to_num(wert));
      }
      if ( webargname == "palette" )
      {
         typ = webargvalue.substring(0,webargvalue.indexOf(":"));
         wert = webargvalue.substring(webargvalue.indexOf(":")+1);
         wert = "#" + wert; 
         typ.replace("colorselect","");
//         Serial.println(typ + ":" + wert);
         palidx=typ.toInt();
//         Serial.printf("PALIDX: %i \n",palidx);
//         Serial.println(String(palidx) + " = " + wert );
         anipalette[palidx]=string_to_num(wert);
         setCornerPixel(string_to_num(wert));
//         Serial.printf ("anipalette %i = %i\n",palidx,anipalette[palidx]);
      }
      if ( webargname == "delay" )
      {
        myanimation.frame[akt_aniframe].delay = webargvalue.toInt();
      }
      if ( webargname == "pixel" )
      {
         typ = webargvalue.substring(0,webargvalue.indexOf(":"));
         wert = webargvalue.substring(webargvalue.indexOf(":")+1);
         wert = "#" + wert; 
         typ.replace("c_","");
         x = typ.substring(0,typ.indexOf("_")).toInt();
         y = typ.substring(typ.indexOf("_")+1).toInt();
         Serial.printf ("pixel x/y %i / %i = %s\n",x,y,wert.c_str());
         myanimation.frame[akt_aniframe].color[x][y] = string_to_color(wert);
       }
       if ( webargname == "copyframe" && akt_aniframe > 0 )
       {
         for ( uint8_t z = 0;z <= 9;z++)
         {
            for ( uint8_t x = 0;x <= 10;x++)
            {
              myanimation.frame[akt_aniframe].color[x][z].red = myanimation.frame[akt_aniframe-1].color[x][z].red;
              myanimation.frame[akt_aniframe].color[x][z].green = myanimation.frame[akt_aniframe-1].color[x][z].green;
              myanimation.frame[akt_aniframe].color[x][z].blue = myanimation.frame[akt_aniframe-1].color[x][z].blue;
            }
          }
        }
      }
    webServer.send(200, "text/plain", "OK");
    screenBufferNeedsUpdate = true;
    }
    delay(0);
}
