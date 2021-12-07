#include "board.h"

using namespace std;

Board::Board() {
	make_board_empty();
}

void Board::make_board_empty() {
        for (int i = 0; i < board_size; i++) {
                vector<shared_ptr<Piece>> row;
		for (int j = 0; j < board_size; ++j) {
			row.push_back(nullptr);
		}
		board.push_back(row);
        }
}

vector<vector<shared_ptr<Piece>>> Board::get_board() {
	return board;
}

void Board::add_player(string player, char color) {
	players[color] = player;
}

void Board::start() {
	if (players.size() != 2) {
		throw GameError{"Two player is required"};	
	}
	if (is_board_empty()) {
		setup_standard();
	}
	notifyObservers();
}

void Board::setup_add(shared_ptr<Piece> piece, Position p) {
	board[p.get_x()][p.get_y()] = piece;	
}

void Board::setup_remove(Position p) {
	board[p.get_x()][p.get_y()] = nullptr;
}

void Board::setup_color(char color) {
	turn = color;
}
        
bool Board::check_setup() {
	return true;
}

void Board::setup_standard() {
	setup_add(make_shared<Rook>('r'), Position(0, 0));
	setup_add(make_shared<Knight>('n'), Position(0, 1));
	setup_add(make_shared<Bishop>('b'), Position(0, 2));
	setup_add(make_shared<Queen>('q'), Position(0, 3));
	setup_add(make_shared<King>('k'), Position(0, 4));
	setup_add(make_shared<Bishop>('b'), Position(0, 5));
	setup_add(make_shared<Knight>('n'), Position(0, 6));
	setup_add(make_shared<Rook>('r'), Position(0, 7));
	for (int i = 0; i < board_size; ++i) {
		setup_add(make_shared<Pawn>('p'), Position(1, i));
	}
	setup_add(make_shared<Rook>('R'), Position(7, 0));
        setup_add(make_shared<Knight>('N'), Position(7, 1));
        setup_add(make_shared<Bishop>('B'), Position(7, 2));
        setup_add(make_shared<Queen>('Q'), Position(7, 3));
        setup_add(make_shared<King>('K'), Position(7, 4));
        setup_add(make_shared<Bishop>('B'), Position(7, 5));
        setup_add(make_shared<Knight>('N'), Position(7, 6));
        setup_add(make_shared<Rook>('R'), Position(7, 7));
	for (int i = 0; i < board_size; ++i) {
                setup_add(make_shared<Pawn>('P'), Position(6, i));
        }
}

bool Board::is_board_empty() {
	for (int i = 0; i < board_size; ++i) {
		for (int j = 0; j < board_size; ++j) {
			if (board[i][j] != nullptr) {
				return false;
			} 
		}
	} 
	return true;
}
