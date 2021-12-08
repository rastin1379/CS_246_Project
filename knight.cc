#include "knight.h"

Knight::Knight(char type): Piece{type} {}

bool Knight::is_valid_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) {
	if (from.distance_squared(to) == 5 &&
	      (board[to.get_y()][to.get_x()] == nullptr ||
	       board[to.get_y()][to.get_x()]->get_color() != get_color())) {
		return true;
	}
	else {
		return false;
	}
}
