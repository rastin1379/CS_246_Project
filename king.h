#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
	private:

	public:
	King(char type);
	bool is_valied_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
   	     Position from,Position to) override;
};

#endif
