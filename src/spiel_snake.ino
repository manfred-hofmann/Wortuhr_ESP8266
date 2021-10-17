/* 
 * Snake game
 */

int curLength;               //Aktuelle Länge der Schlange
int xs[NUMPIXELS+1];         //Array mit allen Schlangen Elementen,
int ys[NUMPIXELS+1];         //Alle Pixel ist die max Länge
int dir;                     //Aktuelle Richtung der Schlange
int score;
uint8_t appletype = 0;
#define SNAKEWIDTH  1        //Länge der Schlange
#define MAXYELLOWAPPLE 12

boolean snakeGameOver;

int ax = 0;                  //Apfel x Position
int ay = 0;                  //Apfel y Position
uint8_t acolor = RED;

uint16_t debugtmp = 0;

//################################################

void snakeInit(){
  //Schlange Start-Position and Richtung
#ifdef DEBUG_GAME
  Serial.println(F("Start Snake"));
#endif
  debugval = 0;
  debugtmp = 0;
  curLength = 3;
  xs[0]=3; xs[1]=2; xs[2]=1;
  ys[0]=FIELD_HEIGHT/2; ys[1]=FIELD_HEIGHT/2; ys[2]=FIELD_HEIGHT/2;
  dir = DIR_RIGHT;
  score = 0;
  //Erzeuge eine zufällige Apfelposition mit einem roten Apfel
  ax = random(FIELD_WIDTH-1);
  ay = random(FIELD_HEIGHT-1);
  appletype = 0;
  snakeGameOver = false;
}

void runSnake(){
  snakeInit();
  gamecount[SNAKE]++;
  unsigned long prevUpdateTime = 0;
  boolean snakeRunning = true;
  gameisrunning = true;
  while(snakeRunning){    
    //Prüfe ob sich die Schlange selbst gebissen hat
    int i=curLength-1;
    while (i>=2){
      if (collide(xs[0], xs[i], ys[0], ys[i], SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH)){
        Serial.println("Selfcollision");
        die();
      }
      if ( i%10 == 0 ) 
      {
        delay(5);
        webServer.handleClient();
      }
      i = i-1;
    }
    
    if (snakeGameOver){
      snakeRunning = false;
      gameisrunning = false;
      break;
    }

    //Prüfe ob die Schlange den Apfel hat
    if (collide(xs[0], ax, ys[0], ay, SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH)){
      //Erhöhe Score ( gelber Apfel (>0) -> +3 roter Apfel (0) -> +1
      if ( appletype == 0 ) 
      {
        score = score +1;
      }
      else
      {
        score = score +3;
      }
      
      curLength = curLength +1;
      //Neues Schlangensegment
      xs[curLength-1] = 255;
      ys[curLength-1] = 255;
      
#ifdef AUDIO_SOUND
      if (gamesound) Play_MP3(700,false,33*gamesound - 20);
#endif
      delay(10);
      newApple();
    }
    if ( appletype > 0 ) appletype = appletype - 1;
    if ( appletype == 0 && acolor == YELLOW ) acolor = RED; // wenn die Zeit des gelben Apfels abgelaufen ist wird dieser rot
    //Verschiebe Schlange um 1 Position
    i = curLength-1;
    while (i>=1){
      xs[i] = xs[i-1];
      ys[i] = ys[i-1];
      i = i-1;
      if ( i%10 == 0 ) 
      {
        delay(5);
        webServer.handleClient();
      }
    }
    //Neue Position des Schlangenkopfs
    if (dir == DIR_RIGHT){
      xs[0] = xs[0] + SNAKEWIDTH;
    } 
    else if (dir == DIR_LEFT){
      xs[0] = xs[0] - SNAKEWIDTH;
    } 
    else if (dir == DIR_UP){
      ys[0] = ys[0] - SNAKEWIDTH;
    } 
    else {//DOWN
      ys[0] = ys[0] + SNAKEWIDTH;
    }
    
    //Prüfen ob außerhalb des Feldes
    if ((xs[0]<0) || (xs[0]>=FIELD_WIDTH) || (ys[0]<0) || (ys[0]>=FIELD_HEIGHT)){
      if (xs[0]<0) {xs[0] =FIELD_WIDTH -1;}
      else if (xs[0]>=FIELD_WIDTH) {xs[0] = 0;}      
      else if (ys[0]<0) {ys[0] =FIELD_HEIGHT -1;}
      else if (ys[0]>=FIELD_HEIGHT) {ys[0] = 0;}    
    }
    
    ledDriver.clear();

    //Zeichne Apfel
    ledDriver.setPixel(ax,ay,acolor,abcBrightness);

    //Zeichne Schlange
    for (int i=0; i<curLength; i++){
      if ( i%10 == 0 ) 
      {
        delay(5);
        webServer.handleClient();
      }
      if ( i > 2 && i%3 == 0 ) 
      {
        ledDriver.setPixelRGB(xs[i], ys[i], i*abcBrightness/curLength/2,i*abcBrightness/curLength/2,abcBrightness);
      }
      else ledDriver.setPixelRGB(xs[i], ys[i], i*abcBrightness/curLength/2,abcBrightness,i*abcBrightness/curLength/2);
    }
#ifdef DEBUG_GAME
    Serial.printf("Snake: x: %i , y: %i\n",xs[0],ys[0]);
#endif
    ledDriver.show();

    //Prüfe die Buttons Loop bis es weiter geht
    unsigned long curTime;
    boolean dirChanged = false;
    do{
      debugtmp++;
      delay(5);
      webServer.handleClient();
      if (curControl == BTN_STOP || curControl == BTN_EXIT){
          snakeRunning = false;
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
#ifdef AUDIO_SOUND
            if (gamesound) Play_MP3(806,false,33*gamesound - 20);          //snake
#endif
            setDirection();
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
    while ((curTime - prevUpdateTime) <300);
    prevUpdateTime = curTime;
    aktscore = score;
    if ( aktscore > highscore[SNAKE] ) highscore[SNAKE] = aktscore;
#ifdef DEBUG_GAME
    debugval = debugtmp;
    debugtmp = 0;
#endif
  }
}

//Neuer Apfel
void newApple()
{
    ax = random(FIELD_WIDTH-1);
    ay = random(FIELD_HEIGHT-1);
    if ( random(10) == 0) {  // ungefähr jeder 10ter Apfel ist ein gelber Apfel
      acolor = YELLOW;
      appletype = MAXYELLOWAPPLE;
    }
    else
    {
      acolor = RED;
      appletype = 0;
    }
    
    int i=curLength-1;
    for(int i=0; i<curLength; i++) {
      if (collide(ax, xs[i], ay, ys[i], SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH)){
         ax = random(FIELD_WIDTH-1);
         ay = random(FIELD_HEIGHT-1);
         i=0;
      }
    }
}

/* Setze neue Richtung */
void setDirection(){
  switch(curControl){
    case BTN_LEFT:
      dir = DIR_LEFT;
#ifdef DEBUG_GAME
Serial.println(F("links(3)"));
#endif      
      break;
    case BTN_RIGHT:
      dir = DIR_RIGHT;
#ifdef DEBUG_GAME
Serial.println(F("rechts(4)"));
#endif     
      break;
    case BTN_DOWN:
      dir = DIR_DOWN;
#ifdef DEBUG_GAME
Serial.println(F("runter(2)"));
#endif   
      break;
    case BTN_UP:
      dir = DIR_UP;
#ifdef DEBUG_GAME
Serial.println(F("hoch(1)"));
#endif   
      break;
    case BTN_START:
      break;
  }
}

/*Ende */
void die(){
  snakeGameOver = true;
#ifdef DEBUG_GAME
  Serial.println("die");
#endif 
}

/* Kollisions check */
boolean collide(int x1, int x2, int y1, int y2, int w1, int w2, int h1, int h2){
  if ((x1+w1>x2) && (x1<x2+w2) && (y1+h1>y2) && (y1<y2+h2)){
    return true;
  } 
  else {
    return false;
  }
}
