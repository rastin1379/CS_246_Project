#ifndef CHESSVIEW_H
#define CHESSVIEW_H

#include <iostream>
#include "chesscontroller.h"
#include "observer.h"
#include <memory>
#include "board.h"
#include <vector>

class ChessView {
	public:
	// runs the chess program
	void run();
	
	private:
	ChessController controller;
	Board board;
	std::vector<std::shared_ptr<Observer>> observers;	
};

#endif
