#include "window.h"
#include "piece.h"
#include "gameUI.h"

GameUI::GameUI(Piece p): piece(p) {
  game = new Window(20,40,0,0);
  game->setCouleurFenetre(CLOUD);
  game->setCouleurBordure(MIDNIGHT);
  help = new Window(10,20,42,22);
  help->setCouleurFenetre(CLOUD);
  help->setCouleurBordure(MIDNIGHT);
  score = new Window(5,20,42,0);
  score->setCouleurFenetre(CLOUD);
  score->setCouleurBordure(MIDNIGHT);
  highscore = new Window(13,20,42,7);
  highscore->setCouleurFenetre(CLOUD);
  highscore->setCouleurBordure(MIDNIGHT);
  blocks = new Window(10,40,0,22);
  blocks->setCouleurFenetre(CLOUD);
  blocks->setCouleurBordure(MIDNIGHT);
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
