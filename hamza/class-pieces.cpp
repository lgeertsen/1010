#include <iostream>
#include "class-pieces.h"
#include "window.h"

using namespace std;

PIECES::PIECES():{}
PIECES::PIECES(size_t x):{}
PIECES::PIECES(int&){}
~PIECES::PIECES(){}

size_t PIECES::getSize() const{
  return n;
}
unsigned int PIECES::getX() const {
  return x;
}

unsigned int PIECES::getY() const {
  return y;
}
Color PIECES::getCouleur() const{
  return Color;
}

void PIECES::setSize(size_t x){
  this->n=x;
}
void PIECES::setX(unsigned int n){
  this->x=n;
}
void PIECES::setY(unsigned int n){
  this->y=n;
}
Color PIECES::setCouleur(Color c){
  this->Couleur=c;
}

void PIECES::pivoter(int&){}
