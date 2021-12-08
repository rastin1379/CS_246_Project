#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include "board.h"
#include <memory>
#include "position.h"

class ChessController {
	private:
	std::shared_ptr<Board> board;	
	Position make_position(std::string point);

	public:
	ChessController(std::shared_ptr<Board> board);
	void start(std::string player1, std::string player2);
	void move(std::string commands);
};

#endif
