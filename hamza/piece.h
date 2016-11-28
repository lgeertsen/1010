#ifndef __PIECE_H
#define __PIECE_H

#include "window.h"

#include <iostream>

struct Coordinates{
  unsigned int x, y;
};

class Piece {
 private:
  int size;
  Coordinates *coord;
  Color colorPiece;

 public:
  Piece(int s, Coordinates *c, Color col);
  Piece(const char* filename);

  int getSize();

  int getX(int n);
  int getY(int n);

  Color getColor();
};

#endif
