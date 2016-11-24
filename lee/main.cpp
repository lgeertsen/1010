#include <iostream>
#include <stdlib.h>

extern "C" {
#include <curses.h>
}

#include "window.h"
#include "piece.h"
#include "gameUI.h"

void myprogram() {
  int input;
  int h=20, w=40;
  Window playField(h,w,2,2);
  
  playField.setCouleurBordure(BGREEN);

  int s = 3;
  Coordinates *c = new Coordinates[3];
  c[0].x = 0;
  c[0].y = 0;
  c[1].x = 1;
  c[1].y = 0;
  c[2].x = 2;
  c[2].y = 0;

  Piece piece(s, c, BRED);

  GameUI gameUI(playField,piece);

  while((input = getch()) != 'q') {
    
  }
}

int main() {
  startProgramX();
  myprogram();
  stopProgramX();
  return 0;
}
