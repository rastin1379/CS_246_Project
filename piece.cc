#include "piece.h"

Piece::Piece(char type): type{ type } {}

char Piece::get_type() { return type; }

char Piece::get_piece_type() {
	if (type < 'a') { return type - 'A' + 'a'; }
        return type;	
}
