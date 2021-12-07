#ifndef BOARD_H
#define BOARD_H

#include "subject.h"
#include <memory>
#include "move.h"
#include "position.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "computerplayer.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

const int board_size = 8;

class Board {
	private:
	std::vector<Move> moves;
	std::map<std::string, char> players;
	shared_ptr<Piece> [board_size][board_size];	
	
	public:	
	get_board();
	add_player(string player, char color);
	start();
};

#endif
