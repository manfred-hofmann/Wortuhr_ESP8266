/******************************************************************************
Colors.h
******************************************************************************/

#ifndef COLORS_H
#define COLORS_H

enum eColorChange : uint8_t
{
	COLORCHANGE_NO,                      // 0
	COLORCHANGE_FIVE,                    // 1
	COLORCHANGE_HOUR,                    // 2
	COLORCHANGE_DAY,                     // 3
  COLORCHANGE_MAIN,                    // 4
	COLORCHANGE_COUNT = COLORCHANGE_DAY
};

enum eColor : uint8_t
{
	WHITE,
	RED,
	RED_25,
	RED_50,
	ORANGE,
	YELLOW,
	YELLOW_25,
	YELLOW_50,
	GREENYELLOW,
	GREEN,
	GREEN_25,
	GREEN_50,
	MINTGREEN,
	CYAN,
	CYAN_25,
	CYAN_50,
	LIGHTBLUE,
	BLUE,
	BLUE_25,
	BLUE_50,
	VIOLET,
	MAGENTA,
	MAGENTA_25,
	MAGENTA_50,
	PINK,
	COLOR_COUNT = PINK
};

struct color_s
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

const color_s defaultColors[] =
{
	{ 0xFF, 0xFF, 0xFF }, // 00 WHITE

	{ 0xFF, 0x00, 0x00 }, // 01 RED
	{ 0xFF, 0x40, 0x40 }, // 02 RED_25
	{ 0xFF, 0x80, 0x80 }, // 03 RED_50

	{ 0xFF, 0x70, 0x00 }, // 04 ORANGE

	{ 0xFF, 0xFF, 0x00 }, // 05 YELLOW
	{ 0xFF, 0xFF, 0x40 }, // 06 YELLOW_25
	{ 0xFF, 0xFF, 0x80 }, // 07 YELLOW_50

	{ 0x7F, 0xFF, 0x00 }, // 08 GREENYELLOW

	{ 0x00, 0xFF, 0x00 }, // 09 GREEN
	{ 0x40, 0xFF, 0x40 }, // 10 GREEN_25
	{ 0x80, 0xFF, 0x80 }, // 11 GREEN_50

	{ 0x00, 0xFF, 0x7F }, // 12 MINTGREEN

	{ 0x00, 0xFF, 0xFF }, // 13 CYAN
	{ 0x40, 0xFF, 0xFF }, // 14 CYAN_25
	{ 0x80, 0xFF, 0xFF }, // 15 CYAN_50

	{ 0x00, 0x7F, 0xFF }, // 16 LIGHTBLUE

	{ 0x0F, 0x0F, 0xFF }, // 17 BLUE
	{ 0x40, 0x40, 0xFF }, // 18 BLUE_25
	{ 0x80, 0x80, 0xFF }, // 19 BLUE_50

	{ 0x7F, 0x00, 0xFF }, // 20 VIOLET

	{ 0xFF, 0x00, 0xFF }, // 21 MAGENTA
	{ 0xFF, 0x40, 0xFF }, // 22 MAGENTA_25
	{ 0xFF, 0x80, 0xFF }, // 23 MAGENTA_50

	{ 0xFF, 0x00, 0x7F }  // 24 PINK
};

#endif
