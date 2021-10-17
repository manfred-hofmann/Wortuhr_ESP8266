/******************************************************************************
Events.h
******************************************************************************/
#ifndef EVENTS_H
#define EVENTS_H
#include <Arduino.h>
#include "Configuration.h"
#include "Colors.h"

#include <FS.h>
#include <Arduino_JSON.h>

#define EVENTFILE "/events.json"

typedef struct
{
  bool aktiv;
	uint8_t month;
  uint8_t day;
	String text;
  uint16_t year;
  uint8_t color;
  uint16_t audio_file;
  String preani;
  String postani;
  uint16_t intervall;  // intervall in Minuten
} s_event;


bool loadEvents();
bool saveEvents();

#endif
