/******************************************************************************
Renderer.h
******************************************************************************/

#ifndef RENDERER_H
#define RENDERER_H

#include <Arduino.h>
#include "Configuration.h"
#include "Languages.h"
#include "Letters.h"
#include "Modes.h"
#include "Numbers.h"
#include "Words.h"
#include "Settings.h"

extern Settings settings;
extern String WEB_Uhrtext;

enum eTextPos : uint8_t
{
	TEXT_POS_TOP,
	TEXT_POS_MIDDLE = 2,
	TEXT_POS_BOTTOM = 5
};

class Renderer
{
public:
	Renderer();

	void setHours(uint8_t hours, boolean glatt, uint16_t matrix[]);
	void setTime(uint8_t hours, uint8_t minutes, uint16_t matrix[]);
	void setCorners(uint8_t minutes, uint16_t matrix[]);
	void setAlarmLed(uint16_t matrix[]);
	void deactivateAlarmLed(uint16_t matrix[]);
	void clearEntryWords(uint16_t matrix[]);
	void setSmallText(String menuText, eTextPos textPos, uint16_t matrix[]);
	void setAMPM(uint8_t hours, uint16_t matrix[]);
	void setPixelInScreenBuffer(uint8_t x, uint8_t y, uint16_t matrix[]);
	void unsetPixelInScreenBuffer(uint8_t x, uint8_t y, uint16_t matrix[]);
	void clearScreenBuffer(uint16_t matrix[]);
	void setAllScreenBuffer(uint16_t matrix[]);

private:
	boolean isNumber(char symbol);
#if defined(FRONTCOVER_FR)
	void FR_hours(uint8_t hours, uint16_t matrix[]);
#endif
#if defined(FRONTCOVER_IT)
	void IT_hours(uint8_t hours, uint16_t matrix[]);
#endif
#if defined(FRONTCOVER_ES)
	void ES_hours(uint8_t hours, uint16_t matrix[]);
#endif
};

#endif
