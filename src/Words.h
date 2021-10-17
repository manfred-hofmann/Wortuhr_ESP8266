//******************************************************************************
// Words.h
//******************************************************************************

#ifndef WORDS_H
#define WORDS_H

#if defined(FRONTCOVER_CH) || defined(FRONTCOVER_CH_GS)

#define CH_VOR				matrix[2] |= 0b0000000011100000
#define CH_AB				matrix[3] |= 0b1100000000000000
#define CH_ESISCH			matrix[0] |= 0b1101111000000000
#define CH_GSI				matrix[9] |= 0b0000000011100000
#define CH_AM				matrix[9] |= 0b0000001100000000
#define CH_PM				matrix[3] |= 0b0000000001100000

#define CH_FUEF				matrix[0] |= 0b0000000011100000
#define CH_ZAEAE			matrix[1] |= 0b0000000011100000
#define CH_VIERTU			matrix[1] |= 0b1111110000000000
#define CH_ZWAENZG			matrix[2] |= 0b1111110000000000
#define CH_HAUBI			matrix[3] |= 0b0001111100000000

#define CH_H_EIS			matrix[4] |= 0b1110000000000000
#define CH_H_ZWOEI			matrix[4] |= 0b0001111000000000
#define CH_H_DRUE			matrix[4] |= 0b0000000011100000
#define CH_H_VIER			matrix[5] |= 0b1111100000000000
#define CH_H_FUEFI			matrix[5] |= 0b0000011110000000
#define CH_H_SAECHSI		matrix[6] |= 0b1111110000000000
#define CH_H_SIEBNI			matrix[6] |= 0b0000001111100000
#define CH_H_ACHTI			matrix[7] |= 0b1111100000000000
#define CH_H_NUENI			matrix[7] |= 0b0000011110000000
#define CH_H_ZAENI			matrix[8] |= 0b1111000000000000
#define CH_H_EUFI			matrix[8] |= 0b0000000111100000
#define CH_H_ZWOEUFI		matrix[9] |= 0b1111110000000000

#endif

#if defined(FRONTCOVER_D3)

#define D3_ESISCH			matrix[0] |= 0b1101111000000000
#define D3_VOR				matrix[3] |= 0b0000000011100000
#define D3_NACH				matrix[3] |= 0b1111000000000000
#define D3_AM				matrix[0] |= 0b1000000000000000
#define D3_PM				matrix[0] |= 0b0100000000000000

#define D3_FUENF			matrix[2] |= 0b0000000111100000
#define D3_ZEHN				matrix[2] |= 0b1111000000000000
#define D3_VIERTL			matrix[1] |= 0b0000111111000000
#define D3_HALB				matrix[4] |= 0b1111000000000000
#define D3_DREIVIERTL		matrix[1] |= 0b1111111111000000

#define D3_H_OISE			matrix[5] |= 0b1111000000000000
#define D3_H_ZWOIE			matrix[6] |= 0b1111100000000000
#define D3_H_DREIE			matrix[7] |= 0b1111100000000000
#define D3_H_VIERE			matrix[9] |= 0b0000001111100000
#define D3_H_FUENFE			matrix[4] |= 0b0000011111000000
#define D3_H_SECHSE			matrix[5] |= 0b0011111100000000
#define D3_H_SIEBNE			matrix[9] |= 0b1111110000000000
#define D3_H_ACHTE			matrix[6] |= 0b0000011111000000
#define D3_H_NEUNE			matrix[8] |= 0b0001111100000000
#define D3_H_ZEHNE			matrix[8] |= 0b1111100000000000
#define D3_H_ELFE			matrix[5] |= 0b0000000111100000
#define D3_H_ZWOELFE		matrix[7] |= 0b0000011111100000

#endif

#if defined(FRONTCOVER_DE_DE) || defined(FRONTCOVER_DE_SW) || defined(FRONTCOVER_DE_BA) || defined(FRONTCOVER_DE_SA)

#define DE_VOR				matrix[3] |= 0b1110000000000000
#define DE_NACH				matrix[3] |= 0b0000000111100000
#define DE_ESIST			matrix[0] |= 0b1101110000000000
#define DE_UHR				matrix[9] |= 0b0000000011100000
#define DE_AM				matrix[5] |= 0b0000011000000000
#define DE_PM				matrix[6] |= 0b0000110000000000

#define DE_FUENF			matrix[0] |= 0b0000000111100000
#define DE_ZEHN				matrix[1] |= 0b1111000000000000
#define DE_VIERTEL			matrix[2] |= 0b0000111111100000
#define DE_ZWANZIG			matrix[1] |= 0b0000111111100000
#define DE_HALB				matrix[4] |= 0b1111000000000000
#define DE_DREIVIERTEL		matrix[2] |= 0b1111111111100000

#define DE_H_EIN			matrix[5] |= 0b1110000000000000
#define DE_H_EINS			matrix[5] |= 0b1111000000000000
#define DE_H_ZWEI			matrix[5] |= 0b0000000111100000
#define DE_H_DREI			matrix[6] |= 0b1111000000000000
#define DE_H_VIER			matrix[6] |= 0b0000000111100000
#define DE_H_FUENF			matrix[4] |= 0b0000000111100000
#define DE_H_SECHS			matrix[7] |= 0b1111100000000000
#define DE_H_SIEBEN			matrix[8] |= 0b1111110000000000
#define DE_H_ACHT			matrix[7] |= 0b0000000111100000
#define DE_H_NEUN			matrix[9] |= 0b0001111000000000
#define DE_H_ZEHN			matrix[9] |= 0b1111000000000000
#define DE_H_ELF			matrix[4] |= 0b0000011100000000
#define DE_H_ZWOELF			matrix[8] |= 0b0000001111100000

#endif

#if defined(FRONTCOVER_DE_MKF_DE) || defined(FRONTCOVER_DE_MKF_SW) || defined(FRONTCOVER_DE_MKF_BA) || defined(FRONTCOVER_DE_MKF_SA)

#define DE_MKF_VOR			matrix[3] |= 0b0000001110000000
#define DE_MKF_NACH			matrix[3] |= 0b0011110000000000
#define DE_MKF_ESIST		matrix[0] |= 0b1101110000000000
#define DE_MKF_UHR			matrix[9] |= 0b0000000011100000
#define DE_MKF_AM			matrix[0] |= 0b1000000000000000
#define DE_MKF_PM			matrix[0] |= 0b0100000000000000

#define DE_MKF_FUENF		matrix[0] |= 0b0000000111100000
#define DE_MKF_ZEHN			matrix[1] |= 0b1111000000000000
#define DE_MKF_VIERTEL		matrix[2] |= 0b0000111111100000
#define DE_MKF_ZWANZIG		matrix[1] |= 0b0000111111100000
#define DE_MKF_HALB			matrix[4] |= 0b1111000000000000
#define DE_MKF_DREIVIERTEL	matrix[2] |= 0b1111111111100000

#define DE_MKF_H_EIN		matrix[5] |= 0b0011100000000000
#define DE_MKF_H_EINS		matrix[5] |= 0b0011110000000000
#define DE_MKF_H_ZWEI		matrix[5] |= 0b1111000000000000
#define DE_MKF_H_DREI		matrix[6] |= 0b0111100000000000
#define DE_MKF_H_VIER		matrix[7] |= 0b0000000111100000
#define DE_MKF_H_FUENF		matrix[6] |= 0b0000000111100000
#define DE_MKF_H_SECHS		matrix[9] |= 0b0111110000000000
#define DE_MKF_H_SIEBEN		matrix[5] |= 0b0000011111100000
#define DE_MKF_H_ACHT		matrix[8] |= 0b0111100000000000
#define DE_MKF_H_NEUN		matrix[7] |= 0b0001111000000000
#define DE_MKF_H_ZEHN		matrix[8] |= 0b0000011110000000
#define DE_MKF_H_ELF		matrix[7] |= 0b1110000000000000
#define DE_MKF_H_ZWOELF		matrix[4] |= 0b0000011111000000

#endif

#if defined(FRONTCOVER_EN)

#define EN_ITIS				matrix[0] |= 0b1101100000000000
#define EN_TIME				matrix[0] |= 0b0000000111100000
#define EN_A				matrix[1] |= 0b1000000000000000
#define EN_OCLOCK			matrix[9] |= 0b0000011111100000
#define EN_AM				matrix[0] |= 0b0000000110000000
#define EN_PM				matrix[0] |= 0b0000000001100000

#define EN_QUATER			matrix[1] |= 0b0011111110000000
#define EN_TWENTY			matrix[2] |= 0b1111110000000000
#define EN_FIVE				matrix[2] |= 0b0000001111000000
#define EN_HALF				matrix[3] |= 0b1111000000000000
#define EN_TEN				matrix[3] |= 0b0000011100000000
#define EN_TO				matrix[3] |= 0b0000000001100000
#define EN_PAST				matrix[4] |= 0b1111000000000000

#define EN_H_NINE			matrix[4] |= 0b0000000111100000
#define EN_H_ONE			matrix[5] |= 0b1110000000000000
#define EN_H_SIX			matrix[5] |= 0b0001110000000000
#define EN_H_THREE			matrix[5] |= 0b0000001111100000
#define EN_H_FOUR			matrix[6] |= 0b1111000000000000
#define EN_H_FIVE			matrix[6] |= 0b0000111100000000
#define EN_H_TWO			matrix[6] |= 0b0000000011100000
#define EN_H_EIGHT			matrix[7] |= 0b1111100000000000
#define EN_H_ELEVEN			matrix[7] |= 0b0000011111100000
#define EN_H_SEVEN			matrix[8] |= 0b1111100000000000
#define EN_H_TWELVE			matrix[8] |= 0b0000011111100000
#define EN_H_TEN			matrix[9] |= 0b1110000000000000

#endif

#if defined(FRONTCOVER_ES)

#define ES_SONLAS			matrix[0] |= 0b0111011100000000
#define ES_ESLA				matrix[0] |= 0b1100011000000000
#define ES_Y				matrix[6] |= 0b0000010000000000
#define ES_MENOS			matrix[6] |= 0b0000001111100000
#define ES_AM				matrix[0] |= 0b1000000000000000
#define ES_PM				matrix[0] |= 0b0100000000000000

#define ES_CINCO			matrix[8] |= 0b0000001111100000
#define ES_DIEZ				matrix[7] |= 0b0000000111100000
#define ES_CUARTO			matrix[9] |= 0b0000011111100000
#define ES_VEINTE			matrix[7] |= 0b0111111000000000
#define ES_VEINTICINCO		matrix[8] |= 0b1111111111100000
#define ES_MEDIA			matrix[9] |= 0b1111100000000000

#define ES_H_UNA			matrix[0] |= 0b0000000011100000
#define ES_H_DOS			matrix[1] |= 0b1110000000000000
#define ES_H_TRES			matrix[1] |= 0b0000111100000000
#define ES_H_CUATRO			matrix[2] |= 0b1111110000000000
#define ES_H_CINCO			matrix[2] |= 0b0000001111100000
#define ES_H_SEIS			matrix[3] |= 0b1111000000000000
#define ES_H_SIETE			matrix[3] |= 0b0000011111000000
#define ES_H_OCHO			matrix[4] |= 0b1111000000000000
#define ES_H_NUEVE			matrix[4] |= 0b0000111110000000
#define ES_H_DIEZ			matrix[5] |= 0b0011110000000000
#define ES_H_ONCE			matrix[5] |= 0b0000000111100000
#define ES_H_DOCE			matrix[6] |= 0b1111000000000000

#endif

#if defined(FRONTCOVER_FR)

#define FR_TRAIT			matrix[8] |= 0b0000010000000000
#define FR_ET				matrix[7] |= 0b1100000000000000
#define FR_LE				matrix[6] |= 0b0000001100000000
#define FR_MOINS			matrix[6] |= 0b1111100000000000
#define FR_ILEST			matrix[0] |= 0b1101110000000000
#define FR_HEURE			matrix[5] |= 0b0000011111000000
#define FR_HEURES			matrix[5] |= 0b0000011111100000
#define FR_AM				matrix[7] |= 0b0000000001100000
#define FR_PM				matrix[9] |= 0b0000000011000000

#define FR_CINQ				matrix[8] |= 0b0000001111000000
#define FR_DIX				matrix[6] |= 0b0000000011100000
#define FR_QUART			matrix[7] |= 0b0001111100000000
#define FR_VINGT			matrix[8] |= 0b1111100000000000
#define FR_DEMIE			matrix[9] |= 0b0001111100000000

#define FR_H_UNE			matrix[2] |= 0b0000111000000000
#define FR_H_DEUX			matrix[0] |= 0b0000000111100000
#define FR_H_TROIS			matrix[1] |= 0b0000001111100000
#define FR_H_QUATRE			matrix[1] |= 0b1111110000000000
#define FR_H_CINQ			matrix[3] |= 0b0000000111100000
#define FR_H_SIX			matrix[3] |= 0b0000111000000000
#define FR_H_SEPT			matrix[2] |= 0b0000000111100000
#define FR_H_HUIT			matrix[3] |= 0b1111000000000000
#define FR_H_NEUF			matrix[2] |= 0b1111000000000000
#define FR_H_DIX			matrix[4] |= 0b0011100000000000
#define FR_H_ONZE			matrix[5] |= 0b1111000000000000
#define FR_H_MIDI			matrix[4] |= 0b1111000000000000
#define FR_H_MINUIT			matrix[4] |= 0b0000011111100000

#endif

#if defined(FRONTCOVER_IT)

#define IT_SONOLE			matrix[0] |= 0b1111011000000000
#define IT_LE				matrix[0] |= 0b0000011000000000
#define IT_ORE				matrix[0] |= 0b0000000011100000
#define IT_E				matrix[1] |= 0b1000000000000000
#define IT_AM				matrix[0] |= 0b1000000000000000
#define IT_PM				matrix[0] |= 0b0100000000000000

#define IT_H_LUNA			matrix[1] |= 0b0011110000000000
#define IT_H_DUE			matrix[1] |= 0b0000000111000000
#define IT_H_TRE			matrix[2] |= 0b1110000000000000
#define IT_H_OTTO			matrix[2] |= 0b0001111000000000
#define IT_H_NOVE			matrix[2] |= 0b0000000111100000
#define IT_H_DIECI			matrix[3] |= 0b1111100000000000
#define IT_H_UNDICI			matrix[3] |= 0b0000011111100000
#define IT_H_DODICI			matrix[4] |= 0b1111110000000000
#define IT_H_SETTE			matrix[4] |= 0b0000001111100000
#define IT_H_QUATTRO		matrix[5] |= 0b1111111000000000
#define IT_H_SEI			matrix[5] |= 0b0000000011100000
#define IT_H_CINQUE			matrix[6] |= 0b1111110000000000

#define IT_MENO				matrix[6] |= 0b0000000111100000
#define IT_E2				matrix[7] |= 0b1000000000000000
#define IT_UN				matrix[7] |= 0b0011000000000000
#define IT_QUARTO			matrix[7] |= 0b0000011111100000
#define IT_VENTI			matrix[8] |= 0b1111100000000000
#define IT_CINQUE			matrix[8] |= 0b0000011111100000
#define IT_DIECI			matrix[9] |= 0b1111100000000000
#define IT_MEZZA			matrix[9] |= 0b0000001111100000

#endif

#if defined(FRONTCOVER_NL)

#define NL_VOOR				matrix[1] |= 0b0000000111100000
#define NL_OVER				matrix[2] |= 0b1111000000000000
#define NL_VOOR2			matrix[4] |= 0b1111000000000000
#define NL_OVER2			matrix[3] |= 0b0000000111100000
#define NL_HETIS			matrix[0] |= 0b1110110000000000
#define NL_UUR				matrix[9] |= 0b0000000011100000
#define NL_AM				matrix[0] |= 0b1000000000000000
#define NL_PM				matrix[0] |= 0b0100000000000000

#define NL_VIJF				matrix[0] |= 0b0000000111100000
#define NL_TIEN				matrix[1] |= 0b1111000000000000
#define NL_KWART			matrix[2] |= 0b0000001111100000
#define NL_ZWANZIG			matrix[1] |= 0b0000111111100000
#define NL_HALF				matrix[3] |= 0b1111000000000000

#define NL_H_EEN			matrix[4] |= 0b0000000111000000
#define NL_H_EENS			matrix[4] |= 0b0000000111100000
#define NL_H_TWEE			matrix[5] |= 0b1111000000000000
#define NL_H_DRIE			matrix[5] |= 0b0000000111100000
#define NL_H_VIER			matrix[6] |= 0b1111000000000000
#define NL_H_VIJF			matrix[6] |= 0b0000111100000000
#define NL_H_ZES			matrix[6] |= 0b0000000011100000
#define NL_H_ZEVEN			matrix[7] |= 0b1111100000000000
#define NL_H_ACHT			matrix[8] |= 0b1111000000000000
#define NL_H_NEGEN			matrix[7] |= 0b0000001111100000
#define NL_H_TIEN			matrix[8] |= 0b0000111100000000
#define NL_H_ELF			matrix[8] |= 0b0000000011100000
#define NL_H_TWAALF			matrix[9] |= 0b1111110000000000

#endif

#endif
