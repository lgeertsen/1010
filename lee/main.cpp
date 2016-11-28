#include <iostream>
#include <fstream>
#include <stdlib.h>

extern "C" {
#include <curses.h>
}

#include "window.h"
#include "piece.h"
#include "gameUI.h"
#include "game.h"

using namespace std;

Color getColor(int x) {
  Color c;
  switch (x) {
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

void myprogram() {
  char data[3];
  ifstream infile;
  infile.open("pieces.dat");
  infile>>data;
  int nbPieces = atoi(&data[0]);
  Piece *p = new Piece[nbPieces];
  for(int i = 0; i < nbPieces; i++) {
    infile>>data;
    int s = atoi(&data[0]);
    Coordinates *c = new Coordinates[s];
    for(int j = 0; j < s; j++) {
      infile>>data;
      c[j].x = atoi(&data[0]);
      infile>>data;
      c[j].y = atoi(&data[0]);
    }
    infile>>data;
    Piece piece(s, c, getColor(atoi(&data[0])));
    p[i] = piece;
  }
  infile.close();

  GameUI gameUI;

  Game game(nbPieces, p, gameUI);
  game.start();
}

int main() {
  startProgramX();
  myprogram();
  stopProgramX();
  return 0;
}
