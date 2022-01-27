/* 
 * Main Tetris game
 */

#include "spiel_tetrisCommon.h"

uint16_t brickSpeed;
uint8_t nbRowsThisLevel;
uint16_t nbRowsTotal;
uint8_t nextbrick = random(7);


boolean tetrisGameOver;

void tetrisInit(){
#ifdef DEBUG_GAME
  Serial.println(F("Start Tetris"));
#endif
  clearField();
  brickSpeed = INIT_SPEED;
  nbRowsThisLevel = 0;
  nbRowsTotal = 0;
  aktscore= 0;
  tetrisGameOver = false;
  pixel_aktiv = 0;
  newActiveBrick();
}

boolean tetrisRunning = false;
void runTetris(void){
  tetrisInit();
  gamecount[TETRIS]++;
  gameisrunning = true;
  unsigned long prevUpdateTime = 0;
  
  tetrisRunning = true;
  while(tetrisRunning){
    unsigned long curTime;
    do{
      delay(10);
      webServer.handleClient();
      if ( readButton() ) {
        if (curControl == BTN_STOP || curControl == BTN_EXIT){
          tetrisGameOver = true;
          break;
        }
        if (curControl != BTN_NONE ){
          playerControlActiveBrick();
          printField();
        }
      }
      if (tetrisGameOver) break;

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
    } while ((curTime - prevUpdateTime) < brickSpeed); //Zeit bis der nächste Schritt kommt
    prevUpdateTime = curTime;
  
    if (tetrisGameOver){
      tetrisRunning = false;
      gameisrunning = false;
      break;
    }
  
    if (activeBrick.enabled){
      shiftActiveBrick(DIR_DOWN);
    } else {
      checkFullLines();
      newActiveBrick();
      prevUpdateTime = millis(); //Reset update time um doppelten Stein move zu verhindern
    }

    if ( checkFieldCollisionSound(&activeBrick) && activeBrick.enabled ) 
    {
#ifdef AUDIO_SOUND
      if (gamesound) Play_MP3(802,false,28*gamesound);   //impact
#endif
    delay(50);
    webServer.handleClient();
    delay(50);
    }
    printField();
  }
  
}

void playerControlActiveBrick(){
  switch(curControl){
    case BTN_LEFT:
#ifdef DEBUG_GAME
    Serial.println(F("links(3)"));
#endif  
      shiftActiveBrick(DIR_LEFT);
      break;
    case BTN_RIGHT:
#ifdef DEBUG_GAME
    Serial.println(F("rechts(4)"));
#endif 
      shiftActiveBrick(DIR_RIGHT);
      break;
    case BTN_DOWN:
#ifdef DEBUG_GAME
    Serial.println(F("runter(2)"));
#endif 
      shiftActiveBrick(DIR_DOWN);
      break;
    case BTN_MIDDLE:   
    case BTN_UP:
#ifdef DEBUG_GAME
    Serial.println(F("drehen(1)"));
#endif  
      rotateActiveBrick();
      break;
    case BTN_EXIT:
      tetrisRunning = false;
      break;
  }
}

void printField(){
  int x,y;
  for (x=0;x<FIELD_WIDTH;x++){
    for (y=0;y<FIELD_HEIGHT;y++){
      uint8_t activeBrickPix = 0;
      if (activeBrick.enabled){ //Nur Stein wenn er aktiv ist
        //Prüfen ob Stein sichtbar ist.
        if ((x>=activeBrick.xpos) && (x<(activeBrick.xpos+(activeBrick.siz)))
            && (y>=activeBrick.ypos) && (y<(activeBrick.ypos+(activeBrick.siz)))){
          activeBrickPix = (activeBrick.pix)[x-activeBrick.xpos][y-activeBrick.ypos];
        }
      }
      if (field.pix[x][y] == 1){
       ledDriver.setPixel(x,y,field.color[x][y],abcBrightness);
      } else if (activeBrickPix == 1){
          ledDriver.setPixel(x,y,activeBrick.color,abcBrightness);
      } else {
         ledDriver.setPixel(x,y,RED,0);  // Pixel löschen!
      }
    }
  }
  switch (nextbrick) {
    case 0:
      ledDriver.setPixel(110,BLUE,abcBrightness);
      ledDriver.setPixel(111,BLUE,abcBrightness);
      ledDriver.setPixel(112,BLUE,abcBrightness);
      ledDriver.setPixel(113,BLUE,abcBrightness);
    break;
    case 1:
      ledDriver.setPixel(110,RED,0);
      ledDriver.setPixel(111,RED,0);
      ledDriver.setPixel(112,RED,abcBrightness);
      ledDriver.setPixel(113,RED,abcBrightness);
    break;
    case 2:
      ledDriver.setPixel(110,YELLOW,abcBrightness);
      ledDriver.setPixel(111,YELLOW,0);
      ledDriver.setPixel(112,YELLOW,abcBrightness);
      ledDriver.setPixel(113,YELLOW,abcBrightness);
    break;
    case 3:
      ledDriver.setPixel(110,MAGENTA,0);
      ledDriver.setPixel(111,MAGENTA,abcBrightness);
      ledDriver.setPixel(112,MAGENTA,abcBrightness);
      ledDriver.setPixel(113,MAGENTA,abcBrightness);
    break;
    case 4:
      ledDriver.setPixel(110,GREEN,abcBrightness);
      ledDriver.setPixel(111,GREEN,0);
      ledDriver.setPixel(112,GREEN,0);
      ledDriver.setPixel(113,GREEN,abcBrightness);
    break;
    case 5:
      ledDriver.setPixel(110,ORANGE,0);
      ledDriver.setPixel(111,ORANGE,abcBrightness);
      ledDriver.setPixel(112,ORANGE,0);
      ledDriver.setPixel(113,ORANGE,abcBrightness);
    break;
    case 6:
      ledDriver.setPixel(110,CYAN,abcBrightness);
      ledDriver.setPixel(111,CYAN,0);
      ledDriver.setPixel(112,CYAN,abcBrightness);
      ledDriver.setPixel(113,CYAN,0);
    break;
  }
  
  ledDriver.show();
}

/* *** Game functions *** */

void newActiveBrick(){
//  uint8_t selectedBrick = 3;

#ifdef AUDIO_SOUND
      while (!digitalRead(PIN_AUDIO_BUSY)) {
        delay(20);
      }
      if (gamesound) Play_MP3(801,false,33*gamesound - 20);       // neues Item
#endif
  uint8_t selectedBrick = nextbrick;
  nextbrick = random(7);
  aktscore++;
  pixel_aktiv = pixel_aktiv + MAX_BRICK_SIZE;
  if ( aktscore > highscore[TETRIS] ) highscore[TETRIS] = aktscore;
#ifdef DEBUG_GAME
  Serial.printf("neuer Stein: %i\n",selectedBrick);
#endif 
  //Set properties of brick
  activeBrick.siz = brickLib[selectedBrick].siz;
  activeBrick.yOffset = brickLib[selectedBrick].yOffset;
  activeBrick.xpos = FIELD_WIDTH/2 - activeBrick.siz/2;
  activeBrick.ypos = BRICKOFFSET-activeBrick.yOffset;
  activeBrick.enabled = true;
  
  //Set color of brick
  activeBrick.color = brickLib[selectedBrick].color;
  //activeBrick.color = colorLib[1];
  
  //Copy pix array of selected Brick
  uint8_t x,y;
  for (y=0;y<MAX_BRICK_SIZE;y++){
    for (x=0;x<MAX_BRICK_SIZE;x++){
      activeBrick.pix[x][y] = (brickLib[selectedBrick]).pix[x][y];
    }
  }
  
  //Check collision, if already, then game is over
  if (checkFieldCollision(&activeBrick)){
    tetrisGameOver = true;
  }
}

//Check collision between bricks in the field and the specified brick
boolean checkFieldCollision(struct Brick* brick){
  uint8_t bx,by;
  uint8_t fx,fy;
  for (by=0;by<MAX_BRICK_SIZE;by++){
    for (bx=0;bx<MAX_BRICK_SIZE;bx++){
      fx = (*brick).xpos + bx;
      fy = (*brick).ypos + by;
      if (( (*brick).pix[bx][by] == 1) 
            && ( field.pix[fx][fy] == 1)){
        return true;
      }
    }
  }
  return false;
}

boolean checkFieldCollisionSound(struct Brick* brick){
  uint8_t bx,by;
  uint8_t fx,fy;
  for (by=0;by<MAX_BRICK_SIZE;by++){
    for (bx=0;bx<MAX_BRICK_SIZE;bx++){
      fx = (*brick).xpos + bx;
      fy = (*brick).ypos + by + 1;
      if (( (*brick).pix[bx][by] == 1) 
            && ( field.pix[fx][fy] == 1)){
        return true;
      }
    }
  }
  return false;
}

//Check Kollision zwischen Stein und den Seiten
boolean checkSidesCollision(struct Brick* brick){
  //Check vertical collision with sides of field
  uint8_t bx,by;
  uint8_t fx,fy;
  for (by=0;by<MAX_BRICK_SIZE;by++){
    for (bx=0;bx<MAX_BRICK_SIZE;bx++){
      if ( (*brick).pix[bx][by] == 1){
        fx = (*brick).xpos + bx; //Ermitteln der aktiven Position des Steins
        fy = (*brick).ypos + by;
        if (fx<0 || fx>=FIELD_WIDTH){
          return true;
        }
      }
    }
  }
  return false;
}

Brick tmpBrick;

void rotateActiveBrick(){
  // Kopiere den aktiven Stein 
  uint8_t x,y;
  for (y=0;y<MAX_BRICK_SIZE;y++){
    for (x=0;x<MAX_BRICK_SIZE;x++){
      tmpBrick.pix[x][y] = activeBrick.pix[x][y];
    }
  }
  tmpBrick.xpos = activeBrick.xpos;
  tmpBrick.ypos = activeBrick.ypos;
  tmpBrick.siz = activeBrick.siz;
  
  // Abhänging von der Steingröße wird anders gedreht
  if (activeBrick.siz == 3){
    //Rotation um den Zentralen Pixel
    tmpBrick.pix[0][0] = activeBrick.pix[0][2];
    tmpBrick.pix[0][1] = activeBrick.pix[1][2];
    tmpBrick.pix[0][2] = activeBrick.pix[2][2];
    tmpBrick.pix[1][0] = activeBrick.pix[0][1];
    tmpBrick.pix[1][1] = activeBrick.pix[1][1];
    tmpBrick.pix[1][2] = activeBrick.pix[2][1];
    tmpBrick.pix[2][0] = activeBrick.pix[0][0];
    tmpBrick.pix[2][1] = activeBrick.pix[1][0];
    tmpBrick.pix[2][2] = activeBrick.pix[2][0];
    // Alle anderen Teile leeren
    tmpBrick.pix[0][3] = 0;
    tmpBrick.pix[1][3] = 0;
    tmpBrick.pix[2][3] = 0;
    tmpBrick.pix[3][3] = 0;
    tmpBrick.pix[3][2] = 0;
    tmpBrick.pix[3][1] = 0;
    tmpBrick.pix[3][0] = 0;
    
  } else if (activeBrick.siz == 4){
    // Rotation um Kreuz
    tmpBrick.pix[0][0] = activeBrick.pix[0][3];
    tmpBrick.pix[0][1] = activeBrick.pix[1][3];
    tmpBrick.pix[0][2] = activeBrick.pix[2][3];
    tmpBrick.pix[0][3] = activeBrick.pix[3][3];
    tmpBrick.pix[1][0] = activeBrick.pix[0][2];
    tmpBrick.pix[1][1] = activeBrick.pix[1][2];
    tmpBrick.pix[1][2] = activeBrick.pix[2][2];
    tmpBrick.pix[1][3] = activeBrick.pix[3][2];
    tmpBrick.pix[2][0] = activeBrick.pix[0][1];
    tmpBrick.pix[2][1] = activeBrick.pix[1][1];
    tmpBrick.pix[2][2] = activeBrick.pix[2][1];
    tmpBrick.pix[2][3] = activeBrick.pix[3][1];
    tmpBrick.pix[3][0] = activeBrick.pix[0][0];
    tmpBrick.pix[3][1] = activeBrick.pix[1][0];
    tmpBrick.pix[3][2] = activeBrick.pix[2][0];
    tmpBrick.pix[3][3] = activeBrick.pix[3][0];
  } else {
    Serial.println("Brick size error");
  }
  
  //Prüfen der Kollisionen
  // Möglichkeiten:
  // - Stein klebt außerhalb
  // - Stein klebt innerhalb
  // Bei Kollision ist kein drehen mehr möglich
  if ((!checkSidesCollision(&tmpBrick)) && (!checkFieldCollision(&tmpBrick))){
    // Kopiere den Temp. Stein zurück
    for (y=0;y<MAX_BRICK_SIZE;y++){
      for (x=0;x<MAX_BRICK_SIZE;x++){
        activeBrick.pix[x][y] = tmpBrick.pix[x][y];
      }
    }
  }
}

// Verschiebe Stein links/rechts/runter (wenn möglich)
void shiftActiveBrick(int dir){
  // Ändere die Position des Steins
  if (dir == DIR_LEFT){
    activeBrick.xpos--;
  } else if (dir == DIR_RIGHT){
    activeBrick.xpos++;
  } else if (dir == DIR_DOWN){
    activeBrick.ypos++;
  }
  
  // Prüfen der Stein Postition
  // 2 Möglichkeiten bei Kollision
  // - Richtung Links/Rechts Postion zurücksetzen
  // - Richtung Runter, Position zurücksetzen und Stein festsetzen
  // Wenn keine Kollision, Stein Position unverändert
  if ((checkSidesCollision(&activeBrick)) || (checkFieldCollision(&activeBrick))){
    //Serial.println("coll");
    if (dir == DIR_LEFT){
      activeBrick.xpos++;
    } else if (dir == DIR_RIGHT){
      activeBrick.xpos--;
    } else if (dir == DIR_DOWN){
      activeBrick.ypos--;//gehe eins zurück nach oben
      addActiveBrickToField();
      activeBrick.enabled = false;//Disable brick, Stein ist nicht mehr zu bewegen!
    }
  }
}

// Kopiere den aktiven Stein ins Feld
void addActiveBrickToField(){
  uint8_t bx,by;
  uint8_t fx,fy;
  for (by=0;by<MAX_BRICK_SIZE;by++){
    for (bx=0;bx<MAX_BRICK_SIZE;bx++){
      fx = activeBrick.xpos + bx;
      fy = activeBrick.ypos + by;
      
      if (fx>=0 && fy>=0 && fx<FIELD_WIDTH && fy<FIELD_HEIGHT && activeBrick.pix[bx][by]){//check ob innerhalb vom Feld
        //field.pix[fx][fy] = field.pix[fx][fy] || activeBrick.pix[bx][by];
        field.pix[fx][fy] = activeBrick.pix[bx][by];
        field.color[fx][fy] = activeBrick.color;
      }
    }
  }
}

//Bewege alle Pixel ab. Startzeile wird überschrieben
void moveFieldDownOne(uint8_t startRow){
  if (startRow == 0){//Topmost row has nothing on top to move...
    return;
  }
  uint8_t x,y;
  for (y=startRow-1; y>0; y--){
    for (x=0;x<FIELD_WIDTH; x++){
      field.pix[x][y+1] = field.pix[x][y];
      field.color[x][y+1] = field.color[x][y];
    }
  }
}

void checkFullLines(){
  int x,y;
  int minY = 0;
  for (y=(FIELD_HEIGHT-1); y>=minY; y--){
    uint8_t rowSum = 0;
    for (x=0; x<FIELD_WIDTH; x++){
      rowSum = rowSum + (field.pix[x][y]);
    }
    if (rowSum>=FIELD_WIDTH){
       // Ganze Zeile gefunden 
      pixel_aktiv = pixel_aktiv - FIELD_WIDTH;
#ifdef AUDIO_SOUND
      AudioBufferClear();
      if (gamesound) 
      {
        while ( Soundaktiv() ) // warte bis Sound zu Ende ist
        {    
          delay(5);
        }
        Play_MP3(803,false,33*gamesound);       //slide
        while ( !Soundaktiv() ) // warte bis Sound läuft
        {    
          delay(5);
        }
      }
#endif
     
      delay(200);
      //starte Löschanimation
      for (x=0;x<FIELD_WIDTH; x++){
        field.pix[x][y] = 0;
        printField();
        delay(100);
      }
#ifdef AUDIO_SOUND
      if (gamesound && pixel_aktiv > 0 ) 
      {
        while ( Soundaktiv() ) // warte bis Sound zu Ende ist
        {    
          delay(5);
        }
        AudioBufferIn(802);             //impact
        PlayAudioBuffer(29*gamesound);
        while ( !Soundaktiv() ) // warte bis Sound läuft
        {    
          delay(5);
        }
      }
#endif
      // Bewege alle Zeilen oberhalb eins runter
      delay(450);
      moveFieldDownOne(y);
      y++; minY++;
      printField();
#ifdef AUDIO_SOUND
      while ( Soundaktiv() )
      {    
        delay(10);
        webServer.handleClient();
      }
#endif
      
      nbRowsThisLevel++; nbRowsTotal++;
      if (nbRowsThisLevel >= LEVELUP){
        nbRowsThisLevel = 0;
        brickSpeed = brickSpeed - SPEED_STEP;
        if (brickSpeed<200){
          brickSpeed = 200;
        }
      }
    }
  }
}

void clearField(){
  uint8_t x,y;
  for (y=0;y<FIELD_HEIGHT;y++){
    for (x=0;x<FIELD_WIDTH;x++){
      field.pix[x][y] = 0;
      field.color[x][y] = 0;
    }
  }
  for (x=0;x<FIELD_WIDTH;x++){// Die letzte Zeile ist nur virtuelle und wird zum Kollisionscheck benötigt
    field.pix[x][FIELD_HEIGHT] = 1; 
  }
}
