#include "chesscontroller.h"
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

ChessController::ChessController(std::shared_ptr<Board> board): board{board} {};

void ChessController::start(string player1, string player2) {
	if (board->get_game_mode() != "pre_game") {
		throw GameError{"current game mode is " + board->get_game_mode()};
	}
	board->add_player(player1, 'w');
       	board->add_player(player2, 'b');
	board->start();	
}

void ChessController::move(std::string commands) {
	if (board->get_game_mode() != "game") {
                throw GameError{"current game mode is " + board->get_game_mode()};
        }
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
			Position from = make_position(move_commands[0]);
                        Position to = make_position(move_commands[1]);
			char promoted = move_commands[2][0];
			board->move_promotion(from, to, promoted);
		}	
		else {
			Position from = make_position(move_commands[0]);
			Position to = make_position(move_commands[1]);
			board->move(from, to);
		}
	}
}

void ChessController::undo() {
	board->full_undo();
}

Position ChessController::make_position(string point) {
	Position p = Position(point[0] - 'a', 7 - point[1] + '1');
	if (p.get_x() < 0 || p.get_x() > 7 || p.get_y() < 0 || p.get_y() > 7) {
		throw GameError{"not a valid position"};
	}
	return p;
}
