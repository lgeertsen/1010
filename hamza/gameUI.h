#ifndef __GAMEUI_H
#define __GAMEUI_H

#include "window.h"
#include "piece.h"

struct Number {
  int size;
  Coordinates *coord;
};

class GameUI {
 private:
  Number numbers[10];

 public:
  GameUI();
  void GameOver(Window *w,int x,int y);

  void printPiece(Window *w, Piece p, float x, float y);
  void printPart(Window *w, float x, float y, Color c);
  void printPointer(Window *w, float x, float y, Color c);

  void showScore(Window *w, int n);

  void printNumber(Window *w, Number n, int x);

  void changeBorder(Window *w, Color c);
  void fill(Window *w, Color c);
};

#endif
