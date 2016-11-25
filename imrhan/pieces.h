#ifndef __PIECE_H
#define __PIECE_H
#include "window.h"
#include "shapes.h"

class piece {

private:

unsigned int x,y,kind;
Color color;

public:

//Constructeurs
Piece();
Piece(int,int);
Piece(const Piece &p);

// Accesseurs en lecture
bool getVivante() const;
unsigned int getX() const;
unsigned int getY() const;
unsigned int getKind() const;
Color getColor() const;

// Accesseurs en écriture
void setX(unsigned int);
void setY(unsigned int);
void setKind(unsigned int);
void setColor(unsigned int);

}
#endif
