#include "level3.h"
#include "computerplayer.h"
#include "position.h"
#include "board.h"

using namespace std;

vector<Position> Level3::play(Board * board_obj) {
	vector<vector<Position>> valid_moves = get_legal_moves(board_obj, board_obj->get_turn());
        vector<vector<Position>> valid_capturing_moves = get_capturing_moves(board_obj, valid_moves);
        vector<vector<Position>> valid_check_moves = get_check_moves(board_obj, valid_moves);
	vector<vector<Position>> valid_avoid_capture_moves = get_avoid_capture_moves(board_obj, valid_moves);	
	if (valid_avoid_capture_moves.size() != 0) {
		return valid_avoid_capture_moves[get_random(0, valid_avoid_capture_moves.size())];
	}
        if (valid_capturing_moves.size() != 0) {
                return valid_capturing_moves[get_random(0, valid_capturing_moves.size())];
        }
	if (valid_check_moves.size() != 0) {
                return valid_check_moves[get_random(0, valid_check_moves.size())];
        }
        else {
                return valid_moves[get_random(0, valid_moves.size())];
        }
}
