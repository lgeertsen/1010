#ifndef __GAME_H
#define __GAME_H

#include <string>

#include "window.h"
#include "piece.h"
#include "gameUI.h"

using namespace std;

struct Highscore {
  string name;
  int score;
  char charScore[10];
};

class Game {
 private:
  int score, piecesCount, selectedPiece;
  int board[10][10], piecesToPlay[3];
  static int points[6];
  bool placeable, isgameOver;
  string name;
  Window *game, *help, *scoreField, *highscore, *highscores, *crown, *blocks[3];
  GameUI gameUI;
  Piece *pieces;
  Coordinates pointer;
  Highscore thehighscores[5];

 public:
  Game(int n, Piece *p, GameUI ui, string nom);

  void start();
  void restart();
  void gameOver();
  void initialize();
  bool load();
  void loadSave();
  void goBack();
  void prompt();

  void createWindows();

  void saveGame();

  void showScore();
  void getHighscores();
  void showHigscores();

  void movePointer(int x, int y);

  void removePointer();

  void placePointer();

  void getRandomPieces();

  int* getRandomNumbers();

  void selectPiece(int n);

  void putPiece();

  void isGameOver();

  int checkColumns(int x, int w);
  int checkRows(int y, int h);

  void deleteColRow(int x, int y, int w, int h);

  void deleteColumn(int x);
  void deleteRow(int y);

  Color getColor(int n);
};

#endif
