#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
	private:

	public:
	Bishop(char type);
	bool is_valid_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) override;
};

#endif
