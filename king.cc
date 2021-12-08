#include "king.h"

King::King(char type): Piece{type} {}

bool King::is_valid_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) {
	return true;
}
