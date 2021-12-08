#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
	private:

	public:
	Queen(char type);

	bool is_valid_move(Board * board_obj,
             Position from,Position to) override;
	
	bool is_diagonal(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to);

	bool is_straight(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to);
};

#endif
