#include "board.h"

using namespace std;

Board::Board() {
	make_board_empty();
}

void Board::move(Position from, Position to) {
	if (board[from.get_y()][from.get_x()]->get_piece_type() == 'k'
			&& from.distance_squared(to) > 1) {
		// castle
	}
	else {
		if (board[from.get_y()][from.get_x()]->is_valied_move(board, from, to)) {
			moves.emplace_back(board[from.get_y()][from.get_x()],
					board[to.get_y()][to.get_x()],
					from, to);
			board[to.get_y()][to.get_x()] = board[from.get_y()][from.get_x()];
			board[from.get_y()][from.get_x()] = nullptr;
		} else {
			throw GameError{"invalid move"};
		}	
	}
	// check win ...
	notifyObservers();	
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
		throw GameError{"two player is required"};	
	}
	if (is_board_empty()) {
		setup_standard();
		turn = 'w';
	}
	notifyObservers();
}

void Board::setup_add(shared_ptr<Piece> piece, Position p) {
	board[p.get_y()][p.get_x()] = piece;	
}

void Board::setup_remove(Position p) {
	board[p.get_y()][p.get_x()] = nullptr;
}

void Board::setup_color(char color) {
	turn = color;
}
        
bool Board::check_setup() {
	return true;
}

void Board::setup_standard() {
	setup_add(make_shared<Rook>('r'), Position(0, 0));
	setup_add(make_shared<Knight>('n'), Position(1, 0));
	setup_add(make_shared<Bishop>('b'), Position(2, 0));
	setup_add(make_shared<Queen>('q'), Position(3, 0));
	setup_add(make_shared<King>('k'), Position(4, 0));
	setup_add(make_shared<Bishop>('b'), Position(5, 0));
	setup_add(make_shared<Knight>('n'), Position(6, 0));
	setup_add(make_shared<Rook>('r'), Position(7, 0));
	for (int i = 0; i < board_size; ++i) {
		setup_add(make_shared<Pawn>('p'), Position(i, 1));
	}
	setup_add(make_shared<Rook>('R'), Position(0, 7));
        setup_add(make_shared<Knight>('N'), Position(1, 7));
        setup_add(make_shared<Bishop>('B'), Position(2, 7));
        setup_add(make_shared<Queen>('Q'), Position(3, 7));
        setup_add(make_shared<King>('K'), Position(4, 7));
        setup_add(make_shared<Bishop>('B'), Position(5, 7));
        setup_add(make_shared<Knight>('N'), Position(6, 7));
        setup_add(make_shared<Rook>('R'), Position(7, 7));
	for (int i = 0; i < board_size; ++i) {
                setup_add(make_shared<Pawn>('P'), Position(i, 6));
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
