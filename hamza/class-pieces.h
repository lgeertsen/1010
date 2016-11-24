#ifndef __PIECES_H
#define __PIECES_H
#include "window.h"

class PIECES{
 private:
  size_t n;
  unsigned int x;
  unsigned int y;
  Color Couleur;
  int t[][];
 public:
  //constructeurs de pièces
  PIECES();
  PIECES(size_t);
  PIECES(int&);
  ~PIECES();
  //accesseur en lecture
  size_t getSize() const;
  unsigned int getX() const;
  unsigned int getY() const;
  Color getCouleur() const;
  //accesseur en ecriture
  void setSize(size_t);
  void setX(unsigned int);
  void setY(unsigned int);
  Color setCouleur(Color);
  //autres methodes
  void pivoter(int&);
  
};
#endf
