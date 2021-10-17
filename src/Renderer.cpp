//******************************************************************************
// Renderer.cpp
//******************************************************************************

#include "Renderer.h"

Renderer::Renderer()
{
}

// Write time to screenbuffer
void Renderer::setTime(uint8_t hours, uint8_t minutes, uint16_t matrix[])
{
#if defined(FRONTCOVER_DE_DE) || defined(FRONTCOVER_DE_SW) || defined(FRONTCOVER_DE_BA) || defined(FRONTCOVER_DE_SA)
		DE_ESIST;
    if (settings.mySettings.itIs) 
    { 
      WEB_Uhrtext = F("Es ist ");
    }
    else 
    { 
      WEB_Uhrtext = "";
    }

		switch (minutes / 5)
		{
		case 0:
			// full hour
			setHours(hours, true, matrix);
			break;
		case 1:
			// 5 nach
			DE_FUENF;
			DE_NACH;
      WEB_Uhrtext += F("f&uuml;nf nach ");
			setHours(hours, false, matrix);
			break;
		case 2:
			// 10 nach
			DE_ZEHN;
			DE_NACH;
      WEB_Uhrtext += F("zehn nach ");
			setHours(hours, false, matrix);
			break;
		case 3:
			// viertel nach
#if defined(FRONTCOVER_DE_SW) || defined(FRONTCOVER_DE_SA)
				DE_VIERTEL;
        WEB_Uhrtext += F("viertel ");
				setHours(hours + 1, false, matrix);
#else
				DE_VIERTEL;
				DE_NACH;
        WEB_Uhrtext += F("viertel nach ");
				setHours(hours, false, matrix);
#endif
			break;
		case 4:
			// 20 nach
#if defined(FRONTCOVER_DE_SA)
				DE_ZEHN;
				DE_VOR;
				DE_HALB;
        WEB_Uhrtext += F("zehn vor halb ");
				setHours(hours + 1, false, matrix);
#else
				DE_ZWANZIG;
				DE_NACH;
        WEB_Uhrtext += F("zwanzig nach ");
				setHours(hours, false, matrix);
#endif
			break;
		case 5:
			// 5 vor halb
			DE_FUENF;
			DE_VOR;
			DE_HALB;
      WEB_Uhrtext += F("f&uuml;nf vor halb ");
			setHours(hours + 1, false, matrix);
			break;
		case 6:
			// halb
			DE_HALB;
      WEB_Uhrtext += F("halb ");
			setHours(hours + 1, false, matrix);
			break;
		case 7:
			// 5 nach halb
			DE_FUENF;
			DE_NACH;
			DE_HALB;
      WEB_Uhrtext += F("f&uuml;nf nach halb ");
			setHours(hours + 1, false, matrix);
			break;
		case 8:
			// 20 vor
#if defined(FRONTCOVER_DE_SA)
				DE_ZEHN;
				DE_NACH;
				DE_HALB;
        WEB_Uhrtext += F("zehn nach halb ");
				setHours(hours + 1, false, matrix);
#else
				DE_ZWANZIG;
				DE_VOR;
        WEB_Uhrtext += F("zwanzig vor ");
				setHours(hours + 1, false, matrix);
#endif
			break;
		case 9:
			// viertel vor
#if defined(FRONTCOVER_DE_SW) || defined(FRONTCOVER_DE_BA) || defined(FRONTCOVER_DE_SA)
				DE_DREIVIERTEL;
        WEB_Uhrtext += F("dreiviertel ");
				setHours(hours + 1, false, matrix);
#else
				DE_VIERTEL;
				DE_VOR;
        WEB_Uhrtext += F("viertel vor ");
				setHours(hours + 1, false, matrix);
#endif
			break;
		case 10:
			// 10 vor
			DE_ZEHN;
			DE_VOR;
      WEB_Uhrtext += F("zehn vor ");
			setHours(hours + 1, false, matrix);
			break;
		case 11:
			// 5 vor
			DE_FUENF;
			DE_VOR;
      WEB_Uhrtext += F("f&uuml;nf vor ");
			setHours(hours + 1, false, matrix);
			break;
		}
    WEB_Uhrtext += F("<br>");
    switch (minutes % 5)
    {
    case 4:
      WEB_Uhrtext += F("&bull;");
    case 3:
      WEB_Uhrtext += F("&bull;");
    case 2:
      WEB_Uhrtext += F("&bull;");
    case 1:
      WEB_Uhrtext += F("&bull;");
    }
#endif

#if defined(FRONTCOVER_DE_MKF_DE) || defined(FRONTCOVER_DE_MKF_SW) || defined(FRONTCOVER_DE_MKF_BA) || defined(FRONTCOVER_DE_MKF_SA)
		DE_MKF_ESIST;
    if (settings.mySettings.itIs) 
    { 
      WEB_Uhrtext = F("Es ist ");
    }
    else 
    { 
      WEB_Uhrtext = "";
    }
		switch (minutes / 5)
		{
		case 0:
			// glatte Stunde
			setHours(hours, true, matrix);
			break;
		case 1:
			// 5 nach
			DE_MKF_FUENF;
			DE_MKF_NACH;
      WEB_Uhrtext += F("f&uuml;nf nach ");
			setHours(hours, false, matrix);
			break;
		case 2:
			// 10 nach
			DE_MKF_ZEHN;
			DE_MKF_NACH;
      WEB_Uhrtext += F("zehn nach ");
			setHours(hours, false, matrix);
			break;
		case 3:
			// viertel nach
#if defined(FRONTCOVER_DE_MKF_SW) || defined(FRONTCOVER_DE_MKF_SA)
				DE_MKF_VIERTEL;
        WEB_Uhrtext += F("viertel ");
				setHours(hours + 1, false, matrix);
#else
				DE_MKF_VIERTEL;
				DE_MKF_NACH;
        WEB_Uhrtext += F("viertel nach ");
				setHours(hours, false, matrix);
#endif
			break;
		case 4:
			// 20 nach
#if defined(FRONTCOVER_DE_MKF_SA)
				DE_MKF_ZEHN;
				DE_MKF_VOR;
				DE_MKF_HALB;
        WEB_Uhrtext += F("zehn vor halb ");
				setHours(hours + 1, false, matrix);
#else
				DE_MKF_ZWANZIG;
				DE_MKF_NACH;
        WEB_Uhrtext += F("zwanzig nach ");
				setHours(hours, false, matrix);
#endif
			break;
		case 5:
			// 5 vor halb
			DE_MKF_FUENF;
			DE_MKF_VOR;
			DE_MKF_HALB;
      WEB_Uhrtext += F("f&uuml;nf vor halb ");
			setHours(hours + 1, false, matrix);
			break;
		case 6:
			// halb
			DE_MKF_HALB;
      WEB_Uhrtext += F("halb ");
			setHours(hours + 1, false, matrix);
			break;
		case 7:
			// 5 nach halb
			DE_MKF_FUENF;
			DE_MKF_NACH;
			DE_MKF_HALB;
      WEB_Uhrtext += F("f&uuml;nf nach halb ");
			setHours(hours + 1, false, matrix);
			break;
		case 8:
			// 20 vor
#if defined(FRONTCOVER_DE_MKF_SA)
				DE_MKF_ZEHN;
				DE_MKF_NACH;
				DE_MKF_HALB;
        WEB_Uhrtext += F("zehn nach halb ");
				setHours(hours + 1, false, matrix);
#else
				DE_MKF_ZWANZIG;
				DE_MKF_VOR;
        WEB_Uhrtext += F("zwanzig vor ");
				setHours(hours + 1, false, matrix);
#endif
			break;
		case 9:
			// viertel vor
#if defined(FRONTCOVER_DE_MKF_SW) || defined(FRONTCOVER_DE_MKF_BA) || defined(FRONTCOVER_DE_MKF_SA)
				DE_MKF_DREIVIERTEL;
        WEB_Uhrtext += F("dreiviertel ");
				setHours(hours + 1, false, matrix);
#else
				DE_MKF_VIERTEL;
				DE_MKF_VOR;
        WEB_Uhrtext += F("viertel vor ");
				setHours(hours + 1, false, matrix);
#endif
			break;
		case 10:
			// 10 vor
			DE_MKF_ZEHN;
			DE_MKF_VOR;
      WEB_Uhrtext += F("zehn vor ");
			setHours(hours + 1, false, matrix);
			break;
		case 11:
			// 5 vor
			DE_MKF_FUENF;
			DE_MKF_VOR;
      WEB_Uhrtext += F("f&uuml;nf vor ");
			setHours(hours + 1, false, matrix);
			break;
		}
    WEB_Uhrtext += F("<br>");
    switch (minutes % 5)
    {
    case 4:
      WEB_Uhrtext += F("&bull;");
    case 3:
      WEB_Uhrtext += F("&bull;");
    case 2:
      WEB_Uhrtext += F("&bull;");
    case 1:
      WEB_Uhrtext += F("&bull;");
    }
#endif

#if defined(FRONTCOVER_D3)
		D3_ESISCH;
		switch (minutes / 5)
		{
		case 0:
			// glatte Stunde
			setHours(hours, true, matrix);
			break;
		case 1:
			// 5 nach
			D3_FUENF;
			D3_NACH;
			setHours(hours, false, matrix);
			break;
		case 2:
			// 10 nach
			D3_ZEHN;
			D3_NACH;
			setHours(hours, false, matrix);
			break;
		case 3:
			// viertl nach
			D3_VIERTL;
			setHours(hours + 1, false, matrix);
			break;
		case 4:
			// 10 vor halb
			D3_ZEHN;
			D3_VOR;
			D3_HALB;
			setHours(hours + 1, false, matrix);
			break;
		case 5:
			// 5 vor halb
			D3_FUENF;
			D3_VOR;
			D3_HALB;
			setHours(hours + 1, false, matrix);
			break;
		case 6:
			// halb
			D3_HALB;
			setHours(hours + 1, false, matrix);
			break;
		case 7:
			// 5 nach halb
			D3_FUENF;
			D3_NACH;
			D3_HALB;
			setHours(hours + 1, false, matrix);
			break;
		case 8:
			// 10 nach halb
			D3_ZEHN;
			D3_NACH;
			D3_HALB;
			setHours(hours + 1, false, matrix);
			break;
		case 9:
			// viertel vor
			D3_DREIVIERTL;
			setHours(hours + 1, false, matrix);
			break;
		case 10:
			// 10 vor
			D3_ZEHN;
			D3_VOR;
			setHours(hours + 1, false, matrix);
			break;
		case 11:
			// 5 vor
			D3_FUENF;
			D3_VOR;
			setHours(hours + 1, false, matrix);
			break;
		}
#endif

#if defined(FRONTCOVER_CH) || defined(FRONTCOVER_CH_GS)
#if	defined(FRONTCOVER_CH_GS)
		if (minutes % 5) CH_GSI;
#endif
		CH_ESISCH;
		switch (minutes / 5)
		{
		case 0:
			// glatte Stunde
			setHours(hours, true, matrix);
			break;
		case 1:
			// 5 ab
			CH_FUEF;
			CH_AB;
			setHours(hours, false, matrix);
			break;
		case 2:
			// 10 ab
			CH_ZAEAE;
			CH_AB;
			setHours(hours, false, matrix);
			break;
		case 3:
			// viertel ab
			CH_VIERTU;
			CH_AB;
			setHours(hours, false, matrix);
			break;
		case 4:
			// 20 ab
			CH_ZWAENZG;
			CH_AB;
			setHours(hours, false, matrix);
			break;
		case 5:
			// 5 vor halb
			CH_FUEF;
			CH_VOR;
			CH_HAUBI;
			setHours(hours + 1, false, matrix);
			break;
		case 6:
			// halb
			CH_HAUBI;
			setHours(hours + 1, false, matrix);
			break;
		case 7:
			// 5 ab halb
			CH_FUEF;
			CH_AB;
			CH_HAUBI;
			setHours(hours + 1, false, matrix);
			break;
		case 8:
			// 20 vor
			CH_ZWAENZG;
			CH_VOR;
			setHours(hours + 1, false, matrix);
			break;
		case 9:
			// viertel vor
			CH_VIERTU;
			CH_VOR;
			setHours(hours + 1, false, matrix);
			break;
		case 10:
			// 10 vor
			CH_ZAEAE;
			CH_VOR;
			setHours(hours + 1, false, matrix);
			break;
		case 11:
			// 5 vor
			CH_FUEF;
			CH_VOR;
			setHours(hours + 1, false, matrix);
			break;
		}
#endif

#if defined(FRONTCOVER_EN)
		EN_ITIS;
		switch (minutes / 5)
		{
		case 0:
			// glatte Stunde
			setHours(hours, true, matrix);
			break;
		case 1:
			// 5 nach
			EN_FIVE;
			EN_PAST;
			setHours(hours, false, matrix);
			break;
		case 2:
			// 10 nach
			EN_TEN;
			EN_PAST;
			setHours(hours, false, matrix);
			break;
		case 3:
			// viertel nach
			EN_A;
			EN_QUATER;
			EN_PAST;
			setHours(hours, false, matrix);
			break;
		case 4:
			// 20 nach
			EN_TWENTY;
			EN_PAST;
			setHours(hours, false, matrix);
			break;
		case 5:
			// 5 vor halb
			EN_TWENTY;
			EN_FIVE;
			EN_PAST;
			setHours(hours, false, matrix);
			break;
		case 6:
			// halb
			EN_HALF;
			EN_PAST;
			setHours(hours, false, matrix);
			break;
		case 7:
			// 5 nach halb
			EN_TWENTY;
			EN_FIVE;
			EN_TO;
			setHours(hours + 1, false, matrix);
			break;
		case 8:
			// 20 vor
			EN_TWENTY;
			EN_TO;
			setHours(hours + 1, false, matrix);
			break;
		case 9:
			// viertel vor
			EN_A;
			EN_QUATER;
			EN_TO;
			setHours(hours + 1, false, matrix);
			break;
		case 10:
			// 10 vor
			EN_TEN;
			EN_TO;
			setHours(hours + 1, false, matrix);
			break;
		case 11:
			// 5 vor
			EN_FIVE;
			EN_TO;
			setHours(hours + 1, false, matrix);
			break;
		}
#endif

#if defined(FRONTCOVER_ES)
		switch (minutes / 5)
		{
		case 0:
			// glatte Stunde
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
			break;
		case 1:
			// 5 nach
			ES_Y;
			ES_CINCO;
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
			break;
		case 2:
			// 10 nach
			ES_Y;
			ES_DIEZ;
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
			break;
		case 3:
			// viertel nach
			ES_Y;
			ES_CUARTO;
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
			break;
		case 4:
			// 20 nach
			ES_Y;
			ES_VEINTE;
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
			break;
		case 5:
			// 5 vor halb
			ES_Y;
			ES_VEINTICINCO;
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
			break;
		case 6:
			// halb
			ES_Y;
			ES_MEDIA;
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
			break;
		case 7:
			// 5 nach halb
			ES_MENOS;
			ES_VEINTICINCO;
			ES_hours(hours + 1, matrix);
			setHours(hours + 1, false, matrix);
			break;
		case 8:
			// 20 vor
			ES_MENOS;
			ES_VEINTE;
			ES_hours(hours + 1, matrix);
			setHours(hours + 1, false, matrix);
			break;
		case 9:
			// viertel vor
			ES_MENOS;
			ES_CUARTO;
			ES_hours(hours + 1, matrix);
			setHours(hours + 1, false, matrix);
			break;
		case 10:
			// 10 vor
			ES_MENOS;
			ES_DIEZ;
			ES_hours(hours + 1, matrix);
			setHours(hours + 1, false, matrix);
			break;
		case 11:
			// 5 vor
			ES_MENOS;
			ES_CINCO;
			ES_hours(hours + 1, matrix);
			setHours(hours + 1, false, matrix);
			break;
		}
#endif

#if defined(FRONTCOVER_FR)
		FR_ILEST;
		switch (minutes / 5)
		{
		case 0:
			// glatte Stunde
			setHours(hours, true, matrix);
			FR_hours(hours, matrix);
			break;
		case 1:
			// 5 nach
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_CINQ;
			break;
		case 2:
			// 10 nach
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_DIX;
			break;
		case 3:
			// viertel nach
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_ET;
			FR_QUART;
			break;
		case 4:
			// 20 nach
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_VINGT;
			break;
		case 5:
			// 5 vor halb
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_VINGT;
			FR_TRAIT;
			FR_CINQ;
			break;
		case 6:
			// halb
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_ET;
			FR_DEMIE;
			break;
		case 7:
			// 5 nach halb
			setHours(hours + 1, false, matrix);
			FR_hours(hours + 1, matrix);
			FR_MOINS;
			FR_VINGT;
			FR_TRAIT;
			FR_CINQ;
			break;
		case 8:
			// 20 vor
			setHours(hours + 1, false, matrix);
			FR_hours(hours + 1, matrix);
			FR_MOINS;
			FR_VINGT;
			break;
		case 9:
			// viertel vor
			setHours(hours + 1, false, matrix);
			FR_hours(hours + 1, matrix);
			FR_MOINS;
			FR_LE;
			FR_QUART;
			break;
		case 10:
			// 10 vor
			setHours(hours + 1, false, matrix);
			FR_hours(hours + 1, matrix);
			FR_MOINS;
			FR_DIX;
			break;
		case 11:
			// 5 vor
			setHours(hours + 1, false, matrix);
			FR_hours(hours + 1, matrix);
			FR_MOINS;
			FR_CINQ;
			break;
		}
#endif

#if defined(FRONTCOVER_IT)
		switch (minutes / 5)
		{
		case 0:
			// glatte Stunde
			setHours(hours, true, matrix);
			IT_hours(hours, matrix);
			break;
		case 1:
			// 5 nach
			IT_E2;
			IT_CINQUE;
			setHours(hours, false, matrix);
			IT_hours(hours, matrix);
			break;
		case 2:
			// 10 nach
			IT_E2;
			IT_DIECI;
			setHours(hours, false, matrix);
			IT_hours(hours, matrix);
			break;
		case 3:
			// viertel nach
			IT_E2;
			IT_UN;
			IT_QUARTO;
			setHours(hours, false, matrix);
			IT_hours(hours, matrix);
			break;
		case 4:
			// 20 nach
			IT_E2;
			IT_VENTI;
			setHours(hours, false, matrix);
			IT_hours(hours, matrix);
			break;
		case 5:
			// 5 vor halb
			IT_E2;
			IT_VENTI;
			IT_CINQUE;
			setHours(hours, false, matrix);
			IT_hours(hours, matrix);
			break;
		case 6:
			// halb
			IT_E2;
			IT_MEZZA;
			setHours(hours, false, matrix);
			IT_hours(hours, matrix);
			break;
		case 7:
			// 5 nach halb
			IT_MENO;
			IT_VENTI;
			IT_CINQUE;
			setHours(hours + 1, false, matrix);
			IT_hours(hours + 1, matrix);
			break;
		case 8:
			// 20 vor
			IT_MENO;
			IT_VENTI;
			setHours(hours + 1, false, matrix);
			IT_hours(hours + 1, matrix);
			break;
		case 9:
			// viertel vor
			IT_MENO;
			IT_UN;
			IT_QUARTO;
			setHours(hours + 1, false, matrix);
			IT_hours(hours + 1, matrix);
			break;
		case 10:
			// 10 vor
			IT_MENO;
			IT_DIECI;
			setHours(hours + 1, false, matrix);
			IT_hours(hours + 1, matrix);
			break;
		case 11:
			// 5 vor
			IT_MENO;
			IT_CINQUE;
			setHours(hours + 1, false, matrix);
			IT_hours(hours + 1, matrix);
			break;
		}
#endif

#if defined(FRONTCOVER_NL)
		NL_HETIS;
		switch (minutes / 5)
		{
		case 0:
			// glatte Stunde
			setHours(hours, true, matrix);
			break;
		case 1:
			// 5 nach
			NL_VIJF;
			NL_OVER;
			setHours(hours, false, matrix);
			break;
		case 2:
			// 10 nach
			NL_TIEN;
			NL_OVER;
			setHours(hours, false, matrix);
			break;
		case 3:
			// viertel nach
			NL_KWART;
			NL_OVER2;
			setHours(hours, false, matrix);
			break;
		case 4:
			// 10 vor halb
			NL_TIEN;
			NL_VOOR;
			NL_HALF;
			setHours(hours + 1, false, matrix);
			break;
		case 5:
			// 5 vor halb
			NL_VIJF;
			NL_VOOR;
			NL_HALF;
			setHours(hours + 1, false, matrix);
			break;
		case 6:
			// halb
			NL_HALF;
			setHours(hours + 1, false, matrix);
			break;
		case 7:
			// 5 nach halb
			NL_VIJF;
			NL_OVER;
			NL_HALF;
			setHours(hours + 1, false, matrix);
			break;
		case 8:
			// 20 vor
			NL_TIEN;
			NL_OVER;
			NL_HALF;
			setHours(hours + 1, false, matrix);
			break;
		case 9:
			// viertel vor
			NL_KWART;
			NL_VOOR2;
			setHours(hours + 1, false, matrix);
			break;
		case 10:
			// 10 vor
			NL_TIEN;
			NL_VOOR;
			setHours(hours + 1, false, matrix);
			break;
		case 11:
			// 5 vor
			NL_VIJF;
			NL_VOOR;
			setHours(hours + 1, false, matrix);
			break;
		}
#endif
}

// Write hours to screenbuffer.
void Renderer::setHours(uint8_t hours, boolean glatt, uint16_t matrix[])
{
#if defined(FRONTCOVER_DE_DE) || defined(FRONTCOVER_DE_SW) || defined(FRONTCOVER_DE_BA) || defined(FRONTCOVER_DE_SA)
		if (glatt)
			DE_UHR;
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			DE_H_ZWOELF;
      WEB_Uhrtext += F("zw&ouml;lf ");
			break;
		case 1:
		case 13:
			if (glatt)
      {
				DE_H_EIN;
        WEB_Uhrtext += F("ein ");
      }
			else
      {
				DE_H_EINS;
        WEB_Uhrtext += F("eins ");
      }
			break;
		case 2:
		case 14:
			DE_H_ZWEI;
      WEB_Uhrtext += F("zwei ");
			break;
		case 3:
		case 15:
			DE_H_DREI;
      WEB_Uhrtext += F("drei ");
			break;
		case 4:
		case 16:
			DE_H_VIER;
      WEB_Uhrtext += F("vier ");
			break;
		case 5:
		case 17:
			DE_H_FUENF;
      WEB_Uhrtext += F("f&uuml;nf ");
			break;
		case 6:
		case 18:
			DE_H_SECHS;
      WEB_Uhrtext += F("sechs ");
			break;
		case 7:
		case 19:
			DE_H_SIEBEN;
      WEB_Uhrtext += F("sieben ");
			break;
		case 8:
		case 20:
			DE_H_ACHT;
      WEB_Uhrtext += F("acht ");
			break;
		case 9:
		case 21:
			DE_H_NEUN;
      WEB_Uhrtext += F("neun ");
			break;
		case 10:
		case 22:
			DE_H_ZEHN;
      WEB_Uhrtext += F("zehn ");
			break;
		case 11:
		case 23:
			DE_H_ELF;
      WEB_Uhrtext += F("elf ");
			break;
		}
    if (glatt) WEB_Uhrtext += F("Uhr");
#endif


#if defined(FRONTCOVER_DE_MKF_DE) || defined(FRONTCOVER_DE_MKF_SW) || defined(FRONTCOVER_DE_MKF_BA) || defined(FRONTCOVER_DE_MKF_SA)
    if (glatt) {
      DE_MKF_UHR;
    }
    switch (hours)
    {
    case 0:
    case 12:
    case 24:
      DE_MKF_H_ZWOELF;
      WEB_Uhrtext += F("zw&ouml;lf ");
      break;
    case 1:
    case 13:
      if (glatt)
      {
        DE_MKF_H_EIN;
        WEB_Uhrtext += F("ein ");
      }
      else
      {
        DE_MKF_H_EINS;
        WEB_Uhrtext += F("eins ");
      }
      break;
    case 2:
    case 14:
      DE_MKF_H_ZWEI;
      WEB_Uhrtext += F("zwei ");
      break;
    case 3:
    case 15:
      DE_MKF_H_DREI;
      WEB_Uhrtext += F("drei ");
      break;
    case 4:
    case 16:
      DE_MKF_H_VIER;
      WEB_Uhrtext += F("vier ");
      break;
    case 5:
    case 17:
      DE_MKF_H_FUENF;
      WEB_Uhrtext += F("f&uuml;nf ");
      break;
    case 6:
    case 18:
      DE_MKF_H_SECHS;
      WEB_Uhrtext += F("sechs ");
      break;
    case 7:
    case 19:
      DE_MKF_H_SIEBEN;
      WEB_Uhrtext += F("sieben ");
      break;
    case 8:
    case 20:
      DE_MKF_H_ACHT;
      WEB_Uhrtext += F("acht ");
      break;
    case 9:
    case 21:
      DE_MKF_H_NEUN;
      WEB_Uhrtext += F("neun ");
      break;
    case 10:
    case 22:
      DE_MKF_H_ZEHN;
      WEB_Uhrtext += F("zehn ");
      break;
    case 11:
    case 23:
      DE_MKF_H_ELF;
      WEB_Uhrtext += F("elf ");
      break;
    }
    if (glatt) WEB_Uhrtext += F("Uhr");
#endif


#if defined(FRONTCOVER_D3)
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			D3_H_ZWOELFE;
			break;
		case 1:
		case 13:
			D3_H_OISE;
			break;
		case 2:
		case 14:
			D3_H_ZWOIE;
			break;
		case 3:
		case 15:
			D3_H_DREIE;
			break;
		case 4:
		case 16:
			D3_H_VIERE;
			break;
		case 5:
		case 17:
			D3_H_FUENFE;
			break;
		case 6:
		case 18:
			D3_H_SECHSE;
			break;
		case 7:
		case 19:
			D3_H_SIEBNE;
			break;
		case 8:
		case 20:
			D3_H_ACHTE;
			break;
		case 9:
		case 21:
			D3_H_NEUNE;
			break;
		case 10:
		case 22:
			D3_H_ZEHNE;
			break;
		case 11:
		case 23:
			D3_H_ELFE;
			break;
		}
#endif

#if defined(FRONTCOVER_CH) || defined(FRONTCOVER_CH_GS)
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			CH_H_ZWOEUFI;
			break;
		case 1:
		case 13:
			CH_H_EIS;
			break;
		case 2:
		case 14:
			CH_H_ZWOEI;
			break;
		case 3:
		case 15:
			CH_H_DRUE;
			break;
		case 4:
		case 16:
			CH_H_VIER;
			break;
		case 5:
		case 17:
			CH_H_FUEFI;
			break;
		case 6:
		case 18:
			CH_H_SAECHSI;
			break;
		case 7:
		case 19:
			CH_H_SIEBNI;
			break;
		case 8:
		case 20:
			CH_H_ACHTI;
			break;
		case 9:
		case 21:
			CH_H_NUENI;
			break;
		case 10:
		case 22:
			CH_H_ZAENI;
			break;
		case 11:
		case 23:
			CH_H_EUFI;
			break;
		}
#endif

#if defined(FRONTCOVER_EN)
		if (glatt)
			EN_OCLOCK;
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			EN_H_TWELVE;
			break;
		case 1:
		case 13:
			EN_H_ONE;
			break;
		case 2:
		case 14:
			EN_H_TWO;
			break;
		case 3:
		case 15:
			EN_H_THREE;
			break;
		case 4:
		case 16:
			EN_H_FOUR;
			break;
		case 5:
		case 17:
			EN_H_FIVE;
			break;
		case 6:
		case 18:
			EN_H_SIX;
			break;
		case 7:
		case 19:
			EN_H_SEVEN;
			break;
		case 8:
		case 20:
			EN_H_EIGHT;
			break;
		case 9:
		case 21:
			EN_H_NINE;
			break;
		case 10:
		case 22:
			EN_H_TEN;
			break;
		case 11:
		case 23:
			EN_H_ELEVEN;
			break;
		}
#endif

#if defined(FRONTCOVER_ES)
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			ES_H_DOCE;
			break;
		case 1:
		case 13:
			ES_H_UNA;
			break;
		case 2:
		case 14:
			ES_H_DOS;
			break;
		case 3:
		case 15:
			ES_H_TRES;
			break;
		case 4:
		case 16:
			ES_H_CUATRO;
			break;
		case 5:
		case 17:
			ES_H_CINCO;
			break;
		case 6:
		case 18:
			ES_H_SEIS;
			break;
		case 7:
		case 19:
			ES_H_SIETE;
			break;
		case 8:
		case 20:
			ES_H_OCHO;
			break;
		case 9:
		case 21:
			ES_H_NUEVE;
			break;
		case 10:
		case 22:
			ES_H_DIEZ;
			break;
		case 11:
		case 23:
			ES_H_ONCE;
			break;
		}
#endif

#if defined(FRONTCOVER_FR)
		switch (hours)
		{
		case 0:
		case 24:
			FR_H_MINUIT;
			break;
		case 12:
			FR_H_MIDI;
			break;
		case 1:
		case 13:
			FR_H_UNE;
			break;
		case 2:
		case 14:
			FR_H_DEUX;
			break;
		case 3:
		case 15:
			FR_H_TROIS;
			break;
		case 4:
		case 16:
			FR_H_QUATRE;
			break;
		case 5:
		case 17:
			FR_H_CINQ;
			break;
		case 6:
		case 18:
			FR_H_SIX;
			break;
		case 7:
		case 19:
			FR_H_SEPT;
			break;
		case 8:
		case 20:
			FR_H_HUIT;
			break;
		case 9:
		case 21:
			FR_H_NEUF;
			break;
		case 10:
		case 22:
			FR_H_DIX;
			break;
		case 11:
		case 23:
			FR_H_ONZE;
			break;
		}
#endif

#if defined(FRONTCOVER_IT)
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			IT_H_DODICI;
			break;
		case 1:
		case 13:
			IT_H_LUNA;
			break;
		case 2:
		case 14:
			IT_H_DUE;
			break;
		case 3:
		case 15:
			IT_H_TRE;
			break;
		case 4:
		case 16:
			IT_H_QUATTRO;
			break;
		case 5:
		case 17:
			IT_H_CINQUE;
			break;
		case 6:
		case 18:
			IT_H_SEI;
			break;
		case 7:
		case 19:
			IT_H_SETTE;
			break;
		case 8:
		case 20:
			IT_H_OTTO;
			break;
		case 9:
		case 21:
			IT_H_NOVE;
			break;
		case 10:
		case 22:
			IT_H_DIECI;
			break;
		case 11:
		case 23:
			IT_H_UNDICI;
			break;
		}
#endif

#if defined(FRONTCOVER_NL)
		if (glatt)
			NL_UUR;
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			NL_H_TWAALF;
			break;
		case 1:
		case 13:
			NL_H_EEN;
			break;
		case 2:
		case 14:
			NL_H_TWEE;
			break;
		case 3:
		case 15:
			NL_H_DRIE;
			break;
		case 4:
		case 16:
			NL_H_VIER;
			break;
		case 5:
		case 17:
			NL_H_VIJF;
			break;
		case 6:
		case 18:
			NL_H_ZES;
			break;
		case 7:
		case 19:
			NL_H_ZEVEN;
			break;
		case 8:
		case 20:
			NL_H_ACHT;
			break;
		case 9:
		case 21:
			NL_H_NEGEN;
			break;
		case 10:
		case 22:
			NL_H_TIEN;
			break;
		case 11:
		case 23:
			NL_H_ELF;
			break;
		}
#endif
}

// Clear entry words.
void Renderer::clearEntryWords(uint16_t matrix[])
{
#if defined(FRONTCOVER_DE_DE) || defined(FRONTCOVER_DE_SW) || defined(FRONTCOVER_DE_BA) || defined(FRONTCOVER_DE_SA)
		matrix[0] &= 0b0010001111111111; // remove ES IST
#endif
#if defined(FRONTCOVER_DE_MKF_DE) || defined(FRONTCOVER_DE_MKF_SW) || defined(FRONTCOVER_DE_MKF_BA) || defined(FRONTCOVER_DE_MKF_SA)
		matrix[0] &= 0b0010001111111111; // remove ES IST
#endif
#if defined(FRONTCOVER_D3)
		matrix[0] &= 0b0010000111111111; // remove ISCH
#endif
#if defined(FRONTCOVER_CH) || defined(FRONTCOVER_CH_GS)
		matrix[0] &= 0b0010000111111111; // remove ES ISCH
#endif
#if defined(FRONTCOVER_EN)
		matrix[0] &= 0b0010011111111111; // remove IT IS
#endif
#if defined(FRONTCOVER_ES)
		matrix[0] &= 0b1000100011111111; // remove SON LAS
		matrix[0] &= 0b0011100111111111; // remove ES LA
#endif
#if defined(FRONTCOVER_FR)
		matrix[0] &= 0b0010001111111111; // remove IL EST
#endif
#if defined(FRONTCOVER_IT)
		matrix[0] &= 0b0000100111111111; // remove SONO LE
		matrix[1] &= 0b0111111111111111; // remove E (L'UNA)
#endif
#if defined(FRONTCOVER_NL)
		matrix[0] &= 0b0001001111111111; // remove HET IS
#endif
}

// Turn on AM or PM.
void Renderer::setAMPM(uint8_t hours, uint16_t matrix[])
{
#if defined(FRONTCOVER_DE_DE) || defined(FRONTCOVER_DE_SW) || defined(FRONTCOVER_DE_BA) || defined(FRONTCOVER_DE_SA)
		if (hours < 12) DE_AM;
		else DE_PM;
#endif
#if defined(FRONTCOVER_DE_MKF_DE) || defined(FRONTCOVER_DE_MKF_SW) || defined(FRONTCOVER_DE_MKF_BA) || defined(FRONTCOVER_DE_MKF_SA)
		if (hours < 12) DE_MKF_AM;
		else DE_MKF_PM;
#endif
#if defined(FRONTCOVER_D3)
		if (hours < 12) D3_AM;
		else D3_PM;
#endif
#if defined(FRONTCOVER_CH) || defined(FRONTCOVER_CH_GS)
		if (hours < 12) CH_AM;
		else CH_PM;
#endif
#if defined(FRONTCOVER_EN)
		if (hours < 12) EN_AM;
		else EN_PM;
#endif
#if defined(FRONTCOVER_ES)
		if (hours < 12) ES_AM;
		else ES_PM;
#endif
#if defined(FRONTCOVER_FR)
		if (hours < 12) FR_AM;
		else FR_PM;
#endif
#if defined(FRONTCOVER_IT)
		if (hours < 12) IT_AM;
		else IT_PM;
#endif
#if defined(FRONTCOVER_NL)
		if (hours < 12) NL_AM;
		else NL_PM;
#endif
}

#if defined(FRONTCOVER_ES)
// Special case ES.
void Renderer::ES_hours(uint8_t hours, uint16_t matrix[])
{
	if ((hours == 1) || (hours == 13))
		ES_ESLA;
	else
		ES_SONLAS;
}
#endif

#if defined(FRONTCOVER_FR)
// Special case FR.
void Renderer::FR_hours(uint8_t hours, uint16_t matrix[])
{
	if ((hours == 1) || (hours == 13))
		FR_HEURE;
	else
		if ((hours == 0) || (hours == 12) || (hours == 24))
			;
		else
			FR_HEURES;
}
#endif

#if defined(FRONTCOVER_IT)
// Special case IT.
void Renderer::IT_hours(uint8_t hours, uint16_t matrix[])
{
	if ((hours != 1) && (hours != 13))
		IT_SONOLE;
	else
		IT_E;
}
#endif

// write minutes to screenbuffer
void Renderer::setCorners(uint8_t minutes, uint16_t matrix[])
{
	uint8_t b_minutes = minutes % 5;
	for (uint8_t i = 0; i < b_minutes; i++)
		bitSet(matrix[i], 4);
}

// switch alarm-LED on
void Renderer::setAlarmLed(uint16_t matrix[])
{
	bitSet(matrix[4], 4);
}

// turn alarm-LED off
void Renderer::deactivateAlarmLed(uint16_t matrix[])
{
	bitClear(matrix[4], 4);
}

// write text to screenbuffer
void Renderer::setSmallText(String menuText, eTextPos textPos, uint16_t matrix[])
{
  uint8_t letter;
  uint8_t number;
	if (menuText.length() == 2)
	{
		for (uint8_t i = 0; i <= 4; i++)
		{
			for (uint8_t j = 0; j < menuText.length(); j++)
			{
				if (!isNumber(menuText[j]))
        {
          letter = pgm_read_byte(&letters[menuText[j] - 'A'][i]);
          matrix[textPos + i] |= letter << (5 + ((j + 1) % 2) * 6);
//					matrix[textPos + i] |= letters[menuText[j] - 'A'][i] << (5 + ((j + 1) % 2) * 6);
        }
				else
        {
          number = pgm_read_byte(&numbers[menuText[j] - '0'][i]);
          matrix[textPos + i] |= number << (5 + ((j + 1) % 2) * 5);
//					matrix[textPos + i] |= numbers[menuText[j] - '0'][i] << (5 + ((j + 1) % 2) * 5);
        }
			}
		}
	}
	else if (menuText.length() == 1)
	{
		for (uint8_t i = 0; i <= 4; i++)
		{
			if (!isNumber(menuText[0]))
      {
        letter = pgm_read_byte(&letters[menuText[0] - 'A'][i]);
        matrix[textPos + i] |= letter << 8;
//				matrix[textPos + i] |= letters[menuText[0] - 'A'][i] << 8;
      }
			else
      {
        number = pgm_read_byte(&numbers[menuText[0] - '0'][i]);
        matrix[textPos + i] |= number << 8;
//			 matrix[textPos + i] |= numbers[menuText[0] - '0'][i] << 8;
      }
		}
	}
}

// test for number
boolean Renderer::isNumber(char symbol)
{
	if ((symbol >= '0') && (symbol <= '9'))
		return true;
	else
		return false;
}

// set pixel in screenbuffer
void Renderer::setPixelInScreenBuffer(uint8_t x, uint8_t y, uint16_t matrix[])
{
	bitSet(matrix[y], x);
}

// remove pixel from screenbuffer
void Renderer::unsetPixelInScreenBuffer(uint8_t x, uint8_t y, uint16_t matrix[])
{
	bitClear(matrix[y], x);
}

// clear screenbuffer
void Renderer::clearScreenBuffer(uint16_t matrix[])
{
	for (uint8_t i = 0; i <= 9; i++)
		matrix[i] = 0b0000000000000000;
}

// switch all LEDs in screenbuffer on
void Renderer::setAllScreenBuffer(uint16_t matrix[])
{
	for (uint8_t i = 0; i <= 9; i++)
		matrix[i] = 0b1111111111111111;
}
