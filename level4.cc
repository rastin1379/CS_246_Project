#include "level4.h"
#include <iostream>
#include "computerplayer.h"
#include "position.h"
#include "board.h"

using namespace std;

vector<Position> Level4::play(Board * board_obj) {
        cout << " LEVEL 4 " << endl;
        return {Position(0, 0), Position(7, 7)};
}
