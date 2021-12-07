#ifndef PIECE_H
#define PIECE_H

class Piece {
	private:
	Position position;
	char type;

	public:
	Piece(char type);
	char getType();	
};

#endif
