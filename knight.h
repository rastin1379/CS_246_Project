#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
	private:

	public:
	Knight(char type);
	bool is_valid_move(Board * board_obj,
             Position from,Position to) override;
};

#endif
