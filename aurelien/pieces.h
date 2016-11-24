class piece {
 private :
  enum Color { noir, bleu, vert, rouge, jaune };
  int type;
  Color color;
  int colonne;
  int ligne;

 public:
  Piece();
  Piece(Color, unsigned int, unsigned int, unsigned int);
  Color getColor() const;
  int getType () const;
  int getColonne() const;
  int getLigne() const;

  void setColonne(unsigned int);
  void setLigne(unsigned int);
  void setColor(Color);
  
