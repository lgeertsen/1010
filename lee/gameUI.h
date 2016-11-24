#ifndef __GAMEUI_H
#define __GAMEUI_H

#include "window.h"
#include "piece.h"

class GameUI {
 private:
  Window game;
  Piece piece;

 public:
  GameUI(Window w, Piece p);
};

#endif
