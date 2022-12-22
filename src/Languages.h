/******************************************************************************
Languages.h
******************************************************************************/

#ifndef LANGUAGES_H
#define LANGUAGES_H

//########################################################################################################################
// ENGLISCH
//########################################################################################################################

#if defined(FRONTCOVER_EN) || defined(FRONTCOVER_BINARY)
#define LANG_WORDCLOCK "word clock"

const char sWeekday[][2] PROGMEM =
{
	{ ' ', ' ' }, // 00
	{ 'S', 'U' }, // 01
	{ 'M', 'O' }, // 02
	{ 'T', 'U' }, // 03
	{ 'W', 'E' }, // 04
	{ 'T', 'H' }, // 05
	{ 'F', 'R' }, // 06
	{ 'S', 'A' }  // 07
};

// Wochentage für die Soundauswahl im Web
#define LANG_SUNDAY "Sunday"
#define LANG_MONDAY "Monday"
#define LANG_TUESDAY "Tuesday"
#define LANG_WEDNESDAY "Wednesday"
#define LANG_THURSDAY "Thursday"
#define LANG_FRIDAY "Friday"
#define LANG_SATURDAY "Saturday"

#define LANG_SUNDAY_SHORT "Su"
#define LANG_MONDAY_SHORT "Mo"
#define LANG_TUESDAY_SHORT "Tu"
#define LANG_WEDNESDAY_SHORT "We"
#define LANG_THURSDAY_SHORT "Th"
#define LANG_FRIDAY_SHORT "Fr"
#define LANG_SATURDAY_SHORT "Sa"
// Zeit
#define LANG_DAYS "Days"
#define LANG_HOURS "Hours"
#define LANG_HOUR "Hour"
#define LANG_MINUTES "Minutes"
#define LANG_MINUTE "Minute"
#define LANG_SECONDS "Seconds"
#define LANG_AM "a.m"
#define LANG_PM "p.m"
//Sonne
#define LANG_SUNRISE "Sunrise"
#define LANG_SUNSET "Sunset"
//Mondphase
#define LANG_NEWMOON "new moon"
#define LANG_FULLMOON "full moon"
#define LANG_INCREASINGMOON "waxing moon"
#define LANG_WANINGMOON "waning moon"
#define LANG_INDOOR "indoor"
#define LANG_OUTDOOR "outdoor"
//OpenWeather
#define LANG_OPENWAETHER_LANG "en"
#define LANG_OW_OK "Everything OK!!!"
#define LANG_OW_ERRTEMP "Temperature error!!"
#define LANG_OW_ERRHUM "Humidity error!!"
#define LANG_OW_ERRPRES "Air pressure error!!"
#define LANG_OW_ERRSUNRISE "No sunrise info!!"
#define LANG_OW_ERRSUNSET "No sunset info!!"
#define LANG_OW_ERRCONNECT "No Connect to Open Weather!!"
#define LANG_OW_ERRAPI "API-Key to short!!"

#define LANG_WINDSPEED "windspeed"
#define LANG_AIRPRESSUREHIST "Air pressure of the last hours: (tendency:"
#define LANG_TEMPHIST "Temperature history of the last 24 hours:"
//Settings
#define LANG_ALARM "Alarm"
#define LANG_TIMER "Timer"
#define LANG_CHIME "Hour chime"
#define LANG_VOLUME "Volume"
#define LANG_RANDOM "random"
#define LANG_LOUDER_ON_WEEKEND "louder 2 hours later on the weekend"
#define LANG_SINGLEGONG "Singlegong"
// Sound Web-Anzeigenamen in Settings:
#define AUDIO_WEBNAME0  "Sound 1"               // 0 s1
#define AUDIO_WEBNAME1  "Sound 2"               // 1 s2
#define AUDIO_WEBNAME2  "Sound 3"               // 2 s3
#define AUDIO_WEBNAME3  "Sound 4"               // 3 s4
#define AUDIO_WEBNAME4  "Cuckoo"                // 4 kuckuck
#define AUDIO_WEBNAME5  "Bing"                  // 5 bing
#define AUDIO_WEBNAME6  "Chirch"                // 6 kirche
#define AUDIO_WEBNAME7  "Westminster 1"         // 7 westminster 1
#define AUDIO_WEBNAME8  "Westminster 2"         // 8 westminster 2
#define AUDIO_WEBNAME9  "old Clock"             // 9 alte Uhr
#define AUDIO_WEBNAME10 "Ding"                  // 10 Ding
#define AUDIO_WEBNAME11 "Dog and Cat"           // 11 Hund und Katz
#define AUDIO_WEBNAME12 "Death"                 // 12 Tod
#define AUDIO_WEBNAME13 "Vicki"                 // 13 Vicki
#define AUDIO_WEBNAME14 "Hans"                  // 14 Hans
#define AUDIO_WEBNAME15 "Vicki/Hans"            // 15 Vicki/Hans
//
#define LANG_VICKYHANS_FORMAT "Hour announcement Vicki/Hans Format"
#define LANG_SPEAKER "Speaker"
#define LANG_DISPLAY "Display" 
#define LANG_TEMPERATURE "temperature" 
#define LANG_MOONPHASE "moonphase" 
#define LANG_WEATHER "weather" 
#define LANG_DATE "date"
#define LANG_EVERY "every"
#define LANG_SUNRISE_SUNSET "Announcement - <br>Sunrise:<br>Sunset"
#define LANG_AUTO_BRIGHTNESS "automatic brightness"
#define LANG_BRIGHTNESS "Brightness"
#define LANG_COLOURS "Colors"
#define LANG_COLOUR_00 "white"
#define LANG_COLOUR_01 "red"
#define LANG_COLOUR_02 "red 75%"
#define LANG_COLOUR_03 "red 50%"
#define LANG_COLOUR_04 "orange"
#define LANG_COLOUR_05 "yellow"
#define LANG_COLOUR_06 "yellow 75%"
#define LANG_COLOUR_07 "yellow 50%"
#define LANG_COLOUR_08 "green-yellow"
#define LANG_COLOUR_09 "green"
#define LANG_COLOUR_10 "green 75%"

#define LANG_COLOUR_11 "green 50%"
#define LANG_COLOUR_12 "mint green"
#define LANG_COLOUR_13 "cyan"
#define LANG_COLOUR_14 "cyan 75%"
#define LANG_COLOUR_15 "cyan 50%"
#define LANG_COLOUR_16 "slightly blue"
#define LANG_COLOUR_17 "blue"
#define LANG_COLOUR_18 "blue 75%"
#define LANG_COLOUR_19 "blue 50%"

#define LANG_COLOUR_20 "violet"
#define LANG_COLOUR_21 "magenta"
#define LANG_COLOUR_22 "magenta 75%"
#define LANG_COLOUR_23 "magenta 50%"
#define LANG_COLOUR_24 "pink"

#define LANG_MINUTE_COLOUR "Minutes LED color"
#define LANG_COLOUR_CHANGE "Color change"
#define LANG_MINUTE_COLOUR_CHANGE "Minutes color change"
#define LANG_LIKEMAIN "like main color"
#define LANG_DAILY "daily"
#define LANG_HOURLY "hourly"
#define LANG_BACKGROUNDCOLOUR "Background color"
#define LANG_OFF "off"
#define LANG_TIME "Time"
#define LANG_ALWAYS "always"
#define LANG_TRANSITIONS "Transitions"
#define LANG_SINGLE "single"
#define LANG_ALL "all"
#define LANG_TRANSITION_00 "normal"
#define LANG_TRANSITION_01 "sea of color"
#define LANG_TRANSITION_02 "up"
#define LANG_TRANSITION_03 "down"
#define LANG_TRANSITION_04 "left"
#define LANG_TRANSITION_05 "right"
#define LANG_TRANSITION_06 "down left"
#define LANG_TRANSITION_07 "down right"
#define LANG_TRANSITION_08 "to the Middle"
#define LANG_TRANSITION_09 "fade"
#define LANG_TRANSITION_10 "matrix"
#define LANG_TRANSITION_11 "spiral left"
#define LANG_TRANSITION_12 "spiral right"
#define LANG_TRANSITION_13 "line by line"
#define LANG_TRANSITION_14 "rainbow"
#define LANG_TRANSITION_15 "center left"
#define LANG_TRANSITION_16 "squares"
#define LANG_TRANSITION_17 "circles"

#define LANG_ONE_AFTER_ANOTHER "one after another"

#define LANG_NIGHT_OFF "off at night"
#define LANG_DAY_ON "on at day"

#define LANG_SHOWITIS "Show \"it is\""
#define LANG_SETDATETIME "Set Date/Time"
#define LANG_TIMEHOST "Time host"
#define LANG_SYSTEMNAME "System name"

#define LANG_LOCATION "Location"
#define LANG_ALTITUDE "Altitude"
#define LANG_LATITUDE "Latitude"
#define LANG_LONGITUDE "Longitude"

#define LANG_RESET_HIGHSCORE "Reset Highscores"

// Buttons
#define LANG_BACK "Back"
#define LANG_SAVE "Save"
#define LANG_SETTINGS "Settings"
#define LANG_ON "on"
#define LANG_ANIMATIONS "Animations"
#define LANG_EVENTS "Events"
#define LANG_MESSAGE "Send message"
#define LANG_GAMES "Games"
#define LANG_MODEBUTTON "Info"
#define LANG_TIMEBUTTON "Time"
#define LANG_CHANGEBUTTON "Change"

//Animationsmenü
#define LANG_ANIMATIONMENU "animation menu"

//Info
#define LANG_NETWORKWIFI "WiFi/Network"
#define LANG_WIFISIGNAL "signal strength"
#define LANG_WIFIQ1 "excellent"
#define LANG_WIFIQ2 "very good"
#define LANG_WIFIQ3 "good"
#define LANG_WIFIQ4 "acceptable"
#define LANG_WIFIQ5 "bad"
#define LANG_WIFIQ6 "very bad"
#define LANG_WIFIQ7 "insufficient"

#define LANG_WIFIRECON "WIFi reconnect per day"
#define LANG_IPADRESS "IP address"
#define LANG_RESETREASON "Reset Reason"
#define LANG_CLOCK "Clock"
#define LANG_LDR_VALUE "LDR-value"
#define LANG_HUMIDITY "humidity"
#define LANG_AIRPRESSURE "Air pressure"
#define LANG_AIRPRESSUREDIFF "Air pressure diff"
#define LANG_AIRPRESSURETHRES "threshold pressure"

#define LANG_OW_LASTUPDATE "Last Update"
#define LANG_INFOSUNSETRISE "Sunrise/Sunset"
#define LANG_MODECOUNT "ModeCount per day"
#define LANG_LASTTRANS "Last Trans"

#define LANG_SNAKE "Snake"
#define LANG_TETRIS "Tetris"
#define LANG_BRICKS "Bricks"
#define LANG_4GEWINNT "Connect four"
#define LANG_MEMORY1 "Animal memory"
#define LANG_MEMORY2 "Music memory"
#define LANG_MEMORY3 "ABBA memory"

#define LANG_HTMLLANG "en"
#define LANG_EXPLORER "Wordclock File Explorer"
#define LANG_FORMATCONF "Realy format? All Files are lost."
#define LANG_NOSPACE "No more Memory left"
#define LANG_FILESIZE "Filesize"
#define LANG_FOLDER "Foldername"
#define LANG_SURE "sure?"
#define LANG_CHAR_NOT_ALLOW "Character &#8220; % & / : ; \\ are not allowed."
#define LANG_FSUSED "used"
#define LANG_FSTOTAL "total"

#endif
//Ende FRONTCOVER_EN

//########################################################################################################################
// DEUTSCH
//########################################################################################################################

#if defined(FRONTCOVER_DE_DE) || defined(FRONTCOVER_DE_SW) || defined(FRONTCOVER_DE_BA) || defined(FRONTCOVER_DE_SA) || defined(FRONTCOVER_D3) || defined(FRONTCOVER_DE_MKF_DE) || defined(FRONTCOVER_DE_MKF_SW) || defined(FRONTCOVER_DE_MKF_BA) || defined(FRONTCOVER_DE_MKF_SA)
const char sWeekday[][2] PROGMEM =
{
	{ ' ', ' ' }, // 00
	{ 'S', 'O' }, // 01
	{ 'M', 'O' }, // 02
	{ 'D', 'I' }, // 03
	{ 'M', 'I' }, // 04
	{ 'D', 'O' }, // 05
	{ 'F', 'R' }, // 06
	{ 'S', 'A' }  // 07
};

#define LANG_WORDCLOCK "Wortuhr"
// Wochentage für die Soundauswahl im Web
#define LANG_SUNDAY "Sonntag"
#define LANG_MONDAY "Montag"
#define LANG_TUESDAY "Dienstag"
#define LANG_WEDNESDAY "Mittwoch"
#define LANG_THURSDAY "Donnerstag"
#define LANG_FRIDAY "Freitag"
#define LANG_SATURDAY "Samstag"

#define LANG_SUNDAY_SHORT "So"
#define LANG_MONDAY_SHORT "Mo"
#define LANG_TUESDAY_SHORT "Di"
#define LANG_WEDNESDAY_SHORT "Mi"
#define LANG_THURSDAY_SHORT "Do"
#define LANG_FRIDAY_SHORT "Fr"
#define LANG_SATURDAY_SHORT "Sa"
// Zeit
#define LANG_DAYS "Tage"
#define LANG_HOURS "Stunden"
#define LANG_HOUR "Stunde"
#define LANG_MINUTES "Minuten"
#define LANG_MINUTE "Minute"
#define LANG_SECONDS "Sekunden"
#define LANG_AM "Uhr"
#define LANG_PM "Uhr"
//Sonne
#define LANG_SUNRISE "Sonnenaufgang"
#define LANG_SUNSET "Sonnenuntergang"
//Mondphase
#define LANG_NEWMOON "Neumond"
#define LANG_FULLMOON "Vollmond"
#define LANG_INCREASINGMOON "zunehmend"
#define LANG_WANINGMOON "abnehmend"
#define LANG_INDOOR "drinnen"
#define LANG_OUTDOOR "drau&szlig;en"
//OpenWeather
#define LANG_OPENWAETHER_LANG "de"
#define LANG_OW_OK "Alles OK!!"
#define LANG_OW_ERRTEMP "Fehler bei Temperatur!!"
#define LANG_OW_ERRHUM "Fehler bei Luftfeuchte!!"
#define LANG_OW_ERRPRES "Fehler bei Luftdruck!!"
#define LANG_OW_ERRSUNRISE "Keine Sonnenaufgangsinfo!!"
#define LANG_OW_ERRSUNSET "Keine Sonnenuntergangsinfo!!"
#define LANG_OW_ERRCONNECT "Keine Connect zu Open Weather!!"
#define LANG_OW_ERRAPI "API-Key zu kurz!!"

#define LANG_WINDSPEED "Windgeschwindigkeit"
#define LANG_AIRPRESSUREHIST "Luftdruck der letzten Stunden: (Tendenz: "
#define LANG_TEMPHIST "Temperaturverlauf der letzten 24 Stunden:"
//Settings
#define LANG_ALARM "Alarm"
#define LANG_TIMER "Timer"
#define LANG_CHIME "Stundenschlag"
#define LANG_VOLUME "Lautst&auml;rke"
#define LANG_RANDOM "zuf&auml;llig"
#define LANG_LOUDER_ON_WEEKEND "am Wochenende 2h später lauter"
#define LANG_SINGLEGONG "Einfachgong"
// Sound Web-Anzeigenamen in Settings:
#define AUDIO_WEBNAME0  "Sound 1"               // 0 s1
#define AUDIO_WEBNAME1  "Sound 2"               // 1 s2
#define AUDIO_WEBNAME2  "Sound 3"               // 2 s3
#define AUDIO_WEBNAME3  "Sound 4"               // 3 s4
#define AUDIO_WEBNAME4  "Kuckuck"               // 4 kuckuck
#define AUDIO_WEBNAME5  "Bing"                  // 5 bing
#define AUDIO_WEBNAME6  "Kirche"                // 6 kirche
#define AUDIO_WEBNAME7  "Westminster 1"         // 7 westminster 1
#define AUDIO_WEBNAME8  "Westminster 2"         // 8 westminster 2
#define AUDIO_WEBNAME9  "alte Uhr"              // 9 alte Uhr
#define AUDIO_WEBNAME10 "Ding"                  // 10 Ding
#define AUDIO_WEBNAME11 "Hund und Katz"         // 11 Hund und Katz
#define AUDIO_WEBNAME12 "Tod"                   // 12 Tod
#define AUDIO_WEBNAME13 "Vicki"                 // 13 Vicki
#define AUDIO_WEBNAME14 "Hans"                  // 14 Hans
#define AUDIO_WEBNAME15 "Vicki/Hans"            // 15 Vicki/Hans
//
#define LANG_VICKYHANS_FORMAT "Stundenansage Vicki/Hans Format"
#define LANG_SPEAKER "Sprecher"
#define LANG_DISPLAY "Anzeige" 
#define LANG_TEMPERATURE "Temperatur" 
#define LANG_MOONPHASE "Mondphase" 
#define LANG_WEATHER "Wetter" 
#define LANG_DATE "Datum"
#define LANG_EVERY "alle"
#define LANG_SUNRISE_SUNSET "Ank&uuml;ndigung - <br>Sonnenaufgang:<br>Sonnenuntergang"
#define LANG_AUTO_BRIGHTNESS "autom. Helligkeit"
#define LANG_BRIGHTNESS "Helligkeit"
#define LANG_COLOURS "Farben"
#define LANG_COLOUR_00 "Weiss"
#define LANG_COLOUR_01 "Rot"
#define LANG_COLOUR_02 "Rot 75%"
#define LANG_COLOUR_03 "Rot 50%"
#define LANG_COLOUR_04 "Orange"
#define LANG_COLOUR_05 "Gelb"
#define LANG_COLOUR_06 "Gelb 75%"
#define LANG_COLOUR_07 "Gelb 50%"
#define LANG_COLOUR_08 "Gr&uuml;n-Gelb"
#define LANG_COLOUR_09 "Gr&uuml;n"
#define LANG_COLOUR_10 "Gr&uuml;n 75%"

#define LANG_COLOUR_11 "Gr&uuml;n 50%"
#define LANG_COLOUR_12 "Mintgr&uuml;n"
#define LANG_COLOUR_13 "Cyan"
#define LANG_COLOUR_14 "Cyan 75%"
#define LANG_COLOUR_15 "Cyan 50%"
#define LANG_COLOUR_16 "Leicht Blau"
#define LANG_COLOUR_17 "Blau"
#define LANG_COLOUR_18 "Blau 75%"
#define LANG_COLOUR_19 "Blau 50%"

#define LANG_COLOUR_20 "Violet"
#define LANG_COLOUR_21 "Magenta"
#define LANG_COLOUR_22 "Magenta 75%"
#define LANG_COLOUR_23 "Magenta 50%"
#define LANG_COLOUR_24 "Pink"

#define LANG_MINUTE_COLOUR "Minuten LED Farbe"
#define LANG_COLOUR_CHANGE "Farbenwechsel"
#define LANG_MINUTE_COLOUR_CHANGE "Minuten Farbenwechsel"
#define LANG_LIKEMAIN "wie Hauptfarbe"
#define LANG_DAILY "tgl."
#define LANG_HOURLY "stdl."
#define LANG_BACKGROUNDCOLOUR "Hintergrundfarbe"
#define LANG_OFF "aus"
#define LANG_TIME "Zeit"
#define LANG_ALWAYS "immer"
#define LANG_TRANSITIONS "&Uuml;berg&auml;nge"
#define LANG_SINGLE "einzeln"
#define LANG_ALL "alle"
#define LANG_TRANSITION_00 "normal"
#define LANG_TRANSITION_01 "Farbenmeer"
#define LANG_TRANSITION_02 "hoch"
#define LANG_TRANSITION_03 "runter"
#define LANG_TRANSITION_04 "links"
#define LANG_TRANSITION_05 "rechts"
#define LANG_TRANSITION_06 "linksrunter"
#define LANG_TRANSITION_07 "rechtsrunter"
#define LANG_TRANSITION_08 "zur Mitte"
#define LANG_TRANSITION_09 "fade"
#define LANG_TRANSITION_10 "Matrix"
#define LANG_TRANSITION_11 "Spirale links"
#define LANG_TRANSITION_12 "Spirale rechts"
#define LANG_TRANSITION_13 "zeilenweise"
#define LANG_TRANSITION_14 "Regenbogen"
#define LANG_TRANSITION_15 "Mitte linksherum"
#define LANG_TRANSITION_16 "Quadrate"
#define LANG_TRANSITION_17 "Kreise"

#define LANG_ONE_AFTER_ANOTHER "nacheinander"

#define LANG_NIGHT_OFF "Nachts aus ab"
#define LANG_DAY_ON "Tags an ab"

#define LANG_SHOWITIS "Zeige \"es ist\""
#define LANG_SETDATETIME "Setze Datum/Zeit"
#define LANG_TIMEHOST "Zeitserver"
#define LANG_SYSTEMNAME "Systemname"

#define LANG_LOCATION "Location"
#define LANG_ALTITUDE "H&ouml;he Standort"
#define LANG_LATITUDE "Latitude"
#define LANG_LONGITUDE "Longitude"

#define LANG_RESET_HIGHSCORE "Reset Highscores"

// Buttons
#define LANG_BACK "zur&uuml;ck"
#define LANG_SAVE "speichern"
#define LANG_SETTINGS "Einstellungen"
#define LANG_ON "ein"
#define LANG_ANIMATIONS "Animationen"
#define LANG_EVENTS "Events"
#define LANG_MESSAGE "Nachricht senden"
#define LANG_GAMES "Spiele"
#define LANG_MODEBUTTON "Infoanzeige"
#define LANG_TIMEBUTTON "Zeitanzeige"
#define LANG_CHANGEBUTTON "&auml;ndern"

//Animationsmenü
#define LANG_ANIMATIONMENU "Animationsmen&uuml;"

//Info
#define LANG_NETWORKWIFI "WiFi/Netzwerk"
#define LANG_WIFISIGNAL "Signalst&auml;rke"
#define LANG_WIFIQ1 "ausgezeichnet"
#define LANG_WIFIQ2 "sehr gut"
#define LANG_WIFIQ3 "gut"
#define LANG_WIFIQ4 "akzeptabel"
#define LANG_WIFIQ5 "schlecht"
#define LANG_WIFIQ6 "sehr schlecht"
#define LANG_WIFIQ7 "ungen&uumlgend"

#define LANG_WIFIRECON "WLAN Reconnect pro Tag"
#define LANG_IPADRESS "IP-Adresse"
#define LANG_RESETREASON "Reset Grund"
#define LANG_CLOCK "Uhr"
#define LANG_LDR_VALUE "LDR-Wert"
#define LANG_HUMIDITY "Luftfeuchte"
#define LANG_AIRPRESSURE "Luftdruck"
#define LANG_AIRPRESSUREDIFF "Luftdruckdiff"
#define LANG_AIRPRESSURETHRES "Druckschwellen"

#define LANG_OW_LASTUPDATE "Letzter Update"
#define LANG_INFOSUNSETRISE "Sonnenauf/untergang"
#define LANG_MODECOUNT "ModeCount pro Tag"
#define LANG_LASTTRANS "Letzte Trans"

#define LANG_SNAKE "Snake"
#define LANG_TETRIS "Tetris"
#define LANG_BRICKS "Bricks"
#define LANG_4GEWINNT "4 gewinnt"
#define LANG_MEMORY1 "Tiermemory"
#define LANG_MEMORY2 "Musikmemory"
#define LANG_MEMORY3 "ABBAmemory"

#define LANG_HTMLLANG "de"
#define LANG_EXPLORER "Wortuhr Datei Manager"
#define LANG_FORMATCONF "Wirklich formatieren? Alle Daten gehen verloren."
#define LANG_NOSPACE "Ungenügend Speicher frei"
#define LANG_FILESIZE "Dateigröße"
#define LANG_FOLDER "Ordner Name"
#define LANG_SURE "sicher?"
#define LANG_CHAR_NOT_ALLOW "Zeichen &#8220; % & / : ; \\ sind nicht erlaubt."
#define LANG_FSUSED "belegt"
#define LANG_FSTOTAL "gesamt"

#endif
//Ende FRONTCOVER_DE

//########################################################################################################################
// SCHWEIZ
//########################################################################################################################

#if defined(FRONTCOVER_CH)
#define LANG_WORDCLOCK "Wortuhr"
const char sWeekday[][2] PROGMEM =
{
  { ' ', ' ' }, // 00
  { 'S', 'O' }, // 01
  { 'M', 'O' }, // 02
  { 'D', 'I' }, // 03
  { 'M', 'I' }, // 04
  { 'D', 'O' }, // 05
  { 'F', 'R' }, // 06
  { 'S', 'A' }  // 07
};

// Wochentage für die Soundauswahl im Web
#define LANG_SUNDAY "Sonntag"
#define LANG_MONDAY "Montag"
#define LANG_TUESDAY "Dienstag"
#define LANG_WEDNESDAY "Mittwoch"
#define LANG_THURSDAY "Donnerstag"
#define LANG_FRIDAY "Freitag"
#define LANG_SATURDAY "Samstag"

#define LANG_SUNDAY_SHORT "So"
#define LANG_MONDAY_SHORT "Mo"
#define LANG_TUESDAY_SHORT "Di"
#define LANG_WEDNESDAY_SHORT "Mi"
#define LANG_THURSDAY_SHORT "Do"
#define LANG_FRIDAY_SHORT "Fr"
#define LANG_SATURDAY_SHORT "Sa"
// Zeit
#define LANG_DAYS "Tage"
#define LANG_HOURS "Stunden"
#define LANG_HOUR "Stunde"
#define LANG_MINUTES "Minuten"
#define LANG_MINUTE "Minute"
#define LANG_SECONDS "Sekunden"
#define LANG_AM "Uhr"
#define LANG_PM "Uhr"
//Sonne
#define LANG_SUNRISE "Sonnenaufgang"
#define LANG_SUNSET "Sonnenuntergang"
//Mondphase
#define LANG_NEWMOON "Neumond"
#define LANG_FULLMOON "Vollmond"
#define LANG_INCREASINGMOON "zunehmend"
#define LANG_WANINGMOON "abnehmend"
#define LANG_INDOOR "drinnen"
#define LANG_OUTDOOR "draussen"
//OpenWeather
#define LANG_OPENWAETHER_LANG "de"
#define LANG_OW_OK "Alles OK!!"
#define LANG_OW_ERRTEMP "Fehler bei Temperatur!!"
#define LANG_OW_ERRHUM "Fehler bei Luftfeuchte!!"
#define LANG_OW_ERRPRES "Fehler bei Luftdruck!!"
#define LANG_OW_ERRSUNRISE "Keine Sonnenaufgangsinfo!!"
#define LANG_OW_ERRSUNSET "Keine Sonnenuntergangsinfo!!"
#define LANG_OW_ERRCONNECT "Keine Connect zu Open Weather!!"
#define LANG_OW_ERRAPI "API-Key zu kurz!!"

#define LANG_WINDSPEED "Windgeschwindigkeit"
#define LANG_AIRPRESSUREHIST "Luftdruck der letzten Stunden: (Tendenz: "
#define LANG_TEMPHIST "Temperaturverlauf der letzten 24 Stunden:"
//Settings
#define LANG_ALARM "Alarm"
#define LANG_TIMER "Timer"
#define LANG_CHIME "Stundenschlag"
#define LANG_VOLUME "Lautst&auml;rke"
#define LANG_RANDOM "zuf&auml;llig"
#define LANG_LOUDER_ON_WEEKEND "am Wochenende 2h später lauter"
#define LANG_SINGLEGONG "Einfachgong"
// Sound Web-Anzeigenamen in Settings:
#define AUDIO_WEBNAME0  "Pendule"               // 0 s1
#define AUDIO_WEBNAME1  "Gong"               // 1 s2
#define AUDIO_WEBNAME2  "Glogge"               // 2 s3
#define AUDIO_WEBNAME3  "Glöggli"               // 3 s4
#define AUDIO_WEBNAME4  "Kuckuck"               // 4 kuckuck
#define AUDIO_WEBNAME5  "Bing"                  // 5 bing
#define AUDIO_WEBNAME6  "Chile"                // 6 kirche
#define AUDIO_WEBNAME7  "Westminster 1"         // 7 westminster 1
#define AUDIO_WEBNAME8  "Westminster 2"         // 8 westminster 2
#define AUDIO_WEBNAME9  "Regulator"              // 9 alte Uhr
#define AUDIO_WEBNAME10 "Ding"                  // 10 Ding
#define AUDIO_WEBNAME11 "Hond ond Chatz"         // 11 Hund und Katz
#define AUDIO_WEBNAME12 "Tod"                   // 12 Tod
#define AUDIO_WEBNAME13 "Vicki"                 // 13 Vicki
#define AUDIO_WEBNAME14 "Hans"                  // 14 Hans
#define AUDIO_WEBNAME15 "Vicki/Hans"            // 15 Vicki/Hans
//
#define LANG_VICKYHANS_FORMAT "Stundenansage Vicki/Hans Format"
#define LANG_SPEAKER "Sprecher"
#define LANG_DISPLAY "Anzeige" 
#define LANG_TEMPERATURE "Temperatur" 
#define LANG_MOONPHASE "Mondphase" 
#define LANG_WEATHER "Wetter" 
#define LANG_DATE "Datum"
#define LANG_EVERY "alle"
#define LANG_SUNRISE_SUNSET "Ank&uuml;ndigung - <br>Sonnenaufgang:<br>Sonnenuntergang"
#define LANG_AUTO_BRIGHTNESS "autom. Helligkeit"
#define LANG_BRIGHTNESS "Helligkeit"
#define LANG_COLOURS "Farben"
#define LANG_COLOUR_00 "Weiss"
#define LANG_COLOUR_01 "Rot"
#define LANG_COLOUR_02 "Rot 75%"
#define LANG_COLOUR_03 "Rot 50%"
#define LANG_COLOUR_04 "Orange"
#define LANG_COLOUR_05 "Gelb"
#define LANG_COLOUR_06 "Gelb 75%"
#define LANG_COLOUR_07 "Gelb 50%"
#define LANG_COLOUR_08 "Gr&uuml;n-Gelb"
#define LANG_COLOUR_09 "Gr&uuml;n"
#define LANG_COLOUR_10 "Gr&uuml;n 75%"

#define LANG_COLOUR_11 "Gr&uuml;n 50%"
#define LANG_COLOUR_12 "Mintgr&uuml;n"
#define LANG_COLOUR_13 "Cyan"
#define LANG_COLOUR_14 "Cyan 75%"
#define LANG_COLOUR_15 "Cyan 50%"
#define LANG_COLOUR_16 "Leicht Blau"
#define LANG_COLOUR_17 "Blau"
#define LANG_COLOUR_18 "Blau 75%"
#define LANG_COLOUR_19 "Blau 50%"

#define LANG_COLOUR_20 "Violet"
#define LANG_COLOUR_21 "Magenta"
#define LANG_COLOUR_22 "Magenta 75%"
#define LANG_COLOUR_23 "Magenta 50%"
#define LANG_COLOUR_24 "Pink"

#define LANG_MINUTE_COLOUR "Minuten LED Farbe"
#define LANG_COLOUR_CHANGE "Farbenwechsel"
#define LANG_MINUTE_COLOUR_CHANGE "Minuten Farbenwechsel"
#define LANG_LIKEMAIN "wie Hauptfarbe"
#define LANG_DAILY "tgl."
#define LANG_HOURLY "stdl."
#define LANG_BACKGROUNDCOLOUR "Hintergrundfarbe"
#define LANG_OFF "aus"
#define LANG_TIME "Zeit"
#define LANG_ALWAYS "immer"
#define LANG_TRANSITIONS "&Uuml;berg&auml;nge"
#define LANG_SINGLE "einzeln"
#define LANG_ALL "alle"
#define LANG_TRANSITION_00 "normal"
#define LANG_TRANSITION_01 "Farbenmeer"
#define LANG_TRANSITION_02 "hoch"
#define LANG_TRANSITION_03 "runter"
#define LANG_TRANSITION_04 "links"
#define LANG_TRANSITION_05 "rechts"
#define LANG_TRANSITION_06 "linksrunter"
#define LANG_TRANSITION_07 "rechtsrunter"
#define LANG_TRANSITION_08 "zur Mitte"
#define LANG_TRANSITION_09 "fade"
#define LANG_TRANSITION_10 "Matrix"
#define LANG_TRANSITION_11 "Spirale links"
#define LANG_TRANSITION_12 "Spirale rechts"
#define LANG_TRANSITION_13 "zeilenweise"
#define LANG_TRANSITION_14 "Regenbogen"
#define LANG_TRANSITION_15 "Mitte linksherum"
#define LANG_TRANSITION_16 "Quadrate"
#define LANG_TRANSITION_17 "Kreise"

#define LANG_ONE_AFTER_ANOTHER "nacheinander"

#define LANG_NIGHT_OFF "Nachts aus ab"
#define LANG_DAY_ON "Tags an ab"

#define LANG_SHOWITIS "Zeige \"es ist\" und \"gsi\""
#define LANG_SETDATETIME "Setze Datum/Zeit"
#define LANG_TIMEHOST "Zeitserver"
#define LANG_SYSTEMNAME "Systemname"

#define LANG_LOCATION "Location"
#define LANG_ALTITUDE "H&ouml;he Standort"
#define LANG_LATITUDE "Latitude"
#define LANG_LONGITUDE "Longitude"

#define LANG_RESET_HIGHSCORE "Reset Highscores"

// Buttons
#define LANG_BACK "zur&uuml;ck"
#define LANG_SAVE "speichern"
#define LANG_SETTINGS "Einstellungen"
#define LANG_ON "ein"
#define LANG_ANIMATIONS "Animationen"
#define LANG_EVENTS "Events"
#define LANG_MESSAGE "Nachricht senden"
#define LANG_GAMES "Spiele"
#define LANG_MODEBUTTON "Infoanzeige"
#define LANG_TIMEBUTTON "Zeitanzeige"
#define LANG_CHANGEBUTTON "&auml;ndern"

//Animationsmenü
#define LANG_ANIMATIONMENU "Animationsmen&uuml;"

//Info
#define LANG_NETWORKWIFI "WiFi/Netzwerk"
#define LANG_WIFISIGNAL "Signalst&auml;rke"
#define LANG_WIFIQ1 "ausgezeichnet"
#define LANG_WIFIQ2 "sehr gut"
#define LANG_WIFIQ3 "gut"
#define LANG_WIFIQ4 "akzeptabel"
#define LANG_WIFIQ5 "schlecht"
#define LANG_WIFIQ6 "sehr schlecht"
#define LANG_WIFIQ7 "ungen&uumlgend"

#define LANG_WIFIRECON "WLAN Reconnect pro Tag"
#define LANG_IPADRESS "IP-Adresse"
#define LANG_RESETREASON "Reset Grund"
#define LANG_CLOCK "Uhr"
#define LANG_LDR_VALUE "LDR-Wert"
#define LANG_HUMIDITY "Luftfeuchte"
#define LANG_AIRPRESSURE "Luftdruck"
#define LANG_AIRPRESSUREDIFF "Luftdruckdiff"
#define LANG_AIRPRESSURETHRES "Druckschwellen"

#define LANG_OW_LASTUPDATE "Letzter Update"
#define LANG_INFOSUNSETRISE "Sonnenauf/untergang"
#define LANG_MODECOUNT "ModeCount pro Tag"
#define LANG_LASTTRANS "Letzte Trans"

#define LANG_SNAKE "Snake"
#define LANG_TETRIS "Tetris"
#define LANG_BRICKS "Bricks"
#define LANG_4GEWINNT "4 gewinnt"
#define LANG_MEMORY1 "Tiermemory"
#define LANG_MEMORY2 "Musikmemory"
#define LANG_MEMORY3 "ABBAmemory"

#define LANG_HTMLLANG "de"
#define LANG_EXPLORER "Wortuhr Datei Manager"
#define LANG_FORMATCONF "Wirklich formatieren? Alle Daten gehen verloren."
#define LANG_NOSPACE "Ungenügend Speicher frei"
#define LANG_FILESIZE "Dateigröße"
#define LANG_FOLDER "Ordner Name"
#define LANG_SURE "sicher?"
#define LANG_CHAR_NOT_ALLOW "Zeichen &#8220; % & / : ; \\ sind nicht erlaubt."
#define LANG_FSUSED "belegt"
#define LANG_FSTOTAL "gesamt"

#endif
//Ende FRONTCOVER_CH

//########################################################################################################################
// SCHWEIZ AARGAU
//########################################################################################################################

#if defined(FRONTCOVER_CH_AG) || defined(FRONTCOVER_CH_AL)
#define LANG_WORDCLOCK "Wortuhr"
const char sWeekday[][2] PROGMEM =
{
  { ' ', ' ' }, // 00
  { 'S', 'O' }, // 01
  { 'M', 'O' }, // 02
  { 'D', 'I' }, // 03
  { 'M', 'I' }, // 04
  { 'D', 'O' }, // 05
  { 'F', 'R' }, // 06
  { 'S', 'A' }  // 07
};

// Wochentage für die Soundauswahl im Web
#define LANG_SUNDAY "Sondig"
#define LANG_MONDAY "Meendig"
#define LANG_TUESDAY "Ziischtig"
#define LANG_WEDNESDAY "Mettwoch"
#define LANG_THURSDAY "Donnschtig"
#define LANG_FRIDAY "Friitig"
#define LANG_SATURDAY "Samschtig"

#define LANG_SUNDAY_SHORT "So"
#define LANG_MONDAY_SHORT "Mo"
#define LANG_TUESDAY_SHORT "Di"
#define LANG_WEDNESDAY_SHORT "Mi"
#define LANG_THURSDAY_SHORT "Do"
#define LANG_FRIDAY_SHORT "Fr"
#define LANG_SATURDAY_SHORT "Sa"
// Zeit
#define LANG_DAYS "Tage"
#define LANG_HOURS "Stunden"
#define LANG_HOUR "Stunde"
#define LANG_MINUTES "Minute"
#define LANG_MINUTE "Minute"
#define LANG_SECONDS "Sekunden"
#define LANG_AM " "
#define LANG_PM " "
//Sonne
#define LANG_SUNRISE "Sonneufgang"
#define LANG_SUNSET "Sonneundergang"
//Mondphase
#define LANG_NEWMOON "Neumoon"
#define LANG_FULLMOON "Vollmoon"
#define LANG_INCREASINGMOON "zunämend"
#define LANG_WANINGMOON "abnämend"
#define LANG_INDOOR "denne"
#define LANG_OUTDOOR "dosse"
//OpenWeather
#define LANG_OPENWAETHER_LANG "de"
#define LANG_OW_OK "Alles OK!!"
#define LANG_OW_ERRTEMP "Fehler bei Temperatur!!"
#define LANG_OW_ERRHUM "Fehler bei Luftfeuchte!!"
#define LANG_OW_ERRPRES "Fehler bei Luftdruck!!"
#define LANG_OW_ERRSUNRISE "Keine Sonnenaufgangsinfo!!"
#define LANG_OW_ERRSUNSET "Keine Sonnenuntergangsinfo!!"
#define LANG_OW_ERRCONNECT "Keine Connect zu Open Weather!!"
#define LANG_OW_ERRAPI "API-Key zu kurz!!"

#define LANG_WINDSPEED "Wendgeschwendigkeit"
#define LANG_AIRPRESSUREHIST "Loftdrock vo de letschte Schtonde: (Tendänz: "
#define LANG_TEMPHIST "Tämperaturverlauf i de letschte 24 Schtond"
//Settings
#define LANG_ALARM "Alarm"
#define LANG_TIMER "Timer"
#define LANG_CHIME "Schtondeschlag"
#define LANG_VOLUME "Luutscht&auml;rchi"
#define LANG_RANDOM "zuef&auml;llig"
#define LANG_LOUDER_ON_WEEKEND "am Wocheänd 2h schpöter lüüter"
#define LANG_SINGLEGONG "Eifachgong"
// Sound Web-Anzeigenamen in Settings:
#define AUDIO_WEBNAME0  "Pendule"               // 0  Pendule
#define AUDIO_WEBNAME1  "Gong"                  // 1  Gong
#define AUDIO_WEBNAME2  "Glogge"                // 2  Glocke
#define AUDIO_WEBNAME3  "Glöggli"             // 3  Glöckchen
#define AUDIO_WEBNAME4  "Kuckuck"               // 4  Kuckuck
#define AUDIO_WEBNAME5  "Bing"                  // 5  Bing
#define AUDIO_WEBNAME6  "Chile"                // 6  Kirche
#define AUDIO_WEBNAME7  "Westminster 1"         // 7  Westminster 1
#define AUDIO_WEBNAME8  "Westminster 2"         // 8  Westminster 2
#define AUDIO_WEBNAME9  "Regulator"             // 9  alte Uhr
#define AUDIO_WEBNAME10 "Ding"                  // 10 Ding
#define AUDIO_WEBNAME11 "Hond ond Chatz"        // 11 Hund und Katz
#define AUDIO_WEBNAME12 "Tod"                   // 12 Tod
#define AUDIO_WEBNAME13 "Vicki"                 // 13 Vicki
#define AUDIO_WEBNAME14 "Hans"                  // 14 Hans
#define AUDIO_WEBNAME15 "Vicki/Hans"            // 15 Vicki/Hans
//
#define LANG_VICKYHANS_FORMAT "Schtondeasag Vicki oder Hans"
#define LANG_SPEAKER "Schprächer"
#define LANG_DISPLAY "Azeig" 
#define LANG_TEMPERATURE "Tämperatur" 
#define LANG_MOONPHASE "Moonphase" 
#define LANG_WEATHER "Wätter" 
#define LANG_DATE "Datum"
#define LANG_EVERY "alli "
#define LANG_SUNRISE_SUNSET "Ak&ouml;ndig <br>Sonneufgang:<br>Sonneundergang"
#define LANG_AUTO_BRIGHTNESS "autom. Helligkeit"
#define LANG_BRIGHTNESS "Helligkeit"
#define LANG_COLOURS "Farbe"
#define LANG_COLOUR_00 "Wiiss"
#define LANG_COLOUR_01 "Rot"
#define LANG_COLOUR_02 "Rot 75%"
#define LANG_COLOUR_03 "Rot 50%"
#define LANG_COLOUR_04 "Orange"
#define LANG_COLOUR_05 "Gääl"
#define LANG_COLOUR_06 "Gääl 75%"
#define LANG_COLOUR_07 "Gääl 50%"
#define LANG_COLOUR_08 "Gr&uuml;en-Gääl"
#define LANG_COLOUR_09 "Gr&uuml;en"
#define LANG_COLOUR_10 "Gr&uuml;en 75%"

#define LANG_COLOUR_11 "Gr&uuml;en 50%"
#define LANG_COLOUR_12 "Mintgr&uuml;en"
#define LANG_COLOUR_13 "Cyan"
#define LANG_COLOUR_14 "Cyan 75%"
#define LANG_COLOUR_15 "Cyan 50%"
#define LANG_COLOUR_16 "Liecht Blau"
#define LANG_COLOUR_17 "Blau"
#define LANG_COLOUR_18 "Blau 75%"
#define LANG_COLOUR_19 "Blau 50%"

#define LANG_COLOUR_20 "Violet"
#define LANG_COLOUR_21 "Magenta"
#define LANG_COLOUR_22 "Magenta 75%"
#define LANG_COLOUR_23 "Magenta 50%"
#define LANG_COLOUR_24 "Pink"

#define LANG_MINUTE_COLOUR "Minute LED Farb"
#define LANG_COLOUR_CHANGE "Farbwächsel"
#define LANG_MINUTE_COLOUR_CHANGE "Minute Farbwächsel"
#define LANG_LIKEMAIN "wie dHauptfarb"
#define LANG_DAILY "tgl."
#define LANG_HOURLY "stdl."
#define LANG_BACKGROUNDCOLOUR "Hindergrundfarb"
#define LANG_OFF "uus"
#define LANG_TIME "Ziit"
#define LANG_ALWAYS "emmer"
#define LANG_TRANSITIONS "&Ouml;berg&auml;ng"
#define LANG_SINGLE "einzel"
#define LANG_ALL "alli"
#define LANG_TRANSITION_00 "normal"
#define LANG_TRANSITION_01 "Farbemeer"
#define LANG_TRANSITION_02 "ue"
#define LANG_TRANSITION_03 "abe"
#define LANG_TRANSITION_04 "links"
#define LANG_TRANSITION_05 "rechts"
#define LANG_TRANSITION_06 "linksabe"
#define LANG_TRANSITION_07 "rechtsabe"
#define LANG_TRANSITION_08 "zo de Metti"
#define LANG_TRANSITION_09 "uusblände"
#define LANG_TRANSITION_10 "Matrix"
#define LANG_TRANSITION_11 "Schpirale links"
#define LANG_TRANSITION_12 "Schpirale rechts"
#define LANG_TRANSITION_13 "zielewiis"
#define LANG_TRANSITION_14 "Rägenboge"
#define LANG_TRANSITION_15 "Metti linksome"
#define LANG_TRANSITION_16 "Quadrate"
#define LANG_TRANSITION_17 "Chreis"

#define LANG_ONE_AFTER_ANOTHER "nachenand"

#define LANG_NIGHT_OFF "zNacht us ab"
#define LANG_DAY_ON "Tagsöber a ab"

#define LANG_SHOWITIS "Zeig \"es esch\" ond \"gsi\""
#define LANG_SETDATETIME "Datom ond Ziit ischtelle"
#define LANG_TIMEHOST "Ziitserver"
#define LANG_SYSTEMNAME "Name vo de Uhr"

#define LANG_LOCATION "Schtandort"
#define LANG_ALTITUDE "H&ouml;chi Schtandort"
#define LANG_LATITUDE "Breitegrad"
#define LANG_LONGITUDE "Längegrad"

#define LANG_RESET_HIGHSCORE "Zroggsetze Highscores"

// Buttons
#define LANG_BACK "zurück"
#define LANG_SAVE "speichern"
#define LANG_SETTINGS "Ischtellige"
#define LANG_ON "i"
#define LANG_ANIMATIONS "Animatione"
#define LANG_EVENTS "Ereignis"
#define LANG_MESSAGE "Nochricht sände"
#define LANG_GAMES "Schpeli"
#define LANG_MODEBUTTON "Infoazeig"
#define LANG_TIMEBUTTON "Ziitazeig"
#define LANG_CHANGEBUTTON "&auml;ndere"

//Animationsmenü
#define LANG_ANIMATIONMENU "Animationsmen&uuml;"

//Info
#define LANG_NETWORKWIFI "WiFi/Netzwerk"
#define LANG_WIFISIGNAL "Signalst&auml;rke"
#define LANG_WIFIQ1 "ausgezeichnet"
#define LANG_WIFIQ2 "sehr gut"
#define LANG_WIFIQ3 "gut"
#define LANG_WIFIQ4 "akzeptabel"
#define LANG_WIFIQ5 "schlecht"
#define LANG_WIFIQ6 "sehr schlecht"
#define LANG_WIFIQ7 "ungen&uuml;gend"

#define LANG_WIFIRECON "WLAN Neuverbindungen pro Tag"
#define LANG_IPADRESS "IP-Adresse"
#define LANG_RESETREASON "Reset Grund"
#define LANG_CLOCK "Uhr"
#define LANG_LDR_VALUE "LDR-Wert"
#define LANG_HUMIDITY "Luftfeuchtigkeit"
#define LANG_AIRPRESSURE "Luftdruck"
#define LANG_AIRPRESSUREDIFF "Luftdruckdifferenz"
#define LANG_AIRPRESSURETHRES "Druckschwelle"

#define LANG_OW_LASTUPDATE "Letztes Update"
#define LANG_INFOSUNSETRISE "Sonnenauf-/untergang"
#define LANG_MODECOUNT "Mode Wechsel pro Tag"
#define LANG_LASTTRANS "Letzte Transition"

#define LANG_SNAKE "Snake"
#define LANG_TETRIS "Tetris"
#define LANG_BRICKS "Bricks"
#define LANG_4GEWINNT "4 gewinnt"
#define LANG_MEMORY1 "Tier Memory"
#define LANG_MEMORY2 "Musik Memory"
#define LANG_MEMORY3 "ABBA Memory"

#define LANG_HTMLLANG "de"
#define LANG_EXPLORER "Wortuhr Datei Manager"
#define LANG_FORMATCONF "Wirklich formatieren? Alle Daten gehen verloren."
#define LANG_NOSPACE "Ungenügend Speicher frei"
#define LANG_FILESIZE "Dateigrösse"
#define LANG_FOLDER "Ordner Name"
#define LANG_SURE "sicher?"
#define LANG_CHAR_NOT_ALLOW "Zeichen &#8220; % & / : ; \\ sind nicht erlaubt."
#define LANG_FSUSED "belegt"
#define LANG_FSTOTAL "gesamt"

#endif
//Ende FRONTCOVER_CH_AG FRONTCOVER_CH_AL


//########################################################################################################################
// SPANISCH
//########################################################################################################################

#if defined(FRONTCOVER_ES)
#define LANG_WORDCLOCK "reloj de palabras"
const char sWeekday[][2] PROGMEM =
{
	{ ' ', ' ' }, // 00
	{ 'D', 'O' }, // 01
	{ 'L', 'U' }, // 02
	{ 'M', 'A' }, // 03
	{ 'M', 'I' }, // 04
	{ 'J', 'U' }, // 05
	{ 'V', 'I' }, // 06
	{ 'S', 'A' }  // 07
};

// Wochentage für die Soundauswahl im Web
#define LANG_SUNDAY "Domingo"
#define LANG_MONDAY "Lunes"
#define LANG_TUESDAY "Martes"
#define LANG_WEDNESDAY "Miércoles"
#define LANG_THURSDAY "Jueves"
#define LANG_FRIDAY "Vierns"
#define LANG_SATURDAY "Sábado"

#define LANG_SUNDAY_SHORT "Do"
#define LANG_MONDAY_SHORT "Lu"
#define LANG_TUESDAY_SHORT "Ma"
#define LANG_WEDNESDAY_SHORT "Mi"
#define LANG_THURSDAY_SHORT "Ju"
#define LANG_FRIDAY_SHORT "Vi"
#define LANG_SATURDAY_SHORT "Sa"
// Zeit
#define LANG_DAYS "días"
#define LANG_HOURS "horas"
#define LANG_HOUR "Hora"
#define LANG_MINUTES "minutos"
#define LANG_MINUTE "minuto"
#define LANG_SECONDS "segundos"
#define LANG_AM "reloj"
#define LANG_PM "reloj"
//Sonne
#define LANG_SUNRISE "amanecer"
#define LANG_SUNSET "puesta de sol"
//Mondphase
#define LANG_NEWMOON "Luna nueva"
#define LANG_FULLMOON "Luna llena"
#define LANG_INCREASINGMOON "cada vez más"
#define LANG_WANINGMOON "decreciente"
#define LANG_INDOOR "en el interior"
#define LANG_OUTDOOR "dfuera de"
//OpenWeather
#define LANG_OPENWAETHER_LANG "es"
#define LANG_OW_OK "Todo está bien!!"
#define LANG_OW_ERRTEMP "Error de temperatura!!"
#define LANG_OW_ERRHUM "error de humedad!!"
#define LANG_OW_ERRPRES "Error de presión de aire!!"
#define LANG_OW_ERRSUNRISE "Sin información del amanecer!!"
#define LANG_OW_ERRSUNSET "Sin información del atardecer!!"
#define LANG_OW_ERRCONNECT "Sin conexión con Open Weather!!"
#define LANG_OW_ERRAPI "API-Key demasiado corto!!"

#define LANG_WINDSPEED "velocidad del viento"
#define LANG_AIRPRESSUREHIST "presión atmosférica en las últimas horas: (Tendenz: "
#define LANG_TEMPHIST "Historial de temperatura de las últimas 24 horas:"
//Settings
#define LANG_ALARM "Alarma"
#define LANG_TIMER "Temporizador"
#define LANG_CHIME "Huelga de hora"
#define LANG_VOLUME "volumen"
#define LANG_RANDOM "Coincidentemente:"
#define LANG_LOUDER_ON_WEEKEND "más fuerte 2 horas más tarde el fin de semana"
#define LANG_SINGLEGONG "solo gong"
// Sound Web-Anzeigenamen in Settings:
#define AUDIO_WEBNAME0  "Sound 1"               // 0 s1
#define AUDIO_WEBNAME1  "Sound 2"               // 1 s2
#define AUDIO_WEBNAME2  "Sound 3"               // 2 s3
#define AUDIO_WEBNAME3  "Sound 4"               // 3 s4
#define AUDIO_WEBNAME4  "cuco"               // 4 kuckuck
#define AUDIO_WEBNAME5  "Bing"                  // 5 bing
#define AUDIO_WEBNAME6  "Iglesia"                // 6 kirche
#define AUDIO_WEBNAME7  "Westminster 1"         // 7 westminster 1
#define AUDIO_WEBNAME8  "Westminster 2"         // 8 westminster 2
#define AUDIO_WEBNAME9  "reloj antiguo"              // 9 alte Uhr
#define AUDIO_WEBNAME10 "Ding"                  // 10 Ding
#define AUDIO_WEBNAME11 "perro y gato"         // 11 Hund und Katz
#define AUDIO_WEBNAME12 "Muerte"                   // 12 Tod
#define AUDIO_WEBNAME13 "Vicki"                 // 13 Vicki
#define AUDIO_WEBNAME14 "Hans"                  // 14 Hans
#define AUDIO_WEBNAME15 "Vicki/Hans"            // 15 Vicki/Hans
//
#define LANG_VICKYHANS_FORMAT "anuncio de hora Vicki/Hans formato"
#define LANG_SPEAKER "altavoz"
#define LANG_DISPLAY "anuncio publicitario" 
#define LANG_TEMPERATURE "la temperatura" 
#define LANG_MOONPHASE "fase lunar" 
#define LANG_WEATHER "clima" 
#define LANG_DATE "fecha"
#define LANG_EVERY "Todo el mundo"
#define LANG_SUNRISE_SUNSET "anuncio - <br>amanecer:<br>puesta de sol"
#define LANG_AUTO_BRIGHTNESS "auto. brillo"
#define LANG_BRIGHTNESS "brillo"
#define LANG_COLOURS "Colores"
#define LANG_COLOUR_00 "Blanco"
#define LANG_COLOUR_01 "Rojo"
#define LANG_COLOUR_02 "Rojo 75%"
#define LANG_COLOUR_03 "Rojo 50%"
#define LANG_COLOUR_04 "Naranja"
#define LANG_COLOUR_05 "Amarillo"
#define LANG_COLOUR_06 "Amarillo 75%"
#define LANG_COLOUR_07 "Amarillo 50%"
#define LANG_COLOUR_08 "Verde-Amarillo"
#define LANG_COLOUR_09 "Verde"
#define LANG_COLOUR_10 "Verde 75%"

#define LANG_COLOUR_11 "Verde 50%"
#define LANG_COLOUR_12 "Menta verde"
#define LANG_COLOUR_13 "Cian"
#define LANG_COLOUR_14 "Cian 75%"
#define LANG_COLOUR_15 "Cian 50%"
#define LANG_COLOUR_16 "Ligeramente azul"
#define LANG_COLOUR_17 "Azul"
#define LANG_COLOUR_18 "Azul 75%"
#define LANG_COLOUR_19 "Azul 50%"

#define LANG_COLOUR_20 "Violeta"
#define LANG_COLOUR_21 "Magenta"
#define LANG_COLOUR_22 "Magenta 75%"
#define LANG_COLOUR_23 "Magenta 50%"
#define LANG_COLOUR_24 "Rosa"

#define LANG_MINUTE_COLOUR "minutos LED color"
#define LANG_COLOUR_CHANGE "cambio de color"
#define LANG_MINUTE_COLOUR_CHANGE "Cambio de color al minuto"
#define LANG_LIKEMAIN "como color principal"
#define LANG_DAILY "diariamente"
#define LANG_HOURLY "cada hora."
#define LANG_BACKGROUNDCOLOUR "color de fondo"
#define LANG_OFF "apagado"
#define LANG_TIME "tiempo"
#define LANG_ALWAYS "siempre"
#define LANG_TRANSITIONS "transiciones"
#define LANG_SINGLE "individualmente"
#define LANG_ALL "Todo el mundo"
#define LANG_TRANSITION_00 "normal"
#define LANG_TRANSITION_01 "mar de color"
#define LANG_TRANSITION_02 "alto"
#define LANG_TRANSITION_03 "abajo"
#define LANG_TRANSITION_04 "Izquierda"
#define LANG_TRANSITION_05 "A la derecha"
#define LANG_TRANSITION_06 "abajo a la izquierda"
#define LANG_TRANSITION_07 "justo abajo"
#define LANG_TRANSITION_08 "al medio"
#define LANG_TRANSITION_09 "amable"
#define LANG_TRANSITION_10 "matriz"
#define LANG_TRANSITION_11 "espiral izquierda"
#define LANG_TRANSITION_12 "espiral derecha"
#define LANG_TRANSITION_13 "linea por linea"
#define LANG_TRANSITION_14 "arcoíris"
#define LANG_TRANSITION_15 "centro izquierda"
#define LANG_TRANSITION_16 "cuadrícula"
#define LANG_TRANSITION_17 "círculos"

#define LANG_ONE_AFTER_ANOTHER "sucesivamente"

#define LANG_NIGHT_OFF "apagado por la noche"
#define LANG_DAY_ON "etiquetas activadas"

#define LANG_SHOWITIS "mostrar \"es\""
#define LANG_SETDATETIME "Establecer fecha/hora"
#define LANG_TIMEHOST "servidor de tiempo"
#define LANG_SYSTEMNAME "Nombre del sistema"

#define LANG_LOCATION "Location"
#define LANG_ALTITUDE "ubicación de altura"
#define LANG_LATITUDE "Latitude"
#define LANG_LONGITUDE "Longitude"

#define LANG_RESET_HIGHSCORE "Restablecer puntajes altos"

// Buttons
#define LANG_BACK "devolver"
#define LANG_SAVE "guardar"
#define LANG_SETTINGS "ajustes"
#define LANG_ON "en"
#define LANG_ANIMATIONS "Animaciones"
#define LANG_EVENTS "Eventos"
#define LANG_MESSAGE "Enviar mensaje"
#define LANG_GAMES "Juegos"
#define LANG_MODEBUTTON "Visualización de Información"
#define LANG_TIMEBUTTON "visualización de la hora"
#define LANG_CHANGEBUTTON "cambio"

//Animationsmenü
#define LANG_ANIMATIONMENU "menú de animación"

//Info
#define LANG_NETWORKWIFI "WiFi/el obra de malla"
#define LANG_WIFISIGNAL "Intensidad de señal"
#define LANG_WIFIQ1 "excelente"
#define LANG_WIFIQ2 "Muy bueno"
#define LANG_WIFIQ3 "Bien"
#define LANG_WIFIQ4 "aceptable"
#define LANG_WIFIQ5 "malo"
#define LANG_WIFIQ6 "muy mal"
#define LANG_WIFIQ7 "insuficiente"

#define LANG_WIFIRECON "WLAN Reconnect por día"
#define LANG_IPADRESS "dirección IP"
#define LANG_RESETREASON "Reset resultado"
#define LANG_CLOCK "reloj"
#define LANG_LDR_VALUE "LDR-Resultado"
#define LANG_HUMIDITY "humedad"
#define LANG_AIRPRESSURE "presión del aire"
#define LANG_AIRPRESSUREDIFF "diferencial de presión de aire"
#define LANG_AIRPRESSURETHRES "umbrales de presión"

#define LANG_OW_LASTUPDATE "Última actualización"
#define LANG_INFOSUNSETRISE "la salida del sol puesta de sol"
#define LANG_MODECOUNT "ModeCount por día"
#define LANG_LASTTRANS "última trans"

#define LANG_SNAKE "Snake"
#define LANG_TETRIS "Tetris"
#define LANG_BRICKS "Bricks"
#define LANG_4GEWINNT "Conecta 4"
#define LANG_MEMORY1 "memoria de animales"
#define LANG_MEMORY2 "memoria musical"
#define LANG_MEMORY3 "memoria ABBA"

#define LANG_HTMLLANG "es"
#define LANG_EXPLORER "Administrador de archivos"
#define LANG_FORMATCONF "¿Realmente formato? Todos los datos se perderán."
#define LANG_NOSPACE "Memoria libre insuficiente"
#define LANG_FILESIZE "tamaño del archivo"
#define LANG_FOLDER "nombre de la carpeta"
#define LANG_SURE "¿Seguro?"
#define LANG_CHAR_NOT_ALLOW "Los caracteres &#8220; % & / : ; \\ no están permitidos."
#define LANG_FSUSED "Utiliza"
#define LANG_FSTOTAL "En total"

#endif
//Ende FRONTCOVER_ES

//########################################################################################################################
// FRANZÖSISCH
//########################################################################################################################

#if defined(FRONTCOVER_FR)
#define LANG_WORDCLOCK "horloge de mots"
const char sWeekday[][2] PROGMEM =
{
	{ ' ', ' ' }, // 00
	{ 'D', 'I' }, // 01
	{ 'L', 'U' }, // 02
	{ 'M', 'A' }, // 03
	{ 'M', 'E' }, // 04
	{ 'J', 'E' }, // 05
	{ 'V', 'E' }, // 06
	{ 'S', 'A' }  // 07
};

// Wochentage für die Soundauswahl im Web
#define LANG_SUNDAY "Dimanche"
#define LANG_MONDAY "Lundi"
#define LANG_TUESDAY "Mardi"
#define LANG_WEDNESDAY "Merdredi"
#define LANG_THURSDAY "Jeudi"
#define LANG_FRIDAY "Vendredi"
#define LANG_SATURDAY "Samedi"

#define LANG_SUNDAY_SHORT "Di"
#define LANG_MONDAY_SHORT "Lu"
#define LANG_TUESDAY_SHORT "Ma"
#define LANG_WEDNESDAY_SHORT "Me"
#define LANG_THURSDAY_SHORT "Je"
#define LANG_FRIDAY_SHORT "Ve"
#define LANG_SATURDAY_SHORT "Sa"
// Zeit
#define LANG_DAYS "jour"
#define LANG_HOURS "heures"
#define LANG_HOUR "heure"
#define LANG_MINUTES "minutes"
#define LANG_MINUTE "minute"
#define LANG_SECONDS "secunde"
#define LANG_AM " "
#define LANG_PM " "
//Sonne
#define LANG_SUNRISE "lever"
#define LANG_SUNSET "le coucher du soleil"
//Mondphase
#define LANG_NEWMOON "nouvelle lune"
#define LANG_FULLMOON "pleine lune"
#define LANG_INCREASINGMOON "croissante"
#define LANG_WANINGMOON "décroissant"
#define LANG_INDOOR "à l'intérieur"
#define LANG_OUTDOOR "à l'extérieur"
//OpenWeather
#define LANG_OPENWAETHER_LANG "fr"
#define LANG_OW_OK "Tout va bien!!"
#define LANG_OW_ERRTEMP "Erreur de température!!"
#define LANG_OW_ERRHUM "Erreur d'humidité!!"
#define LANG_OW_ERRPRES "Erreur de pression d'air!!"
#define LANG_OW_ERRSUNRISE "Aucune information sur le lever du soleil!!"
#define LANG_OW_ERRSUNSET "Aucune information sur le coucher du soleil!!"
#define LANG_OW_ERRCONNECT "Pas de connexion à Open Weather!!"
#define LANG_OW_ERRAPI "API-Key trop court!!"

#define LANG_WINDSPEED "vitesse du vent"
#define LANG_AIRPRESSUREHIST "Pression atmosphérique des dernières heures: Tendance: "
#define LANG_TEMPHIST "Historique des températures des dernières 24 heures:"
//Settings
#define LANG_ALARM "alarme"
#define LANG_TIMER "minuteur"
#define LANG_CHIME "heure de grève"
#define LANG_VOLUME "le volume"
#define LANG_RANDOM "par coïncidence"
#define LANG_LOUDER_ON_WEEKEND "plus fort 2 heures plus tard le week-end"
#define LANG_SINGLEGONG "gong unique"
// Sound Web-Anzeigenamen in Settings:
#define AUDIO_WEBNAME0  "du son 1"               // 0 s1
#define AUDIO_WEBNAME1  "du son 2"               // 1 s2
#define AUDIO_WEBNAME2  "du son 3"               // 2 s3
#define AUDIO_WEBNAME3  "du son 4"               // 3 s4
#define AUDIO_WEBNAME4  "coucou"               // 4 kuckuck
#define AUDIO_WEBNAME5  "Bing"                  // 5 bing
#define AUDIO_WEBNAME6  "Église"                // 6 kirche
#define AUDIO_WEBNAME7  "Westminster 1"         // 7 westminster 1
#define AUDIO_WEBNAME8  "Westminster 2"         // 8 westminster 2
#define AUDIO_WEBNAME9  "vieille horloge"              // 9 alte Uhr
#define AUDIO_WEBNAME10 "chose"                  // 10 Ding
#define AUDIO_WEBNAME11 "chien et chat"         // 11 Hund und Katz
#define AUDIO_WEBNAME12 "décès"                   // 12 Tod
#define AUDIO_WEBNAME13 "Vicki"                 // 13 Vicki
#define AUDIO_WEBNAME14 "Hans"                  // 14 Hans
#define AUDIO_WEBNAME15 "Vicki/Hans"            // 15 Vicki/Hans
//
#define LANG_VICKYHANS_FORMAT "annonce de l'heure Vicki/Hans Format"
#define LANG_SPEAKER "conférencier"
#define LANG_DISPLAY "publicité" 
#define LANG_TEMPERATURE "Température" 
#define LANG_MOONPHASE "phase de lune" 
#define LANG_WEATHER "Météo" 
#define LANG_DATE "Date"
#define LANG_EVERY "Tout le monde"
#define LANG_SUNRISE_SUNSET "annonce - <br>lever du soleil:<br>le coucher du soleil"
#define LANG_AUTO_BRIGHTNESS "auto. luminosité"
#define LANG_BRIGHTNESS "luminosité"
#define LANG_COLOURS "Couleurs"
#define LANG_COLOUR_00 "Weiss"
#define LANG_COLOUR_01 "Rouge"
#define LANG_COLOUR_02 "Rouge 75%"
#define LANG_COLOUR_03 "Rouge 50%"
#define LANG_COLOUR_04 "Orange"
#define LANG_COLOUR_05 "Jaune"
#define LANG_COLOUR_06 "Jaune 75%"
#define LANG_COLOUR_07 "Jaune 50%"
#define LANG_COLOUR_08 "Vert-Jaune"
#define LANG_COLOUR_09 "Vert"
#define LANG_COLOUR_10 "Vert 75%"

#define LANG_COLOUR_11 "Vert 50%"
#define LANG_COLOUR_12 "Menthe verte"
#define LANG_COLOUR_13 "Cyan"
#define LANG_COLOUR_14 "Cyan 75%"
#define LANG_COLOUR_15 "Cyan 50%"
#define LANG_COLOUR_16 "Légèrement bleu"
#define LANG_COLOUR_17 "Bleu"
#define LANG_COLOUR_18 "Bleu 75%"
#define LANG_COLOUR_19 "Bleu 50%"

#define LANG_COLOUR_20 "Violet"
#define LANG_COLOUR_21 "Magenta"
#define LANG_COLOUR_22 "Magenta 75%"
#define LANG_COLOUR_23 "Magenta 50%"
#define LANG_COLOUR_24 "Rose"

#define LANG_MINUTE_COLOUR "minute couleur LED"
#define LANG_COLOUR_CHANGE "changement de couleur"
#define LANG_MINUTE_COLOUR_CHANGE "Changement de couleur infime"
#define LANG_LIKEMAIN "comme la couleur principale"
#define LANG_DAILY "du quotidien"
#define LANG_HOURLY "toutes les heures"
#define LANG_BACKGROUNDCOLOUR "Couleur de l'arrière plan"
#define LANG_OFF "arrêt"
#define LANG_TIME "temps"
#define LANG_ALWAYS "toujours"
#define LANG_TRANSITIONS "transitions"
#define LANG_SINGLE "individuellement"
#define LANG_ALL "Tout le monde"
#define LANG_TRANSITION_00 "Ordinaire"
#define LANG_TRANSITION_01 "mer de couleur"
#define LANG_TRANSITION_02 "haute"
#define LANG_TRANSITION_03 "vers le bas"
#define LANG_TRANSITION_04 "La gauche"
#define LANG_TRANSITION_05 "À droite"
#define LANG_TRANSITION_06 "en bas à gauche"
#define LANG_TRANSITION_07 "tout en bas"
#define LANG_TRANSITION_08 "au milieu"
#define LANG_TRANSITION_09 "fade"
#define LANG_TRANSITION_10 "matrice"
#define LANG_TRANSITION_11 "spirale à gauche"
#define LANG_TRANSITION_12 "spirale à droite"
#define LANG_TRANSITION_13 "ligne par ligne"
#define LANG_TRANSITION_14 "arc en ciel"
#define LANG_TRANSITION_15 "centre gauche"
#define LANG_TRANSITION_16 "carrés"
#define LANG_TRANSITION_17 "cercles"

#define LANG_ONE_AFTER_ANOTHER "successivement"

#define LANG_NIGHT_OFF "éteint la nuit"
#define LANG_DAY_ON "balises activées"

#define LANG_SHOWITIS "montrer \"c'est\""
#define LANG_SETDATETIME "Définir la date/l'heure"
#define LANG_TIMEHOST "serveur de temps"
#define LANG_SYSTEMNAME "nom du système"

#define LANG_LOCATION "Emplacement"
#define LANG_ALTITUDE "la taille Emplacement"
#define LANG_LATITUDE "Latitude"
#define LANG_LONGITUDE "Longitude"

#define LANG_RESET_HIGHSCORE "Réinitialiser les meilleurs scores"

// Buttons
#define LANG_BACK "revenir"
#define LANG_SAVE "sauver"
#define LANG_SETTINGS "réglages"
#define LANG_ON "marche"
#define LANG_ANIMATIONS "animations"
#define LANG_EVENTS "Événements"
#define LANG_MESSAGE "Envoyer le message"
#define LANG_GAMES "Jeux"
#define LANG_MODEBUTTON "affichage d'informations"
#define LANG_TIMEBUTTON "affichage de l'heure"
#define LANG_CHANGEBUTTON "modifier"

//Animationsmenü
#define LANG_ANIMATIONMENU "menus d'animations"

//Info
#define LANG_NETWORKWIFI "WiFi/réseau"
#define LANG_WIFISIGNAL "force du signal"
#define LANG_WIFIQ1 "excellent"
#define LANG_WIFIQ2 "très bien"
#define LANG_WIFIQ3 "Bien"
#define LANG_WIFIQ4 "acceptable"
#define LANG_WIFIQ5 "mal"
#define LANG_WIFIQ6 "très mauvais"
#define LANG_WIFIQ7 "insuffisant"

#define LANG_WIFIRECON "WLAN Reconnexion par jour"
#define LANG_IPADRESS "IP-adresse"
#define LANG_RESETREASON "Reset raison"
#define LANG_CLOCK "Regardez"
#define LANG_LDR_VALUE "LDR-évaluer"
#define LANG_HUMIDITY "humidité"
#define LANG_AIRPRESSURE "pression de l'air"
#define LANG_AIRPRESSUREDIFF "différence de pression d'air"
#define LANG_AIRPRESSURETHRES "seuils de pression"

#define LANG_OW_LASTUPDATE "Dernière mise à jour"
#define LANG_INFOSUNSETRISE "lever du soleil"
#define LANG_MODECOUNT "ModeCount par jour"
#define LANG_LASTTRANS "Ldernière trans"

#define LANG_SNAKE "Snake"
#define LANG_TETRIS "Tetris"
#define LANG_BRICKS "Bricks"
#define LANG_4GEWINNT "Puissance 4"
#define LANG_MEMORY1 "animaux memory"
#define LANG_MEMORY2 "musique memory"
#define LANG_MEMORY3 "ABBA memory"

#define LANG_HTMLLANG "fr"
#define LANG_EXPLORER "Explorateur de fichiers"
#define LANG_FORMATCONF "Formater vraiment ? Toutes les données seront perdues."
#define LANG_NOSPACE "Mémoire libre insuffisante"
#define LANG_FILESIZE "taille du fichier"
#define LANG_FOLDER "nom de dossier"
#define LANG_SURE "Sécurisé?"
#define LANG_CHAR_NOT_ALLOW "Les caractères &#8220; % & / : ; \\ ne sont pas autorisés."
#define LANG_FSUSED "Utilise"
#define LANG_FSTOTAL "Au total"

#endif
//Ende FRONTCOVER_FR

//########################################################################################################################
// ITALIENISCH
//########################################################################################################################

#if defined(FRONTCOVER_IT)
#define LANG_WORDCLOCK "orologio di parole"
const char sWeekday[][2] PROGMEM =
{
	{ ' ', ' ' }, // 00
	{ 'D', 'O' }, // 01
	{ 'L', 'U' }, // 02
	{ 'M', 'A' }, // 03
	{ 'M', 'E' }, // 04
	{ 'G', 'I' }, // 05
	{ 'V', 'E' }, // 06
	{ 'S', 'A' }  // 07
};

// Wochentage für die Soundauswahl im Web
#define LANG_SUNDAY "Domenica"
#define LANG_MONDAY "Lunedi"
#define LANG_TUESDAY "Martedi"
#define LANG_WEDNESDAY "Mercoledi"
#define LANG_THURSDAY "Giovedi"
#define LANG_FRIDAY "Venerdi"
#define LANG_SATURDAY "Sabato"

#define LANG_SUNDAY_SHORT "Do"
#define LANG_MONDAY_SHORT "Lu"
#define LANG_TUESDAY_SHORT "Ma"
#define LANG_WEDNESDAY_SHORT "Me"
#define LANG_THURSDAY_SHORT "Gi"
#define LANG_FRIDAY_SHORT "Ve"
#define LANG_SATURDAY_SHORT "Sa"
// Zeit
#define LANG_DAYS "giorni"
#define LANG_HOURS "ore"
#define LANG_HOUR "Ora"
#define LANG_MINUTES "minuti"
#define LANG_MINUTE "minuto"
#define LANG_SECONDS "secondi"
#define LANG_AM " "
#define LANG_PM " "
//Sonne
#define LANG_SUNRISE "Alba"
#define LANG_SUNSET "tramonto"
//Mondphase
#define LANG_NEWMOON "nuova luna"
#define LANG_FULLMOON "Luna piena"
#define LANG_INCREASINGMOON "Luna crescente"
#define LANG_WANINGMOON "Luna calante"
#define LANG_INDOOR "dentro"
#define LANG_OUTDOOR "fuori"
//OpenWeather
#define LANG_OPENWAETHER_LANG "it"
#define LANG_OW_OK "Tutto ok!!"
#define LANG_OW_ERRTEMP "Errore di temperatura!!"
#define LANG_OW_ERRHUM "Errore di umidità!!"
#define LANG_OW_ERRPRES "Errore di pressione dell'aria!!"
#define LANG_OW_ERRSUNRISE "Nessuna informazione sull'alba!!"
#define LANG_OW_ERRSUNSET "Nessuna informazione sul tramonto!!"
#define LANG_OW_ERRCONNECT "Nessuna connessione per Open Weather!!"
#define LANG_OW_ERRAPI "API-Key troppo corta!!"

#define LANG_WINDSPEED "velocità del vento"
#define LANG_AIRPRESSUREHIST "Pressione atmosferica delle ultime ore: (Andamento:"
#define LANG_TEMPHIST "Storico della temperatura delle ultime 24 ore:"
//Settings
#define LANG_ALARM "allarme"
#define LANG_TIMER "Timer"
#define LANG_CHIME "sciopero dell'ora"
#define LANG_VOLUME "volume"
#define LANG_RANDOM "coincidentalmente"
#define LANG_LOUDER_ON_WEEKEND "più forte 2 ore dopo durante il fine settimana"
#define LANG_SINGLEGONG "singolo gong"
// Sound Web-Anzeigenamen in Settings:
#define AUDIO_WEBNAME0  "suoni 1"               // 0 s1
#define AUDIO_WEBNAME1  "suoni 2"               // 1 s2
#define AUDIO_WEBNAME2  "suoni 3"               // 2 s3
#define AUDIO_WEBNAME3  "suoni 4"               // 3 s4
#define AUDIO_WEBNAME4  "cuculo"                // 4 kuckuck
#define AUDIO_WEBNAME5  "Bing"                  // 5 bing
#define AUDIO_WEBNAME6  "Chiesa"                // 6 kirche
#define AUDIO_WEBNAME7  "Westminster 1"         // 7 westminster 1
#define AUDIO_WEBNAME8  "Westminster 2"         // 8 westminster 2
#define AUDIO_WEBNAME9  "vecchio orologio"             // 9 alte Uhr
#define AUDIO_WEBNAME10 "Ding"                  // 10 Ding
#define AUDIO_WEBNAME11 "cane e gatto"           // 11 Hund und Katz
#define AUDIO_WEBNAME12 "Morte"                 // 12 Tod
#define AUDIO_WEBNAME13 "Vicki"                 // 13 Vicki
#define AUDIO_WEBNAME14 "Hans"                  // 14 Hans
#define AUDIO_WEBNAME15 "Vicki/Hans"            // 15 Vicki/Hans
//
#define LANG_VICKYHANS_FORMAT "Annuncio dell'ora Formato Vicki/Hans"
#define LANG_SPEAKER "oratore"
#define LANG_DISPLAY "annuncio" 
#define LANG_TEMPERATURE "temperatura" 
#define LANG_MOONPHASE "fase lunare" 
#define LANG_WEATHER "tempo atmosferico" 
#define LANG_DATE "Data"
#define LANG_EVERY "ogni"
#define LANG_SUNRISE_SUNSET "Annuncio - <br>alba:<br>tramonto"
#define LANG_AUTO_BRIGHTNESS "luminosità automatica"
#define LANG_BRIGHTNESS "luminosità"
#define LANG_COLOURS "Colori"
#define LANG_COLOUR_00 "Bianco"
#define LANG_COLOUR_01 "Rosso"
#define LANG_COLOUR_02 "Rosso 75%"
#define LANG_COLOUR_03 "Rosso 50%"
#define LANG_COLOUR_04 "Arancia"
#define LANG_COLOUR_05 "Giallo"
#define LANG_COLOUR_06 "Giallo 75%"
#define LANG_COLOUR_07 "Giallo 50%"
#define LANG_COLOUR_08 "Giallo verde"
#define LANG_COLOUR_09 "Verde"
#define LANG_COLOUR_10 "Verde 75%"

#define LANG_COLOUR_11 "Verde 50%"
#define LANG_COLOUR_12 "Menta verde"
#define LANG_COLOUR_13 "Ciano"
#define LANG_COLOUR_14 "Ciano 75%"
#define LANG_COLOUR_15 "Ciano 50%"
#define LANG_COLOUR_16 "Leggermente blu"
#define LANG_COLOUR_17 "Blu"
#define LANG_COLOUR_18 "Blu 75%"
#define LANG_COLOUR_19 "Blu 50%"

#define LANG_COLOUR_20 "Viola"
#define LANG_COLOUR_21 "Magenta"
#define LANG_COLOUR_22 "Magenta 75%"
#define LANG_COLOUR_23 "Magenta 50%"
#define LANG_COLOUR_24 "Rosa"

#define LANG_MINUTE_COLOUR "minuti di colore del LED"
#define LANG_COLOUR_CHANGE "cambio di colore"
#define LANG_MINUTE_COLOUR_CHANGE "Minuto cambio di colore"
#define LANG_LIKEMAIN "come il colore di sfondo"
#define LANG_DAILY "Ogni giorno"
#define LANG_HOURLY "ogni ora"
#define LANG_BACKGROUNDCOLOUR "colore di sfondo"
#define LANG_OFF "spento"
#define LANG_TIME "volta"
#define LANG_ALWAYS "sempre"
#define LANG_TRANSITIONS "transizioni"
#define LANG_SINGLE "individualmente"
#define LANG_ALL "ogni"
#define LANG_TRANSITION_00 "normale"
#define LANG_TRANSITION_01 "mare di colore"
#define LANG_TRANSITION_02 "su"
#define LANG_TRANSITION_03 "verso il basso"
#define LANG_TRANSITION_04 "A sinistra"
#define LANG_TRANSITION_05 "A destra"
#define LANG_TRANSITION_06 "in basso a sinistra"
#define LANG_TRANSITION_07 "proprio giù"
#define LANG_TRANSITION_08 "al Medio"
#define LANG_TRANSITION_09 "blando"
#define LANG_TRANSITION_10 "matrice"
#define LANG_TRANSITION_11 "spirale a sinistra"
#define LANG_TRANSITION_12 "spirale a destra"
#define LANG_TRANSITION_13 "linea per linea"
#define LANG_TRANSITION_14 "arcobaleno"
#define LANG_TRANSITION_15 "centro sinistra"
#define LANG_TRANSITION_16 "piazze"
#define LANG_TRANSITION_17 "cerchi"

#define LANG_ONE_AFTER_ANOTHER "successivamente"

#define LANG_NIGHT_OFF "spento di notte"
#define LANG_DAY_ON "tag on off"

#define LANG_SHOWITIS "Mostra \"sono le\""
#define LANG_SETDATETIME "Imposta data/ora"
#define LANG_TIMEHOST "server del tempo"
#define LANG_SYSTEMNAME "nome del sistema"

#define LANG_LOCATION "Posizione"
#define LANG_ALTITUDE "posizione di altezza"
#define LANG_LATITUDE "altitudine"
#define LANG_LONGITUDE "lunghezza"

#define LANG_RESET_HIGHSCORE "Reimposta i punteggi più alti"

// Buttons
#define LANG_BACK "indietro"
#define LANG_SAVE "salvare"
#define LANG_SETTINGS "impostazioni"
#define LANG_ON "acceso"
#define LANG_ANIMATIONS "Animazioni"
#define LANG_EVENTS "Eventi"
#define LANG_MESSAGE "Invia messaggio"
#define LANG_GAMES "Giochi"
#define LANG_MODEBUTTON "visualizzazione delle informazioni"
#define LANG_TIMEBUTTON "visualizzazione del tempo"
#define LANG_CHANGEBUTTON "modificare"

//Animationsmenü
#define LANG_ANIMATIONMENU "menu di animazione"

//Info
#define LANG_NETWORKWIFI "Rete Wi-Fi"
#define LANG_WIFISIGNAL "potenza del segnale"
#define LANG_WIFIQ1 "eccellente"
#define LANG_WIFIQ2 "Molto bene"
#define LANG_WIFIQ3 "Bene"
#define LANG_WIFIQ4 "accettabile"
#define LANG_WIFIQ5 "cattivo"
#define LANG_WIFIQ6 "molto brutto"
#define LANG_WIFIQ7 "insufficiente"

#define LANG_WIFIRECON "Riconnessione Wi-Fi al giorno"
#define LANG_IPADRESS "indirizzo IP"
#define LANG_RESETREASON "ripristinare il motivo"
#define LANG_CLOCK "guarda"
#define LANG_LDR_VALUE "valore LDR"
#define LANG_HUMIDITY "umidità"
#define LANG_AIRPRESSURE "pressione dell'aria"
#define LANG_AIRPRESSUREDIFF "differenza di pressione dell'aria"
#define LANG_AIRPRESSURETHRES "soglie di pressione"

#define LANG_OW_LASTUPDATE "Ultimo aggiornamento"
#define LANG_INFOSUNSETRISE "Alba/tramonto"
#define LANG_MODECOUNT "ModeCount al giorno"
#define LANG_LASTTRANS "Ultima Transizione"

#define LANG_SNAKE "Snake"
#define LANG_TETRIS "Tetris"
#define LANG_BRICKS "Bricks"
#define LANG_4GEWINNT "Forza Quattro"
#define LANG_MEMORY1 "Memoria animale"
#define LANG_MEMORY2 "Memoria musicale"
#define LANG_MEMORY3 "Memoria ABBA"

#define LANG_HTMLLANG "it"
#define LANG_EXPLORER "Gestore di file"
#define LANG_FORMATCONF "Formato davvero? Tutti i dati andranno persi."
#define LANG_NOSPACE "Memoria libera insufficiente"
#define LANG_FILESIZE "dimensione del file"
#define LANG_FOLDER "nome della cartella"
#define LANG_SURE "sicuro?"
#define LANG_CHAR_NOT_ALLOW "I caratteri &#8220; % & / : ; \\ non sono consentiti."
#define LANG_FSUSED "Usato"
#define LANG_FSTOTAL "In totale"

#endif
//Ende FRONTCOVER_IT

//########################################################################################################################
// NIEDERLÄNDISCH
//########################################################################################################################

#if defined(FRONTCOVER_NL)
#define LANG_WORDCLOCK "woord klok"
const char sWeekday[][2] PROGMEM =
{
	{ ' ', ' ' }, // 00
	{ 'Z', 'O' }, // 01
	{ 'M', 'A' }, // 02
	{ 'D', 'I' }, // 03
	{ 'W', 'O' }, // 04
	{ 'D', 'O' }, // 05
	{ 'V', 'R' }, // 06
	{ 'Z', 'A' }  // 07
};

// Wochentage für die Soundauswahl im Web
#define LANG_SUNDAY "Zondag"
#define LANG_MONDAY "Maandag"
#define LANG_TUESDAY "Dinsdag"
#define LANG_WEDNESDAY "Woensdag"
#define LANG_THURSDAY "Donderdag"
#define LANG_FRIDAY "Vrijdag"
#define LANG_SATURDAY "Zaterdag"

#define LANG_SUNDAY_SHORT "Zo"
#define LANG_MONDAY_SHORT "Ma"
#define LANG_TUESDAY_SHORT "Di"
#define LANG_WEDNESDAY_SHORT "Wo"
#define LANG_THURSDAY_SHORT "Do"
#define LANG_FRIDAY_SHORT "Vr"
#define LANG_SATURDAY_SHORT "Za"
// Zeit
#define LANG_DAYS "dagen"
#define LANG_HOURS "uur"
#define LANG_HOUR "Uur"
#define LANG_MINUTES "minuten"
#define LANG_MINUTE "minuut"
#define LANG_SECONDS "seconden"
#define LANG_AM "uur"
#define LANG_PM "uur"
//Sonne
#define LANG_SUNRISE "zonsopkomst"
#define LANG_SUNSET "zonsondergang"
//Mondphase
#define LANG_NEWMOON "nieuwe maan"
#define LANG_FULLMOON "volle maan"
#define LANG_INCREASINGMOON "toenemende maan"
#define LANG_WANINGMOON "afnemende maan"
#define LANG_INDOOR "binnen"
#define LANG_OUTDOOR "buiten"
//OpenWeather
#define LANG_OPENWAETHER_LANG "nl"
#define LANG_OW_OK "Alles ok!!"
#define LANG_OW_ERRTEMP "Temperatuurfout!!"
#define LANG_OW_ERRHUM "Vochtigheid fout!!"
#define LANG_OW_ERRPRES "Luchtdruk fout!!"
#define LANG_OW_ERRSUNRISE "Geen zonsopgang info!!"
#define LANG_OW_ERRSUNSET "Geen zonsondergang info!!"
#define LANG_OW_ERRCONNECT "Geen verbinding met Open Weather!!"
#define LANG_OW_ERRAPI "API-Key te kort!!"

#define LANG_WINDSPEED "windsnelheid"
#define LANG_AIRPRESSUREHIST "Luchtdruk van de laatste uren: (Trend:"
#define LANG_TEMPHIST "Temperatuurgeschiedenis van de afgelopen 24 uur:"
//Settings
#define LANG_ALARM "allarm"
#define LANG_TIMER "tijdopnemer"
#define LANG_CHIME "uurstaking"
#define LANG_VOLUME "volume"
#define LANG_RANDOM "toevallig"
#define LANG_LOUDER_ON_WEEKEND "luider 2 uur later in het weekend"
#define LANG_SINGLEGONG "enkele gong"
// Sound Web-Anzeigenamen in Settings:
#define AUDIO_WEBNAME0  "klinkt 1"               // 0 s1
#define AUDIO_WEBNAME1  "klinkt 2"               // 1 s2
#define AUDIO_WEBNAME2  "klinkt 3"               // 2 s3
#define AUDIO_WEBNAME3  "klinkt 4"               // 3 s4
#define AUDIO_WEBNAME4  "koekoek"                // 4 kuckuck
#define AUDIO_WEBNAME5  "Bing"                  // 5 bing
#define AUDIO_WEBNAME6  "Kerk"                // 6 kirche
#define AUDIO_WEBNAME7  "Westminster 1"         // 7 westminster 1
#define AUDIO_WEBNAME8  "Westminster 2"         // 8 westminster 2
#define AUDIO_WEBNAME9  "oude klok"             // 9 alte Uhr
#define AUDIO_WEBNAME10 "Ding"                  // 10 Ding
#define AUDIO_WEBNAME11 "hond en kat"           // 11 Hund und Katz
#define AUDIO_WEBNAME12 "Dood"                 // 12 Tod
#define AUDIO_WEBNAME13 "Vicki"                 // 13 Vicki
#define AUDIO_WEBNAME14 "Hans"                  // 14 Hans
#define AUDIO_WEBNAME15 "Vicki/Hans"            // 15 Vicki/Hans
//
#define LANG_VICKYHANS_FORMAT "Uuraankondiging Vicki/Hans formaat"
#define LANG_SPEAKER "spreker"
#define LANG_DISPLAY "advertentie" 
#define LANG_TEMPERATURE "temperatuur" 
#define LANG_MOONPHASE "maanfase" 
#define LANG_WEATHER "het weer" 
#define LANG_DATE "datum"
#define LANG_EVERY "Iedereen"
#define LANG_SUNRISE_SUNSET "Aankondiging - <br>zonsopgang:<br>zonsondergang"
#define LANG_AUTO_BRIGHTNESS "automatische helderheid"
#define LANG_BRIGHTNESS "helderheid"
#define LANG_COLOURS "Kleuren"
#define LANG_COLOUR_00 "Wit"
#define LANG_COLOUR_01 "Rood"
#define LANG_COLOUR_02 "Rood 75%"
#define LANG_COLOUR_03 "Rood 50%"
#define LANG_COLOUR_04 "Oranje"
#define LANG_COLOUR_05 "Geel"
#define LANG_COLOUR_06 "Geel 75%"
#define LANG_COLOUR_07 "Geel 50%"
#define LANG_COLOUR_08 "Groente-Geel"
#define LANG_COLOUR_09 "Groente"
#define LANG_COLOUR_10 "Groente 75%"

#define LANG_COLOUR_11 "Groente 50%"
#define LANG_COLOUR_12 "Muntgroen"
#define LANG_COLOUR_13 "Cyaan"
#define LANG_COLOUR_14 "Cyaan 75%"
#define LANG_COLOUR_15 "Cyaan 50%"
#define LANG_COLOUR_16 "Iets blauw"
#define LANG_COLOUR_17 "Blauw"
#define LANG_COLOUR_18 "Blauw 75%"
#define LANG_COLOUR_19 "Blauw 50%"

#define LANG_COLOUR_20 "Paars"
#define LANG_COLOUR_21 "Magenta"
#define LANG_COLOUR_22 "Magenta 75%"
#define LANG_COLOUR_23 "Magenta 50%"
#define LANG_COLOUR_24 "Roze"

#define LANG_MINUTE_COLOUR "minuten LED-kleur"
#define LANG_COLOUR_CHANGE "kleur verandering"
#define LANG_MINUTE_COLOUR_CHANGE "Minuut kleurverandering"
#define LANG_LIKEMAIN "zoals hoofdkleur"
#define LANG_DAILY "Elke dag"
#define LANG_HOURLY "elk uur"
#define LANG_BACKGROUNDCOLOUR "Achtergrond kleur"
#define LANG_OFF "uit"
#define LANG_TIME "tijd"
#define LANG_ALWAYS "altijd"
#define LANG_TRANSITIONS "overgangen"
#define LANG_SINGLE "individueel"
#define LANG_ALL "Iedereen"
#define LANG_TRANSITION_00 "normaal"
#define LANG_TRANSITION_01 "zee van kleur"
#define LANG_TRANSITION_02 "hoog"
#define LANG_TRANSITION_03 "omlaag"
#define LANG_TRANSITION_04 "Links"
#define LANG_TRANSITION_05 "naar rechts"
#define LANG_TRANSITION_06 "beneden links"
#define LANG_TRANSITION_07 "recht naar beneden"
#define LANG_TRANSITION_08 "naar het midden"
#define LANG_TRANSITION_09 "flauw"
#define LANG_TRANSITION_10 "matrix"
#define LANG_TRANSITION_11 "spiraal links"
#define LANG_TRANSITION_12 "spiraal rechts"
#define LANG_TRANSITION_13 "lijn bij lijn"
#define LANG_TRANSITION_14 "regenboog"
#define LANG_TRANSITION_15 "centrum links"
#define LANG_TRANSITION_16 "vierkanten"
#define LANG_TRANSITION_17 "cirkels"

#define LANG_ONE_AFTER_ANOTHER "achtereenvolgens"

#define LANG_NIGHT_OFF "'s nachts vrij"
#define LANG_DAY_ON "labels aan uit"

#define LANG_SHOWITIS "Toon \"Het is\""
#define LANG_SETDATETIME "Datum/tijd instellen"
#define LANG_TIMEHOST "tijdserver"
#define LANG_SYSTEMNAME "systeemnaam"

#define LANG_LOCATION "Plaats"
#define LANG_ALTITUDE "hoogte locatie"
#define LANG_LATITUDE "Latitude"
#define LANG_LONGITUDE "Longitude"

#define LANG_RESET_HIGHSCORE "Hoge scores resetten"

// Buttons
#define LANG_BACK "rug"
#define LANG_SAVE "opslaan"
#define LANG_SETTINGS "Instellingen"
#define LANG_ON "aan"
#define LANG_ANIMATIONS "Animaties"
#define LANG_EVENTS "Evenementen"
#define LANG_MESSAGE "Bericht versturen"
#define LANG_GAMES "Spelletjes"
#define LANG_MODEBUTTON "infoweergave"
#define LANG_TIMEBUTTON "tijdweergave"
#define LANG_CHANGEBUTTON "wijzigen"

//Animationsmenü
#define LANG_ANIMATIONMENU "animatiemenu"

//Info
#define LANG_NETWORKWIFI "WiFi-netwerk"
#define LANG_WIFISIGNAL "signaalsterkte"
#define LANG_WIFIQ1 "uitstekend"
#define LANG_WIFIQ2 "zeer goed"
#define LANG_WIFIQ3 "We zullen"
#define LANG_WIFIQ4 "aanvaardbaar"
#define LANG_WIFIQ5 "slechte"
#define LANG_WIFIQ6 "heel slecht"
#define LANG_WIFIQ7 "niet voldoende"

#define LANG_WIFIRECON "Wifi opnieuw verbinden per dag"
#define LANG_IPADRESS "IP adres"
#define LANG_RESETREASON "reset reden"
#define LANG_CLOCK "horloge"
#define LANG_LDR_VALUE "LDR-waarde"
#define LANG_HUMIDITY "vochtigheid"
#define LANG_AIRPRESSURE "luchtdruk"
#define LANG_AIRPRESSUREDIFF "luchtdrukverschil"
#define LANG_AIRPRESSURETHRES "drukdrempels"

#define LANG_OW_LASTUPDATE "Laatste update"
#define LANG_INFOSUNSETRISE "Zonsopgang/zonsondergang"
#define LANG_MODECOUNT "ModeCount per dag"
#define LANG_LASTTRANS "Laatste overgang"

#define LANG_SNAKE "Snake"
#define LANG_TETRIS "Tetris"
#define LANG_BRICKS "Bricks"
#define LANG_4GEWINNT "4 overwinningen"
#define LANG_MEMORY1 "Dierlijk geheugen"
#define LANG_MEMORY2 "Muziek geheugen"
#define LANG_MEMORY3 "ABBA geheugen"

#define LANG_HTMLLANG "nl"
#define LANG_EXPLORER "woord klok bestandsbeheerder"
#define LANG_FORMATCONF "Echt formatteren? Alle gegevens gaan verloren."
#define LANG_NOSPACE "Onvoldoende vrij geheugen"
#define LANG_FILESIZE "bestandsgrootte"
#define LANG_FOLDER "naam van de map"
#define LANG_SURE "zeker?"
#define LANG_CHAR_NOT_ALLOW "Karakters &#8220; % & / : ; \\ zijn niet toegestaan."
#define LANG_FSUSED "bezet"
#define LANG_FSTOTAL "In totaal"

#endif
//Ende FRONTCOVER_NL
//########################################################################################################################

#endif
