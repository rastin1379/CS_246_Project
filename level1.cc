#include "level1.h"
#include "computerplayer.h"
#include <iostream>
#include "board.h"
#include "position.h"

using namespace std;

vector<Position> Level1::play(Board * board_obj) {
	cout << " LEVEL 1 " << endl;
	return {Position(0, 0), Position(7, 7)};
}
