#ifndef BOARD_H
#define BOARD_H

#include "subject.h"
#include <memory>
#include <map>
#include <vector>
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

class GameError {
	private:
	string message;

	public:
	GameError(string message): message{ message } {}
	void get_message() { return message; }
};

class Board : public Subject{
	private:
	std::vector<Move> moves;
	std::map<char, std::string> players;
	shared_ptr<Piece> [board_size][board_size] board;	
	char turn;
	void setup_standard();
	bool is_board_empty();

	public:	
	shared_ptr<Piece> [board_size][board_size] get_board();
	void add_player(string player, char color);
	void start();
	void setup_add(Piece piece, Position p);
	void setup_remove(Position p);
	void setup_color(char color);
	bool check_setup();
	void clean_board();
};

#endif
