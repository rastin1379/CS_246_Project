#include "computerplayer.h"
#include <vector>
#include <memory>
#include "board.h"
#include <iostream>
#include "position.h"
#include <random>

using namespace std;

int ComputerPlayer::get_random(int a, int b) {
	random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> dist(a, b - 1);
        return dist(rng);
}

vector<vector<Position>> ComputerPlayer::get_legal_moves(Board * board_obj, char color) {
	vector<vector<Position>> legal_moves;
	vector<vector<shared_ptr<Piece>>> board = board_obj->get_board();
	char king = (color == 'w' ? 'K' : 'k');
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] != nullptr && board[i][j]->get_color() == color) {
				for (int m = 0; m < 8; ++m) {
					for (int n = 0; n < 8; ++n) {
						if (board[i][j]->is_valid_move(board_obj, Position(j, i), Position(n, m))) {
							try {
								board_obj->move(Position(j, i), Position(n, m), true);
							} catch (GameError e) {
								cout << "j i n m #" << j << " " << i << " " << n << " " << m << endl;
								throw;
							}
							Position king_position = board_obj->get_position_piece(king);
							if (!board_obj->is_position_check(king_position, board_obj->get_turn())) {
								legal_moves.push_back({Position(j, i), Position(n, m)});
							}
							board_obj->undo();
						}
					}
				}
			}
		}
	}
	return legal_moves;
}

vector<std::vector<Position>> ComputerPlayer::get_capturing_moves (Board * board_obj, 
		std::vector<std::vector<Position>> legal_moves) {
	vector<vector<Position>> capturing_moves;
	vector<vector<shared_ptr<Piece>>> board = board_obj->get_board();
	int size = legal_moves.size();
	for (int i = 0; i < size; ++i) {
		if (board[legal_moves[i][1].get_y()][legal_moves[i][1].get_x()] != nullptr) {
			capturing_moves.push_back(legal_moves[i]);
		}
	}
	return capturing_moves;
}
		
vector<vector<Position>> ComputerPlayer::get_check_moves (Board * board_obj, 
		vector<vector<Position>> legal_moves) {
	vector<vector<Position>> check_moves;
	vector<vector<shared_ptr<Piece>>> board = board_obj->get_board();
	int size = legal_moves.size();
	char op_king = (board_obj->get_turn() == 'w' ? 'k' : 'K');
	char op_color = (board_obj->get_turn() == 'w' ? 'b' : 'w');
	Position position_op_king = board_obj->get_position_piece(op_king);
	for (int i = 0; i < size; ++i) {
		board_obj->move(legal_moves[i][0], legal_moves[i][1], true);
		if (board_obj->is_position_check(position_op_king, op_color)) {
			check_moves.push_back(legal_moves[i]);
		}
		board_obj->undo();
	}
	return check_moves;
}


vector<vector<Position>> ComputerPlayer::get_avoid_capture_moves (Board * board_obj, 
		vector<vector<Position>> legal_moves) {
	vector<vector<Position>> avoid_capture_moves;
	vector<vector<shared_ptr<Piece>>> board = board_obj->get_board();
	int size = legal_moves.size();
	int current_attackable = count_attackable_pieces(board_obj);
	for (int i = 0; i < size; ++i) {
                board_obj->move(legal_moves[i][0], legal_moves[i][1], true);
		if (count_attackable_pieces(board_obj) < current_attackable) {
			avoid_capture_moves.push_back(legal_moves[i]);
		}
		board_obj->undo();
	}
	return avoid_capture_moves;
}


int ComputerPlayer::count_attackable_pieces(Board * board_obj) {
	vector<vector<shared_ptr<Piece>>> board = board_obj->get_board();
	int count = 0;
	for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) { 
			if (board[i][j] != nullptr && board[i][j]->get_color() == board_obj->get_turn() &&
					board[i][j]->get_piece_type() != 'k') {
				if (board_obj->is_position_check(Position(j, i), board_obj->get_turn())) {
					count++;
				}		
			}
		}
	}
	return count;
}



