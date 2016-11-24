#include <iostream>
#include <stdlib.h>

extern "C" {
#include <curses.h>
}

#include "window.h"
#include "piece.h"

void myprogram() {
  int input;
  int h=20, w=40;
  Window playField(h,w,10,10);
  
  playField.setCouleurBordure(BGREEN);

  int x=w/2,y=h/2;
  playField.print(x,y,WCYAN);

  int s = 3;
  Coordinates *c = new Coordinates[3];
  c[0].x = 0;
  c[0].y = 0;
  c[1].x = 1;
  c[1].y = 0;
  c[2].x = 2;
  c[2].y = 0;

  Piece piece(s, c, BGREEN);

  int n = piece.getX(2);
  std::cout<<n<<std::endl;

  while((input = getch()) != 'q') {
    
  }
}

int main() {
  startProgramX();
  myprogram();
  stopProgramX();
  return 0;
}
