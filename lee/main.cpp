#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

extern "C" {
#include <curses.h>
}

#include "window.h"
#include "piece.h"
#include "gameUI.h"
#include "game.h"

using namespace std;

void myprogram(string name) {
  string nom = name;
  char data[3];
  ifstream infile;
  infile.open("pieces.dat");
  infile>>data;
  int nbPieces = atoi(&data[0]);
  Piece *p = new Piece[nbPieces];
  for(int i = 0; i < nbPieces; i++) {
    infile>>data;
    int s = atoi(&data[0]);
    Coordinates *c = new Coordinates[s];
    for(int j = 0; j < s; j++) {
      infile>>data;
      c[j].x = atoi(&data[0]);
      infile>>data;
      c[j].y = atoi(&data[0]);
    }
    infile>>data;
    Piece piece(s, c, atoi(&data[0]));
    p[i] = piece;
  }
  infile.close();

  GameUI gameUI;

  Game game(nbPieces, p, gameUI, nom);
  game.start();
}

int main(int argc,char* argv[]) {
  for (int i=1;i<argc;i++){
    if (argv[i]==string("help")){
      ifstream aide("help.txt",ios::in);
      string line;
      while (getline(aide,line)){
  cout<<line<<"\n";
      }
      cout<<"Bonne partie!\n"<<endl;
    }else if (argv[i]==string("version")){
      cout<<"Version:1.0"<<endl;
    }else if (argv[i]==string("auteurs")){
      cout<<"Auteurs:\n"<<"Hamza Mellouki\n"<<"Lee Geertsen\n"<<"Imrhan Dareine\n"<<"Aurelien Ambroise\n"<<endl;
    }
  }
  if (argc==1){
    string name;
    cout<<"Enter you name: ";
    cin>>name;
    startProgramX();
    myprogram(name);
    stopProgramX();
  }
  return 0;
}
