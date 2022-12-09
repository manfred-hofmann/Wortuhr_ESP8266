# Wortuhr_ESP8266  
Wortuhr mit ESP8266 WeMos D1 mini und NeoPixel WS2812B LEDs mit  
mp3 Sounds, Animationen, Transitions, Events und Spiele, Webzugriff, Multlingual  
-----------------------------------------------------------------
## Bedienungsanleitung:  
https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/main/Bedienungsanleitung_Wortuhr_mp3_20221222.pdf  

## Manual:  
https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/main/Manual_Wordclock_mp3_20221222.pdf  

## Sonstiges:  
* Mehrsprachig: de, ch, en, fr, es, it, nl  (Sprach-Layout wird in configuration.h ausgewählt)  
* Automatischer W-Lan Reconnect.  
* Mondphase wird in Abwechslung der Temp. und Datumsanzeige angezeigt.  
* Die Minuten LED können nun eine eigene Farbe haben.  
* Silvester CountDown.  
* Zwei Eingabe Taster sind möglich: On/Off und Mode. 
  Diese sind per Touch oder als physikalischer Taster in configuration.h einstellbar.  
* Sonnenauf-/untergangsanimation   
* Ausführen von Adhoc Events mit http-Request:   
z.B.: http://wortuhr-ip/setEvent?text=I+love+you&color=1&audio=701&preani=HERZ&postani=HERZ  


## Temperatur und Luftdruck:  
* Als Temp. Sensor hatte ich einen BME280.  
* Aufzeichnen der Temperatur und Anzeige im Webfrontend.  
* Aufzeichnen des Luftdrucks und Anzeige im Webfrontend.   
* Wetterlage wird als Animation angezeigt.  


## Transitions:  
* 17 Transitions (Spirale, Matrix, Zur Mitte, u.s.w.) und diese einzeln oder per Zufall angewählt.   
* Alle Transitions sind jetzt 2 farbig.  
  D.h. z.B. Übergang 'nach links': die Buchstaben der 'alten' Zeit verschwinden mit der 'alten' Farbe nach links,  
  während rechts die Buchstaben der 'neuen' Zeit mit der 'neuen' Farbe reinkommen.  
  (sichtbar natürlich nur wenn die neue Farbe unterschiedlich zur alten Farbe ist. z.B. neue Farbe alle 5 Minuten)  


## Sound:   
* Anschluss eines MP3 Moduls (https://www.az-delivery.de/products/mp3-player-modul?_pos=1&_sid=9812a53bb&_ss=r) um der Uhr das Sprechen und verschiedene Sound zu entlocken. (Sounds werden einfach auf einer SD Karte nummeriert abgespeichert)  
* Verschiedene Stunden Sounds (Gong, Kuckuck, Vicki sagt die Uhrzeit , Hans sagt die Uhrzeit, usw.) per Settings einstellbar oder pro Tag ein anderer Sound.  
* Soundlautstärke in abh. der Tages/Nachtzeit.  
* Uhr erklärt nun im AP Mode was zu tun ist.  
* zusätzliche Stundensound (Westminster, alte Uhr, Kirche, usw.)  


## Webfrontend:   
* Alle CSS Files sind im LittlefS des ESP abgelegt.  
* Eigenes Wortuhr Favicon eingefügt.  
* Werte auf Info Seite zur Einsicht aller wichtigen Parameter   
* Sonnenaufgangs- und Sonnenuntergangszeiten  
* Wettersymbole  


## Animationen:  
* Es können eigene Animationen für Deine Events erstellt werden.  
![Herz](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/HERZ.gif "Herz")  
* Über den eingebauten Animationseditor können Animationen erstellt werden  
![Animationsmenue](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Animationsmenue.jpg "Animationsmenue")  
![Animationsmenue2](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Animationsmenue2.jpg "Animationsmenue2")  
* Animationen mit bis zu 25 Frames möglich  
* Dadurch der gif2animation Konverter von kollabierer (https://www.kollabierer.de/farbe) direkt nutzbar.   
* Animationen mit Namen ZHHMM werden zur jeweiligen Stunde und Minute angezeigt (z.B. Z1200 startet eine Animation um 12 Uhr)  
* Animation mit Name ALARM wird während des Alarms angezeigt.  
![Alarm](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/ALARM.gif "Alarm")   
* Alle Animationen werden im SPIFFS unter dem Name ani_ANINAME.json gespeichert und können über den Dateimanager gesichert/kopiert werden.  


## Events:   
* Verschiedene Melodien werden passend zu den Events abgespielt.  
* Events werden über die Weboberfläche gepflegt.  
![Events](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Events.jpg "Events") 
* Es können eigene Animationen für Deine Events erstellt werden.  
* Alle Events werden im SPIFFS unter dem Namen events.json abgelegt und können über den Dateimanager gesichert/kopiert werden.  


## Spiele:  
* 7 Wortuhrspiele integriert: 
Snake   
![Snake](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/snake.gif "Snake")  
Tetris  
![Tetris](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/tetris.gif "Tetris")  
Bricks  
![Bricks](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/bricks.gif "Bricks")  
4 gewinnt  
![4gewinnt](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/4gewinnt.gif "4Gewinnt")  
Tier Memory / Musik Memory /ABBA Memory  
Ein Spiel für die ganze Familie!  
Es können bis zu 4 Spieler spielen  
![Memory_01](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/memory_01.jpg "Memory_01")  
Spieler müssen sich mit der URL  
 http://wortuhr-ip/spieler  
am Spiel anmelden.  
Jeder Spieler bekommt eine andere Farbe zugewiesen.   
Spieler2:  
![Memory_02](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/memory_02.jpg "Memory_02")  
Spieler3:  
![Memory_02](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/memory_03.jpg "Memory_03")  
Spieler4:  
![Memory_04](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/memory_04.jpg "Memory_04")  
Ziel ist es ein passendes Sound/Musik Paar zu finden:  
![Memory_05t](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/memory_05t.jpg "Memory_05t")  
Nach einem Spiel müssen die einzelnen Mitspieler jeweils nur die WebSeite refreshen um sich wieder anzumelden.  
Welche Spieler angemeldet sind erkennt man in der Hauptspielseite an den farbigen Spielerpunkten (siehe oben).  
  
Viel Spaß mit den Spielen!  
    
* Sichern der Highscores im EEPROM    


## Settings:  
* Eingabe des Zeitservers über die Settings.  
* Systemname in Settings.    
* Hier ist der Dateimanager für LittleFS.  
![LittleFS](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/LittleFS_Explorer.png "LittleFS")
* Angabe der Location und Höhe über 0 in Settings (wird für die WetterAPI und Berechnung des Luftdrucks auf Meereshöhe benötigt).  
* Hier API-Key von OpenWeather eintragen!  
* Eingabe des Automodeintervall in Settings  ( Intervall wie oft verschiedene Modes Wetter, Temperatur, Mondphase... angezeigt werden)  
* Highscores können hier gelöscht werden.  
* Stundensound pro Wochentag einstellbar und Testmöglichkeit der Sounds.  
* "Wochenend Lautstärke Erhöhung" wählbar. Am Wochenende zwischen 5 und 11 Uhr 2 h später lauter.  
* Sprecher Vicki oder Hans.  
* Stundenansage Vicki/Hans 12h oder 24h Format  
* definieren einer beliebigen Hintergrundfarbe  
* und vieles mehr  


## System:  
* Neustart mit <UHR-IP>/reboot  
* W-Lan Daten löschen mit <UHR-IP>/wifireset  
* Wortuhr-API mit <UHR-IP>/apidata  
* compilierbar auch ohne mp3 Player (#define AUDIO_SOUND in der Configuration kommentieren)    
* WLAN Empfangsstärke wird auf der Infoseite angezeigt  
* Anzeige der IP-Adresse im erweiterten Testmenü (nach den Sekunden nochmal die Taste Mode drücken. 
Hier gibt es dann :
IP-Adresse, Matrixtest und Farbentests  

## Schaltplan:
https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/main/Platine_Plan_Wortuhr_mp3.pdf  

## LED-Layout: 
Es können verschiedene LED Layouts verwendet werden.  
In der configuration.h sind 4 voreingestellte Layouts zu finden:  

// Das LED Layout (Siehe in LedDriver.cpp):  
#define LED_LAYOUT_HORIZONTAL_2  
//#define LED_LAYOUT_VERTICAL_1  
//#define LED_LAYOUT_VERTICAL_2  
//#define LED_LAYOUT_VERTICAL_3  

Die Layouts sind in LedDriver.cpp  definiert.
Hier können nach belieben auch eigene angelegt werden.
Hierbei ist zu beachten:  
die ersten 10 Zeilen in ledMap sind die LEDs für die Wörter.
die letzte Zeile sind die Minuten LEDs angefangen links oben, rechts oben, rechts unten, links unten und die Alarm LED.  
Die Zahlen entsprechen der LED-Nummer in der LED-Kette:   
```
#ifdef LED_LAYOUT_VERTICAL_2
    uint8_t ledMap[] = {
          9,  10,  29,  30,  49,  50,  69,  70,  89,  90, 109,
          8,  11,  28,  31,  48,  51,  68,  71,  88,  91, 108,
          7,  12,  27,  32,  47,  52,  67,  72,  87,  92, 107,
          6,  13,  26,  33,  46,  53,  66,  73,  86,  93, 106,
          5,  14,  25,  34,  45,  54,  65,  74,  85,  94, 105,
          4,  15,  24,  35,  44,  55,  64,  75,  84,  95, 104,
          3,  16,  23,  36,  43,  56,  63,  76,  83,  96, 103,
          2,  17,  22,  37,  42,  57,  62,  77,  82,  97, 102,
          1,  18,  21,  38,  41,  58,  61,  78,  81,  98, 101,
          0,  19,  20,  39,  40,  59,  60,  79,  80,  99, 100,
      112,110,114,113,111
    };
#endif
```

Hier ein Beispiel Layout:  
![LED-Layout](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/LED-Beispiel-Layout.jpg "LED-Layout")   

Möchte man auf die "Alarm LED" verzichten, so muss in der configuration.h die Anzahl der LEDs angepasst werden:  
#define NUMPIXELS 114 -> ohne eigen Alarm LED  
#define NUMPIXELS 115 -> mit Alarm LED  

## ESP:  
z.B.: https://de.aliexpress.com/item/1005004547410607.html?spm=a2g0o.order_list.0.0.21ef5c5ftzOASF&gatewayAdapt=glo2deu  
D1 MINI WEMOS Pro 4M   

Arduino IDE Einstellungen:  
Board: "LOLIN(WEMOS) D1 R2 & mini"  
CPU Frequenz auf 160 MHz  
Flash Size 4MB ( FS:2MB OTA~1019KB)  
SLL Support Basic  

- besser  
D1 MINI WEMOS Pro 16M  
Arduino IDE Einstellungen:  
Board: "LOLIN(WEMOS) D1 pro"  
CPU Frequenz auf 160 MHz  
Flash Size: 16MB ( FS:14MB OTA~1019KB)  
SLL Support Basic  

## Inbetriebnahme:  
* ESP8266 Board Version >= 3.0.2    

* folgende Libraries werden benötigt (min. Versionen) (alle zu finden unter Bibliotheken verwalten):  
    * Arduino_JSON - Version 0.1.0  
	* BME280 - Adafruit BME280 Version 2.1.4  
	* MP3-Player - DFRobotDFPlayer Version 1.0.5  
	* Adafruit Unified Sensor Version 1.1.4  
	* Adafruit Neopixel: Version 1.10.6  
	* SunRise: Version 2.0.2 by Cyrus Rahman   
	* MP3-Player - DFRobotDFPlayer Version 1.0.5  
	* ArduinoOTA 1.0.3  
	* TimeLib 1.6.0  by Michael Margolis
	* Ticker 4.4.0 by Stefan Staub  
	
optional:  
    * IRremoteESP8266 2.7.4 by David Conran,..  
    * DS3232RTC by Jack Christensen Version 2.0.1   
	
	* Openweather API-Key (https://openweathermap.org/) für die Wetterinformationen.  
* Die mp3 Files (Sound) in den Ordner "mp3" auf die SD-Karte kopieren welche in den mp3-Player kommt. Es reicht eine 4GB Karte.
* Software mit Arduino IDE (min. Version 1.8.12) auf den ESP8266 laden.   


* ESP8266 starten und mit dem Handy das WLAN der Wortuhr (Wortuhr) suchen und anmelden.  
* Dann sollte automatisch der Browser starten. Hier die WLAN Zugangsdaten eingeben.  
(Falls der Browser nicht startet, die Default IP des AP ist 192.168.4.1)  
* Danach den ESP8266 neustarten und über die Webadresse 

http://<wortuhr-ip>/fs   
 
den Fileexplorer aufrufen um das LittleFS zu füllen.  

1. LittleFS ist am Anfang leer:   
<img src="https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Wortuhr_Dateimanager_leer.jpg" width=50"/>
2. Vor dem Upload root:   
Alle Dateien vom data Verzeichnis auswählen und uploaden:  
![LittleFS_02](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Wortuhr_Dateimanager_vor_upload_root.jpg "LittleFS_02"){ width=50% }  
3. Upload der Files im Serial Monitor:  
![LittleFS_03](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Wortuhr_Dateimanager_upload_files.jpg "LittleFS_03")  
4. nach Upload root:  
![LittleFS_04](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Wortuhr_Dateimanager_nach_upload_root.jpg "LittleFS_04")  
5. Dann noch das Web Verzeichnis  
web Verzeichnis anwählen:  
![LittleFS_05](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Wortuhr_Dateimanager_vor_upload_web1.jpg "LittleFS_05")  
Alle Dateien vom data/web Verzeichnis auswählen:  
![LittleFS_06](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Wortuhr_Dateimanager_vor_upload_web2.jpg "LittleFS_06")  
6. Nach Upload Web-Verzeichnis:  
![LittleFS_07](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Wortuhr_Dateimanager_nach_upload_web.jpg "LittleFS_07")  
7. Upload andere Sprachen (optional):  
Falls eine andere Sprache als deutsch gewählt wurde, einfach den Inhalt des jeweiligen web Verzeichnisses (web_ch, web_en, web_es, web_fr, web_nl)  
in den web Ordner übertragen. Dazu den web Ordner nochmal auswählen:  
![LittleFS_08](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Wortuhr_Dateimanager_vor_upload_web1.jpg "LittleFS_08")  
Und alle Dateien des jeweiligen web_xx Ordner auswählen und uploaden.  

Hier nochmal wie beschrieben:  
![LittleFS_Film](https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/Load_LittleFS_2.gif "LittleFS_Film") 

* Danach den ESP8266 neustarten und über die Webadresse des ESP in den Menüpunkt Settings die Wortuhr anpassen.  
Hier sind folgende Punkte wichtig:
- Systemname    
- Zeitserver  
- API-Key von OpenWeather + Standort + Höhe über Meeresspiegel.  


* __Evtl. nochmal die configuration.h durchgehen und die Einstellungen den eigenen Gegebenheiten anpassen!__   
* restliche Einstellungen sind auf der Settings Seite zu finden  

Eine ausführliche Bedienungsanleitung ist hier zu finden:  
## Bedienungsanleitung:  
https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/main/Bedienungsanleitung_Wortuhr_mp3_20221222.pdf  

## Manual (English):  
https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/main/Manual_Wordclock_mp3_20221222.pdf   
-----
* Hier mein Aufbau:
<img src="https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/WU_links.jpg" width="233" height="472" />  
<img src="https://github.com/manfred-hofmann/Wortuhr_ESP8266/blob/bv.20221222/pic/WU_unten.jpg" width="751" height="370" />  
  
-----  
  
Alles weiter findet sich auf  
  http://diskussion.christians-bastel-laden.de/viewtopic.php?f=23&t=3846&sid=a6ac77fb774177c3168e12998a42e791  
Ein Beispielvideo einer Vorvorvorversion ist hier zu sehen:   
https://www.youtube.com/watch?v=rQZoOGkao-w  

Viel Spaß damit!  

  

