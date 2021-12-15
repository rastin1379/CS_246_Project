#include "chesscontroller.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"

using namespace std;

ChessController::ChessController(Board * board): board{board} {};

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
		board->computer_move();
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
			board->move(from, to, false);
		}
	}
}

void ChessController::undo() {
	if (board->get_game_mode() != "game") {
                throw GameError{"current game mode is " + board->get_game_mode()};
        }
	board->full_undo();
}

Position ChessController::make_position(string point) {
	Position p = Position(point[0] - 'a', 7 - point[1] + '1');
	if (p.get_x() < 0 || p.get_x() > 7 || p.get_y() < 0 || p.get_y() > 7) {
		throw GameError{"not a valid position"};
	}
	return p;
}

void ChessController::setup() {
	if (board->get_game_mode() != "pre_game") {
                throw GameError{"current game mode is " + board->get_game_mode()};
        }
	board->setup();
}

void ChessController::setup_add(char piece, string position) {
	if (board->get_game_mode() != "setup") {
                throw GameError{"current game mode is " + board->get_game_mode()};
        }
	if (piece == 'k' || piece == 'K') {
		board->setup_add(make_shared<King>(piece), make_position(position));
	} else if (piece == 'q' || piece == 'Q') {
		board->setup_add(make_shared<Queen>(piece), make_position(position));
	} else if (piece == 'b' || piece == 'B') {
		board->setup_add(make_shared<Bishop>(piece), make_position(position));
	} else if (piece == 'r' || piece == 'R') {
		board->setup_add(make_shared<Rook>(piece), make_position(position));
	} else if (piece == 'n' || piece == 'N') {
		board->setup_add(make_shared<Knight>(piece), make_position(position));
	} else if (piece == 'p' || piece == 'P') {
		board->setup_add(make_shared<Pawn>(piece), make_position(position));
	}
}

void ChessController::setup_remove(string position) {
	if (board->get_game_mode() != "setup") {
                throw GameError{"current game mode is " + board->get_game_mode()};
        }
	board->setup_remove(make_position(position));
}

void ChessController::setup_color(char color) {
	if (board->get_game_mode() != "setup") {
                throw GameError{"current game mode is " + board->get_game_mode()};
        }
	board->setup_color(color);
}

void ChessController::setup_done() {
	if (board->get_game_mode() != "setup") {
                throw GameError{"current game mode is " + board->get_game_mode()};
        }
	board->setup_done();
}

void ChessController::resign() {
	if (board->get_game_mode() != "game") {
                throw GameError{"current game mode is " + board->get_game_mode()};
        }
	board->resign();
}
