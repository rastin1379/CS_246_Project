#include "chesscontroller.h"
#include <iostream>
#include <string.h>
#include <sstream>

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

void ChessController::move(std::string commands) {
	if (commands == "") {
		// computer move
	}
	else {
		string move_commands [3];
		stringstream ss(commands);
		int size = 0;
		while (ss >> move_commands[size]) {
    			size++;
		}
		if (size == 3) {
			// pawn promotion
		}	
		else {
			try {
				Position from = make_position(move_commands[0]);
				Position to = make_position(move_commands[1]);
				board->move(from, to);
			} catch (GameError ge) {
		                cout << "game error: " << ge.get_message() << endl;
       			}
		}
	}
}

Position ChessController::make_position(string point) {
	Position p = Position(point[0] - 'a', 7 - point[1] + '1');
	if (p.get_x() < 0 || p.get_x() > 7 || p.get_y() < 0 || p.get_y() > 7) {
		throw GameError{"not a valid position"};
	}
	return p;
}
