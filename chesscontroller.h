#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include "board.h"
#include <memory>

class ChessController {
	private:
	std::shared_ptr<Board> board;	
	
	public:
	ChessController(std::shared_ptr<Board> board);
	void start(std::string player1, std::string player2);
};

#endif
