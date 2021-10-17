/******************************************************************************
Languages.h
******************************************************************************/

#ifndef LANGUAGES_H
#define LANGUAGES_H

//enum eLanguage : uint8_t
//{
//	LANGUAGE_DE_DE,
//	LANGUAGE_DE_SW,
//	LANGUAGE_DE_BA,
//	LANGUAGE_DE_SA,
//	LANGUAGE_DE_MKF_DE,
//	LANGUAGE_DE_MKF_SW,
//	LANGUAGE_DE_MKF_BA,
//	LANGUAGE_DE_MKF_SA,
//	LANGUAGE_D3,
//	LANGUAGE_CH,
//	LANGUAGE_CH_GS,
//	LANGUAGE_EN,
//	LANGUAGE_ES,
//	LANGUAGE_FR,
//	LANGUAGE_IT,
//	LANGUAGE_NL,
//	LANGUAGE_COUNT = LANGUAGE_NL
//};

//const char sLanguage[][4] =
//{
//	{ 'D', 'E', ' ', ' ' }, // 00
//	{ 'D', 'E', 'S', 'W' }, // 01
//	{ 'D', 'E', 'B', 'A' }, // 02
//	{ 'D', 'E', 'S', 'A' }, // 03
//	{ 'M', 'K', 'D', 'E' }, // 04
//	{ 'M', 'K', 'S', 'W' }, // 05
//	{ 'M', 'K', 'B', 'A' }, // 06
//	{ 'M', 'K', 'S', 'A' }, // 07
//	{ 'D', '3', ' ', ' ' }, // 08
//	{ 'C', 'H', ' ', ' ' }, // 09
//	{ 'C', 'H', 'G', 'S' }, // 10
//	{ 'E', 'N', ' ', ' ' }, // 11
//	{ 'E', 'S', ' ', ' ' }, // 12
//	{ 'F', 'R', ' ', ' ' }, // 13
//	{ 'I', 'T', ' ', ' ' }, // 14
//	{ 'N', 'L', ' ', ' ' }  // 15
//};

#if defined(FRONTCOVER_EN) || defined(FRONTCOVER_BINARY)
const char sWeekday[][2] =
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
const String Wochentage[] =
{ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" , "Saturday" };  // Wochentage für die Soundauswahl im Web
#endif

#if defined(FRONTCOVER_DE_DE) || defined(FRONTCOVER_DE_SW) || defined(FRONTCOVER_DE_BA) || defined(FRONTCOVER_DE_SA) || defined(FRONTCOVER_D3) || defined(FRONTCOVER_DE_MKF_DE) || defined(FRONTCOVER_DE_MKF_SW) || defined(FRONTCOVER_DE_MKF_BA) || defined(FRONTCOVER_DE_MKF_SA) || defined(FRONTCOVER_CH) || defined(FRONTCOVER_CH_GS)
const char sWeekday[][2] =
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
const String Wochentage[] =
{ "Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag" , "Samstag" };  // Wochentage für die Soundauswahl im Web
#endif

#if defined(FRONTCOVER_ES)
const char sWeekday[][2] =
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
#endif

#if defined(FRONTCOVER_FR)
const char sWeekday[][2] =
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
#endif

#if defined(FRONTCOVER_IT)
const char sWeekday[][2] =
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
#endif

#if defined(FRONTCOVER_NL)
const char sWeekday[][2] =
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
#endif

#endif
