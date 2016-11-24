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
  int x = 0, y = 0;

  game->print(x, y, piece.getColor());
}
