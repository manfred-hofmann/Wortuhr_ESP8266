//******************************************************************************
// Audio.cpp
//******************************************************************************


#include "Audio.h"

#ifdef AUDIO_SOUND
uint8_t VOLINTENSIT[25] = {AUDIO_H00,AUDIO_H01,AUDIO_H02,AUDIO_H03,AUDIO_H04,AUDIO_H05,AUDIO_H06,AUDIO_H07,AUDIO_H08,AUDIO_H09,AUDIO_H10,AUDIO_H11,AUDIO_H12,\
                           AUDIO_H13,AUDIO_H14,AUDIO_H15,AUDIO_H16,AUDIO_H17,AUDIO_H18,AUDIO_H19,AUDIO_H20,AUDIO_H21,AUDIO_H22,AUDIO_H23,AUDIO_H24};
//uint8_t VOLUME_ALT = 0;

//******************************************************************************
// Temperaturansage
//******************************************************************************
void Temperaturansage(int ANSAGEBASE, bool in_out, float fTemperature, uint8_t setvolume)
{
  int vKfTemperature = int(fTemperature);
  float fnKfTemperature;
  int nKfTemperature;
  int AUDIO_FILENR;
  
  fnKfTemperature = ( fTemperature - float(vKfTemperature)) * 10.0;
  nKfTemperature = int(fnKfTemperature);
  vKfTemperature = abs(vKfTemperature);
  nKfTemperature = abs(nKfTemperature);

  if ( in_out )
  {
    AUDIO_FILENR = ANSAGEBASE + 34;
  }
  else
  {
    AUDIO_FILENR = ANSAGEBASE + 36;
  }
  Play_MP3(AUDIO_FILENR,true,setvolume);

  if (fTemperature > 0 && fTemperature < 5 )
  {
    AUDIO_FILENR = ANSAGEBASE + 53; //Plus
    if ( !MODE_BUTTON_BOOL ) {
      Play_MP3(AUDIO_FILENR,true,setvolume);
    }
  }
    if (fTemperature < 0  )
  {
    AUDIO_FILENR = ANSAGEBASE + 54; //Minus
    if ( !MODE_BUTTON_BOOL ) {
      Play_MP3(AUDIO_FILENR,true,setvolume);
    }
  }

  AUDIO_FILENR = ANSAGEBASE + 200 + vKfTemperature;
    if ( !MODE_BUTTON_BOOL ) {
      Play_MP3(AUDIO_FILENR,true,setvolume);
    }
  AUDIO_FILENR = ANSAGEBASE + 55; //Komma
    if ( !MODE_BUTTON_BOOL ) {
      Play_MP3(AUDIO_FILENR,true,setvolume);
    }
  AUDIO_FILENR = ANSAGEBASE + 200 + nKfTemperature;
    if ( !MODE_BUTTON_BOOL ) {
      Play_MP3(AUDIO_FILENR,true,setvolume);
    }
   if ( !MODE_BUTTON_BOOL ) {
    AUDIO_FILENR = ANSAGEBASE + 58; //Grad
    Play_MP3(AUDIO_FILENR,true,setvolume);
   }
}

//******************************************************************************
// Humidityansage
//******************************************************************************
void Humidityansage(int ANSAGEBASE, bool in_out, float fHumidity, uint8_t setvolume)
{
  int vfHumidity = int(fHumidity + 0.5);
  int AUDIO_FILENR;
if ( in_out )
  {
    AUDIO_FILENR = ANSAGEBASE + 35;
  }
  else
  {
    AUDIO_FILENR = ANSAGEBASE + 37;
  }
  
  Play_MP3(AUDIO_FILENR,true,setvolume);

  AUDIO_FILENR = ANSAGEBASE + 200 + vfHumidity;
  if ( vfHumidity == 100 ) AUDIO_FILENR = ANSAGEBASE + 301;
  if ( vfHumidity == 1 ) AUDIO_FILENR = ANSAGEBASE + 41;
    if ( !MODE_BUTTON_BOOL ) {
      Play_MP3(AUDIO_FILENR,true,setvolume);
    }
   if ( !MODE_BUTTON_BOOL ) {
    AUDIO_FILENR = ANSAGEBASE + 56; //Prozent
    Play_MP3(AUDIO_FILENR,true,setvolume);
   }
}

//******************************************************************************
// Zeitansage
//******************************************************************************
void Zeitansage(int ANSAGEBASE, uint8_t setvolume)
{
  int stunden = hour();
  int minuten = minute();
  int AUDIO_FILENR;
  if (stunden == 0) stunden = 24;
  AUDIO_FILENR = ANSAGEBASE + stunden;
  Play_MP3(AUDIO_FILENR,true,setvolume);
  if ( minuten > 0 ) {
    if ( !MODE_BUTTON_BOOL ) {
      AUDIO_FILENR = ANSAGEBASE + 200 + minuten;
      Play_MP3(AUDIO_FILENR,true,setvolume);
     }
  }
}
//******************************************************************************
// Wochentagansage
//******************************************************************************
void Wochentagansage(int ANSAGEBASE, uint8_t setvolume)
{
  int wochentag = weekday();
  int AUDIO_FILENR;
  
  AUDIO_FILENR = ANSAGEBASE + 62; // heute ist
  Play_MP3(AUDIO_FILENR,true,setvolume);
  if ( !MODE_BUTTON_BOOL ) {
    AUDIO_FILENR = ANSAGEBASE + 140 + wochentag;
    Play_MP3(AUDIO_FILENR,true,setvolume);
  }
}
//******************************************************************************
// Datumsansage
//******************************************************************************
void Datumsansage(int ANSAGEBASE, uint8_t setvolume)
{
  int tag = day();
  int monat = month();
  int jahr = year();
  int jahr2;
  int AUDIO_FILENR;
  AUDIO_FILENR = ANSAGEBASE + 63; //der
  Play_MP3(AUDIO_FILENR,true,setvolume);
  AUDIO_FILENR = ANSAGEBASE + 100 + tag;
  if ( !MODE_BUTTON_BOOL ) {
     Play_MP3(AUDIO_FILENR,true,setvolume);
  }
     AUDIO_FILENR = ANSAGEBASE + 150 + monat;
  delay(100);
  if ( !MODE_BUTTON_BOOL ) {
    Play_MP3(AUDIO_FILENR,true,setvolume);
  }
  if ( !MODE_BUTTON_BOOL ) {
    if (jahr < 2100) { 
      AUDIO_FILENR = ANSAGEBASE + 60;
      jahr2 = jahr - 2000;
      Play_MP3(AUDIO_FILENR,true,setvolume);
      AUDIO_FILENR = ANSAGEBASE + 200 + jahr2;
      Play_MP3(AUDIO_FILENR,true,setvolume);
    }
    if (jahr == 2100) {
      AUDIO_FILENR = ANSAGEBASE + 61;
      Play_MP3(AUDIO_FILENR,true,setvolume);
    }
    if (jahr > 2100) {
      AUDIO_FILENR = ANSAGEBASE + 61;
      jahr2 = jahr - 2100;
      Play_MP3(AUDIO_FILENR,true,setvolume);
      AUDIO_FILENR = ANSAGEBASE + 200 + jahr2;
      Play_MP3(AUDIO_FILENR,true,setvolume);
    }
  }
}
//******************************************************************************
// Play MP3 Sound
//******************************************************************************
void Play_MP3(int filenr, bool warte_bis_fertig, uint16_t setvolume)
{
  uint16_t vol100; 
  uint8_t vol30;
  int tout;
  int stunde = hour();
  bool preaudioaktiv;
  if ( setvolume > 0 ) {
    vol100 = setvolume;
  }
  else {
    vol100 = settings.mySettings.volume;
  }


if ( settings.mySettings.weekendlater ) 
{
// Samstag und Sonntag werden wir zwischen 5 und 11 Uhr 2 Stunden später lauter
  if ( weekday() == 1 || weekday() == 7 ) {
    if ( stunde > 4 && stunde < 12 ) {
      stunde = stunde - 2;
    }
  }
}

 
  vol30 = (int) ( (float)3/10 * (float)vol100 * (float)VOLINTENSIT[stunde]/100 ) ; // max Lautstärke ist 30
  if ( vol30 > 30 ) {
    vol30 = 30;
  }
#ifdef DEBUG_AUDIO
      Serial.printf("PlayMP3 File: %i  Volume100: %i %% VOLINTENSIT: %i %% -> Volume30: %i\r\n", filenr, vol100, VOLINTENSIT[stunde],  vol30);
#endif
  if ( vol30 != VOLUME_ALT ) {
    Mp3Player.volume(vol30);
    VOLUME_ALT = vol30;
  }
  if (digitalRead(PIN_AUDIO_BUSY) ) preaudioaktiv = false; else preaudioaktiv = true;
  
  Mp3Player.playMp3Folder(filenr);

//warte_bis_fertig = false;

  if ( warte_bis_fertig ) 
  {
    if ( preaudioaktiv ) 
    {

      tout = 0;
      while (!digitalRead(PIN_AUDIO_BUSY) && tout < 200 )  // Schleife bis busy aus ist ( Sound war vorher aktiv)
      {
       delay(10);
       tout++;
      } 
#ifdef DEBUG_AUDIO
      Serial.printf("Sound war vorher aktiv! Zu Ende nach %i ms\n",tout*10);
#endif     
    }
    
    tout = 0;
    while (digitalRead(PIN_AUDIO_BUSY) && tout < 300 )  // Schleife bis busy an ist ( Sound wurde gestartet)
    {
     delay(10);
     tout++;
    }
#ifdef DEBUG_AUDIO
      Serial.printf("Sound wurde nach %i ms gestartet\n",tout*10);
#endif 
    tout = 0;
    while (!digitalRead(PIN_AUDIO_BUSY) && tout < 300 ) // Schleife bis busy aus ist ( Sound ist zu ende)
    {
      delay(10);
      tout++;
      if ( MODE_BUTTON_BOOL ) 
      {
        Mp3Player.playMp3Folder(99); //stop
        delay(300);
        break;
      }
    }
    #ifdef DEBUG_AUDIO
      Serial.printf("PlayMP3 Stop nach %i ms\n",tout*10);
      if ( tout > 280 )  Serial.println(F( "Evtl. keinen Busy Pin angeschlossen!"));
    #endif
  }
}

void ZahltoAudioBuffer(int ansagebase, int zahl)
{
  bool x;
  int gzahl;
  #ifdef DEBUG_AUDIO
  Serial.print("ZahltoAudioBuffer:");
  Serial.println(zahl);
  #endif
  if ( zahl == 0 ) 
  {
    AudioBufferIn(ansagebase + 200); // Null
  }
  else
    {
    if ( zahl < 0 ) 
    { 
      AudioBufferIn(ansagebase + 54); //Minus
      zahl = zahl * -1;
    }
    if ( zahl > 999 ) 
    {
      gzahl = zahl - ( zahl % 1000);
      AudioBufferIn(ansagebase + 310 + gzahl/1000); // Tausender
      zahl = zahl - gzahl;
    }
    if ( zahl > 99 ) 
    {
      gzahl = zahl - ( zahl % 100);
      AudioBufferIn(ansagebase + 300 + gzahl/100); // Hunderter
      zahl = zahl - gzahl;
    }
    if ( zahl > 0 ) AudioBufferIn(ansagebase + 200 + zahl); // Zehner
  }
}


// IO-Buffer zum Einlesen der Soundfiles
#define AUDIO_BUFFER_SIZE 8
#define AUDIO_BUFFER_MASK (AUDIO_BUFFER_SIZE-1)
struct AudioBuffer {
  uint16_t data[AUDIO_BUFFER_SIZE];
  uint8_t read; // zeigt auf das Feld mit dem ältesten Inhalt
  uint8_t write; // zeigt immer auf leeres Feld
} audiobuffer = {{}, 0, 0};

void AudioBufferIn(uint16_t audiofilenr)
{
#ifdef DEBUG_AUDIO
  Serial.printf("AudioBufferIn: value: %i, write %i read %i\n", audiofilenr, audiobuffer.write, audiobuffer.read);
#endif 
  uint16_t next = ((audiobuffer.write + 1) & AUDIO_BUFFER_MASK);

//  if (audiobuffer.read == next)
//    return false; // voll

  audiobuffer.data[audiobuffer.write] = audiofilenr; 
  audiobuffer.write = next;

//  return true;
}

bool busypinprev = false;
uint8_t soundaktiv = 0;

uint8_t PlayAudioBuffer(uint16_t setvolume)
{
  uint16_t audiofile = 0;
  if ( soundaktiv == 0 && digitalRead(PIN_AUDIO_BUSY) )
  {
    if (audiobuffer.read == audiobuffer.write)
    {
  #ifdef DEBUG_AUDIO
    Serial.println("PlayAudioBuffer: kein Sound zu abspielen im Buffer!");
  #endif       
      return 0; // kein Sound zu abspielen im Buffer 
    }
    
    audiofile = audiobuffer.data[audiobuffer.read];
  #ifdef DEBUG_AUDIO
    Serial.printf("PlayAudioBuffer: audiofile: %i, write %i read %i\n", audiofile, audiobuffer.write, audiobuffer.read);
  #endif 
    audiobuffer.read = (audiobuffer.read+1) & AUDIO_BUFFER_MASK;
    soundaktiv = 30;      // entspricht ca. 1,5 Sekunden bis Timeout
    busypinprev = digitalRead(PIN_AUDIO_BUSY);
    BusyPinCheck.attach_ms(50,busypincheck);
    Play_MP3(audiofile, false, setvolume);
    return 2; // Sound wurde gestartet
  }
  else
  {
  #ifdef DEBUG_AUDIO
    Serial.println("PlayAudioBuffer: alter Sound wird noch gespielt!");
  #endif 
    return 1; //alter Sound wird noch gespielt
  }
}

bool Soundaktiv()
{
  if ( soundaktiv == 0 && digitalRead(PIN_AUDIO_BUSY) )
  return false;
  else
  return true;
}

void AudioBufferClear()
{
  for(uint8_t i=0; i<AUDIO_BUFFER_SIZE; i++) {
    audiobuffer.data[i]=0;
  }
  audiobuffer.read = 0;
  audiobuffer.write = 0;
}

void busypincheck()
{
  soundaktiv--;
  if ( busypinprev && !digitalRead(PIN_AUDIO_BUSY))
  {
    soundaktiv=0;
  }
  busypinprev = digitalRead(PIN_AUDIO_BUSY);
  if ( soundaktiv == 0 ) 
  {
    BusyPinCheck.detach();
#ifdef DEBUG_AUDIO
    Serial.println(F("Sound gestartet"));
#endif
  } 
}



#endif
