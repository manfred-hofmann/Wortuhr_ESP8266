/******************************************************************************
Timezones.h
******************************************************************************/

#ifndef TIMEZONES_H
#define TIMEZONES_H

#ifdef TIMEZONE_IDLW
TimeChangeRule IDLW = { "IDLW", First, Sun, Jan, 1, -720 };
Timezone timeZone(IDLW, IDLW);
#endif

#ifdef TIMEZONE_SST
TimeChangeRule SST = { "SST", First, Sun, Jan, 1, -660 };
Timezone timeZone(SST, SST);
#endif

#ifdef TIMEZONE_HST
TimeChangeRule HST = { "HST", First, Sun, Jan, 1, -600 };
Timezone timeZone(HST, HST);
#endif

#ifdef TIMEZONE_AKST
TimeChangeRule usAKDT = { "AKDT", Second, Sun, Mar, 2, -480 };
TimeChangeRule usAKST = { "AKST", First, Sun, Nov, 2, -540 };
Timezone timeZone(usAKDT, usAKST);
#endif

#ifdef TIMEZONE_USPST
TimeChangeRule usPDT = { "PDT", Second, Sun, Mar, 2, -420 };
TimeChangeRule usPST = { "PST", First, Sun, Nov, 2, -480 };
Timezone timeZone(usPDT, usPST);
#endif

#ifdef TIMEZONE_USMST
TimeChangeRule usMDT = { "MDT", Second, Sun, Mar, 2, -360 };
TimeChangeRule usMST = { "MST", First, Sun, Nov, 2, -420 };
Timezone timeZone(usMDT, usMST);
#endif

#ifdef TIMEZONE_USAZ
TimeChangeRule usMST = { "MST", First, Sun, Nov, 2, -420 };
Timezone timeZone(usMST, usMST);
#endif

#ifdef TIMEZONE_USCST
TimeChangeRule usCDT = { "CDT", Second, Sun, Mar, 2, -300 };
TimeChangeRule usCST = { "CST", First, Sun, Nov, 2, -360 };
Timezone timeZone(usCDT, usCST);
#endif

#ifdef TIMEZONE_USEST
TimeChangeRule usEDT = { "EDT", Second, Sun, Mar, 2, -240 };
TimeChangeRule usEST = { "EST", First, Sun, Nov, 2, -300 };
Timezone timeZone(usEDT, usEST);
#endif

#ifdef TIMEZONE_AST
TimeChangeRule AST = { "AST", First, Sun, Jan, 1, -240 };
Timezone timeZone(AST, AST);
#endif

#ifdef TIMEZONE_BST
TimeChangeRule BST = { "BST", First, Sun, Jan, 1, -180 };
Timezone timeZone(BST, BST);
#endif

#ifdef TIMEZONE_VTZ
TimeChangeRule VTZ = { "VTZ", First, Sun, Jan, 1, -120 };
Timezone timeZone(VTZ, VTZ);
#endif

#ifdef TIMEZONE_AZOT
TimeChangeRule AZOT = { "AZOT", First, Sun, Jan, 1, -60 };
Timezone timeZone(AZOT, AZOT);
#endif

#ifdef TIMEZONE_GMT
TimeChangeRule BST = { "BST", Last, Sun, Mar, 1, 60 };
TimeChangeRule GMT = { "GMT", Last, Sun, Oct, 2, 0 };
Timezone timeZone(BST, GMT);
#endif

#ifdef TIMEZONE_CET
TimeChangeRule CEST = { "CEST", Last, Sun, Mar, 2, 120 };
TimeChangeRule CET = { "CET", Last, Sun, Oct, 3, 60 };
Timezone timeZone(CEST, CET);
#endif

#ifdef TIMEZONE_EST
TimeChangeRule EST = { "EST", First, Sun, Jan, 1, 120 };
Timezone timeZone(EST, EST);
#endif

#ifdef TIMEZONE_MSK
TimeChangeRule MSK = { "MSK", First, Sun, Jan, 1, 180 };
Timezone timeZone(MSK, MSK);
#endif

#ifdef TIMEZONE_GST
TimeChangeRule GST = { "GST", First, Sun, Jan, 1, 240 };
Timezone timeZone(GST, GST);
#endif

#ifdef TIMEZONE_PKT
TimeChangeRule PKT = { "PKT", First, Sun, Jan, 1, 300 };
Timezone timeZone(PKT, PKT);
#endif

#ifdef TIMEZONE_BDT
TimeChangeRule BDT = { "BDT", First, Sun, Jan, 1, 360 };
Timezone timeZone(BDT, BDT);
#endif

#ifdef TIMEZONE_JT
TimeChangeRule JT = { "JT", First, Sun, Jan, 1, 420 };
Timezone timeZone(JT, JT);
#endif

#ifdef TIMEZONE_CNST
TimeChangeRule CNST = { "CNST", First, Sun, Jan, 1, 480 };
Timezone timeZone(CNST, CNST);
#endif

#ifdef TIMEZONE_HKT
TimeChangeRule HKT = { "HKT", First, Sun, Jan, 1, 480 };
Timezone timeZone(HKT, HKT);
#endif

#ifdef TIMEZONE_PYT
TimeChangeRule PYT = { "PYT", First, Sun, Jan, 1, 510 };
Timezone timeZone(PYT, PYT);
#endif

#ifdef TIMEZONE_CWT
TimeChangeRule CWT = { "CWT", First, Sun, Jan, 1, 525 };
Timezone timeZone(CWT, CWT);
#endif

#ifdef TIMEZONE_JST
TimeChangeRule JST = { "JST", First, Sun, Jan, 1, 525 };
Timezone timeZone(JST, JST);
#endif

#ifdef TIMEZONE_ACST
TimeChangeRule ACST = { "ACST", First, Sun, Jan, 1, 570 };
Timezone timeZone(ACST, ACST);
#endif

#ifdef TIMEZONE_AEST
TimeChangeRule aEDT = { "AEDT", First, Sun, Oct, 2, 660 };
TimeChangeRule aEST = { "AEST", First, Sun, Apr, 3, 600 };
Timezone timeZone(aEDT, aEST);
#endif

#ifdef TIMEZONE_LHST
TimeChangeRule LHST = { "LHST", First, Sun, Jan, 1, 630 };
Timezone timeZone(LHST, LHST);
#endif

#ifdef TIMEZONE_SBT
TimeChangeRule SBT = { "SBT", First, Sun, Jan, 1, 660 };
Timezone timeZone(SBT, SBT);
#endif

#ifdef TIMEZONE_NZST
TimeChangeRule NZST = { "NZST", First, Sun, Jan, 1, 720 };
Timezone timeZone(NZST, NZST);
#endif

#endif
