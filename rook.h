#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
	private:

	public:
	Rook(char type);
	bool is_valied_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) override;
};

#endif
