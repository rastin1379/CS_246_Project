#include "king.h"
#include "board.h"

using namespace std;

King::King(char type): Piece{type} {}

bool King::is_valid_move(Board * board_obj,
             Position from,Position to) {
	vector<vector<shared_ptr<Piece>>> board = board_obj->get_board();
        if (board[to.get_y()][to.get_x()] != nullptr &&
		board[to.get_y()][to.get_x()]->get_color() == get_color()) {
		return false;
	}
	if (from.distance_squared(to) > 2 ||
			board_obj->is_position_check(to, board[from.get_y()][from.get_x()]->get_color())) {
		return false;
	}	
	return true;
}
