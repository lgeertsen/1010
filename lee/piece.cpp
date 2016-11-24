#include "window.h"
#include "piece.h"

#include <iostream>

Piece::Piece(int s, Coordinates *c, Color col) {
  size = s;
  coord = new Coordinates[s];
  for(int i = 0; i < size; i++) {
    coord[i] = c[i];
  }
  colorPiece = col;
}

int Piece::getX(int n) {
  return coord[n].x;
}

int Piece::getY(int n) {
  return coord[n].y;
}

Color Piece::getColor() {
  return colorPiece;
}
