#include "window.h"
#include "piece.h"
#include "gameUI.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

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
}

void GameUI::printPiece(Window *w, Piece p, int x, int y) {
  for(int c = 0; c < p.getSize(); c++) {
    int X = (x + p.getX(c)) * 4;
    int Y = (y + p.getY(c)) * 2;
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
      	w->print(X+i, Y+j, n, p.getColor());
      }
    }
  }
}

void GameUI::printPointer(Window *w, int x, int y, Color c) {
  int X = x * 4;
  int Y = y * 2;
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 2; j++) {
      w->print(X+i, Y+j, c);
    }
  }
}


void GameUI::showScore(Window *w, int n) {
  int i = 0;
  if(n == 0) {
    printNumber(w, numbers[0], 0);
  } else {
    while(n != 0) {
      int x = n % 10;
      printNumber(w, numbers[x], i);
      n -= x;
      n /= 10;
      i++;
    }
  }
}

void GameUI::printNumber(Window *w, Number n, int x) {
  for(int i = 0; i < n.size; i++) {
    int X = (18 - (x * 8)) + n.coord[i].x * 2;
    int Y = 1 + n.coord[i].y;
    for(int j = 0; j < 2; j++) {
      w->print(X+j, Y, LIME);
    }
  }
}

void GameUI::changeBorder(Window *w, Color c) {
  w->setCouleurBordure(c);
}
