#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
	private:

	public:
	King(char type);
	bool is_valid_move(Board * board_obj,
   	     Position from,Position to) override;
};

#endif
