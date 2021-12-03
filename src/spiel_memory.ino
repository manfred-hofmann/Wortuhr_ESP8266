/* 
  * memory
*/

#define M_HEIGHT 6

// board 
#define SPIELER_RED -1
#define SPIELER_GREEN -2
#define SPIELER_YELLOW -3
#define SPIELER_BLUE -4

#define SPIELER_FARBE_DIV 3
#define FREIE_FARBE_DIV 6
#define SPIELER_FARBE_BLINK_DIV 1
#define FREIE_FARBE_BLINK_DIV 1

 struct s_mspieler {
    uint8_t rang;
    uint8_t paare;
    uint16_t spielzeit; 
    uint8_t farbe;
  };
uint8_t m_xoffset;
uint8_t m_yoffset;
uint8_t m_width_size;

void MemoryInit(uint8_t maudiobaseadd){
  gameisrunning = true;
  #ifdef DEBUG_GAME
    Serial.println(F("Start Memory"));
  #endif
  if ( gamesize == 1 ) m_width_size = 5;
  else if ( gamesize == 2 ) m_width_size = 7;
  else m_width_size = 9;
  
  m_xoffset = (FIELD_WIDTH - m_width_size)/2;
  m_yoffset = (FIELD_HEIGHT - M_HEIGHT)/2;
  initMBoard(maudiobaseadd);
  for ( uint8_t m=0; m<11;m++) mischeMBoard();
  showMBoard();
  ButtonClear();
#ifdef DEBUG_GAME
  printMBoard();
#endif
  aktivPlayer = 0;
}


void runMemory()
{
  uint16_t maudiobase = 0;
  if ( aktgame == TIERMEMORY )  
  {
    gamecount[TIERMEMORY]++;
    maudiobase = 810; // Tiersounds
  }
  if ( aktgame == MUSIKMEMORY ) 
  {
    gamecount[MUSIKMEMORY]++;
    maudiobase = 840; // Musiksounds
  }
  if ( aktgame == ABBAMEMORY ) 
  {
    gamecount[ABBAMEMORY]++;
    maudiobase = 870; // Abbasounds
  }
  // einen zufälligen Startaudiobereich bestimmen:
  uint8_t maudiobaseadd = 0;
  if ( aktgame == ABBAMEMORY ) 
  {
    if ( gamesize == 1 ) maudiobaseadd = random(0,13);
    else if ( gamesize == 2 ) maudiobaseadd = random(0,7);
    else maudiobaseadd = 0;
  }
  else
  {
    if ( gamesize == 1 ) maudiobaseadd = random(0,15);
    else if ( gamesize == 2 ) maudiobaseadd = random(0,9);
    else maudiobaseadd = random(0,3);    
  }
  
  MemoryInit(maudiobaseadd);
  
  uint8_t posAx = m_width_size / 2;
  uint8_t posAy = M_HEIGHT / 2;
  uint8_t posBx = 0;
  uint8_t posBy = 0;
 
  uint8_t mstep = 0;
  int8_t aktivMPlayer;    // Spieler im Borad bekommen eine neg. Zahl (-1 bis -4)
  int8_t prevPlayer=0;
  int8_t AKarte;          // Eine Soundkarte bekommt jeweils die pos. Zahl des Soundfiles 
  uint8_t fehlerhinweis = 0;
  unsigned long spielzeit = millis();
  
  unsigned long Ablinkzeit = millis();
  unsigned long Bblinkzeit = millis();  
  bool Aonoff = false;
  bool Bonoff = true;
  uint8_t paareges = M_HEIGHT*m_width_size/2;
  
  struct s_mspieler mspieler[5]{};
  for (uint8_t r = 1; r <= anzPlayer ; r++){ 
    mspieler[r].rang = r;
  }
  mspieler[1].farbe = RED;
  mspieler[2].farbe = GREEN;
  mspieler[3].farbe = YELLOW;
  mspieler[4].farbe = BLUE;
  
  bool MemoryRunning = true;

  if ( aktivPlayer == 0 ) aktivPlayer = random(1,anzPlayer+1);
  aktivMPlayer = aktivPlayer * -1;
  fadeMPlayer(WHITE,mspieler[aktivPlayer].farbe);

#ifdef DEBUG_GAME
    Serial.println("--- Memory ---");
    Serial.printf("AudioBase: %i!\n",maudiobase);
#endif
uint16_t audiolautstaerke = 33*gamesound;
//############################### Start Spiel-Loop
  while ( MemoryRunning )
  { 

#ifdef DEBUG_GAME
    Serial.println("------------------");
    Serial.printf("Spieler: %i ist dran %i. Karte!\n",aktivPlayer,mstep+1);
#endif
    MemoryRunning = moveMCursor(posAx, posAy, posBx, posBy, mstep );
    audiolautstaerke = 33*gamesound;
    if ( gamesound < 3 ) audiolautstaerke = audiolautstaerke + 20;
    if ( MemoryRunning )
    {
#ifdef DEBUG_GAME
      Serial.printf("MSTEP: %i , posAx: %i posAy: %i, posBx: %i, posBy: %i, SoundNrA: %i SoundNrB: %i\n",mstep,posAx,posAy,posBx,posBy,board[posAx][posAy],board[posBx][posBy]);
#endif
      switch (mstep){
// ############################## erste Karte ###########################################################
      case 0:                                       
// ############################## erste Karte: richtige Karte gedreht      
        if ( board[posAx][posAy] > 0 )                                          
        {
          AKarte = board[posAx][posAy];

#ifdef AUDIO_SOUND
#ifdef DEBUG_GAME
          Serial.printf("Play SoundA: x: %i , y: %i, SoundNr: %i Audiofile: %i\n",posAx,posAy, AKarte, maudiobase + board[posAx][posAy]);
#endif
          AudioBufferClear();
          AudioBufferIn(maudiobase + board[posAx][posAy]); 
          while ( PlayAudioBuffer(audiolautstaerke) || Soundaktiv() )
          {
            Aonoff = blinkeMKarte(posAx,posAy, Aonoff, Ablinkzeit, 100);
            delay(10);
            mstop_check(MemoryRunning);
          }
#endif
          posBy = posAy;
          posBx = posAx;
          finde_mleeresfeld(posBx,posBy);
          mstep = 1;
        }
        else
        {
// ############################## erste Karte: falsche Karte (farbige)
          falscheKarte(posAx,posAy,fehlerhinweis);
        }

      break;
// ############################## zweite Karte ###########################################################
      case 1:
// ############################## zweite Karte: die gleiche Karte nochmal gedreht: Spieler darf nochmal     
        if (posBx == posAx && posBy == posAy)                         
        {
#ifdef DEBUG_GAME
          Serial.printf("Play SoundA(nochmal): x: %i , y: %i, SoundNr: %i\n",posBx,posBy, board[posBx][posBy]);
#endif
#ifdef AUDIO_SOUND
          AudioBufferClear();
          AudioBufferIn(maudiobase + board[posAx][posAy]);    
          while ( PlayAudioBuffer(audiolautstaerke) || Soundaktiv() )
          {
            Aonoff = blinkeMKarte(posAx,posAy, Aonoff, Ablinkzeit, 100);
            delay(10);
            mstop_check(MemoryRunning);
          }
#endif
          posBy = posAy;
          posBx = posAx;
          finde_mleeresfeld(posBx,posBy);
        } 
// ############################## zweite Karte: eine richtige Karte gedreht         
        else if( board[posBx][posBy] > 0 && !(posBx == posAx && posBy == posAy) ) 
        {
#ifdef DEBUG_GAME
          Serial.printf("Play SoundB: x: %i , y: %i, SoundNr: %i\n",posBx,posBy, board[posBx][posBy]);
#endif
#ifdef AUDIO_SOUND
          AudioBufferClear();
          AudioBufferIn(maudiobase + board[posBx][posBy]); 
          while ( PlayAudioBuffer(audiolautstaerke) || Soundaktiv() )
          {
            Aonoff = blinkeMKarte(posAx,posAy, Aonoff, Ablinkzeit, 500);
            Bonoff = blinkeMKarte(posBx,posBy, Bonoff, Bblinkzeit, 100);
            delay(10);
            mstop_check(MemoryRunning);
          }
#endif          
// ############################## zweite Karte: Karte passt (gleich wie erste Karte)
          if ( board[posBx][posBy] == AKarte)
          {
            paareges--;
            
#ifdef DEBUG_GAME
            Serial.printf("Sound passt: A: %i , B: %i\n",AKarte, board[posBx][posBy]);
            Serial.printf("Paare übrig: %i\n",paareges);
#endif
// Score
            mspieler[aktivPlayer].paare++;
            mspieler[aktivPlayer].spielzeit =  (millis() - spielzeit)/100 + mspieler[aktivPlayer].spielzeit;
            Score_mSpieler( mspieler );
            
            board[posAx][posAy] = aktivMPlayer; // setze beide Karten auf den Aktiven Spieler 
            board[posBx][posBy] = aktivMPlayer;
#ifdef AUDIO_SOUND
            if (gamesound) 
            {
              AudioBufferClear();
              AudioBufferIn(807);               //Erfolg
              PABStatus = PlayAudioBuffer(33*gamesound);
            }
#endif
            for ( uint8_t l=0;l<8;l++)
            {
              delay(30);
              handle_Webserver(__LINE__);
            }
            fadeMPaar(posAx,posAy,posBx,posBy,mspieler[aktivPlayer].farbe);
            mstop_check(MemoryRunning);
            delay(10);
            ButtonClear();
            if ( paareges == 0 )
            {
              MemoryRunning = false;
              mSpielende( mspieler );
              delay(500);
              handle_Webserver(__LINE__);
              delay(500);
              handle_Webserver(__LINE__);
              delay(100);
              ButtonClear();
            }
          }
          else
// ############################## zweite Karte: Karte passt nicht (erste Karte war eine Andere)
          {
#ifdef DEBUG_GAME
            Serial.printf("Sound passt nicht: A: %i , B: %i\n",AKarte, board[posBx][posBy]);
#endif
            setzeMKarte(posAx,posAy);  
            setzeMKarte(posBx,posBy);
// Score
            mspieler[aktivPlayer].spielzeit = (millis() - spielzeit)/100 + mspieler[aktivPlayer].spielzeit;
            Score_mSpieler( mspieler );
            prevPlayer = aktivPlayer;
            if ( aktivPlayer + 1 > anzPlayer ) aktivPlayer = 1; //wechsle Spieler
            else aktivPlayer++;
            
            aktivMPlayer = aktivPlayer * -1;
            fadeMPlayer(mspieler[prevPlayer].farbe,mspieler[aktivPlayer].farbe);
#ifdef AUDIO_SOUND
            if ( anzPlayer > 1 ) 
            {
              AUDIO_FILENR = ANSAGEBASE + 500 + aktivPlayer;   // Spieler X ist dran
              if (gamesound) AudioBufferIn(AUDIO_FILENR);
            }
#endif
          }
          posAx = posBx;
          posAy = posBy;
          finde_mleeresfeld(posAx,posAy);
          spielzeit = millis();
          mstep = 0;
        }
        else
        {
// ############################## zweite Karte: falsche Karte (farbige): Spieler darf nochmal
          falscheKarte(posBx,posBy,fehlerhinweis);
        }
      break;
      }
    }
  }
//############################### Ende Spiel-Loop
}

//#####################################################################
//#####################################################################

void mstop_check(bool &MemoryRunning)  // prüfen ob die stop-Taste gedrückt wurde
{
  handle_Webserver(__LINE__);
  if (curControl == BTN_STOP || curControl == BTN_EXIT)
  {
    gameisrunning = false;
    MemoryRunning = false;
  }
}

void finde_mleeresfeld (uint8_t &xb, uint8_t &yb)
{
  int8_t addy, addx;
  
  for (uint8_t sr = 0; sr <= m_width_size; sr++)
  {
    for (uint8_t ay = 0; ay <= sr; ay++)
    {
      for (int8_t vorzy = 0; vorzy <= 1; vorzy++)
      {
        if (vorzy == 0) addy = ay * -1; else addy = ay;
        for (uint8_t ax = 0; ax <= sr; ax++)
        {
          for (int8_t vorzx = 0; vorzx <= 1; vorzx++)
          {
            if (vorzx == 0) addx = ax * -1; else addx = ax;
            if ( innerhalbMBoard(xb + addx,yb + addy))
            {
              if (board[xb + addx][yb + addy] > 0 && !( addx == 0 && addy == 0))
              {
                xb = xb + addx;
                yb = yb + addy;
                return;
              }
            }
          }
        }
      }
    }
  }
}



void Score_mSpieler (struct s_mspieler msp[]  )
{
   
   for (uint8_t s = 1; s <= anzPlayer ; s++)
   { 
     msp[s].rang = 1;
   } 

   for ( uint8_t s = 1; s <= anzPlayer; s++)
   {
     for (uint8_t v = 1; v <= anzPlayer ; v++)
     { 
        if ( msp[s].paare*100000 + 100000 - msp[s].spielzeit - s < msp[v].paare*100000 + 100000 - msp[v].spielzeit - v )
        {
          msp[s].rang++;
        }
     }
   }
   for (uint8_t s = 1; s <= anzPlayer ; s++)
   { 
     ledDriver.setPixel(109+msp[s].rang,msp[s].farbe,abcBrightness);
#ifdef DEBUG_GAME
     Serial.printf("Score Player %i : rang: %i , paare: %i , spielzeit: %i\n",s, msp[s].rang, msp[s].paare, msp[s].spielzeit);
#endif
   }
   ledDriver.show();
}



void falscheKarte (uint8_t posx, uint8_t posy, uint8_t &hinweis)
{
#ifdef AUDIO_SOUND
  if ( hinweis < 7 ) hinweis++;
  uint8_t audiohinweis=random(0,hinweis);
  if (gamesound) AudioBufferIn(ANSAGEBASE + 505 + board[posx][posy]*-1); // Farbe rot - blau
  PABStatus = PlayAudioBuffer(33*gamesound);
  if ( audiohinweis < 5 )
  {
    if (gamesound) AudioBufferIn(ANSAGEBASE + 510 + audiohinweis);  //Hinweis 1-5
  }
#endif
}

bool moveMCursor(uint8_t &posAx, uint8_t &posAy, uint8_t &posBx, uint8_t &posBy, uint8_t mstep )
{
  
  bool mcursorende = false;
  uint8_t posxneu, posyneu;
  uint8_t ansageverz=1;
  unsigned long Ablinkzeit = millis();
  unsigned long Bblinkzeit = millis();  
  unsigned long ansagezeit = millis(); 
  bool Aonoff = false;
  bool Bonoff = true;
  webServer.handleClient();
  delay(10);
  ButtonClear();

  switch(mstep){ 
    case 0:
      posxneu = posAx;
      posyneu = posAy;
      break;
    case 1:
      posxneu = posBx;
      posyneu = posBy;
      break;
  }
  
  do{
    if (curControl == BTN_STOP || curControl == BTN_EXIT){
      gameisrunning = false;
      mcursorende = true;
      break;
    }
    
    if ( readButton() )
    {
      if (curControl != BTN_NONE && gameisrunning )
      {
        setzeMKarte(posxneu,posyneu);
        if ( curControl == BTN_RIGHT + aktivPlayer*10 - 10 ) 
        { 
          if ( innerhalbMBoard(posxneu + 1, posyneu ) )
          {
            posxneu = posxneu + 1; 
#ifdef DEBUG_GAME
            Serial.printf("rechts: x: %i , y: %i\n",posxneu,posyneu);
#endif
          }
        }
        if ( curControl == BTN_LEFT + aktivPlayer*10 - 10 )  
        { 
          if ( innerhalbMBoard(posxneu - 1, posyneu ) )
          {
            posxneu = posxneu - 1;
#ifdef DEBUG_GAME
            Serial.printf("links: x: %i , y: %i\n",posxneu,posyneu);
#endif
          }
        }
        if ( curControl == BTN_DOWN + aktivPlayer*10 - 10 )  
        { 
          if ( innerhalbMBoard(posxneu, posyneu + 1 ) )
          {
            posyneu = posyneu + 1;
#ifdef DEBUG_GAME
            Serial.printf("runter: x: %i , y: %i\n",posxneu,posyneu);
#endif
          }
        }
        if ( curControl == BTN_UP + aktivPlayer*10 - 10 )    
        { 
          if ( innerhalbMBoard(posxneu, posyneu - 1 ) )
          {
            posyneu = posyneu - 1;
#ifdef DEBUG_GAME
            Serial.printf("hoch: x: %i , y: %i\n",posxneu,posyneu);
#endif
          }
        }
        ansagezeit = millis() + ansageverz*10000;
        if ( curControl == BTN_MIDDLE + aktivPlayer*10 - 10 ) return true;
      }
    }

    switch(mstep){ 
      case 0:
        Aonoff = blinkeMKarte(posxneu,posyneu, Aonoff, Ablinkzeit, 100);
        posAx = posxneu;
        posAy = posyneu;
        break;
      case 1:
        Aonoff = blinkeMKarte(posAx,posAy, Aonoff, Ablinkzeit, 500);
        posBx = posxneu;
        posBy = posyneu;
        Bonoff = blinkeMKarte(posBx,posBy, Bonoff, Bblinkzeit, 100);

        break;
    }
    
    
    #if defined(RTC_BACKUP) || defined(SENSOR_BME280)
      if ( lastMinute != minute() ) {
        lastMinute = minute();
        if ( (minute()%20) - 1  == 0 || ( minute()%20 == 0 ) )
        {
          #ifdef DEBUG_GAME
            Serial.println(F("aktuallisiere Temp- und Luftfeuchtigkeitswerte"));
          #endif 
          getRoomConditions(); // alle 20 Min. aktuallisieren/historisieren der Temp. und Luftfeuchtigkeitswerte Werte (00,01,20,21,40,41)
          
        }
      }
    #endif
    webServer.handleClient();
    delay(10); 
     
#ifdef AUDIO_SOUND 
    if ( millis() > ansagezeit + 20000 )
    {
      AUDIO_FILENR = ANSAGEBASE + 500 + aktivPlayer;   // Spieler X ist dran
      if (gamesound) AudioBufferIn(AUDIO_FILENR);
      ansagezeit = millis() + ansageverz*20000;
      ansageverz++;
      if ( ansageverz > 250 ) ansageverz = 250;
    }
    PABStatus = PlayAudioBuffer(33*gamesound);         
#endif
  } while ( !mcursorende );
  return false;
}


bool blinkeMKarte(uint8_t x, uint8_t y, bool onoff, unsigned long &blinkzeit, uint16_t blinkdelay)
{
   if ( millis() > blinkzeit + blinkdelay )
   {
      if ( onoff ) 
      { 
        ledDriver.setPixel(x+m_xoffset,y+m_yoffset,RED,0);
        ledDriver.show();
        blinkzeit = millis();
        return false;
      }
      else
      {
        if (board[x][y] == SPIELER_RED)
          ledDriver.setPixel(x+m_xoffset,y+m_yoffset,RED,abcBrightness/SPIELER_FARBE_BLINK_DIV);
        if (board[x][y] == SPIELER_GREEN)
          ledDriver.setPixel(x+m_xoffset,y+m_yoffset,GREEN,abcBrightness/SPIELER_FARBE_BLINK_DIV);
        if (board[x][y] == SPIELER_YELLOW)
          ledDriver.setPixel(x+m_xoffset,y+m_yoffset,YELLOW,abcBrightness/SPIELER_FARBE_BLINK_DIV);
        if (board[x][y] == SPIELER_BLUE)
          ledDriver.setPixel(x+m_xoffset,y+m_yoffset,BLUE,abcBrightness/SPIELER_FARBE_BLINK_DIV);
        if (board[x][y] >0)
          ledDriver.setPixel(x+m_xoffset,y+m_yoffset,WHITE,abcBrightness/FREIE_FARBE_BLINK_DIV);
        ledDriver.show();
        blinkzeit = millis();
        return true;
      }
   }
   else return onoff;
}

void setzeMKarte(uint8_t x, uint8_t y)
{
   if (board[x][y] == SPIELER_RED)
     ledDriver.setPixel(x+m_xoffset,y+m_yoffset,RED,abcBrightness/SPIELER_FARBE_DIV);
   if (board[x][y] == SPIELER_GREEN)
     ledDriver.setPixel(x+m_xoffset,y+m_yoffset,GREEN,abcBrightness/SPIELER_FARBE_DIV);
   if (board[x][y] == SPIELER_YELLOW)
     ledDriver.setPixel(x+m_xoffset,y+m_yoffset,YELLOW,abcBrightness/SPIELER_FARBE_DIV);
   if (board[x][y] == SPIELER_BLUE)
     ledDriver.setPixel(x+m_xoffset,y+m_yoffset,BLUE,abcBrightness/SPIELER_FARBE_DIV);
   if (board[x][y] >0)
     ledDriver.setPixel(x+m_xoffset,y+m_yoffset,WHITE,abcBrightness/FREIE_FARBE_DIV);
   ledDriver.show();
}

void fadeMPaar(uint8_t posAx, uint8_t posAy, uint8_t posBx, uint8_t posBy, uint8_t aktivfarbe)
{
    for ( uint8_t b=0 ;b<abcBrightness-6;b=b+5)
    {
       ledDriver.setPixel(posAx+m_xoffset,posAy+m_yoffset,aktivfarbe,b);
       ledDriver.setPixel(posBx+m_xoffset,posBy+m_yoffset,aktivfarbe,b);
       delay(1+(abcBrightness - b)/7);
       ledDriver.show();
    }
    for ( uint8_t b=abcBrightness ;b>abcBrightness/SPIELER_FARBE_DIV;b=b-5)
    {
      ledDriver.setPixel(posAx+m_xoffset,posAy+m_yoffset,aktivfarbe,b);
      ledDriver.setPixel(posBx+m_xoffset,posBy+m_yoffset,aktivfarbe,b);
      delay(25);
      ledDriver.show();
    }
}

bool innerhalbMBoard(int x, int y)
{
    return y>=0 && y<M_HEIGHT && x>=0 && x<m_width_size;
}

void initMBoard(uint8_t maudiobaseadd)
{
  uint8_t ms=1;
  for (uint8_t y = 0; y < M_HEIGHT ; y++){
    for (uint8_t x = 0; x < m_width_size ; x++){
      board[x][y]=ms+maudiobaseadd;
      ms++;
      if (ms > M_HEIGHT*m_width_size/2) ms=1;    
//      if (ms < 10 ) board[x][y]= SPIELER_RED;
//      if ( ms > 12 ) board[x][y]= SPIELER_GREEN;
    }
  }  
}

void mischeMBoard()
{
  uint8_t boardbuffer;
  uint8_t zxy;
  // vertausche zufällig x Werte
  for (uint8_t y = 0; y < M_HEIGHT ; y++){
    for (uint8_t x = 0; x < m_width_size ; x++){
      zxy = random(0,m_width_size); 
      boardbuffer = board[x][y];
      board[x][y] = board[zxy][y];
      board[zxy][y] = boardbuffer;
    }
    delay(1);
  }  
  // vertausche zufällig y Werte
  for (uint8_t x = 0; x < m_width_size ; x++){
    for (uint8_t y = 0; y < M_HEIGHT ; y++){
      zxy = random(0,M_HEIGHT); 
      boardbuffer = board[x][y];
      board[x][y] = board[x][zxy];
      board[x][zxy] = boardbuffer;
    }
    delay(1);
  }  
}

void fadeMPlayer(uint8_t prevcolor, uint8_t aktivcolor)
{

  for ( uint8_t fi=0;fi<=1;fi++)
  {
    for ( uint8_t b=0 ;b<abcBrightness/4;b++)
    {
      for(uint8_t x=0;x<FIELD_WIDTH;x++)
      {
        for(uint8_t y=0;y<FIELD_HEIGHT;y++)
        {
          if ( x < 1|| x >= FIELD_WIDTH-1 || y < 1 || y >= FIELD_HEIGHT-1) 
          {
            if ( fi == 0 && prevcolor != WHITE ) ledDriver.setPixel(x,y,prevcolor,abcBrightness/4-b);
            if ( fi == 1 ) ledDriver.setPixel(x,y,aktivcolor,b);
          }
        }
      }
      delay(30-10*fi);
      ledDriver.show();
    }
  }
}


void showMBoard()
{
  // Hintergrund
  ledDriver.clear();

    switch (anzPlayer) {
    case 4:
      ledDriver.setPixel(113,BLUE,abcBrightness);
    case 3:
      ledDriver.setPixel(112,YELLOW,abcBrightness);
    case 2:
      ledDriver.setPixel(111,GREEN,abcBrightness);
    case 1:
      ledDriver.setPixel(110,RED,abcBrightness);
    }
  
  //board
   for (uint8_t y = 0; y < M_HEIGHT ; y++){
    for (uint8_t x = 0; x < m_width_size ; x++){

      if (board[x][y] == SPIELER_RED)
        ledDriver.setPixel(x+m_xoffset,y+m_yoffset,RED,abcBrightness/SPIELER_FARBE_DIV);
      if (board[x][y] == SPIELER_GREEN)
        ledDriver.setPixel(x+m_xoffset,y+m_yoffset,GREEN,abcBrightness/SPIELER_FARBE_DIV);
      if (board[x][y] == SPIELER_YELLOW)
        ledDriver.setPixel(x+m_xoffset,y+m_yoffset,YELLOW,abcBrightness/SPIELER_FARBE_DIV);
      if (board[x][y] == SPIELER_BLUE)
        ledDriver.setPixel(x+m_xoffset,y+m_yoffset,BLUE,abcBrightness/SPIELER_FARBE_DIV);
      if (board[x][y] >0)
      ledDriver.setPixel(x+m_xoffset,y+m_yoffset,WHITE,abcBrightness / FREIE_FARBE_DIV);
    }
  }  
  ledDriver.show();
}

void printMBoard()
{
 Serial.printf("BOARD:\n");
 for (uint8_t y = 0; y < M_HEIGHT ; y++){
    Serial.printf("%i: ",y);
    for (uint8_t x = 0; x < m_width_size ; x++){
      if (board[x][y] > 0)
      Serial.printf("%2d ", board[x][y]);
      if (board[x][y] == SPIELER_GREEN)
      Serial.printf("GR ");
      if (board[x][y] == SPIELER_RED)
      Serial.printf("RE ");
      if (board[x][y] == SPIELER_YELLOW)
      Serial.printf("YE ");
      if (board[x][y] == SPIELER_BLUE)
      Serial.printf("BL ");
    }
    Serial.printf("\n");
  }  
  Serial.printf("\n");
}


//############################################################
//
void mSpielende( struct s_mspieler msp[] )
{
   uint8_t rangbasis = 0;
   unsigned long Eblinkzeit = millis();
   uint8_t Eonoff = 1;
   for(uint8_t rang = 1;rang<4;rang++)
   {
     for (uint8_t s = 1; s <= anzPlayer ; s++)
     { 
       if ( msp[s].rang == rang )
       {
#ifdef DEBUG_GAME
         Serial.printf("Spieler %i ist %i. mit %i Paare\n",s,rang, msp[s].paare);
#endif
         Eblinkzeit = millis();
         Eonoff = 0;
#ifdef AUDIO_SOUND
   uint16_t audiolautstaerke = 33*gamesound;
         if ( gamesound < 3 ) audiolautstaerke = audiolautstaerke + 20;
         AudioBufferIn(ANSAGEBASE + 520 + rangbasis + s);
         if ( msp[s].paare == 1 ) 
         {
          AudioBufferIn(ANSAGEBASE + 41);  // Ein
          AudioBufferIn(ANSAGEBASE + 519); // Paar
         }
         else
         {
           ZahltoAudioBuffer(ANSAGEBASE, msp[s].paare ); // X
           AudioBufferIn(ANSAGEBASE + 520);              // Paare
         }
         
         while ( PlayAudioBuffer(audiolautstaerke) || Soundaktiv() )
         {
           delay(10);
           if ( millis() > Eblinkzeit+200 )
           {
             for (uint8_t y = 0; y < M_HEIGHT ; y++)
             {
               for (uint8_t x = 0; x < m_width_size ; x++)
               {
                 if (board[x][y] == s*-1) ledDriver.setPixel(x+m_xoffset,y+m_yoffset, msp[s].farbe,abcBrightness*Eonoff);
               }
             } 
             if ( Eonoff ) Eonoff = 0; else Eonoff = 1;
             ledDriver.setPixel(109+msp[s].rang,msp[s].farbe,abcBrightness*Eonoff);
             ledDriver.show();
             Eblinkzeit = millis();
           }
         }
         delay(10);
         for (uint8_t y = 0; y < M_HEIGHT ; y++)
         {
           for (uint8_t x = 0; x < m_width_size ; x++)
           {
             if (board[x][y] == s*-1) ledDriver.setPixel(x+m_xoffset,y+m_yoffset, msp[s].farbe,abcBrightness/SPIELER_FARBE_DIV);
           }
         } 
         ledDriver.setPixel(109+msp[s].rang,msp[s].farbe,abcBrightness);
         ledDriver.show();
         delay(100);
#endif   
         rangbasis = rangbasis + 5;
       }
     }
   }
}
