/* Bricks game
 */


#include "spiel_bricksCommon.h"

void bricksInit(){
#ifdef DEBUG_GAME
  Serial.println(F("Start Bricks"));
#endif
  positionPlayer = FIELD_WIDTH / 2;
  scorePlayer = 0;
  AktBall = 1;
  Stage = 0;
  hitPlayerC = false;
  ballX = positionPlayer;
  ballY = FIELD_HEIGHT-2;
  BalltoFloat();
  
  richtung = UP;
  steigung = random(2,20);
  if ( steigung == 10.0 ) steigung = steigung + 2.0;
  steigung = steigung / 10.0;
  ledDriver.clear();
  newBricks();
}

void runBricks(){
  gamecount[BRICKS]++;
  bricksInit();
  unsigned long prevUpdateTime = 0;
  boolean bricksRunning = true;
  gameisrunning = true;
  while(bricksRunning){    
    
    if ( AktBall > MAX_BAELLE ){
      bricksRunning = false;
      gameisrunning = false;
      break;
    }
    moveBall();
    checkBallHitByPaddle();
    checkBallOutOfBounds();
    if ( checkBlockCollision() ) checkBallOutOfBounds();
      
    checkBallLost();
    delay(10);
    webServer.handleClient();
    
    if ( bricks_left == 0 )
    {
       Stage++;
       if ( Stage >= COLOR_COUNT ) Stage = COLOR_COUNT; 
       newBricks(); 
       newBalltoPlayer();
    }
    
    ledDriver.clear();
    //  zeichne Balls left in die Eck Leds
    if ( AktBall <= 4 )
    {
      for(uint8_t i = AktBall ;i <= 4; i++)
      {
        ledDriver.setPixel(109+i,YELLOW,abcBrightness);
      }
    }
    else
    {
      for(uint8_t i = 1 ;i <= 4; i++)
      {
        ledDriver.setPixel(109+i,YELLOW,0); // lösche Eckpixel
      }
    }

    
    // zeichne Ball
    if ( ballX >= 0 && ballX < FIELD_WIDTH && ballY>=0 && ballY < FIELD_HEIGHT )
      ledDriver.setPixel(ballX,ballY,WHITE,abcBrightness);


    // zeichne Schläger
    if ( hitPlayerC ) 
    {
      hitPlayerC = false;
      ledDriver.setPixel(positionPlayer-1, FIELD_HEIGHT-1,ORANGE,abcBrightness);
      ledDriver.setPixel(positionPlayer, FIELD_HEIGHT-1,ORANGE,abcBrightness);
      ledDriver.setPixel(positionPlayer+1, FIELD_HEIGHT-1,ORANGE,abcBrightness);
    }
    else
    {
      ledDriver.setPixel(positionPlayer-1, FIELD_HEIGHT-1,YELLOW,abcBrightness);
      ledDriver.setPixel(positionPlayer, FIELD_HEIGHT-1,YELLOW,abcBrightness);
      ledDriver.setPixel(positionPlayer+1, FIELD_HEIGHT-1,YELLOW,abcBrightness);
    }
    
#ifdef DEBUG_GAME
    Serial.printf("Bricksball: %i / %i Schläger: %i / %i\n",ballX,ballY,positionPlayer,FIELD_HEIGHT-1);
#endif
    // zeichne Steine
    for(uint8_t blockX=0;blockX<FIELD_WIDTH;blockX++)                                       // Schleife über alle Blocks
    {
      for (uint8_t blockY=0;blockY<BlockMatrixHEIGHT;blockY++)
      {
        if(bricksmatrix[blockX][blockY] == 1)
        {
          ledDriver.setPixel(blockX,blockY,Stage,abcBrightness);
        }
      }
    }
    delay(10);
    webServer.handleClient();
    ledDriver.show();
    unsigned long curTime;
    boolean dirChanged = false;
    do{
      delay(10);
      webServer.handleClient();
      if (curControl == BTN_STOP || curControl == BTN_EXIT){
        bricksRunning = false;
        gameisrunning = false;
        break;
      }  
      if ( !dirChanged )             //Richtungswechel nur einmal pro Durchlauf
      {
        if ( readButton() )
        {
          if (curControl != BTN_NONE )
          {
            dirChanged = true;
            setPositionPaddle();
          }
        }
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
      curTime = millis();
    } 
    while ((curTime - prevUpdateTime) < START_DELAY - Stage * 10 );
    
    prevUpdateTime = curTime;
    aktscore = scorePlayer;
    if ( aktscore > highscore[BRICKS] ) highscore[BRICKS] = aktscore;
#ifdef DEBUG_GAME
    debugval = steigung * 100;
    if ( debugval == 0 ) debugval = 9999;
#endif
  }
}
//  ############### Ende runBricks() ########################

void moveBall(){
    if ( ballY < 7 ) hitPlayer = false;
#ifdef DEBUG_GAME
  Serial.printf("move Ball: (%i|%i) (%f|%f) r: %i / s: %f ",ballX,ballY,ballXf,ballYf, richtung,steigung);
#endif
//Serial.printf("moveBall-Bricksball start: r: %i / s: %f ( %i / %i ) ( %f / %f )\n",richtung,steigung,ballX,ballY,ballXf,ballYf);
    if ( steigung < 0.25 && steigung >= 0 ) steigung = 0.25;
    if ( steigung > -0.25 && steigung <= 0 ) steigung = -0.25;
    if ( steigung > 4.0 ) steigung = 4.0;
    if ( steigung < -4.0 ) steigung = -4.0;
    
    if ( steigung > 0.0 )
    {
      if ( steigung <= 1.0 )
      {
         ballXf=ballXf + float(richtung);
         ballYf=ballYf - float(richtung) * steigung;
      }
      else
      {
        ballXf=ballXf + float(richtung) / steigung;
        ballYf=ballYf - float(richtung);
      }
    }
    if ( steigung < 0.0 )
    {
      if ( steigung >= -1.0 )
      {
         ballXf=ballXf - float(richtung);
         ballYf=ballYf + float(richtung) * steigung;
      }
      else
      {
        ballXf=ballXf + float(richtung) / steigung;
        ballYf=ballYf - float(richtung);
      }
    }
    
    
    ballX=int(ballXf);
    if ( ballXf > 0.0 ) ballX=int(ballXf+0.5);
    if ( ballXf < 0.0 ) ballX=int(ballXf-0.5);
    ballY=int(ballYf);
    if ( ballYf > 0.0 ) ballY=int(ballYf+0.5);
    if ( ballYf < 0.0 ) ballY=int(ballYf-0.5);
    
    if ( ballY > FIELD_HEIGHT ) 
    {
      ballY = FIELD_HEIGHT;
      ballYf = ballY;
    }

#ifdef DEBUG_GAME
    Serial.printf("-> (%i|%i) (%f|%f) r: %i / s: %f \n",ballX,ballY, ballXf,ballYf,richtung,steigung);
#endif
}

void setPositionPaddle(){
  switch(curControl){
    case BTN_RIGHT:
      if(positionPlayer + 1 < FIELD_WIDTH-1){
        ++positionPlayer;
      } 
      else
      {
        ButtonClear();
      }
      break;
    case BTN_LEFT:
      if(positionPlayer - 1 > 0) {
        --positionPlayer;
      }
      else
      {
        ButtonClear();
      }
      break;
    case BTN_START:
      break;
    case BTN_UP:
      break;
    case BTN_DOWN:
      break;
  }
}

void checkBallHitByPaddle() {
  bool hitP = false;
  if(ballY == FIELD_HEIGHT-2 and hitPlayer == false )
  {
    ButtonClear();
    if (ballX == positionPlayer)
    {
      hitP = true;
      hitPlayer = true;
      steigung = steigung * -1.0;
      richtung = UP;
      BalltoFloat();
    } 
/*
    else if (ballX == positionPlayer - 1.0 && ballX == 0) 
    {
      hitP = true;
      hitPlayer = true;
      steigung = 1.2;
      richtung = UP;
      BalltoFloat();       
    }

    else if (ballX == positionPlayer + 1.0 && ballX == FIELD_WIDTH-1) 
    {
      hitP = true;
      hitPlayer = true;
      steigung = -1.2;
      richtung = UP;
      BalltoFloat();       
    }
*/
    else if (ballX == positionPlayer -1 && steigung < 0 ) // Schläger links von link getroffen
    {
      hitP = true;
      hitPlayer = true;
      steigung = steigung * -2.0;
      richtung = UP;
      BalltoFloat(); 
    }
    else if (ballX == positionPlayer -1 && steigung > 0) // Schläger links von rechts getroffen
    {
      hitP = true;
      hitPlayer = true;
      steigung = steigung * -0.5;
      richtung = UP;
      BalltoFloat(); 
    }      
    else if (ballX == positionPlayer -2 && steigung < 0 ) // Schläger links auf Spitze getroffen
    {
      hitP = true;
      hitPlayer = true;
      steigung = 1.0/steigung;
      richtung = UP;
      BalltoFloat();
    }     
    else if (ballX == positionPlayer + 1 && steigung > 0 ) // Schläger rechts von rechts getroffen
    {
      hitP = true;
      hitPlayer = true;
      steigung = steigung * -2.0;
      richtung = UP;
      BalltoFloat();
    }
    else if (ballX == positionPlayer + 1 && steigung < 0 ) // Schläger rechts von links getroffen
    {
      hitP = true;
      hitPlayer = true;
      steigung = steigung * -0.5; 
      richtung = UP;
      BalltoFloat();
    }
    else if (ballX == positionPlayer + 2 && steigung > 0 ) // Schläger rechts auf Spitze getroffen
    {
      hitP = true;
      hitPlayer = true;
      steigung = 1.0 / steigung;
      richtung = UP;
      BalltoFloat();
    } 
  } 
#ifdef DEBUG_GAME
  if ( hitP ) Serial.printf("checkBallHitByPaddle ende: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung, ballX, ballY);
#endif
  if ( hitP ) hitPlayerC = true;
}

//###################################################################

void checkBallOutOfBounds() {
  bool hitBound = false;
  
  if ( ballY > 0 ) hitTop = false;
  
  if ( ballY <= 0 ) 
  { 
    if ( richtung == UP && ! hitTop ) 
    {
      hitBound = true;
      hitTop = true;
      steigung = -steigung;
    }
    richtung = DOWN;
  } 
  
  if(ballX <= 0) 
  {
    hitBound = true;
    if ( richtung == UP ) 
    {
      if ( steigung < 0 ) steigung = -steigung;
    } 
    else
    {
      if ( steigung > 0 ) steigung = -steigung;
    }
  } 
  else if(ballX >= FIELD_WIDTH-1) 
  {
    hitBound = true;
    if ( richtung == UP ) 
    {
      if ( steigung > 0 ) steigung = -steigung;
    } 
    else
    {
      if ( steigung < 0 ) steigung = -steigung;
    }

  } 
#ifdef DEBUG_GAME
  if ( hitBound ) Serial.printf("checkBallOutOfBounds ende: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung, ballX, ballY);
#endif
}

void BalltoFloat()
{
  ballXf = ballX;
  ballYf = ballY;
}

bool checkBlockCollision(){
    int ballTop = ballY-rad;        
    int ballBottom = ballY+rad;
    int ballLeft = ballX-rad;
    int ballRight = ballX+rad;
    int richtung_neu = richtung;
    float steigung_neu = steigung;
    bool ballhitBlock;
    bool ballhitAnyBlock = false;


  do{
    ballhitBlock = false;
    if ( richtung == UP )  
    {
      if ( ballTop >= 0 && ballTop < BlockMatrixHEIGHT )
      {
        if(bricksmatrix[ballX][ballTop] == 1)    // Block oberhalb getroffen
        {
           ballhitBlock = true;
           bricksmatrix[ballX][ballTop] = 2;     // Block zum löschen vorsehen
           richtung_neu = richtung_neu * -1;     // Richtungsumkehr vorsehen
           steigung_neu = steigung_neu * -1.0;     // Steigungssumkehr vorsehen
#ifdef DEBUG_GAME
           Serial.printf("checkBlockCollision Block oberhalb getroffen: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung,ballX,ballTop);
#endif
        }        
      }
      if ( ballY >= 0 && ballY < BlockMatrixHEIGHT )
      {
        if ( ballLeft >= 0 )
        {
          if(bricksmatrix[ballLeft][ballY] == 1 && steigung < 0 )    // Block links getroffen
          {
            ballhitBlock = true;
            bricksmatrix[ballLeft][ballY] = 2;     // Block zum löschen vorsehen
            steigung_neu = steigung_neu * -1.0;      // Steigungssumkehr vorsehen
#ifdef DEBUG_GAME
            Serial.printf("checkBlockCollision Block links getroffen: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung,ballLeft,ballY);
#endif
          }
        }
        if ( ballRight < FIELD_WIDTH )
        {
          if(bricksmatrix[ballRight][ballY] == 1 && steigung > 0 )    // Block rechts getroffen
          {
            ballhitBlock = true;
            bricksmatrix[ballRight][ballY] = 2;     // Block zum löschen vorsehen
            steigung_neu = steigung_neu * -1.0;       // Steigungssumkehr vorsehen
#ifdef DEBUG_GAME
            Serial.printf("checkBlockCollision Block rechts getroffen: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung, ballRight,ballY);
#endif
          }
        }
      }
      if ( ballTop >= 0 && ballTop < BlockMatrixHEIGHT )
      { 
        if ( ballhitBlock == false && ballLeft >= 0 && ballTop >= 0 )
        {
          if(bricksmatrix[ballLeft][ballTop] == 1 && steigung < 0 )    // Block links schräg getroffen
          {
            ballhitBlock = true;
            bricksmatrix[ballLeft][ballTop] = 2;   // Block zum löschen vorsehen
            richtung_neu = richtung_neu * -1;      // Richtungsumkehr vorsehen
            steigung_neu = 1.0/steigung_neu;         // Steigungsänderung vorsehen
#ifdef DEBUG_GAME
            Serial.printf("checkBlockCollision Block links schräg getroffen: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung,ballLeft,ballTop);
#endif
          }
        }
        if ( ballhitBlock == false && ballRight < FIELD_WIDTH && ballTop >= 0 )
        {
          if(bricksmatrix[ballRight][ballTop] == 1 && steigung > 0 )    // Block rechts schräg getroffen
          {
            ballhitBlock = true;
            bricksmatrix[ballRight][ballTop] = 2;   // Block zum löschen vorsehen
            richtung_neu = richtung_neu * -1;      // Richtungsumkehr vorsehen
            steigung_neu = 1.0/steigung_neu;         // Steigungsänderung vorsehen
#ifdef DEBUG_GAME
            Serial.printf("checkBlockCollision Block rechts schräg getroffen: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung,ballRight,ballTop);
#endif
          }
        }
      }
    }

    if ( richtung == DOWN )  
    {
      if ( ballY >= 0 && ballBottom < BlockMatrixHEIGHT )
      {
        if(bricksmatrix[ballX][ballBottom] == 1)    // Block unterhalb getroffen
        {
           ballhitBlock = true;
           bricksmatrix[ballX][ballBottom] = 2;     // Block zum löschen vorsehen
           richtung_neu = richtung_neu * -1;     // Richtungsumkehr vorsehen
           steigung_neu = steigung_neu * -1.0;     // Steigungssumkehr vorsehen
#ifdef DEBUG_GAME
           Serial.printf("checkBlockCollision Block unterhalb getroffen: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung,ballX,ballBottom);
#endif
        }        
      }
      if ( ballY >= 0 && ballY < BlockMatrixHEIGHT )
      {
        if ( ballLeft >= 0 )
        {
          if(bricksmatrix[ballLeft][ballY] == 1 && steigung > 0 )    // Block links getroffen
          {
            ballhitBlock = true;
            bricksmatrix[ballLeft][ballY] = 2;     // Block zum löschen vorsehen
            if ( ballX != 0 ) steigung_neu = steigung_neu * -1.0;      // Steigungssumkehr vorsehen
#ifdef DEBUG_GAME
            Serial.printf("checkBlockCollision Block links getroffen: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung, ballLeft,ballY);
#endif
          }
        }
        if ( ballRight < FIELD_WIDTH )
        {
          if(bricksmatrix[ballRight][ballY] == 1 && steigung < 0 )    // Block rechts getroffen
          {
            ballhitBlock = true;
            bricksmatrix[ballRight][ballY] = 2;     // Block zum löschen vorsehen
            if ( ballX != 0 ) steigung_neu = steigung_neu * -1.0;       // Steigungssumkehr vorsehen
#ifdef DEBUG_GAME
            Serial.printf("checkBlockCollision Block rechts getroffen: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung, ballRight,ballY);
#endif
          }
        }
      }
      if ( ballY >= 0 && ballBottom < BlockMatrixHEIGHT )
      {
        if ( ballhitBlock == false && ballLeft >= 0 && ballBottom < BlockMatrixHEIGHT )
        {
          if(bricksmatrix[ballLeft][ballBottom] == 1 && steigung > 0 )    // Block links schräg getroffen
          {
            ballhitBlock = true;
            bricksmatrix[ballLeft][ballBottom] = 2;   // Block zum löschen vorsehen
            richtung_neu = richtung_neu * -1;      // Richtungsumkehr vorsehen
            steigung_neu = 1.0/steigung_neu;         // Steigungsänderung vorsehen
#ifdef DEBUG_GAME
            Serial.printf("checkBlockCollision Block links schräg getroffen: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung,ballLeft,ballBottom);
#endif
          }
        }
        if ( ballhitBlock == false && ballRight < FIELD_WIDTH && ballBottom < BlockMatrixHEIGHT )
        {
          if(bricksmatrix[ballRight][ballBottom] == 1 && steigung < 0 )    // Block rechts schräg getroffen
          {
            ballhitBlock = true;
            bricksmatrix[ballRight][ballBottom] = 2;   // Block zum löschen vorsehen
            richtung_neu = richtung_neu * -1;      // Richtungsumkehr vorsehen
            steigung_neu = 1.0/steigung_neu;         // Steigungsänderung vorsehen
#ifdef DEBUG_GAME
            Serial.printf("checkBlockCollision Block rechts schräg getroffen: r: %i ; s: %f | x: %i y: %i\n",richtung,steigung,ballRight,ballBottom);
#endif
          }
        }
      }
    }

    
//********************************************************************************************************
    if ( ballhitBlock ) 
    {
      ballhitAnyBlock = true;
      hitTop = false;
      BalltoFloat();
      richtung = richtung_neu;
      steigung = steigung_neu;
      for(uint8_t blockX=0;blockX<FIELD_WIDTH;blockX++)                    // Schleife über alle Blocks
      {
        for (uint8_t blockY=0;blockY<BlockMatrixHEIGHT;blockY++)
        {
          if(bricksmatrix[blockX][blockY] == 2)                            // soll der Block gelöscht werden?
          {
            bricksmatrix[blockX][blockY] = 0;                              // Block löschen
#ifdef DEBUG_GAME
            Serial.printf("checkBlockCollision Block: x: %i y: %i gelöscht\n",blockX,blockY);
#endif
            scorePlayer++;
            bricks_left--;
          }
        }
      }
    }
  } while ( ballhitBlock);  
  return ballhitAnyBlock;                                               
}

void checkBallLost()
{
  if(ballY >= FIELD_HEIGHT) 
  {
    AktBall++;
#ifdef AUDIO_SOUND
      if (gamesound) Play_MP3(800,false,33*gamesound);          //fail
#endif
    delay (300);
    if ( AktBall <= MAX_BAELLE )
    {
      newBalltoPlayer();
    }
#ifdef DEBUG_GAME
    Serial.printf("checkBallLost: neuer Ball: %i, Stage: %i\n", AktBall, Stage);
#endif
  } 
}

void newBalltoPlayer()
{
    for(uint8_t X=0;X<FIELD_WIDTH;X++)
    {
      ledDriver.setPixel(X,FIELD_HEIGHT-1,WHITE,0);
    }
    ledDriver.setPixel(positionPlayer-1, FIELD_HEIGHT-1,YELLOW,abcBrightness);
    ledDriver.setPixel(positionPlayer, FIELD_HEIGHT-1,YELLOW,abcBrightness);
    ledDriver.setPixel(positionPlayer+1, FIELD_HEIGHT-1,YELLOW,abcBrightness);
    for ( uint8_t b = 0; b <= abcBrightness; b++)
    {
      ledDriver.setPixel(positionPlayer,FIELD_HEIGHT-2,WHITE,b);
      if ( AktBall > 1 && AktBall <= 5) ledDriver.setPixel(108+AktBall,YELLOW,abcBrightness-b);
      ledDriver.show();
      delay (10);
    }
    ledDriver.setPixel(ballX,ballY,WHITE,0);
    ledDriver.show();
    delay (200);
    richtung = UP;
    ballY = FIELD_HEIGHT-2;
    ballX = positionPlayer;
    BalltoFloat();
}

void newBricks()
{
  bricks_left = ANZAHL_BRICKS;
#ifdef AUDIO_SOUND
      if (gamesound) Play_MP3(801,false,33*gamesound);          //neues Item
#endif
  delay (200);
  for (uint8_t blockY=0;blockY<=BlockMatrixHEIGHT;blockY++) // Schleife über alle Blocks
  {
    for(uint8_t blockX=0;blockX<FIELD_WIDTH;blockX++)
    {
      if ( blockY < BlockMatrixHEIGHT ) 
      {
        bricksmatrix[blockX][blockY] = 1;                   // Stein setzen
        ledDriver.setPixel(blockX,blockY,Stage,abcBrightness);
      }
      else bricksmatrix[blockX][blockY] = 0;
    }
    ledDriver.show();
    delay(80);
  }
}
