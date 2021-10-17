//******************************************************************************
// Audio.h
//******************************************************************************

#ifndef AUDIO_H
#define AUDIO_H

#include <Arduino.h>
#include <TimeLib.h>
#include <Ticker.h>
#include "Configuration.h"
#include "Settings.h"
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

extern Settings settings;
extern DFRobotDFPlayerMini Mp3Player;
extern Ticker BusyPinCheck;
extern bool MODE_BUTTON_BOOL;
extern uint8_t VOLUME_ALT;

void Temperaturansage(int ANSAGEBASE, bool in_out, float fTemperature, uint8_t setvolume);
void Humidityansage(int ANSAGEBASE, bool in_out, float fHumidity, uint8_t setvolume);
void Zeitansage(int ANSAGEBASE, uint8_t setvolume);
void Wochentagansage(int ANSAGEBASE, uint8_t setvolume);
void Datumsansage(int ANSAGEBASE, uint8_t setvolume);
void Play_MP3(int filenr, bool warte_bis_fertig, uint16_t setvolume);

void ZahltoAudioBuffer(int ansagebase, int zahl);
void AudioBufferIn(uint16_t audiofilenr);
uint8_t PlayAudioBuffer(uint16_t setvolume);
void AudioBufferClear();
bool Soundaktiv();
void busypincheck();

#define WETTERSOUNDBASE 410

const uint16_t wettersoundmapping[][2] PROGMEM = {
  {1,200},{1,201},{1,202},{1,230},{1,231},{1,232},       //Gewitter mit Regen
  {2,210},{2,211},{2,212},{2,221},                       //Gewitter
  {3,300},{3,301},{3,302},{3,310},{3,311},{3,312},       //Nieselregen
  {4,500},{4,501},{4,520},                               //leichter Regen
  {5,313},{5,321},{5,501},{5,521},{5,531},               //Regen
  {6,314},{6,502},{6,503},{6,504},{6,522},               //starker Regen
  {7,511},                                               //gefrierender Regen
  {8,600},                                               //leichter Schneefall
  {9,601},{9,602},                                       //Schneefall
  {10,611},{10,615},{10,616},{10,620},{10,621},{10,622}, //Schneeregen
  {11,612},                                              //Graupelschauer
  {12,701},{12,711},{12,731},{12,741},                   //Nebel
  {13,721},                                              //Dunst  
  {14,751},{14,761},{14,762},                            //Staub
  {15,771},{15,781},                                     //Sturm
  {16,800},                                              //klarer Himmel 
  {17,801},{17,802},                                     //leichte Bewölkung
  {18,803},                                              //bewölkt
  {19,804},                                              //stark bewölkt
  {0,0}                                                  //Ende Soundmapping
};

#endif
