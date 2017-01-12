#ifndef __GAMEUI_H
#define __GAMEUI_H

#include <string>

using namespace std;

#include "window.h"
#include "piece.h"

struct Number {
  int size;
  Coordinates *coord;
};

struct Letter {
  int size;
  Coordinates *coord;
};

class GameUI {
 private:
  Number numbers[10];
  Letter letters[8];

 public:
  GameUI();

  void printPiece(Window *w, Piece p, float x, float y);
  void printPart(Window *w, float x, float y, Color c);
  void printPointer(Window *w, float x, float y, Color c);

  void showScore(Window *w, int n, Color c);
  void showHighscore(Window *w, int x, int y, string name, char score[]);

  void printNumber(Window *w, Number n, int x, Color c);

  void printGameOver(Window *w);

  void changeBorder(Window *w, Color c);
  void fill(Window *w, Color c);
};

#endif
