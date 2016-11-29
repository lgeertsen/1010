#include "window.h"
#include "piece.h"

#include <fstream>
#include <iostream>

Piece::Piece(int s, Coordinates *c, Color col) {
  size = s;
  coord = new Coordinates[s];
  for(int i = 0; i < size; i++) {
    coord[i] = c[i];
  }
  colorPiece = col;
}
Piece::Piece(const char* filename){
  ifstream fichier("filename.txt"|ios::in,ios::app);
  int a;
  fichier>>a;
  Coordinates *c;
  fichier>>*c;
  Color x;
  fichier>>x;
  fichier.close();
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

Color Piece::getColor() {
  return colorPiece;
}
