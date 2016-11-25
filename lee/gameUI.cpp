#include "window.h"
#include "piece.h"
#include "gameUI.h"

GameUI::GameUI(Piece p): piece(p) {
  score = new Window(7,20,0,0);
  score->setCouleurFenetre(CLOUD);
  score->setCouleurBordure(MIDNIGHT);

  crown = new Window(7,20,22,0);
  crown->setCouleurFenetre(CLOUD);
  crown->setCouleurBordure(MIDNIGHT);
  crown->printBold(5, 1, "/\\  /\\  /\\", YELLOWT);
  crown->printBold(4, 2, "/  \\/  \\/  \\", YELLOWT);
  crown->printBold(4, 3, "|          |", YELLOWT);
  crown->printBold(5, 3, " * * * * *", REDT);
  crown->printBold(4, 4, "|__________|", YELLOWT);

  highscore = new Window(7,20,44,0);
  highscore->setCouleurFenetre(CLOUD);
  highscore->setCouleurBordure(MIDNIGHT);
  
  game = new Window(20,40,0,9);
  game->setCouleurFenetre(CLOUD);
  game->setCouleurBordure(MIDNIGHT);

  blocks = new Window(10,64,0,31);
  blocks->setCouleurFenetre(CLOUD);
  blocks->setCouleurBordure(MIDNIGHT);
  
  highscores = new Window(11,22,42,9);
  highscores->setCouleurFenetre(CLOUD);
  highscores->setCouleurBordure(MIDNIGHT);
  
  help = new Window(7,22,42,22);
  help->setCouleurFenetre(CLOUD);
  help->setCouleurBordure(MIDNIGHT);
}

void GameUI::printPiece() {
  for(int c = 0; c < piece.getSize(); c++) {
    int x = 8 + piece.getX(c) * 4;
    int y = 5 + piece.getY(c) * 2;
    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 2; j++) {
	int n;
	if(j == 0) {
	  if(i == 0)
	    n = 1;
	  else if(i == 3)
	    n = 2;
	  else
	    n = 5;
	} else {
	  if(i == 0)
	    n = 3;
	  else if(i == 3)
	    n = 4;
	  else
	    n = 5;
	}
	game->print(x+i, y+j, n, piece.getColor());
      }
    }
  }
}
