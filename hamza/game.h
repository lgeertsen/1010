#ifndef __GAME_H
#define __GAME_H

#include "window.h"
#include "piece.h"
#include "gameUI.h"
#include <iostream>
#include <fstream>

class Game {
 private:
  int score, piecesCount, selectedPiece;
  int board[10][10], piecesToPlay[3];
  static int points[6];
  bool placeable;
  Window *game, *help, *scoreField, *highscore, *highscores, *crown, *blocks[3];
  GameUI gameUI;
  Piece *pieces;
  Coordinates pointer;

 public:
  Game(int n, Piece *p, GameUI ui);

  void start();
  void restart();
  void initialize();
  void prompt();

  void createWindows();

  void showScore();

  void movePointer(int x, int y);

  void removePointer();

  void placePointer();

  void getRandomPieces();

  int* getRandomNumbers();

  void selectPiece(int n);

  void putPiece();

  int checkColumns(int x, int w);
  int checkRows(int y, int h);

  void deleteColRow(int x, int y, int w, int h);

  void deleteColumn(int x);
  void deleteRow(int y);

  Color getColor(int n);
  int getScore() const;
  int getBoard(int i,int j) const;
  bool getPlaceable() const;
  int getpiecesToPlay(int i) const;

  void setScore(int n);
  void setBoard(int i,int j,int n);

  void GameOver();
};

#endif
