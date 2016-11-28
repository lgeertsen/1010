#ifndef __GAME_H
#define __GAME_H

#include "window.h"
#include "piece.h"
#include "gameUI.h"

class Game {
 private:
  int score, piecesCount, selectedPiece;
  int board[10][10], piecesToPlay[3];
  Window *game, *help, *scoreField, *highscore, *highscores, *crown, *blocks[3];
  GameUI gameUI;
  Piece *pieces;
  Coordinates pointer;

 public:
  Game(int n, Piece *p, GameUI ui);

  void start();
  void prompt();

  void createWindows();

  void showScore();

  void getRandomPieces();

  int* getRandomNumbers();

  void selectPiece(int n);
};

#endif
