#ifndef PIECE_H
#define PIECE_H

#include "position.h"

class Piece {
	private:
	char type;

	public:
	Piece(char type);
	char get_type();	
};

#endif
