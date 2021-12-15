#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include "board.h"
#include <memory>
#include "position.h"

class ChessController {
	private:
	Board * board;	
	Position make_position(std::string point);

	public:
	ChessController(Board * board);
	void start(std::string player1, std::string player2);
	void move(std::string commands);
	void undo();
	void setup();
	void setup_add(char piece, std::string position);
	void setup_remove(std::string position);
	void setup_color(char color);
	void setup_done();
	void resign();
};

#endif
