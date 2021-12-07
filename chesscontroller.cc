#include "chesscontroller.h"
#include <iostream>

using namespace std;

ChessController::ChessController(std::shared_ptr<Board> board): board{board} {};

void ChessController::start(string player1, string player2) {
	try {
		board->add_player(player1, 'w');
        	board->add_player(player2, 'b');
		board->start();	
	} catch (GameError ge) {
		cout << "game error: " << ge.get_message() << endl; 
	} 
}
