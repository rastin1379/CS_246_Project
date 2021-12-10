#include "computerplayer.h"
#include <vector>
#include <memory>
#include "board.h"
#include "position.h"

using namespace std;

vector<vector<Position>> ComputerPlayer::get_legal_moves(Board * board_obj, char color) {
	vector<vector<Position>> legal_moves;
	vector<vector<shared_ptr<Piece>>> board = board_obj->get_board();
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] != nullptr && board[i][j]->get_color() == color) {
				for (int m = 0; m < 8; ++m) {
					for (int n = 0; n < 8; ++n) {
						if (board[i][j]->is_valid_move(board_obj, Position(j, i), Position(n, m))) {
							legal_moves.push_back({Position(j, i), Position(n, m)});
						}
					}
				}
			}
		}
	}
	return legal_moves;
}
