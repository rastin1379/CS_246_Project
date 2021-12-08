#include "move.h"

using namespace std;

Move::Move(shared_ptr<Piece> piece, shared_ptr<Piece> removed_piece,
		Position from, Position to, bool en_passant, bool castle, bool promotion): piece{piece}, removed_piece{removed_piece}
		, from{from}, to{to}, en_passant{en_passant}, castle{castle}, promotion{promotion} {}

shared_ptr<Piece> Move::get_piece() { return piece; }

shared_ptr<Piece> Move::get_removed_piece() {return removed_piece; }

Position Move::get_from() { return from; }

Position Move::get_to() { return to; }

bool Move::is_en_passant() { return en_passant; }

bool Move::is_castle() { return castle; }

bool Move::is_promotion() { return promotion; }
	
void Move::set_promotion(bool new_promotion) { promotion = new_promotion; }
