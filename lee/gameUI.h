#ifndef __GAMEUI_H
#define __GAMEUI_H

#include "window.h"
#include "piece.h"

class GameUI {
 private:
  Window *game, *help, *score, *highscore, *blocks;
  Piece piece;

 public:
  GameUI(Piece p);

  void printPiece();
};

#endif
