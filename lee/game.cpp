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
  gameUI.printPointer(game, pointer.x, pointer.y, RED);
  prompt();
}

void Game::prompt() {
  int input;
  while((input = getch()) != 'q') {
    switch (input) {
    case 'a':
      if(selectedPiece != 0) {
        selectPiece(0);
      }
      break;
    case 'z':
      if(selectedPiece != 1) {
        selectPiece(1);
      }
      break;
    case 'e':
      if(selectedPiece != 2) {
        selectPiece(2);
      }
      break;
    case 'p':
      gameUI.printPiece(game, pieces[piecesToPlay[selectedPiece]], pointer.x, pointer.y);
      break;
    case KEY_UP:
      if(pointer.y > 0) {
        gameUI.printPointer(game, pointer.x, pointer.y, CLOUD);
        pointer.y--;
        gameUI.printPointer(game, pointer.x, pointer.y, RED);
      }
    	break;
    case KEY_DOWN:
      if(pointer.y < 9) {
        gameUI.printPointer(game, pointer.x, pointer.y, CLOUD);
        pointer.y++;
        gameUI.printPointer(game, pointer.x, pointer.y, RED);
      }
    	break;
    case KEY_LEFT:
      if(pointer.x > 0) {
        gameUI.printPointer(game, pointer.x, pointer.y, CLOUD);
        pointer.x--;
        gameUI.printPointer(game, pointer.x, pointer.y, RED);
      }
    	break;
    case KEY_RIGHT:
      if(pointer.x < 9) {
        gameUI.printPointer(game, pointer.x, pointer.y, CLOUD);
        pointer.x++;
        gameUI.printPointer(game, pointer.x, pointer.y, RED);
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

void Game::getRandomPieces() {
  int *n = getRandomNumbers();
  for(int i = 0; i < 3; i++) {
    piecesToPlay[i] = n[i];
    gameUI.printPiece(blocks[i], pieces[n[i]], 1, 1);
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
  if(piecesToPlay[n] != -1) {
    selectedPiece = n;
    gameUI.changeBorder(blocks[selectedPiece], RED);
  }
}
