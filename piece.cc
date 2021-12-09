#include "piece.h"

Piece::Piece(char type): type{ type }, move_counts{0} {}

char Piece::get_type() { return type; }

char Piece::get_piece_type() {
	if (type < 'a') { return type - 'A' + 'a'; }
        return type;	
}

char Piece::get_color() {
	if (type >= 'a' && type <= 'z') { return 'b'; }
	else { return 'w'; }
}

int Piece::get_move_counts() {
	return move_counts;
}
void Piece::add_move_counts() {
	move_counts += 1;
}

void Piece::sub_move_counts() {
	move_counts -= 1;
}
