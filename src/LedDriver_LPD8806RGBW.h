/******************************************************************************
LedDriver_LPD8806RGBW.h
******************************************************************************/
#ifndef LEDDRIVER_LPD8806RGBW_H
#define LEDDRIVER_LPD8806RGBW_H

#include "Configuration.h"
#ifdef LED_LIBRARY_LPD8806RGBW
#include "LPD8806RGBW.h"
#include "Colors.h"
#include "Modes.h"
#include "Settings.h"
extern Mode mode;
extern Settings settings;
extern uint8_t brightness;

class LedDriver_LPD8806RGBW
{
public:
	LedDriver_LPD8806RGBW();
	
	void clear();
	void show();
	void setPixel(uint8_t x, uint8_t y, uint8_t color, uint8_t brightness);
	void setPixel(uint8_t num, uint8_t color, uint8_t brightness);
  void setPixelRGB(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue);
  void setPixelRGB(uint8_t num, uint8_t red, uint8_t green, uint8_t blue );

	private:
	LPD8806RGBW *strip;
};

#endif
#endif
