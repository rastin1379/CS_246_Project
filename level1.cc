#include "level1.h"
#include "computerplayer.h"
#include <iostream>
#include "board.h"
#include "position.h"

using namespace std;

vector<Position> Level1::play(Board * board_obj) {
	vector<vector<Position>> valid_moves = get_legal_moves(board_obj, board_obj->get_turn());
	int a = get_random(0, valid_moves.size());
	cout << "xfrom yto xto yto: " << valid_moves[a][0].get_x() << 
	       valid_moves[a][0].get_y() <<
       valid_moves[a][1].get_x() << 
               valid_moves[a][1].get_y() << endl;	       
	return valid_moves[a];
}
