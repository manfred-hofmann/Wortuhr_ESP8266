/* 
 *  Tetris Definitionen
 */
#ifndef TETRIS_H
#define TETRIS_H

//Size of bricks.
#define  MAX_BRICK_SIZE    4
#define  BRICKOFFSET       -1 // Y offset Neuer Block

#define  INIT_SPEED        1000// Initial delay in ms zwischen Block Abwurf
#define  SPEED_STEP        20  // Faktor für speed Erhöhung bei neuem Levels, default 20
#define  LEVELUP           3   // Anzahl Zeilen bis neuer Levvel, default 3

int pixel_aktiv = 0;

// Spielfeld
struct Field{
  uint8_t pix[FIELD_WIDTH][FIELD_HEIGHT+1];// für die Kollisionsermittlung das Feld nach unten virtuell erweitern
  unsigned int color[FIELD_WIDTH][FIELD_HEIGHT];  
};
Field field;

//Struktur eines Steins
struct Brick{
  boolean enabled;// Stein disabled sobald er gelandet ist
  int xpos,ypos;
  int yOffset;//Y-offset beim einsetzen des Steins
  uint8_t siz;
  uint8_t pix[MAX_BRICK_SIZE][MAX_BRICK_SIZE];

  unsigned int color;
};
Brick activeBrick;

//Struktur um die verschiedenen (7) Steine zu definieren
struct AbstractBrick{
  int yOffset;
  uint8_t siz;
  uint8_t color;
  uint8_t pix[MAX_BRICK_SIZE][MAX_BRICK_SIZE];
};

//Brick "library"
AbstractBrick brickLib[7] = {
  {
      1,//yoffset beim einsetzten des Steins
      4,
      BLUE,
      { {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
      }
  },
  {
      0,
      4,
      RED,
      { {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0}
      }
  },
  {
      1,
      3,
      YELLOW,
      { {0,0,0,0},
        {1,1,1,0},
        {0,0,1,0},
        {0,0,0,0}
      }
  },
  {
      1,
      3,
      MAGENTA,
      { {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
      }
  },
  {
      1,
      3,
      GREEN,
      { {0,0,0,0},
        {1,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
      }
  },
  {
      1,
      3,
      ORANGE,
      { {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
      }
  },
  {
      1,
      3,
      CYAN,
      { {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
      }
  }
};

#endif
