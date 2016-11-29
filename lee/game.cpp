#include "window.h"
#include "piece.h"
#include "gameUI.h"
#include "game.h"

#include <cstdlib>

int Game::points[] = {10, 25, 45, 60, 75, 90};

Game::Game(int n, Piece *p, GameUI ui): piecesCount(n), gameUI(ui) {
  pieces = new Piece[n];
  for(int i = 0; i < n; i++) {
    pieces[i] = p[i];
  }

  score = 0;
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      board[i][j] = 0;
    }
  }
  createWindows();
}

void Game::start() {
  initialize();
  prompt();
}

void Game::restart() {
  selectPiece(0);
  score = 0;
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      board[i][j] = 0;
      gameUI.printPointer(game, i, j, CLOUD);
    }
  }
  for(int i = 0; i < 3; i++) {
    Piece p = pieces[piecesToPlay[i]];
    for(int c = 0; c < p.getSize(); c++) {
      float X = 0.25 + p.getX(c);
      float Y = 0.5 + p.getY(c);
      gameUI.printPointer(blocks[i], X, Y, CLOUD);
    }
  }
  initialize();
}

void Game::initialize() {
  showScore();
  selectedPiece = 0;
  getRandomPieces();
  pointer.x = 0;
  pointer.y = 0;
  placeable = true;
  placePointer();
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
      if(pointer.y < 10 - pieces[piecesToPlay[selectedPiece]].getHeight()) {
      	movePointer(0, 1);
      }
      break;
    case KEY_LEFT:
      if(pointer.x > 0) {
      	movePointer(-1, 0);
      }
      break;
    case KEY_RIGHT:
      if(pointer.x < 10 - pieces[piecesToPlay[selectedPiece]].getWidth()) {
      	movePointer(1, 0);
      }
      break;
    case 'r':
      restart();
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
  removePointer();
  pointer.x += x;
  pointer.y += y;
  placePointer();
}

void Game::removePointer() {
  Piece p = pieces[piecesToPlay[selectedPiece]];
  for(int i = 0; i < p.getSize(); i++) {
    int x = pointer.x + p.getX(i);
    int y = pointer.y + p.getY(i);
    int n = board[x][y];
    if(n != 0)
      gameUI.printPart(game, x*4, y*2, getColor(n));
    else
      gameUI.printPointer(game, x, y, CLOUD);
  }
}

void Game::placePointer() {
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
  for(int i = 0; i < p.getSize(); i++) {
    int x = pointer.x + p.getX(i);
    int y = pointer.y + p.getY(i);
    if(placeable)
      gameUI.printPointer(game, x, y, LIGHTGREEN);
    else
      gameUI.printPointer(game, x, y, RED);
  }
  
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
  removePointer();
  selectedPiece = n;
  gameUI.changeBorder(blocks[selectedPiece], RED);
  placePointer();
}

void Game::putPiece(){
  Piece p = pieces[piecesToPlay[selectedPiece]];
  for(int i = 0; i < p.getSize(); i++) {
    int x = pointer.x + p.getX(i);
    int y = pointer.y + p.getY(i);
    board[x][y] = p.getColorId();
  }
  gameUI.printPiece(game, p, pointer.x, pointer.y);
  score += p.getSize();

  int c = checkColumns(pointer.x, p.getWidth());
  int r = checkRows(pointer.y, p.getHeight());

  if(c != 0 || r != 0) {
    if(c == 0) {
      score += points[r-1];
    }
    else if(r == 0) {
      score += points[c-1];
    }
    else {
      score += 2 * (points[c-1] + points[r-1]);
    }
    deleteColRow(pointer.x, pointer.y, p.getWidth(), p.getHeight());
  }

  showScore();

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

int Game::checkColumns(int x, int w) {
  int n = 0;
  for(int i = 0; i < w; i++) {
    bool loop = true;
    int j = 0;
    while(loop && j < 10) {
      if(board[x+i][j] == 0)
        loop = false;
      j++;
    }
    if(loop)
      n++;
  }
  return n;
}

int Game::checkRows(int y, int h) {
  int n = 0;
  for(int i = 0; i < h; i++) {
    bool loop = true;
    int j = 0;
    while(loop && j < 10) {
      if(board[j][y+i] == 0)
        loop = false;
      j++;
    }
    if(loop)
      n++;
  }
  return n;
}

void Game::deleteColRow(int x, int y, int w, int h) {
  bool loop, loop2;
  if(w > 0) {
    loop = true;
    int i = 0;
    while(loop && i < 10) {
      if(board[x][i] == 0)
        loop = false;
      i++;
    }
  }
  if(h > 0) {
    loop2 = true;
    int i = 0;
    while(loop2 && i < 10) {
      if(board[i][y] == 0)
        loop2 = false;
      i++;
    }
  }
  if(w-1 > 0 || h-1 > 0)
    deleteColRow(x+1, y+1, w-1, h-1);
  if(loop)
    deleteColumn(x);
  if(loop2)
    deleteRow(y);

//  for(int i = 0; i < w; i++) {
//    bool loop = true;
//    int j = 0;
//    while(loop && j < 10) {
//      if(board[x+i][j] == 0)
//        loop = false;
//      j++;
//    }
//    for(int k = 0; k < h; k++) {
//      bool loop2 = true;
//      int l = 0;
//      while(loop2 && l < 10) {
//        if(board[l][y+k] == 0)
//          loop2 = false;
//        l++;
//      }
//      if(loop2) {
//        deleteColRow(x+i+1, y+k+1, w-i-1, h-k-1);
//        deleteRow(y+k);
//      }
//    }
//    if(loop) {
//      deleteColumn(x+i);
//    }
//  }
}

void Game::deleteColumn(int x) {
  std::cout<<"Deleted colum "<<x<<std::endl;
  for(int i = 0; i < 10; i++) {
    board[x][i] = 0;
    gameUI.printPointer(game, x, i, CLOUD);
  }
}

void Game::deleteRow(int y) {
  std::cout<<"Deleted row "<<y<<std::endl;
  for(int i = 0; i < 10; i++) {
    board[i][y] = 0;
    gameUI.printPointer(game, i, y, CLOUD);
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
