#include "board.h"

using namespace std;

shared_ptr<Piece> [board_size][board_size] board::get_board() {
	return board;
}

void board::add_player(string player, char color) {
	players[color] = player;
}

void board::start() {
	if (players.size() != 2) {
		throw GameError{"Two player is required"};	
	}
	if (is_board_empty) {
		setup_standard();
	}
	notifyObservers();
}

void board::setup_add(shared_ptr<Piece> piece, Position p) {
	board[p.get_x][p.get_y] = piece;	
}

void board::setup_remove(Position p) {
	board[p.get_x][p.get_y] = nullptr;
}

void board::setup_color(char color) {
	turn = color;
}
        
bool board::check_setup() {
	return true;
}

void board::setup_standard() {
	
}

bool board::is_board_empty() {
	for (int i = 0; i < board_size; ++i) {
		for (int j = 0; j < board_size; ++j) {
			if (board[i][j] != nullptr) {
				return false;
			} 
		}
	} 
	return true;
}
