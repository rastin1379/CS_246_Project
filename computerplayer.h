#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "memory.h"
#include <vector>

class Board;
class Position;
class Piece;

class ComputerPlayer {
	protected:
	std::vector<std::vector<Position>> get_legal_moves(Board * board_obj, char color);	
	public:
	virtual std::vector<Position> play(Board * board_obj) = 0;
	virtual ~ComputerPlayer() = default;
};

#endif
