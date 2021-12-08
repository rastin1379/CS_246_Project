#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
	private:

	public:
	Pawn(char type);
	bool is_valied_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) override;
};

#endif
