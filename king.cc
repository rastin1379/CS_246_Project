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
	char opponent_king = (get_color() == 'w' ? 'k' : 'K');
	Position position_opponent_king = board_obj->get_position_piece(opponent_king);
	if (to.distance_squared(position_opponent_king) <= 2) {
		return false;
	}	
	if (from.get_x() == 4 && from.get_y() == 7 && board[7][4]->get_move_counts() == 0 &&
                        board[7][5] == nullptr && board[7][6] == nullptr &&
                        board[7][7] != nullptr && to.get_x() == 6 && to.get_y() == 7 && board[7][7]->get_type() == 'R' &&
                                         board[7][7]->get_move_counts() == 0 && !board_obj->is_position_check(Position(4, 7), 'w') &&
                                         !board_obj->is_position_check(Position(5, 7), 'w') && !board_obj->is_position_check(Position(6, 7), 'w')) {
		return true;
        }
        if (from.get_x() == 4 && from.get_y() == 7 && board[7][4]->get_move_counts() == 0 &&
                        board[7][3] == nullptr && board[7][2] == nullptr && board[7][0] != nullptr &&
                        to.get_x() == 2 && to.get_y() == 7 && board[7][0]->get_type() == 'R' &&
                                         board[7][0]->get_move_counts() == 0 && !board_obj->is_position_check(Position(4, 7), 'w') &&
                                         !board_obj->is_position_check(Position(3, 7), 'w') && !board_obj->is_position_check(Position(2, 7), 'w')) {
		return true;
        }
        if (from.get_x() == 4 && from.get_y() == 0 && board[0][4]->get_move_counts() == 0 &&
                        board[0][5] == nullptr && board[0][6] == nullptr && board[0][7] != nullptr &&
                        to.get_x() == 6 && to.get_y() == 0 && board[0][7]->get_type() == 'r' &&
                                         board[0][7]->get_move_counts() == 0 && !board_obj->is_position_check(Position(4, 0), 'b') &&
                                         !board_obj->is_position_check(Position(5, 0), 'b') && !board_obj->is_position_check(Position(6, 0), 'b')) {
		return true;
        }
        if (from.get_x() == 4 && from.get_y() == 0 && board[0][4]->get_move_counts() == 0 &&
                        board[0][3] == nullptr && board[0][2] == nullptr && board[0][0] != nullptr &&
                        to.get_x() == 2 && to.get_y() == 0 && board[0][0]->get_type() == 'r' &&
                                         board[0][0]->get_move_counts() == 0 && !board_obj->is_position_check(Position(4, 0), 'b') &&
                                         !board_obj->is_position_check(Position(3, 0), 'b') && !board_obj->is_position_check(Position(2, 0), 'b')) {
		return true;
        }
	if (from.distance_squared(to) > 2 ||
                        board_obj->is_position_check(to, board[from.get_y()][from.get_x()]->get_color())) {
		return false;
	}

	return true;
}
