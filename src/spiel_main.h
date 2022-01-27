/******************************************************************************
spiel_main.h
******************************************************************************/
#ifndef GAME_H
#define GAME_H
#include <Arduino.h>
#include "Configuration.h"
#include "Colors.h"


#define  FIELD_WIDTH       11
#define  FIELD_HEIGHT      10
#define  DIR_UP    1
#define  DIR_DOWN  2
#define  DIR_LEFT  3
#define  DIR_RIGHT 4

#define  BTN_NONE  0
#define  BTN_UP    1
#define  BTN_DOWN  2
#define  BTN_LEFT  3
#define  BTN_RIGHT  4
#define  BTN_MIDDLE  5
#define  BTN_START  6
#define  BTN_STOP   7
#define  BTN_EXIT   8

#define SNAKE 1
#define TETRIS 2
#define BRICKS 3
#define VIERGEWINNT 4
#define TIERMEMORY 5
#define MUSIKMEMORY 6
#define ABBAMEMORY 7

int8_t board[9][9] = {0};

uint8_t curControl = BTN_NONE;
uint8_t aktgame = 0;

bool gameisrunning = false;
uint16_t highscore[9] = {0,0,0,0,0,0,0,0,0}; //Snake, Tetris, Bricks,4gewinnt...
uint8_t gamecount[9]  = {0,0,0,0,0,0,0,0,0}; 

uint16_t aktscore;
uint8_t gamelevel = 2;
uint8_t gamesize = 2;
int8_t aktivPlayer = 0;
uint8_t anzPlayer = 0;

String PlayerIP[4]={"","","",""};

int debugval;
int gamesound = 2;

const int8_t pruefrichtung[4][4][2] =
{
  { { 0,0 } ,{ 0,1 }, {0,2}, {0,3}},
  { { 0,0 } ,{ 1,1 }, {2,2}, {3,3}},
  { { 0,0 } ,{ 1,-1 }, {2,-2}, {3,-3}},
  { { 0,0 } ,{ 1,0 }, {2,0}, {3,0}}
};

#endif
