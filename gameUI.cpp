#include "window.h"
#include "piece.h"
#include "gameUI.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

GameUI::GameUI() {
  char data[5];
  ifstream infile;
  infile.open("numbers.dat");
  for(int i = 0; i < 10; i++) {
    infile>>data;
    int s = atoi(&data[0]);
    numbers[i].size = s;
    numbers[i].coord = new Coordinates[s];
    for(int j = 0; j < s; j++) {
      infile>>data;
      numbers[i].coord[j].x = atoi(&data[0]);
      infile>>data;
      numbers[i].coord[j].y = atoi(&data[0]);
    }
  }
  infile.close();
  infile.open("letters.dat");
  for(int i = 0; i < 8; i++) {
    infile>>data;
    int s = atoi(&data[0]);
    letters[i].size = s;
    letters[i].coord = new Coordinates[s];
    for(int j = 0; j < s; j++) {
      infile>>data;
      letters[i].coord[j].x = atoi(&data[0]);
      infile>>data;
      letters[i].coord[j].y = atoi(&data[0]);
    }
  }
}

void GameUI::printPiece(Window *w, Piece p, float x, float y) {
  for(int c = 0; c < p.getSize(); c++) {
    int X = (x + p.getX(c)) * 4;
    int Y = (y + p.getY(c)) * 2;
    printPart(w, X, Y, p.getColor());
  }
}

void GameUI::printPart(Window *w, float x, float y, Color c) {
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
      w->print(x+i, y+j, n, c);
    }
  }
}


void GameUI::printPointer(Window *w, float x, float y, Color c) {
  int X = x * 4;
  int Y = y * 2;
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 2; j++) {
      w->print(X+i, Y+j, c);
    }
  }
}


void GameUI::showScore(Window *w, int n, Color c) {
  fill(w, CLOUD);
  int i = 0;
  if(n == 0) {
    printNumber(w, numbers[0], 0, c);
  } else {
    while(n != 0) {
      int x = n % 10;
      printNumber(w, numbers[x], i, c);
      n -= x;
      n /= 10;
      i++;
    }
  }
}

void GameUI::showHighscore(Window *w, int x, int y, string name, char score[]) {
  w->print(x, y, name);
  w->print(x+15, y, score);
}

void GameUI::printNumber(Window *w, Number n, int x, Color c) {
  for(int i = 0; i < n.size; i++) {
    int X = (41 - (x * 8)) + n.coord[i].x * 2;
    int Y = 1 + n.coord[i].y;
    for(int j = 0; j < 2; j++) {
      w->print(X+j, Y, c);
    }
  }
}

void GameUI::printGameOver(Window *w) {
  for(int i = 0; i < 8; i++) {
    int x, y;
    Letter L = letters[i];
    switch(i) {
    case 0:
      x = 0;
      y = 2;
      break;
    case 1:
      x = 10;
      y = 2;
      break;
    case 2:
      x = 22;
      y = 2;
      break;
    case 3:
      x = 34;
      y = 2;
      break;
    case 4:
      x = 1;
      y = 10;
      break;
    case 5:
      x = 11;
      y = 10;
      break;
    case 6:
      x = 23;
      y = 10;
      break;
    case 7:
      x = 31;
      y = 10;
      break;
    }

    for(int j = 0; j < L.size; j++) {
      int X = x + L.coord[j].x *2;
      int Y = y + L.coord[j].y;
      for(int k = 0; k < 2; k++) {
        w->print(X+k, Y, '*', BRED);
      }
    }
  }
}

void GameUI::changeBorder(Window *w, Color c) {
  w->setCouleurBordure(c);
}

void GameUI::fill(Window *w, Color c) {
  w->setCouleurFenetre(c);
}
