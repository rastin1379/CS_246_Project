#ifndef PIECE_H
#define PIECE_H

#include "position.h"
#include <memory>
#include <vector>

class Piece {
	private:
	char type;

	public:
	Piece(char type);
	char get_type();	
	char get_piece_type();
	virtual bool is_valied_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
		       Position	from,Position to) = 0;
};

#endif
