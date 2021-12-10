#include "level2.h"
#include <iostream>
#include "computerplayer.h"
#include "position.h"
#include "board.h"

using namespace std;

vector<Position> Level2::play(Board * board_obj) {
        cout << " LEVEL 2 " << endl;
        return {Position(0, 0), Position(7, 7)};
}
