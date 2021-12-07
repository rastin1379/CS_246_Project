#include "chesscontroller.h"

using namespace std;

ChessController::ChessController(shared_ptr board): board{board} {};

void ChessController::start(string player1, string player2) {
	board.add_player(player1, 'w');
        board.add_player(player2, 'b');
	board.start();	
}
