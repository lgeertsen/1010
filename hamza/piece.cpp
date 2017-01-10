#include "window.h"
#include "piece.h"

#include <iostream>

Piece::Piece() {}

Piece::Piece(int s, Coordinates *c, int color) {
  size = s;
  coord = new Coordinates[s];
  for(int i = 0; i < size; i++) {
    coord[i] = c[i];
  }
  colorId = color;
}

int Piece::getSize() {
  return size;
}

int Piece::getX(int n) {
  return coord[n].x;
}

int Piece::getY(int n) {
  return coord[n].y;
}

int Piece::getWidth() {
  int n = 0;
  for(int i = 0; i < getSize(); i++) {
    if(n < getX(i))
      n = getX(i);
  }
  return n+1;
}

int Piece::getHeight() {
  int n = 0;
  for(int i = 0; i < getSize(); i++) {
    if(n < getY(i))
      n = getY(i);
  }
  return n+1;
}

int Piece::getColorId() {
  return colorId;
}

Color Piece::getColor() {
  Color c;
  switch (colorId) {
    case 0:
      c = CLOUD;
      break;
    case 1:
      c = RED;
      break;
    case 2:
      c = PINK;
      break;
    case 3:
      c = PURPLE;
      break;
    case 4:
      c = DEEPPURPLE;
      break;
    case 5:
      c = INDIGO;
      break;
    case 6:
      c = BLUE;
      break;
    case 7:
      c = LIGHTBLUE;
      break;
    case 8:
      c = CYAN;
      break;
    case 9:
      c = TEAL;
      break;
    case 10:
      c = GREEN;
      break;
    case 11:
      c = LIGHTGREEN;
      break;
    case 12:
      c = LIME;
      break;
    case 13:
      c = YELLOW;
      break;
    case 14:
      c = AMBER;
      break;
    case 15:
      c = ORANGE;
      break;
    case 16:
      c = DEEPORANGE;
      break;
  }
  return c;
}
