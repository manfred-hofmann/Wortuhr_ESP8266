#include "spiel_main.h"

// Starte Animationsmenü
void startGame()
{
 String webstring;
 String gamestring;
#ifdef DEBUG_GAME
  Serial.print("Start Game: ");
  Serial.println(webServer.arg("game"));
#endif
  aktgame = webServer.arg("game").toInt();
  if ( aktgame == SNAKE )
    gamestring = "SNAKE";
  if ( aktgame == TETRIS )
    gamestring = "TETRIS";
  if ( aktgame == BRICKS )
    gamestring = "BRICKS";
  if ( aktgame == VIERGEWINNT )
    gamestring = "VIERGEWINNT";
  aktscore = 0;
  webstring = F("<!doctype html><html><head><script>window.onload=function(){window.location.replace('/GameControl.html?game=");
  webstring += gamestring;
  webstring += F("&highscore=");
  webstring += String(highscore[aktgame]);
  #ifdef AUDIO_SOUND
    webstring += "&sound=" + String(gamesound);
  #else
    webstring += F("&sound=-1");
    gamesound = 0;
  #endif
  if (aktgame == VIERGEWINNT) 
  {
    webstring += F("&level=");
    webstring += String(gamelevel);
  }
   
  webstring += F("');}</script></head></html>");
  webServer.send(200, "text/html",webstring);
#ifdef AUDIO_SOUND
      AUDIO_FILENR = ANSAGEBASE + 180 + aktgame;
      if (gamesound) Play_MP3(AUDIO_FILENR,false,33*gamesound);
#endif
  curControl= BTN_NONE;  
  handle_Webserver(__LINE__);
  delay(0);
}

void handleGameControl()
{
  bool buttonret;
  String webreturn;
  if ( webServer.arg("button") == "start" ) 
  {

#ifdef DEBUG_GAME
      webreturn += "1#" + String(highscore[aktgame]) + "#" + String(aktscore) + "#" + String(debugval);
#else
      webreturn += "1#" + String(highscore[aktgame]) + "#" + String(aktscore) + "#0";
#endif 

    webServer.send(200, "text/plain", webreturn); 
    handle_Webserver(__LINE__);
    delay(0);
    ButtonClear();
    setMode(MODE_GAME);
    if ( aktgame == SNAKE       ) runSnake();
    if ( aktgame == TETRIS      ) runTetris();
    if ( aktgame == BRICKS      ) runBricks();
    if ( aktgame == VIERGEWINNT ) runViergewinnt();
    handle_Webserver(__LINE__);
    delay(0);
    ButtonClear();
#ifdef DEBUG_GAME
  Serial.println(F("Game over"));
#endif
    gameisrunning = false;
    delay(500);

// sichern der Higshcore Werte
    if (  highscore[SNAKE] > settings.mySettings.highscore[SNAKE] || highscore[TETRIS] > settings.mySettings.highscore[TETRIS] 
       || highscore[BRICKS] > settings.mySettings.highscore[BRICKS] || highscore[VIERGEWINNT] > settings.mySettings.highscore[VIERGEWINNT] ) 
    {
#ifdef DEBUG_GAME
  Serial.println(F("sichere Highscore in EEPROM"));
#endif
      settings.mySettings.highscore[SNAKE] = highscore[SNAKE];
      settings.mySettings.highscore[TETRIS] = highscore[TETRIS];
      settings.mySettings.highscore[BRICKS] = highscore[BRICKS];
      settings.mySettings.highscore[VIERGEWINNT] = highscore[VIERGEWINNT];
      settings.saveToEEPROM();
    }
    delay(500);
    webServer.handleClient();
    if (curControl != BTN_STOP && aktgame != VIERGEWINNT)
    {
      delay(800);
#ifdef AUDIO_SOUND
      AUDIO_FILENR = ANSAGEBASE + 180;
      if (gamesound) Play_MP3(AUDIO_FILENR,false,33*gamesound);
#endif
      delay(200);
      webServer.handleClient();
      uint8_t gor = random(3);
      if ( gor == 0 ) {
#ifdef DEBUG_GAME
  Serial.println(F("Game over Animation"));
#endif
         animation = "GAME_OVER";
         mode = MODE_TIME;
         playanimation = true;
         screenBufferNeedsUpdate = true;
         setMode(MODE_TIME);
      }
      if ( gor == 1 ) {
#ifdef DEBUG_GAME
  Serial.println(F("Game over Pixel"));
#endif
        ledDriver.clear();
        ledDriver.setPixel(10,1,YELLOW,abcBrightness);
        ledDriver.show();
        delay(200);
        ledDriver.setPixel(8,3,YELLOW,abcBrightness);
        ledDriver.show();
        delay(200);
        ledDriver.setPixel(6,5,YELLOW,abcBrightness);
        ledDriver.show();
        delay(200);
        ledDriver.setPixel(4,8,YELLOW,abcBrightness);
        ledDriver.show();
        delay(200);
        webServer.handleClient();
        ledDriver.setPixel(1,3,RED,abcBrightness);
        ledDriver.show();
        delay(200);
        ledDriver.setPixel(4,2,RED,abcBrightness);
        ledDriver.show();
        delay(200);
        ledDriver.setPixel(5,4,RED,abcBrightness);
        ledDriver.show();
        delay(200);
        ledDriver.setPixel(7,2,RED,abcBrightness);
        ledDriver.show();
        delay(1000);
        webServer.handleClient();
        delay(1000);
        webServer.handleClient();
        screenBufferNeedsUpdate = true;
        setMode(MODE_TIME);
      }
      if ( gor == 2 ) {
#ifdef DEBUG_GAME
  Serial.println(F("Game over Feed"));
#endif
          feedColor = MAGENTA;
          feedText = F("  Game Over   ");
          feedPosition = 0;
          renderer.clearScreenBuffer(matrix);
          renderer.clearScreenBuffer(matrixOld);
          setMode(MODE_FEED);
      }
    }
    else
    {
      screenBufferNeedsUpdate = true;
    }
    
#ifdef DEBUG_GAME
  Serial.println(F("zurück zur Uhr..."));
#endif
  }
  else
  {
    if ( webServer.arg("button") == "stop" ) {
      curControl= BTN_STOP;
      buttonret = ButtonIn(BTN_STOP);
    }
    
    if ( webServer.arg("button") == "sound0" ) gamesound = 0;
    if ( webServer.arg("button") == "sound1" ) gamesound = 1;
    if ( webServer.arg("button") == "sound2" ) gamesound = 2;
    if ( webServer.arg("button") == "sound3" ) gamesound = 3;
    if ( webServer.arg("button") == "sound1" || webServer.arg("button") == "sound2" || webServer.arg("button") == "sound3" )
    {
#ifdef AUDIO_SOUND
      if (gamesound) Play_MP3(700,false,33*gamesound);
#endif
    }
    
    if ( webServer.arg("gb") == "up" ) buttonret = ButtonIn(BTN_UP);
    if ( webServer.arg("gb") == "down" ) buttonret = ButtonIn(BTN_DOWN);
    if ( webServer.arg("gb") == "left" ) buttonret = ButtonIn(BTN_LEFT);
    if ( webServer.arg("gb") == "right" ) buttonret = ButtonIn(BTN_RIGHT);

    if ( webServer.arg("level").length() > 0) 
    {
      gamelevel = webServer.arg("level").toInt();
#ifdef DEBUG_GAME
      Serial.printf("GameLevel: %i\n",gamelevel);
#endif      
    }
    
    if ( webServer.arg("button") == "back" )
    {
#ifdef DEBUG_GAME
      webreturn += "0#" + String(highscore[aktgame]) + "#" + String(aktscore) + "#" + String(debugval);
#else
      webreturn += "0#" + String(highscore[aktgame]) + "#" + String(aktscore) + "#0";
#endif

      webServer.send(200, "text/plain", webreturn); 
      buttonret = ButtonIn(BTN_EXIT);
      curControl= BTN_NONE;
      setMode(MODE_TIME);
      callRoot();
    }
    if ( webServer.arg("poll") == "poll" ) 
    {
#ifdef DEBUG_GAME
      Serial.println(F("Web Poll"));
#endif
    }
#ifdef DEBUG_GAME
      Serial.printf("Debugval: %i\n",debugval);
#endif
    if ( gameisrunning ) webreturn = "1#"; else webreturn = "0#";
#ifdef DEBUG_GAME
    webreturn += String(highscore[aktgame]) + "#" + String(aktscore)+ "#" + String(debugval);
#else
    webreturn += String(highscore[aktgame]) + "#" + String(aktscore) + "#0";
#endif
    webServer.send(200, "text/plain", webreturn);
  }
}


// IO-Buffer zum Einlesen der Buttons
#define CURCONTROL_BUFFER_SIZE 8
#define CURCONTROL_BUFFER_MASK (CURCONTROL_BUFFER_SIZE-1)
struct ButtonBuffer {
  uint8_t data[CURCONTROL_BUFFER_SIZE];
  uint8_t read; // zeigt auf das Feld mit dem ältesten Inhalt
  uint8_t write; // zeigt immer auf leeres Feld
} buttonbuffer = {{}, 0, 0};

bool ButtonIn(uint8_t buttonvalue)
{
#ifdef DEBUG_GAME
  Serial.printf("Button write: value: %i, write %i read %i\n", buttonvalue, buttonbuffer.write, buttonbuffer.read);
#endif 
  uint8_t next = ((buttonbuffer.write + 1) & CURCONTROL_BUFFER_MASK);

  if (buttonbuffer.read == next)
    return false; // voll

  buttonbuffer.data[buttonbuffer.write] = buttonvalue;
  // buttonbuffer.data[buttonbuffer.write & CURCONTROL_BUFFER_MASK] = buttonvalue; // absolut Sicher
  buttonbuffer.write = next;

  return true;
}

bool readButton()
{


  if (buttonbuffer.read == buttonbuffer.write)
  {
    curControl = BTN_NONE;
    return false;
  }
  
#ifdef DEBUG_GAME
  Serial.printf("Button read: value: %i, write %i read %i\n", buttonbuffer.data[buttonbuffer.read], buttonbuffer.write, buttonbuffer.read);
#endif 
  curControl = buttonbuffer.data[buttonbuffer.read];

  buttonbuffer.read = (buttonbuffer.read+1) & CURCONTROL_BUFFER_MASK;

  return true;
}

void ButtonClear()
{
  for(uint8_t i=0; i<CURCONTROL_BUFFER_SIZE; i++) {
    buttonbuffer.data[i]=0;
  }
  buttonbuffer.read = 0;
  buttonbuffer.write = 0;
  curControl= BTN_NONE;
}
