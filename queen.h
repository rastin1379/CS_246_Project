#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
	private:

	public:
	Queen(char type);

	bool is_valied_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) override;
};

#endif
