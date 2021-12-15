#include "level1.h"
#include "computerplayer.h"
#include "board.h"
#include "position.h"

using namespace std;

vector<Position> Level1::play(Board * board_obj) {
	vector<vector<Position>> valid_moves = get_legal_moves(board_obj, board_obj->get_turn());
	return valid_moves[get_random(0, valid_moves.size())];
}
