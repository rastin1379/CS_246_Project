#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
	private:

	public:
	Rook(char type);
	bool is_valid_move(Board * board_obj,
             Position from,Position to) override;
};

#endif
