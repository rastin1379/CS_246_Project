#include "level1.h"
#include "computerplayer.h"
#include <iostream>
#include "board.h"
#include "position.h"
#include <random>

using namespace std;

vector<Position> Level1::play(Board * board_obj) {
	vector<vector<Position>> valid_moves = get_legal_moves(board_obj, board_obj->get_turn());
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> dist(0, valid_moves.size() - 1);	
	return valid_moves[dist(rng)];
}