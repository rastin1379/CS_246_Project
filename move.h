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
	bool en_passant;
	bool castle;
	bool promotion;

	public:
	Move(std::shared_ptr<Piece> piece, std::shared_ptr<Piece> removed_piece, 
			Position from, Position to, bool en_passant, bool castle, bool promotion);
	std::shared_ptr<Piece> get_piece();
	std::shared_ptr<Piece> get_removed_piece();
	Position get_from();
	Position get_to();
	bool is_en_passant();
	bool is_castle();
	bool is_promotion();
	void set_promotion(bool new_promotion);
};

#endif
