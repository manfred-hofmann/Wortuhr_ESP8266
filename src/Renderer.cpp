//******************************************************************************
// Renderer.cpp
//******************************************************************************


#include "Renderer.h"
#include <TimeLib.h>

Renderer::Renderer()
{
}

// Write time to screenbuffer
void Renderer::setTime(uint8_t hours, uint8_t minutes, uint16_t matrix[])
{

//########################################################################################################################
// DEUTSCH
//########################################################################################################################
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

//########################################################################################################################
// SCHWEIZ
//########################################################################################################################

#if defined(FRONTCOVER_CH)
    

    if (settings.mySettings.itIs) 
    {
      if (minutes % 5) CH_GSI;
    }

    CH_ESISCH;
    if (settings.mySettings.itIs) 
    {
      WEB_Uhrtext = F("Es isch ");
    }
    else
    {
      WEB_Uhrtext = F("");
    }

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
      WEB_Uhrtext += F("f&ouml;f ab ");
			setHours(hours, false, matrix);
			break;
		case 2:
			// 10 ab
			CH_ZAEAE;
			CH_AB;
      WEB_Uhrtext += F("z&auml;&auml; ab ");
			setHours(hours, false, matrix);
			break;
		case 3:
			// viertel ab
			CH_VIERTU;
			CH_AB;
      WEB_Uhrtext += F("viertu ab ");
			setHours(hours, false, matrix);
			break;
		case 4:
			// 20 ab
			CH_ZWAENZG;
			CH_AB;
      WEB_Uhrtext += F("zw&auml;nzg ab ");
			setHours(hours, false, matrix);
			break;
		case 5:
			// 5 vor halb
			CH_FUEF;
			CH_VOR;
			CH_HAUBI;
      WEB_Uhrtext += F("f&ouml;f vor haubi ");
			setHours(hours + 1, false, matrix);
			break;
		case 6:
			// halb
			CH_HAUBI;
      WEB_Uhrtext += F("haubi ");
			setHours(hours + 1, false, matrix);
			break;
		case 7:
			// 5 ab halb
			CH_FUEF;
			CH_AB;
			CH_HAUBI;
      WEB_Uhrtext += F("f&ouml;f ab haubi ");
			setHours(hours + 1, false, matrix);
			break;
		case 8:
			// 20 vor
			CH_ZWAENZG;
			CH_VOR;
      WEB_Uhrtext += F("zw&auml;nzg vor ");
			setHours(hours + 1, false, matrix);
			break;
		case 9:
			// viertel vor
			CH_VIERTU;
			CH_VOR;
      WEB_Uhrtext += F("viertu vor ");
			setHours(hours + 1, false, matrix);
			break;
		case 10:
			// 10 vor
			CH_ZAEAE;
			CH_VOR;
      WEB_Uhrtext += F("z&auml;&auml; vor ");
			setHours(hours + 1, false, matrix);
			break;
		case 11:
			// 5 vor
			CH_FUEF;
			CH_VOR;
      WEB_Uhrtext += F("f&ouml;if vor ");
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

//########################################################################################################################
// SCHWEIZ AARGAU
//########################################################################################################################

 #if defined(FRONTCOVER_CH_AG) || defined(FRONTCOVER_CH_AL)
    CH_ESIST;
    
    if (settings.mySettings.itIs) 
    {
      if (minutes % 5) CH_H_GSI;
      WEB_Uhrtext = F("Es esch ");
    }
    else
    {
      WEB_Uhrtext = F("");
    }
    
    switch (minutes / 5)
    {
    case 0:
      // full hour
      setHours(hours, true, matrix);
      break;
    case 1:
      // 5 nach
      CH_FUENF;
      CH_NACH;
      WEB_Uhrtext += F("f&ouml;if ab ");
      setHours(hours, false, matrix);
      break;
    case 2:
      // 10 nach
      CH_ZEHN;
      CH_NACH;
      WEB_Uhrtext += F("z&auml;&auml; ab ");    
      setHours(hours, false, matrix);
      break;
    case 3:
      // viertel nach
  #if defined(FRONTCOVER_CH_AG)
      CH_VIERTU;
      CH_NACH;
      WEB_Uhrtext += F("viertu ab ");
      setHours(hours, false, matrix);
  #else
      CH_VIERTEL;
      CH_NACH;
      WEB_Uhrtext += F("viertel ab ");      
      setHours(hours, false, matrix);
#endif
      break;
    case 4:
      // 20 nach
      CH_ZWANZIG;
      CH_NACH;
      WEB_Uhrtext += F("zw&auml;nzg ab ");
      setHours(hours, false, matrix);
      break;
    case 5:
      // 5 vor halb
#if defined(FRONTCOVER_CH_AG)        
      CH_FUENF;
      CH_VOR;
      CH_HALB;
      WEB_Uhrtext += F("f&ouml;if vor haubi ");
      setHours(hours + 1, false, matrix);
#else      
      CH_FUENF;
      CH_VOR;
      CH_HALB;
      WEB_Uhrtext += F("f&ouml;if vor halbi ");
      setHours(hours + 1, false, matrix);
#endif
      break;
    case 6:
      // halb
#if defined(FRONTCOVER_CH_AG)      
      CH_HALB;
      WEB_Uhrtext += F("haubi ");
      setHours(hours + 1, false, matrix);
#else
      CH_HALB;
      WEB_Uhrtext += F("halbi ");
      setHours(hours + 1, false, matrix);
#endif 
      break;
    case 7:
      // 5 nach halb
#if defined(FRONTCOVER_CH_AG)
      CH_FUENF;
      CH_NACH;
      CH_HALB;
      WEB_Uhrtext += F("f&ouml;if ab haubi ");
      setHours(hours + 1, false, matrix);
#else
      CH_FUENF;
      CH_NACH;
      CH_HALB;
      WEB_Uhrtext += F("f&ouml;if ab halbi ");
      setHours(hours + 1, false, matrix);
#endif      
      break;
    case 8:
      // 20 vor
      CH_ZWANZIG;
      CH_VOR;
      WEB_Uhrtext += F("zw&auml;nzg vor ");
      setHours(hours + 1, false, matrix);
      break;
    case 9:
      // viertel vor
#if defined(FRONTCOVER_CH_AG)
      CH_VIERTU;
      CH_VOR;
      WEB_Uhrtext += F("viertu vor ");
      setHours(hours + 1, false, matrix);
#else
      CH_VIERTEL;
      CH_VOR;
      WEB_Uhrtext += F("viertel vor ");      
      setHours(hours + 1, false, matrix);
<<<<<<< HEAD
=======
#endif
     break;
    case 10:
      // 10 vor
      CH_ZEHN;
      CH_VOR;
      WEB_Uhrtext += F("z&auml;&auml; vor ");
      setHours(hours + 1, false, matrix);
      break;
    case 11:
      // 5 vor
      CH_FUENF;
      CH_VOR;
      WEB_Uhrtext += F("f&ouml;if vor ");
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
>>>>>>> 96b59cb4a65705bd521ef611a8bb5862bcff01f0
#endif
     break;
    case 10:
      // 10 vor
      CH_ZEHN;
      CH_VOR;
      WEB_Uhrtext += F("z&auml;&auml; vor ");
      setHours(hours + 1, false, matrix);
      break;
    case 11:
      // 5 vor
      CH_FUENF;
      CH_VOR;
      WEB_Uhrtext += F("f&ouml;if vor ");
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

//########################################################################################################################
// ENGLISCH
//########################################################################################################################

//########################################################################################################################
// ENGLISCH
//########################################################################################################################

#if defined(FRONTCOVER_EN)
		EN_ITIS;
    if (settings.mySettings.itIs) 
    { 
      WEB_Uhrtext = F("It is ");
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
			EN_FIVE;
			EN_PAST;
      WEB_Uhrtext += F("five past ");
			setHours(hours, false, matrix);
			break;
		case 2:
			// 10 nach
			EN_TEN;
			EN_PAST;
      WEB_Uhrtext += F("ten past ");
			setHours(hours, false, matrix);
			break;
		case 3:
			// viertel nach
			EN_A;
			EN_QUATER;
			EN_PAST;
      WEB_Uhrtext += F("a quarter past ");
			setHours(hours, false, matrix);
			break;
		case 4:
			// 20 nach
			EN_TWENTY;
			EN_PAST;
      WEB_Uhrtext += F("twenty past ");
			setHours(hours, false, matrix);
			break;
		case 5:
			// 5 vor halb
			EN_TWENTY;
			EN_FIVE;
			EN_PAST;
      WEB_Uhrtext += F("twenty-five past ");
			setHours(hours, false, matrix);
			break;
		case 6:
			// halb
			EN_HALF;
			EN_PAST;
      WEB_Uhrtext += F("half past ");
			setHours(hours, false, matrix);
			break;
		case 7:
			// 5 nach halb
			EN_TWENTY;
			EN_FIVE;
			EN_TO;
      WEB_Uhrtext += F("twenty-five to ");
			setHours(hours + 1, false, matrix);
			break;
		case 8:
			// 20 vor
			EN_TWENTY;
			EN_TO;
      WEB_Uhrtext += F("twenty to ");
			setHours(hours + 1, false, matrix);
			break;
		case 9:
			// viertel vor
			EN_A;
			EN_QUATER;
			EN_TO;
      WEB_Uhrtext += F("a quarter to ");
			setHours(hours + 1, false, matrix);
			break;
		case 10:
			// 10 vor
			EN_TEN;
			EN_TO;
      WEB_Uhrtext += F("ten to ");
			setHours(hours + 1, false, matrix);
			break;
		case 11:
			// 5 vor
			EN_FIVE;
			EN_TO;
      WEB_Uhrtext += F("five to ");
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

//########################################################################################################################
// SPANISCH
//########################################################################################################################

#if defined(FRONTCOVER_ES)
    WEB_Uhrtext = "";
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
      WEB_Uhrtext += F("y cinco ");
			break;
		case 2:
			// 10 nach
			ES_Y;
			ES_DIEZ;
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
      WEB_Uhrtext += F("y diez ");
			break;
		case 3:
			// viertel nach
			ES_Y;
			ES_CUARTO;
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
      WEB_Uhrtext += F("y cuarto ");
			break;
		case 4:
			// 20 nach
			ES_Y;
			ES_VEINTE;
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
      WEB_Uhrtext += F("y veinte ");
			break;
		case 5:
			// 5 vor halb
			ES_Y;
			ES_VEINTICINCO;
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
      WEB_Uhrtext += F("y veinticinco ");
			break;
		case 6:
			// halb
			ES_Y;
			ES_MEDIA;
			ES_hours(hours, matrix);
			setHours(hours, false, matrix);
      WEB_Uhrtext += F("y media ");
			break;
		case 7:
			// 5 nach halb
			ES_MENOS;
			ES_VEINTICINCO;
			ES_hours(hours + 1, matrix);
			setHours(hours + 1, false, matrix);
      WEB_Uhrtext += F("menos veinticinco ");
			break;
		case 8:
			// 20 vor
			ES_MENOS;
			ES_VEINTE;
			ES_hours(hours + 1, matrix);
			setHours(hours + 1, false, matrix);
      WEB_Uhrtext += F("menos veinte ");
			break;
		case 9:
			// viertel vor
			ES_MENOS;
			ES_CUARTO;
			ES_hours(hours + 1, matrix);
			setHours(hours + 1, false, matrix);
      WEB_Uhrtext += F("menos cuarto ");
			break;
		case 10:
			// 10 vor
			ES_MENOS;
			ES_DIEZ;
			ES_hours(hours + 1, matrix);
			setHours(hours + 1, false, matrix);
      WEB_Uhrtext += F("menos diez ");
			break;
		case 11:
			// 5 vor
			ES_MENOS;
			ES_CINCO;
			ES_hours(hours + 1, matrix);
			setHours(hours + 1, false, matrix);
      WEB_Uhrtext += F("menos cinco ");
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

//########################################################################################################################
// FRANZÖSISCH
//########################################################################################################################

#if defined(FRONTCOVER_FR)
		FR_ILEST;
    if (settings.mySettings.itIs) 
    { 
      WEB_Uhrtext = F("Il est ");
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
			FR_hours(hours, matrix);
      
			break;
		case 1:
			// 5 nach
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_CINQ;
      WEB_Uhrtext += F("cinq");
			break;
		case 2:
			// 10 nach
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_DIX;
      WEB_Uhrtext += F("dix");
			break;
		case 3:
			// viertel nach
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_ET;
			FR_QUART;
      WEB_Uhrtext += F("et quart");
			break;
		case 4:
			// 20 nach
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_VINGT;
      WEB_Uhrtext += F("vingt");
			break;
		case 5:
			// 5 vor halb
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_VINGT;
			FR_TRAIT;
			FR_CINQ;
      WEB_Uhrtext += F("vingt-cinq");
			break;
		case 6:
			// halb
			setHours(hours, false, matrix);
			FR_hours(hours, matrix);
			FR_ET;
			FR_DEMIE;
      WEB_Uhrtext += F("et demi");
			break;
		case 7:
			// 5 nach halb
			setHours(hours + 1, false, matrix);
			FR_hours(hours + 1, matrix);
			FR_MOINS;
			FR_VINGT;
			FR_TRAIT;
			FR_CINQ;
      WEB_Uhrtext += F("moins vingt-cinq");
			break;
		case 8:
			// 20 vor
			setHours(hours + 1, false, matrix);
			FR_hours(hours + 1, matrix);
			FR_MOINS;
			FR_VINGT;
      WEB_Uhrtext += F("moins vingt");
			break;
		case 9:
			// viertel vor
			setHours(hours + 1, false, matrix);
			FR_hours(hours + 1, matrix);
			FR_MOINS;
			FR_LE;
			FR_QUART;
      WEB_Uhrtext += F("moins le quart");
			break;
		case 10:
			// 10 vor
			setHours(hours + 1, false, matrix);
			FR_hours(hours + 1, matrix);
			FR_MOINS;
			FR_DIX;
      WEB_Uhrtext += F("moins dix");
			break;
		case 11:
			// 5 vor
			setHours(hours + 1, false, matrix);
			FR_hours(hours + 1, matrix);
			FR_MOINS;
			FR_CINQ;
      WEB_Uhrtext += F("moins cinq");
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

//########################################################################################################################
// ITALIENISCH
//########################################################################################################################

#if defined(FRONTCOVER_IT)
    WEB_Uhrtext = "";
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
      WEB_Uhrtext += F("e cinque");
			break;
		case 2:
			// 10 nach
			IT_E2;
			IT_DIECI;
			setHours(hours, false, matrix);
			IT_hours(hours, matrix);
      WEB_Uhrtext += F("e dieci");
			break;
		case 3:
			// viertel nach
			IT_E2;
			IT_UN;
			IT_QUARTO;
			setHours(hours, false, matrix);
			IT_hours(hours, matrix);
      WEB_Uhrtext += F("e un quarto");
			break;
		case 4:
			// 20 nach
			IT_E2;
			IT_VENTI;
			setHours(hours, false, matrix);
			IT_hours(hours, matrix);
      WEB_Uhrtext += F("e venti");
			break;
		case 5:
			// 5 vor halb
			IT_E2;
			IT_VENTI;
			IT_CINQUE;
			setHours(hours, false, matrix);
			IT_hours(hours, matrix);
      WEB_Uhrtext += F("e venti cinque");
			break;
		case 6:
			// halb
			IT_E2;
			IT_MEZZA;
			setHours(hours, false, matrix);
			IT_hours(hours, matrix);
      WEB_Uhrtext += F("e mezza");
			break;
		case 7:
			// 5 nach halb
			IT_MENO;
			IT_VENTI;
			IT_CINQUE;
			setHours(hours + 1, false, matrix);
			IT_hours(hours + 1, matrix);
      WEB_Uhrtext += F("meno venti cinque");
			break;
		case 8:
			// 20 vor
			IT_MENO;
			IT_VENTI;
			setHours(hours + 1, false, matrix);
			IT_hours(hours + 1, matrix);
      WEB_Uhrtext += F("meno venti");
			break;
		case 9:
			// viertel vor
			IT_MENO;
			IT_UN;
			IT_QUARTO;
			setHours(hours + 1, false, matrix);
			IT_hours(hours + 1, matrix);
      WEB_Uhrtext += F("meno un quarto");
			break;
		case 10:
			// 10 vor
			IT_MENO;
			IT_DIECI;
			setHours(hours + 1, false, matrix);
			IT_hours(hours + 1, matrix);
      WEB_Uhrtext += F("meno dieci");
			break;
		case 11:
			// 5 vor
			IT_MENO;
			IT_CINQUE;
			setHours(hours + 1, false, matrix);
			IT_hours(hours + 1, matrix);
      WEB_Uhrtext += F("meno un cinque");
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

//########################################################################################################################
// NIEDERLÄNDISCH
//########################################################################################################################

#if defined(FRONTCOVER_NL)
		NL_HETIS;
    if (settings.mySettings.itIs) 
    { 
      WEB_Uhrtext = F("het is ");
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
			NL_VIJF;
			NL_OVER;
      WEB_Uhrtext += F("vijf over ");
			setHours(hours, false, matrix);
			break;
		case 2:
			// 10 nach
			NL_TIEN;
			NL_OVER;
      WEB_Uhrtext += F("tien over ");
			setHours(hours, false, matrix);
			break;
		case 3:
			// viertel nach
			NL_KWART;
			NL_OVER2;
      WEB_Uhrtext += F("kwart over ");
			setHours(hours, false, matrix);
			break;
		case 4:
			// 10 vor halb
			NL_TIEN;
			NL_VOOR;
			NL_HALF;
      WEB_Uhrtext += F("tien voor half ");
			setHours(hours + 1, false, matrix);
			break;
		case 5:
			// 5 vor halb
			NL_VIJF;
			NL_VOOR;
			NL_HALF;
      WEB_Uhrtext += F("vijf voor half ");
			setHours(hours + 1, false, matrix);
			break;
		case 6:
			// halb
			NL_HALF;
      WEB_Uhrtext += F("half ");
			setHours(hours + 1, false, matrix);
			break;
		case 7:
			// 5 nach halb
			NL_VIJF;
			NL_OVER;
			NL_HALF;
      WEB_Uhrtext += F("vijf over half ");
			setHours(hours + 1, false, matrix);
			break;
		case 8:
			// 20 vor
			NL_TIEN;
			NL_OVER;
			NL_HALF;
      WEB_Uhrtext += F("tien over half ");
			setHours(hours + 1, false, matrix);
			break;
		case 9:
			// viertel vor
			NL_KWART;
			NL_VOOR2;
      WEB_Uhrtext += F("kwart voor ");
			setHours(hours + 1, false, matrix);
			break;
		case 10:
			// 10 vor
			NL_TIEN;
			NL_VOOR;
      WEB_Uhrtext += F("tien voor ");
			setHours(hours + 1, false, matrix);
			break;
		case 11:
			// 5 vor
			NL_VIJF;
			NL_VOOR;
      WEB_Uhrtext += F("vijf voor ");
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
}

//########################################################################################################################
//########################################################################################################################
//########################################################################################################################
// Write hours to screenbuffer.
//########################################################################################################################
void Renderer::setHours(uint8_t hours, boolean glatt, uint16_t matrix[])
{

//########################################################################################################################
// DEUTSCH
//########################################################################################################################  
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

//########################################################################################################################
// SCHWEIZ
//########################################################################################################################

#if defined(FRONTCOVER_CH)
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			CH_H_ZWOEUFI;
      WEB_Uhrtext += F("Zw&ouml;ufi ");
			break;
		case 1:
		case 13:
			CH_H_EIS;
      WEB_Uhrtext += F("Eis ");
			break;
		case 2:
		case 14:
			CH_H_ZWOEI;
      WEB_Uhrtext += F("Zw&ouml;i ");
			break;
		case 3:
		case 15:
			CH_H_DRUE;
      WEB_Uhrtext += F("Dr&uuml;&uuml; ");
			break;
		case 4:
		case 16:
			CH_H_VIER;
      WEB_Uhrtext += F("Vieri ");
			break;
		case 5:
		case 17:
			CH_H_FUEFI;
      WEB_Uhrtext += F("F&ouml;ifi ");
			break;
		case 6:
		case 18:
			CH_H_SAECHSI;
      WEB_Uhrtext += F("S&auml;chsi ");
			break;
		case 7:
		case 19:
			CH_H_SIEBNI;
      WEB_Uhrtext += F("Sebni ");
			break;
		case 8:
		case 20:
			CH_H_ACHTI;
      WEB_Uhrtext += F("Achti ");
			break;
		case 9:
		case 21:
			CH_H_NUENI;
      WEB_Uhrtext += F("N&uuml;&uuml;ni ");
			break;
		case 10:
		case 22:
			CH_H_ZAENI;
      WEB_Uhrtext += F("Z&auml;hni ");
			break;
		case 11:
		case 23:
			CH_H_EUFI;
      WEB_Uhrtext += F("Eufi ");
			break;
		}
    if (settings.mySettings.itIs) 
    {
      if (minute() % 5 ) WEB_Uhrtext += F("gsi");
//      if (glatt) WEB_Uhrtext += F("gsi");
    }
<<<<<<< HEAD
#endif

//########################################################################################################################
// SCHWEIZ AARGAU
//########################################################################################################################

  #if defined(FRONTCOVER_CH_AG) || defined(FRONTCOVER_CH_AL)
 //   if (glatt)
 //     CH_H_GSI;
    switch (hours)
    {
    case 0:
    case 12:
    case 24:
  #if defined(FRONTCOVER_CH_AG)   
      CH_H_ZWOELF;
      WEB_Uhrtext += F("Zw&ouml;ufi ");
  #else
      CH_H_ZWOELF;
      WEB_Uhrtext += F("Zw&ouml;lfi ");
  #endif      
      break;
    case 1:
    case 13:
//      if (glatt)
//      {
        CH_H_EIN;
        WEB_Uhrtext += F("Eis ");
//      }
//      else
//      {
//        CH_H_EINS;
//        WEB_Uhrtext += F("eis ");
//      }
        break;
    case 2:
    case 14:
      CH_H_ZWEI;
      WEB_Uhrtext += F("Zw&ouml;i ");
      break;
    case 3:
    case 15:
      CH_H_DREI;
      WEB_Uhrtext += F("Dr&uuml;&uuml; ");
      break;
    case 4:
    case 16:
      CH_H_VIER;
      WEB_Uhrtext += F("Vieri ");
      break;
    case 5:
    case 17:
      CH_H_FUENF;
      WEB_Uhrtext += F("F&ouml;ifi ");
      break;
    case 6:
    case 18:
      CH_H_SECHS;
      WEB_Uhrtext += F("S&auml;chsi ");
      break;
    case 7:
    case 19:
      CH_H_SIEBEN;
      WEB_Uhrtext += F("Sebni ");
      break;
    case 8:
    case 20:
      CH_H_ACHT;
      WEB_Uhrtext += F("Achti ");
      break;
    case 9:
    case 21:
      CH_H_NEUN;
      WEB_Uhrtext += F("N&uuml;&uuml;ni ");
      break;
    case 10:
    case 22:
      CH_H_ZEHN;
      WEB_Uhrtext += F("Z&auml;hni ");
      break;
    case 11:
    case 23:
  #if defined(FRONTCOVER_CH_AG) 
      CH_H_ELF;
      WEB_Uhrtext += F("Eufi ");
  #else
      CH_H_ELF;
      WEB_Uhrtext += F("Elfi ");
  #endif      
      break;
    }
    if (settings.mySettings.itIs) 
    {
      if (minute() % 5 ) WEB_Uhrtext += F("gsi");
//      if (glatt) WEB_Uhrtext += F("gsi");
    }
    
#endif

//########################################################################################################################
=======
#endif

//########################################################################################################################
// SCHWEIZ AARGAU
//########################################################################################################################

  #if defined(FRONTCOVER_CH_AG) || defined(FRONTCOVER_CH_AL)
 //   if (glatt)
 //     CH_H_GSI;
    switch (hours)
    {
    case 0:
    case 12:
    case 24:
  #if defined(FRONTCOVER_CH_AG)   
      CH_H_ZWOELF;
      WEB_Uhrtext += F("Zw&ouml;ufi ");
  #else
      CH_H_ZWOELF;
      WEB_Uhrtext += F("Zw&ouml;lfi ");
  #endif      
      break;
    case 1:
    case 13:
//      if (glatt)
//      {
        CH_H_EIN;
        WEB_Uhrtext += F("Eis ");
//      }
//      else
//      {
//        CH_H_EINS;
//        WEB_Uhrtext += F("eis ");
//      }
        break;
    case 2:
    case 14:
      CH_H_ZWEI;
      WEB_Uhrtext += F("Zw&ouml;i ");
      break;
    case 3:
    case 15:
      CH_H_DREI;
      WEB_Uhrtext += F("Dr&uuml;&uuml; ");
      break;
    case 4:
    case 16:
      CH_H_VIER;
      WEB_Uhrtext += F("Vieri ");
      break;
    case 5:
    case 17:
      CH_H_FUENF;
      WEB_Uhrtext += F("F&ouml;ifi ");
      break;
    case 6:
    case 18:
      CH_H_SECHS;
      WEB_Uhrtext += F("S&auml;chsi ");
      break;
    case 7:
    case 19:
      CH_H_SIEBEN;
      WEB_Uhrtext += F("Sebni ");
      break;
    case 8:
    case 20:
      CH_H_ACHT;
      WEB_Uhrtext += F("Achti ");
      break;
    case 9:
    case 21:
      CH_H_NEUN;
      WEB_Uhrtext += F("N&uuml;&uuml;ni ");
      break;
    case 10:
    case 22:
      CH_H_ZEHN;
      WEB_Uhrtext += F("Z&auml;hni ");
      break;
    case 11:
    case 23:
  #if defined(FRONTCOVER_CH_AG) 
      CH_H_ELF;
      WEB_Uhrtext += F("Eufi ");
  #else
      CH_H_ELF;
      WEB_Uhrtext += F("Elfi ");
  #endif      
      break;
    }
    if (settings.mySettings.itIs) 
    {
      if (minute() % 5 ) WEB_Uhrtext += F("gsi");
//      if (glatt) WEB_Uhrtext += F("gsi");
    }
    
#endif

//########################################################################################################################
>>>>>>> 96b59cb4a65705bd521ef611a8bb5862bcff01f0
// ENGLISCH
//########################################################################################################################

#if defined(FRONTCOVER_EN)
		if (glatt)
			EN_OCLOCK;
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			EN_H_TWELVE;
      WEB_Uhrtext += F("twelve ");
			break;
		case 1:
		case 13:
			EN_H_ONE;
      WEB_Uhrtext += F("one ");
			break;
		case 2:
		case 14:
			EN_H_TWO;
      WEB_Uhrtext += F("two ");
			break;
		case 3:
		case 15:
			EN_H_THREE;
      WEB_Uhrtext += F("three ");
			break;
		case 4:
		case 16:
			EN_H_FOUR;
      WEB_Uhrtext += F("four ");
			break;
		case 5:
		case 17:
			EN_H_FIVE;
      WEB_Uhrtext += F("five ");
			break;
		case 6:
		case 18:
			EN_H_SIX;
      WEB_Uhrtext += F("six ");
			break;
		case 7:
		case 19:
			EN_H_SEVEN;
      WEB_Uhrtext += F("seven ");
			break;
		case 8:
		case 20:
			EN_H_EIGHT;
      WEB_Uhrtext += F("eight ");
			break;
		case 9:
		case 21:
			EN_H_NINE;
      WEB_Uhrtext += F("nine ");
			break;
		case 10:
		case 22:
			EN_H_TEN;
      WEB_Uhrtext += F("ten ");
			break;
		case 11:
		case 23:
			EN_H_ELEVEN;
      WEB_Uhrtext += F("eleven ");
			break;
		}
   if (glatt) WEB_Uhrtext += F("o'clock");
#endif

//########################################################################################################################
// SPANISCH
//########################################################################################################################

#if defined(FRONTCOVER_ES)
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			ES_H_DOCE;
      WEB_Uhrtext += F("doce ");
			break;
		case 1:
		case 13:
			ES_H_UNA;
      WEB_Uhrtext += F("una ");
			break;
		case 2:
		case 14:
			ES_H_DOS;
      WEB_Uhrtext += F("dos ");
			break;
		case 3:
		case 15:
			ES_H_TRES;
      WEB_Uhrtext += F("tres ");
			break;
		case 4:
		case 16:
			ES_H_CUATRO;
      WEB_Uhrtext += F("cuatro ");
			break;
		case 5:
		case 17:
			ES_H_CINCO;
      WEB_Uhrtext += F("cinco ");
			break;
		case 6:
		case 18:
			ES_H_SEIS;
      WEB_Uhrtext += F("seis ");
			break;
		case 7:
		case 19:
			ES_H_SIETE;
      WEB_Uhrtext += F("siete ");
			break;
		case 8:
		case 20:
			ES_H_OCHO;
      WEB_Uhrtext += F("ocho ");
			break;
		case 9:
		case 21:
			ES_H_NUEVE;
      WEB_Uhrtext += F("nueve ");
			break;
		case 10:
		case 22:
			ES_H_DIEZ;
      WEB_Uhrtext += F("diez ");
			break;
		case 11:
		case 23:
			ES_H_ONCE;
      WEB_Uhrtext += F("once ");
			break;
		}
#endif

//########################################################################################################################
// FRANZÖSISCH
//########################################################################################################################

#if defined(FRONTCOVER_FR)
		switch (hours)
		{
		case 0:
		case 24:
			FR_H_MINUIT;
      WEB_Uhrtext += F("minuit ");
			break;
		case 12:
			FR_H_MIDI;
      WEB_Uhrtext += F("midi ");
			break;
		case 1:
		case 13:
			FR_H_UNE;
      WEB_Uhrtext += F("une ");
			break;
		case 2:
		case 14:
			FR_H_DEUX;
      WEB_Uhrtext += F("deux ");
			break;
		case 3:
		case 15:
			FR_H_TROIS;
      WEB_Uhrtext += F("trois ");
			break;
		case 4:
		case 16:
			FR_H_QUATRE;
      WEB_Uhrtext += F("quatre ");
			break;
		case 5:
		case 17:
			FR_H_CINQ;
      WEB_Uhrtext += F("cinq ");
			break;
		case 6:
		case 18:
			FR_H_SIX;
      WEB_Uhrtext += F("six ");
			break;
		case 7:
		case 19:
			FR_H_SEPT;
      WEB_Uhrtext += F("sept ");
			break;
		case 8:
		case 20:
			FR_H_HUIT;
      WEB_Uhrtext += F("huit ");
			break;
		case 9:
		case 21:
			FR_H_NEUF;
      WEB_Uhrtext += F("neuf ");
			break;
		case 10:
		case 22:
			FR_H_DIX;
     WEB_Uhrtext += F("dix ");
			break;
		case 11:
		case 23:
			FR_H_ONZE;
      WEB_Uhrtext += F("onze ");
			break;
		}
#endif

//########################################################################################################################
// ITALIENISCH
//########################################################################################################################

#if defined(FRONTCOVER_IT)
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			IT_H_DODICI;
      WEB_Uhrtext += F("dodici ");
			break;
		case 1:
		case 13:
			IT_H_LUNA;
      WEB_Uhrtext += F("l'una ");
			break;
		case 2:
		case 14:
			IT_H_DUE;
      WEB_Uhrtext += F("due ");
			break;
		case 3:
		case 15:
			IT_H_TRE;
      WEB_Uhrtext += F("tre ");
			break;
		case 4:
		case 16:
			IT_H_QUATTRO;
      WEB_Uhrtext += F("quattro ");
			break;
		case 5:
		case 17:
			IT_H_CINQUE;
      WEB_Uhrtext += F("cinque ");
			break;
		case 6:
		case 18:
			IT_H_SEI;
      WEB_Uhrtext += F("sei ");
			break;
		case 7:
		case 19:
			IT_H_SETTE;
      WEB_Uhrtext += F("sette ");
			break;
		case 8:
		case 20:
			IT_H_OTTO;
      WEB_Uhrtext += F("otto ");
			break;
		case 9:
		case 21:
			IT_H_NOVE;
      WEB_Uhrtext += F("nove ");
			break;
		case 10:
		case 22:
			IT_H_DIECI;
      WEB_Uhrtext += F("dieci ");
			break;
		case 11:
		case 23:
			IT_H_UNDICI;
      WEB_Uhrtext += F("undici ");
			break;
		}
#endif

//########################################################################################################################
// NIEDERLÄNDISCH
//########################################################################################################################

#if defined(FRONTCOVER_NL)
		if (glatt)
			NL_UUR;
		switch (hours)
		{
		case 0:
		case 12:
		case 24:
			NL_H_TWAALF;
      WEB_Uhrtext += F("twaalf");
			break;
		case 1:
		case 13:
			NL_H_EEN;
      WEB_Uhrtext += F("een");
			break;
		case 2:
		case 14:
			NL_H_TWEE;
      WEB_Uhrtext += F("twee");
			break;
		case 3:
		case 15:
			NL_H_DRIE;
      WEB_Uhrtext += F("drie");
			break;
		case 4:
		case 16:
			NL_H_VIER;
      WEB_Uhrtext += F("vier");
			break;
		case 5:
		case 17:
			NL_H_VIJF;
      WEB_Uhrtext += F("vijf");
			break;
		case 6:
		case 18:
			NL_H_ZES;
      WEB_Uhrtext += F("zes");
			break;
		case 7:
		case 19:
			NL_H_ZEVEN;
      WEB_Uhrtext += F("zeven");
			break;
		case 8:
		case 20:
			NL_H_ACHT;
      WEB_Uhrtext += F("acht");
			break;
		case 9:
		case 21:
			NL_H_NEGEN;
      WEB_Uhrtext += F("negen");
			break;
		case 10:
		case 22:
			NL_H_TIEN;
      WEB_Uhrtext += F("tien");
			break;
		case 11:
		case 23:
			NL_H_ELF;
      WEB_Uhrtext += F("elf");
			break;
		}
    if (glatt) WEB_Uhrtext += F("uur");
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
#if defined(FRONTCOVER_CH) || defined(FRONTCOVER_CH_AG) || defined(FRONTCOVER_CH_AL)
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
#if defined(FRONTCOVER_CH) || defined(FRONTCOVER_CH_AG) || defined(FRONTCOVER_CH_AL)
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
  {
		ES_ESLA;
    if (settings.mySettings.itIs) 
    { 
<<<<<<< HEAD
      WEB_Uhrtext += F("es la ");
    }
    else 
    { 
      WEB_Uhrtext += "";
=======
      WEB_Uhrtext = F("es la ");
    }
    else 
    { 
      WEB_Uhrtext = "";
>>>>>>> 96b59cb4a65705bd521ef611a8bb5862bcff01f0
    }
  }
	else
  {
		ES_SONLAS;
    if (settings.mySettings.itIs) 
    { 
<<<<<<< HEAD
      WEB_Uhrtext += F("son las ");
    }
    else 
    { 
      WEB_Uhrtext += "";
=======
      WEB_Uhrtext = F("son las ");
    }
    else 
    { 
      WEB_Uhrtext = "";
>>>>>>> 96b59cb4a65705bd521ef611a8bb5862bcff01f0
    }
  }    
}
#endif

#if defined(FRONTCOVER_FR)
// Special case FR.
void Renderer::FR_hours(uint8_t hours, uint16_t matrix[])
{
	if ((hours == 1) || (hours == 13))
  {
		FR_HEURE;
    WEB_Uhrtext += F("heure ");
  }
	else
  {
		if ((hours == 0) || (hours == 12) || (hours == 24))
			;
		else
    {
			FR_HEURES;
      WEB_Uhrtext += F("heures ");
    }
  }
}
#endif

#if defined(FRONTCOVER_IT)
// Special case IT.
void Renderer::IT_hours(uint8_t hours, uint16_t matrix[])
{
	if ((hours != 1) && (hours != 13))
	{	
	  IT_SONOLE;
    if (settings.mySettings.itIs) 
    { 
<<<<<<< HEAD
      WEB_Uhrtext += F("Sono le ");
    }
    else 
    { 
      WEB_Uhrtext += "";
=======
      WEB_Uhrtext = F("Sono le ");
    }
    else 
    { 
      WEB_Uhrtext = "";
>>>>>>> 96b59cb4a65705bd521ef611a8bb5862bcff01f0
    }
	}
	else
  {
		IT_E;
    if (settings.mySettings.itIs) 
    { 
<<<<<<< HEAD
      WEB_Uhrtext += F("È ");
    }
    else 
    { 
      WEB_Uhrtext += "";
=======
      WEB_Uhrtext = F("È ");
    }
    else 
    { 
      WEB_Uhrtext = "";
>>>>>>> 96b59cb4a65705bd521ef611a8bb5862bcff01f0
    }
  }
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
