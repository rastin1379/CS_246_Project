#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include "board.h"

class ChessController {
	private:
	Board board;	
	
	public:
	ChessController(std::shared_ptr board);
	void start(std::string player1, std::string player2);
};

#endif
