#include "window.h"
#include "piece.h"
#include "gameUI.h"
#include "game.h"

#include <cstdlib>

Game::Game(int n, Piece *p, GameUI ui): piecesCount(n), gameUI(ui) {
  pieces = new Piece[n];
  for(int i = 0; i < n; i++) {
    pieces[i] = p[i];
  }

  score = 789;
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      board[i][j] = 0;
    }
  }
}

void Game::start() {
  createWindows();
  showScore();
  selectedPiece = 0;
  getRandomPieces();
  pointer.x = 0;
  pointer.y = 0;
  placeable = true;
  gameUI.printPointer(game, pointer.x, pointer.y, LIGHTGREEN);
  prompt();
}

void Game::prompt() {
  int input;
  while((input = getch()) != 'q') {
    switch (input) {
    case 'a':
      if(piecesToPlay[0] != -1 && selectedPiece != 0) {
        selectPiece(0);
      }
      break;
    case 'z':
      if(piecesToPlay[1] != -1 && selectedPiece != 1) {
        selectPiece(1);
      }
      break;
    case 'e':
      if(piecesToPlay[2] != -1 && selectedPiece != 2) {
        selectPiece(2);
      }
      break;
    case ' ':
      if(placeable)
        putPiece();
      break;
    case KEY_UP:
      if(pointer.y > 0) {
      	movePointer(0, -1);
      }
    	break;
    case KEY_DOWN:
      if(pointer.y < 9) {
      	movePointer(0, 1);
      }
    	break;
    case KEY_LEFT:
      if(pointer.x > 0) {
      	movePointer(-1, 0);
      }
    	break;
    case KEY_RIGHT:
      if(pointer.x < 9) {
      	movePointer(1, 0);
      }
    	break;
    }
  }
}

void Game::createWindows() {
  scoreField = new Window(7,25,0,0);
  scoreField->setCouleurFenetre(CLOUD);
  scoreField->setCouleurBordure(MIDNIGHT);

  crown = new Window(7,16,27,0);
  crown->setCouleurFenetre(CLOUD);
  crown->setCouleurBordure(MIDNIGHT);
  crown->printBold(3, 1, "/\\  /\\  /\\", YELLOWT);
  crown->printBold(2, 2, "/  \\/  \\/  \\", YELLOWT);
  crown->printBold(2, 3, "|          |", YELLOWT);
  crown->printBold(3, 3, " * * * * *", REDT);
  crown->printBold(2, 4, "|__________|", YELLOWT);

  highscore = new Window(7,25,45,0);
  highscore->setCouleurFenetre(CLOUD);
  highscore->setCouleurBordure(MIDNIGHT);


  game = new Window(20,40,0,9);
  game->setCouleurFenetre(CLOUD);
  game->setCouleurBordure(MIDNIGHT);

  Window *block1 = new Window(12,22,0,31);
  Window *block2 = new Window(12,22,24,31);
  Window *block3 = new Window(12,22,48,31);

  blocks[0] = block1;
  blocks[1] = block2;
  blocks[2] = block3;
  blocks[0]->setCouleurFenetre(CLOUD);
  blocks[0]->setCouleurBordure(RED);
  blocks[1]->setCouleurFenetre(CLOUD);
  blocks[1]->setCouleurBordure(MIDNIGHT);
  blocks[2]->setCouleurFenetre(CLOUD);
  blocks[2]->setCouleurBordure(MIDNIGHT);

  highscores = new Window(11,28,42,9);
  highscores->setCouleurFenetre(CLOUD);
  highscores->setCouleurBordure(MIDNIGHT);
  highscores->print(1, 1, "Highscores");
  highscores->print(1, 2, "__________");

  help = new Window(7,28,42,22);
  help->setCouleurFenetre(CLOUD);
  help->setCouleurBordure(MIDNIGHT);
  help->print(1, 1, "q: quit");
}

void Game::showScore() {
  gameUI.showScore(scoreField, score);
}

void Game::movePointer(int x, int y) {
  int n = board[pointer.x][pointer.y];
  if(n != 0)
    gameUI.printPart(game, pointer.x*4, pointer.y*2, getColor(n));
  else
    gameUI.printPointer(game, pointer.x, pointer.y, CLOUD);
  pointer.x += x;
  pointer.y += y;
  placeablePointer();
}

void Game::placeablePointer() {
  int i = 0;
  Piece p = pieces[piecesToPlay[selectedPiece]];
  placeable = true;
  while(placeable && i < p.getSize()) {
    int x = pointer.x + p.getX(i);
    int y = pointer.y + p.getY(i);
    if(x > 9 || y > 9 || board[x][y] != 0)
      placeable = false;
    i++;
  }
  if(placeable)
    gameUI.printPointer(game, pointer.x, pointer.y, LIGHTGREEN);
  else
    gameUI.printPointer(game, pointer.x, pointer.y, RED);
}

void Game::getRandomPieces() {
  int *n = getRandomNumbers();
  for(int i = 0; i < 3; i++) {
    piecesToPlay[i] = n[i];
    gameUI.printPiece(blocks[i], pieces[n[i]], 0.25, 0.5);
  }
}

int* Game::getRandomNumbers() {
  srand( (unsigned)time( NULL ) );
  static int n[3];
  for(int i = 0; i < 3; i++) {
  	rand();
  	n[i] = rand() % piecesCount;
  }
  return n;
}

void Game::selectPiece(int n) {
  gameUI.changeBorder(blocks[selectedPiece], MIDNIGHT);
  selectedPiece = n;
  gameUI.changeBorder(blocks[selectedPiece], RED);
  placeablePointer();
}

void Game::putPiece(){
  Piece p = pieces[piecesToPlay[selectedPiece]];
  for(int i = 0; i < p.getSize(); i++) {
    int x = pointer.x + p.getX(i);
    int y = pointer.y + p.getY(i);
    board[x][y] = p.getColorId();
  }
  gameUI.printPiece(game, p, pointer.x, pointer.y);

  for(int c = 0; c < p.getSize(); c++) {
    float X = 0.25 + p.getX(c);
    float Y = 0.5 + p.getY(c);
    gameUI.printPointer(blocks[selectedPiece], X, Y, CLOUD);
  }
  gameUI.fill(blocks[selectedPiece], CLOUD);
  piecesToPlay[selectedPiece] = -1;
  bool selected = false;
  int i = 0;
  while(!selected && i < 3) {
    if(piecesToPlay[i] != -1) {
      selectPiece(i);
      selected = true;
    }
    i++;
  }
  if(!selected) {
    getRandomPieces();
    selectPiece(0);
  }
}

Color Game::getColor(int n) {
  Color c;
  switch (n) {
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
