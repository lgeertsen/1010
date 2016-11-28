#ifndef __PIECE_H
#define __PIECE_H

#include "window.h"

#include <iostream>

struct Coordinates {
  int x, y;
};

class Piece {
 private:
  int size, colorId;
  Coordinates *coord;

 public:
  Piece();
  Piece(int s, Coordinates *c, int color);

  int getSize();

  int getX(int n);
  int getY(int n);

  int getColorId();
  Color getColor();
};

#endif
