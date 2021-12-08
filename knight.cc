#include "knight.h"
#include "board.h"

Knight::Knight(char type): Piece{type} {}

bool Knight::is_valid_move(Board * board_obj,
             Position from,Position to) {
        std::vector<std::vector<std::shared_ptr<Piece>>> board = board_obj->get_board();
	if (from.distance_squared(to) == 5 &&
	      (board[to.get_y()][to.get_x()] == nullptr ||
	       board[to.get_y()][to.get_x()]->get_color() != get_color())) {
		return true;
	}
	else {
		return false;
	}
}
