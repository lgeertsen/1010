#include "window.h"
#include "piece.h"
#include "gameUI.h"
#include "game.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

int Game::points[] = {10, 25, 45, 60, 75, 90};

Game::Game(int n, Piece *p, GameUI ui, string nom): piecesCount(n), gameUI(ui) {
  name = nom;
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
  loadSave();
  initialize();
  prompt();
}

void Game::restart() {
  ofstream outfile("save.dat", ios::out | ios::trunc);
  outfile.close();
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
  getRandomPieces();
  initialize();
}

void Game::gameOver() {
  ofstream outfile("save.dat", ios::out | ios::trunc);
  outfile.close();

  gameUI.printGameOver(game);
  int x = 5;
  while( x > 0 && score > thehighscores[x-1].score) {
    x--;
  }
  Highscore high[5];
  bool added = false;
  int i = 0;
  while(!added && i < 5) {
    if(score > thehighscores[i].score) {
      high[i].score = score;
      high[i].name = name;
      added = true;
    } else {
      high[i] = thehighscores[i];
      i++;
    }
  }
  while(i < 4) {
    high[i+1] = thehighscores[i];
    i++;
  }

  for(int i = 0; i < 5; i++) {
    thehighscores[i] = high[i];
  }

  if(added) {
    ofstream outfile("highscores.dat", ios::out | ios::trunc);
    for(int i = 0; i < 5; i++) {
      outfile<<thehighscores[i].name<<endl;
      outfile<<thehighscores[i].score<<endl;
    }
    outfile.close();
  }
}

void Game::initialize() {
  showScore();
  selectedPiece = 0;
  pointer.x = 0;
  pointer.y = 0;
  isgameOver = false;
  placePointer();
  getHighscores();
  showHigscores();
}

bool Game::load() {
  ifstream infile("save.dat");
  infile.seekg( 0, ios::end );
  if(infile.tellg() > 0) {
    char c;
    infile.seekg(-2, ios::end);
    infile.get(c);
    while(c != 'a') {
      infile.seekg(-2, ios::cur);
      infile.get(c);
    }
    char data[10];
    infile>>data;
    score = atoi(&data[0]);
    for(int i = 0; i < 10; i ++) {
      for(int j = 0; j < 10; j++) {
        infile>>data;
        int n = atoi(&data[0]);
        board[j][i] = n;
        if(n != 0)
          gameUI.printPart(game, j*4, i*2, getColor(n));
      }
    }
    for(int i = 0; i < 3; i++) {
      infile>>data;
      piecesToPlay[i] = atoi(&data[0]);
      gameUI.printPiece(blocks[i], pieces[piecesToPlay[i]], 0.25, 0.5);
    }
    infile.close();
    return true;
  }
  infile.close();
  return false;
}

void Game::loadSave() {
  if(!load()){
    getRandomPieces();
  }
}

void Game::goBack() {
  ifstream infile("save.dat");
  ofstream outfile("temp.dat", ios::out | ios::trunc);
  infile.seekg(0, ios::end);
  char c;
  infile.seekg(-2, ios::end);
  infile.get(c);
  while(c != 'a') {
    infile.seekg(-2, ios::cur);
    infile.get(c);
  }
  char data[10];
  int tempScore;
  int tempScore2 = -1;
  infile>>data;
  tempScore = atoi(&data[0]);

  infile.seekg(0, ios::beg);
  while(tempScore != tempScore2) {
    infile.get(c);
    while(c != 'a') {
      outfile<<c;
      infile.get(c);
    }
    infile>>data;
    tempScore2 = atoi(&data[0]);
    if(tempScore2 != tempScore) {
      outfile<<c<<'\n';
      outfile<<tempScore2;
    }
  }
  infile.close();
  outfile.close();

  infile.open("temp.dat");
  outfile.open("save.dat", ios::out | ios::trunc);
  infile.seekg( 0, ios::end );
  if(infile.tellg() > 0) {
    infile.seekg(0, ios::beg);
    while(!infile.eof()) {
      infile.get(c);
      outfile<<c;
    }
    for(int i = 0; i < 10; i++) {
      deleteColumn(i);
    }
    for(int i = 0; i < 3; i++) {
      Piece p = pieces[piecesToPlay[i]];
      for(int c = 0; c < p.getSize(); c++) {
        float X = 0.25 + p.getX(c);
        float Y = 0.5 + p.getY(c);
        gameUI.printPointer(blocks[i], X, Y, CLOUD);
      }
    }

    showScore();
    infile.close();
    outfile.close();
    load();
    bool selected = false;
    int i = 0;
    while(!selected && i < 3) {
      if(piecesToPlay[i] != -1) {
        selectPiece(i);
        selected = true;
      }
      i++;
    }
  } else {
    restart();
    infile.close();
    outfile.close();
  }
}

void Game::prompt() {
  int input;
  while((input = getch()) != 'q' && input != 'Q') {
    if(!isgameOver) {
      switch (input) {
      case 'a':
      case 'A':
        if(piecesToPlay[0] != -1 && selectedPiece != 0) {
          selectPiece(0);
        }
        break;
      case 'z':
      case 'Z':
        if(piecesToPlay[1] != -1 && selectedPiece != 1) {
          selectPiece(1);
        }
        break;
      case 'e':
      case 'E':
        if(piecesToPlay[2] != -1 && selectedPiece != 2) {
          selectPiece(2);
        }
        break;
      case '\n':
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
      case 'R':
        restart();
        break;
      case KEY_BACKSPACE:
        goBack();
        break;
      }
    }
    switch (input) {
    case 'r':
    case 'R':
      restart();
      break;
    }
  }
}

void Game::createWindows() {
  scoreField = new Window(7,48,0,0);
  scoreField->setCouleurFenetre(CLOUD);
  scoreField->setCouleurBordure(MIDNIGHT);

  crown = new Window(7,13,50,0);
  crown->setCouleurFenetre(MIDNIGHT);
  crown->setCouleurBordure(MIDNIGHT);
  crown->printBold(2, 1, "  _.+._  ", REDT);
  crown->printBold(2, 2, "(^\\/^\\/^)", YELLOWT);
  crown->printBold(2, 3, " \\     /", YELLOWT);
  crown->printBold(4, 3, "@*@*@", GREENT);
  crown->printBold(2, 4, " {_____}", YELLOWT);

  highscore = new Window(7,48,64,0);
  highscore->setCouleurFenetre(CLOUD);
  highscore->setCouleurBordure(MIDNIGHT);

  game = new Window(20,40,0,9);
  game->setCouleurFenetre(CLOUD);
  game->setCouleurBordure(MIDNIGHT);

  Window *block1 = new Window(12,22,42,17);
  Window *block2 = new Window(12,22,66,17);
  Window *block3 = new Window(12,22,90,17);

  blocks[0] = block1;
  blocks[1] = block2;
  blocks[2] = block3;
  blocks[0]->setCouleurFenetre(CLOUD);
  blocks[0]->setCouleurBordure(RED);
  blocks[1]->setCouleurFenetre(CLOUD);
  blocks[1]->setCouleurBordure(MIDNIGHT);
  blocks[2]->setCouleurFenetre(CLOUD);
  blocks[2]->setCouleurBordure(MIDNIGHT);

  highscores = new Window(6,46,42,9);
  highscores->setCouleurFenetre(CLOUD);
  highscores->setCouleurBordure(MIDNIGHT);

  help = new Window(6,22,90,9);
  help->setCouleurFenetre(CLOUD);
  help->setCouleurBordure(MIDNIGHT);
  help->print(1, 1, "a,z,e: choose piece");
  help->print(1, 2, "enter/space: place");
  help->print(1, 3, "arrows: move");
  help->print(1, 4, "r: restart");
  help->print(1, 5, "q: quit");
}

void Game::saveGame() {
  ofstream outfile("save.dat", ios::out | ios::app);
  outfile<<"a"<<endl;
  outfile<<score<<endl;
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      outfile<<board[j][i]<<" ";
    }
    outfile<<endl;
  }
  for(int i = 0; i < 3; i++) {
    outfile<<piecesToPlay[i]<<endl;
  }
  outfile.close();
}

void Game::showScore() {
  gameUI.showScore(scoreField, score, LIGHTGREEN);
}

void Game::getHighscores() {
  char data [10];
  ifstream infile;
  infile.open("highscores.dat");
  for(int i = 0; i < 5; i++) {
    infile>>data;
    thehighscores[i].name = data;
    infile>>data;
    thehighscores[i].score = atoi(&data[0]);
    for(int j = 0; j < 10; j++) {
      thehighscores[i].charScore[j] = data[j];
    }
  }
  infile.close();
}

void Game::showHigscores() {
  highscores->clear();
  highscores->print(1, 1, "Highscores");
  highscores->print(1, 2, "__________");
  int y = 1;
  for(int i = 0; i < 5; i++) {
    gameUI.showHighscore(highscores, 20, y*i + 1, thehighscores[i].name, thehighscores[i].charScore);
  }
  gameUI.showScore(highscore, thehighscores[0].score, RED);
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
  int x = 10 - pieces[piecesToPlay[selectedPiece]].getWidth();
  int y = 10 - pieces[piecesToPlay[selectedPiece]].getHeight();
  if(pointer.x > x)
    pointer.x = x;
  if(pointer.y > y)
    pointer.y = y;
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

  saveGame();

  isGameOver();
}

void Game::isGameOver() {
  int i = 0;
  bool free = false;
  while(!free && i < 10) {
    int j = 0;
    while(!free && j < 10) {
      if(board[i][j] == 0) {
        int k = 0;
        while(!free && k < 3) {
          int m = 0;
          int ptp = piecesToPlay[k];
          if(ptp >= 0 ) {
            Piece p = pieces[piecesToPlay[k]];
            bool place = true;
            while(place && m < p.getSize()) {
              int x = i + p.getX(m);
              int y = j + p.getY(m);
              if(x > 9 || y > 9 || board[x][y] != 0)
                place = false;
              m++;
            }
            if(place)
                free = true;
          }
          k++;
        }
      }
      j++;
    }
    i++;
  }
  if(!free)
    isgameOver = true;

  if(isgameOver)
    gameOver();
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
}

void Game::deleteColumn(int x) {
  for(int i = 0; i < 10; i++) {
    board[x][i] = 0;
    gameUI.printPointer(game, x, i, CLOUD);
  }
}

void Game::deleteRow(int y) {
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
