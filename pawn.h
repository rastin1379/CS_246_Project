#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
	private:

	public:
	Pawn(char type);
	bool is_valid_move(Board * board_obj,
             Position from,Position to) override;
};

#endif
