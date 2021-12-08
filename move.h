#ifndef MOVE_H
#define MOVE_H

#include "position.h"
#include "piece.h"
#include <memory>

class Move {
	private:
	std::shared_ptr<Piece> piece;	
	std::shared_ptr<Piece> removed_piece;
	Position from;
	Position to;

	public:
	Move(std::shared_ptr<Piece> piece, std::shared_ptr<Piece> removed_piece, 
			Position from, Position to);
	std::shared_ptr<Piece> get_piece();
	std::shared_ptr<Piece> get_removed_piece();
	Position get_from();
	Position get_to();
};

#endif
