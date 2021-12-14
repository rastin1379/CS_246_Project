#include "pawn.h"
#include <cmath>
#include "board.h"

using namespace std;

Pawn::Pawn(char type): Piece{type} {}

bool Pawn::is_valid_move(Board * board_obj,
             Position from,Position to) {
        vector<vector<shared_ptr<Piece>>> board = board_obj->get_board();
	int step = ((get_color() == 'w') ? -1 : 1);
        if (to.get_x() == from.get_x() && to.get_y() == from.get_y() + step 
			&& board[to.get_y()][to.get_x()] == nullptr) {
		return true;
	}
	if (to.get_x() == from.get_x() && to.get_y() == from.get_y() + step * 2
                        && board[to.get_y()][to.get_x()] == nullptr
			&& board[to.get_y() - step][to.get_x()] == nullptr
			&& get_move_counts() == 0
			&& ((step == -1 && from.get_y() == 6) || (step == 1 && from.get_y() == 1))) {
                return true;
        }
	if (abs(to.get_x() - from.get_x()) == 1 && to.get_y() - from.get_y() == step &&
			board[to.get_y()][to.get_x()] != nullptr &&
			board[to.get_y()][to.get_x()]->get_color() != get_color()) {
		return true;
	}
	// en passant
	if (board_obj->get_move_size() == 0) {
		return false;
	}
	Move last_move = board_obj->get_last_move();
        if (last_move.get_piece()->get_piece_type() == 'p' &&
                        last_move.get_from().distance_squared(last_move.get_to()) == 4 &&
                        last_move.get_piece()->get_color() != board[from.get_y()][from.get_x()]->get_color() &&
                        to.get_x() == last_move.get_to().get_x() && (to.get_y() == last_move.get_to().get_y() + step) &&
                        (abs(to.get_x() - from.get_x()) == 1) && (to.get_y() - from.get_y() == step)) {
        	return true;
	}
	return false;
}
