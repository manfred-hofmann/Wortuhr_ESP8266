/* 
 * Definitionen für Bricks
 */
#ifndef BRICKS_H
#define BRICKS_H

#include <Arduino.h>

#define UP 1
#define DOWN -1
#define BlockMatrixHEIGHT    3
#define ANZAHL_BRICKS      FIELD_WIDTH * BlockMatrixHEIGHT
#define MAX_BAELLE    5
#define START_DELAY 260
 
int ballX = 6;
int ballY = 8;
float ballXf = ballX;
float ballYf = ballY;

int richtung = UP;
float steigung = 1;

int rad = 1;
int scorePlayer = 0;
int AktBall = 1;
uint8_t Stage = 0;
uint8_t bricks_left = ANZAHL_BRICKS;

int positionPlayer = FIELD_WIDTH / 2;

boolean continueGame = true;

bool hitPlayer = false;
bool hitPlayerC = false;

bool hitTop = false;


uint8_t bricksmatrix[FIELD_WIDTH][BlockMatrixHEIGHT+1];

  #endif
