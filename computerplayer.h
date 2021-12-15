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
	std::vector<std::vector<Position>> get_capturing_moves
		(Board * board_obj, std::vector<std::vector<Position>> legal_moves);
	std::vector<std::vector<Position>> get_check_moves
                (Board * board_obj, std::vector<std::vector<Position>> legal_moves);
	std::vector<std::vector<Position>> get_avoid_capture_moves
		(Board * board_obj, std::vector<std::vector<Position>> legal_moves);	
	int get_random(int a, int b);
	int count_attackable_pieces(Board * board_obj);	
	public:
	virtual std::vector<Position> play(Board * board_obj) = 0;
	virtual ~ComputerPlayer() = default;
};

#endif
