#ifndef PIECE_H
#define PIECE_H

#include "position.h"
#include <memory>
#include <vector>

class Piece {
	private:
	char type;
	int move_counts;

	public:
	Piece(char type);
	char get_type();
	int get_move_counts();
	void add_move_counts();	
	char get_piece_type();
	char get_color();
	virtual bool is_valid_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
		       Position	from,Position to) = 0;
};

#endif
