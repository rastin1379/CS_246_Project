#include "board.h"
#include <cmath>
#include <iostream>

using namespace std;

Board::Board()
{
	scores["White"] = 0;
	scores["Black"] = 0;
	game_mode = "pre_game";
	make_board_empty();
}

void Board::set_game_mode(std::string mode)
{
	game_mode = mode;
}

string Board::get_game_mode()
{
	return game_mode;
}

void Board::handle_next_turn()
{
	string result = analyze_state();
	bool game_ended = false;
	if (result == "eb" || result == "ew" || result == "s")
	{
		if (result == "eb" || result == "ew")
		{
			char winner = result[1];
			if (result == "eb")
			{
				scores["Black"] += 1;
			}
			else
			{
				scores["White"] += 1;
			}
			scores[players[winner]] += 1;
		}
		else
		{
			scores["White"] += 0.5;
			scores["Black"] += 0.5;
			scores[players['w']] += 0.5;
			scores[players['b']] += 0.5;
		}
		game_ended = true;
	}
	else
	{
		change_turn();
	}
	notifyObservers(result);
	if (game_ended)
	{
		clean_board();
	}
}

void Board::clean_board()
{
	make_board_empty();
	moves.clear();
	players.clear();
	game_mode = "pre_game";
}

map<std::string, int> Board::get_scores()
{
	return scores;
}

string Board::analyze_state()
{
	bool white_in_check = is_position_check(get_position_piece('K'), 'w');
	bool black_in_check = is_position_check(get_position_piece('k'), 'b');
	bool white_in_stalemate = is_stalemate('w');
	bool black_in_stalemate = is_stalemate('b');
	// normal
	if (!white_in_stalemate && !black_in_stalemate && !white_in_check && !black_in_check)
	{
		return "n";
	}
	// stalemate
	if (white_in_stalemate || black_in_stalemate)
	{
		return "s";
	}

	if ((turn == 'w' && white_in_check) ||
			(turn == 'b' && black_in_check))
	{
		undo();
		throw GameError{"not a valid move, you are/will be in check!"};
	}
	Move last_move = moves[moves.size() - 1];
	bool can_defend = is_piece_blockable(last_move.get_to());
	bool white_king_can_move = can_piece_move(get_position_piece('K'));
	bool black_king_can_move = can_piece_move(get_position_piece('k'));
	// ended black won
	if (white_in_check && !white_king_can_move && !can_defend)
	{
		return "eb";
	}
	// ended white won
	if (black_in_check && !black_king_can_move && !can_defend)
	{
		return "ew";
	}
	// white in check
	if (white_in_check && (white_king_can_move || can_defend))
	{
		return "cw";
	}
	// black in check
	if (black_in_check && (black_king_can_move || can_defend))
	{
		return "cb";
	}
	// normal
	return "n";
}

bool Board::can_piece_move(Position p)
{
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			if ((i != p.get_y() && j != p.get_x()) &&
					board[p.get_y()][p.get_x()]->is_valid_move(this, p, Position(j, i)))
			{
				return true;
			}
		}
	}
	return false;
}

bool Board::is_stalemate(char color)
{
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			if ((board[i][j] != nullptr) &&
					(board[i][j]->get_color() == color))
			{
				for (int m = 0; m < board_size; ++m)
				{
					for (int n = 0; n < board_size; ++n)
					{
						if (board[i][j]->is_valid_move(this,
																					 Position(j, i),
																					 Position(n, m)))
						{
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

bool Board::is_piece_blockable(Position p)
{
	if (board[p.get_y()][p.get_x()]->get_piece_type() == 'n')
	{
		if (is_position_check(p, board[p.get_y()][p.get_x()]->get_color()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	char king = 'K';
	if (board[p.get_y()][p.get_x()]->get_color() == 'w')
	{
		king = 'k';
	}
	Position op_king = get_position_piece(king);
	int step_x = 0;
	if (op_king.get_x() - p.get_x() != 0)
	{
		step_x = (op_king.get_x() - p.get_x() > 0 ? 1 : -1);
	}
	int step_y = 0;
	if (op_king.get_y() - p.get_y() != 0)
	{
		step_y = (op_king.get_y() - p.get_y() > 0 ? 1 : -1);
	}
	int current_x = p.get_x();
	int current_y = p.get_y();
	while (current_x != op_king.get_x() ||
				 current_y != op_king.get_y())
	{
		if (is_position_check(Position(current_x, current_y),
													board[p.get_y()][p.get_x()]->get_color()))
		{
			return true;
		}
		current_x += step_x;
		current_y += step_y;
	}
	return false;
}

Position Board::get_position_piece(char name)
{
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			if (board[i][j] != nullptr &&
					board[i][j]->get_type() == name)
			{
				return Position(j, i);
			}
		}
	}
	return Position(-1, -1);
}

void Board::full_undo()
{
	undo();
	handle_next_turn();
}

void Board::undo()
{
	int moves_size = moves.size();
	if (moves_size == 0)
	{
		throw GameError{"undo illegal"};
	}
	Move last_move = moves[moves_size - 1];
	board[last_move.get_from().get_y()][last_move.get_from().get_x()] = last_move.get_piece();
	board[last_move.get_to().get_y()][last_move.get_to().get_x()] = last_move.get_removed_piece();
	board[last_move.get_from().get_y()][last_move.get_from().get_x()]->sub_move_counts();
	if (last_move.is_en_passant())
	{
		int step = (last_move.get_piece()->get_color() == 'w') ? -1 : 1;
		if (last_move.get_piece()->get_color() == 'w')
		{
			board[last_move.get_to().get_y() - step][last_move.get_to().get_x()] = make_shared<Pawn>('p');
		}
		else
		{
			board[last_move.get_to().get_y() - step][last_move.get_to().get_x()] = make_shared<Pawn>('P');
		}
		board[last_move.get_to().get_y() - step][last_move.get_to().get_x()]->add_move_counts();
	}
	if (last_move.is_castle())
	{
		if (last_move.get_to().get_x() == 6 && last_move.get_to().get_y() == 0)
		{
			board[0][7] = board[0][5];
			board[0][5] = nullptr;
		}
		if (last_move.get_to().get_x() == 2 && last_move.get_to().get_y() == 0)
		{
			board[0][0] = board[0][3];
			board[0][3] = nullptr;
		}
		if (last_move.get_to().get_x() == 6 && last_move.get_to().get_y() == 7)
		{
			board[7][0] = board[7][5];
			board[7][5] = nullptr;
		}
		else
		{
			board[7][7] = board[7][3];
			board[7][3] = nullptr;
		}
	}
}

void Board::move(Position from, Position to)
{
	if (board[from.get_y()][from.get_x()] == nullptr)
	{
		throw GameError{"no piece detected"};
	}
	if (board[from.get_y()][from.get_x()]->get_color() != turn)
	{
		throw GameError{"invalid color"};
	}
	if (from.get_x() == to.get_x() && from.get_y() == to.get_y())
	{
		throw GameError{"no move detected"};
	}
	if (board[from.get_y()][from.get_x()]->get_piece_type() == 'k')
	{
		handle_king_move(from, to);
	}
	else if (board[from.get_y()][from.get_x()]->get_piece_type() == 'p')
	{
		handle_pawn_move(from, to);
	}
	else
	{
		if (board[from.get_y()][from.get_x()]->is_valid_move(this, from, to))
		{
			moves.emplace_back(board[from.get_y()][from.get_x()],
												 board[to.get_y()][to.get_x()],
												 from, to, false, false, false);
			board[to.get_y()][to.get_x()] = board[from.get_y()][from.get_x()];
			board[from.get_y()][from.get_x()]->add_move_counts();
			board[from.get_y()][from.get_x()] = nullptr;
		}
		else
		{
			throw GameError{"invalid move"};
		}
	}
	handle_next_turn();
}

void Board::move_promotion(Position from, Position to, char promoted)
{
	if (board[from.get_y()][from.get_x()]->get_piece_type() != 'p')
	{
		throw GameError{"no pawn detected at the given position"};
	}
	if (promoted != 'r' && promoted != 'b' && promoted != 'k' && promoted != 'q' && promoted != 'R' && promoted != 'B' && promoted != 'K' && promoted != 'Q')
	{
		throw GameError{"promotion to rook, bishop, kinght, or queen is valid"};
	}
	if (board[from.get_y()][from.get_x()]->is_valid_move(this, from, to) &&
			((board[from.get_y()][from.get_x()]->get_color() == 'w' && to.get_y() == 0) ||
			 (board[from.get_y()][from.get_x()]->get_color() == 'b' && to.get_y() == 7)))
	{
		promote(from, to, promoted);
	}
	else
	{
		throw GameError{"invalid promotion"};
	}
	handle_next_turn();
}

void Board::promote(Position from, Position to, char promoted)
{
	char color = (promoted < 'a') ? 'w' : 'b';
	if (color != board[from.get_y()][from.get_x()]->get_color())
	{
		throw GameError{"promoted and piece color do not match"};
	}
	moves.emplace_back(board[from.get_y()][from.get_x()],
										 board[to.get_y()][to.get_x()],
										 from, to, false, false, true);
	board[from.get_y()][from.get_x()] = nullptr;
	if (promoted == 'r' || promoted == 'R')
	{
		board[to.get_y()][to.get_x()] = make_shared<Rook>(promoted);
	}
	if (promoted == 'b' || promoted == 'B')
	{
		board[to.get_y()][to.get_x()] = make_shared<Bishop>(promoted);
	}
	if (promoted == 'k' || promoted == 'K')
	{
		board[to.get_y()][to.get_x()] = make_shared<Knight>(promoted);
	}
	else
	{
		board[to.get_y()][to.get_x()] = make_shared<Queen>(promoted);
	}
	board[to.get_y()][to.get_x()]->add_move_counts();
}

void Board::handle_king_move(Position from, Position to)
{
	if (board[from.get_y()][from.get_x()]->is_valid_move(this, from, to))
	{
		moves.emplace_back(board[from.get_y()][from.get_x()],
											 board[to.get_y()][to.get_x()],
											 from, to, false, false, false);
		board[to.get_y()][to.get_x()] = board[from.get_y()][from.get_x()];
		board[from.get_y()][from.get_x()]->add_move_counts();
		board[from.get_y()][from.get_x()] = nullptr;
	}
	// castle check
	else if (from.get_x() == 4 && from.get_y() == 7 && board[7][4]->get_move_counts() == 0 && board[7][5] == nullptr && board[7][6] == nullptr && board[7][7] != nullptr && to.get_x() == 6 && to.get_y() == 7 && board[7][7]->get_type() == 'R' &&
					 board[7][7]->get_move_counts() == 0 && !is_position_check(Position(4, 7), 'w') &&
					 !is_position_check(Position(5, 7), 'w') && !is_position_check(Position(6, 7), 'w'))
	{
		add_castle_move(Position(4, 7), Position(6, 7), Position(7, 7), Position(5, 7));
	}
	else if (from.get_x() == 4 && from.get_y() == 7 && board[7][4]->get_move_counts() == 0 && board[7][3] == nullptr && board[7][2] == nullptr && board[7][0] != nullptr && to.get_x() == 2 && to.get_y() == 7 && board[7][0]->get_type() == 'R' &&
					 board[7][0]->get_move_counts() == 0 && !is_position_check(Position(4, 7), 'w') &&
					 !is_position_check(Position(3, 7), 'w') && !is_position_check(Position(2, 7), 'w'))
	{
		add_castle_move(Position(4, 7), Position(2, 7), Position(0, 7), Position(3, 7));
	}
	else if (from.get_x() == 4 && from.get_y() == 0 && board[0][4]->get_move_counts() == 0 && board[0][5] == nullptr && board[0][6] == nullptr && board[0][7] != nullptr && to.get_x() == 6 && to.get_y() == 0 && board[0][7]->get_type() == 'r' &&
					 board[0][7]->get_move_counts() == 0 && !is_position_check(Position(4, 0), 'b') &&
					 !is_position_check(Position(5, 0), 'b') && !is_position_check(Position(6, 0), 'b'))
	{
		add_castle_move(Position(4, 0), Position(6, 0), Position(7, 0), Position(5, 0));
	}
	else if (from.get_x() == 4 && from.get_y() == 0 && board[0][4]->get_move_counts() == 0 && board[0][3] == nullptr && board[0][2] == nullptr && board[0][0] != nullptr && to.get_x() == 2 && to.get_y() == 0 && board[0][0]->get_type() == 'r' &&
					 board[0][0]->get_move_counts() == 0 && !is_position_check(Position(4, 0), 'b') &&
					 !is_position_check(Position(3, 0), 'b') && !is_position_check(Position(2, 0), 'b'))
	{
		add_castle_move(Position(4, 0), Position(2, 0), Position(0, 0), Position(3, 0));
	}
	else
	{
		throw GameError{"invalid king/castle move"};
	}
}

void Board::add_castle_move(Position king_from, Position king_to, Position rook_from, Position rook_to)
{
	moves.emplace_back(board[king_from.get_y()][king_from.get_x()],
										 nullptr,
										 king_from, king_to, false, true, false);
	board[king_to.get_y()][king_to.get_x()] = board[king_from.get_y()][king_from.get_x()];
	board[king_to.get_y()][king_to.get_x()]->add_move_counts();
	board[rook_to.get_y()][rook_to.get_x()] = board[rook_from.get_y()][rook_from.get_x()];
	board[rook_to.get_y()][rook_to.get_x()]->add_move_counts();
	board[king_from.get_y()][king_from.get_x()] = nullptr;
	board[rook_from.get_y()][rook_from.get_x()] = nullptr;
}

// is the given position under check
bool Board::is_position_check(Position p, char color)
{
	// imagine it is filled with a piece
	shared_ptr<Piece> tmp = board[p.get_y()][p.get_x()];
	char queen = (color == 'w' ? 'Q' : 'q');
	board[p.get_y()][p.get_x()] = make_shared<Queen>(queen);

	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			if ((board[i][j] == nullptr) ||
					(board[i][j]->get_color() == color))
			{
				continue;
			}
			if (board[i][j]->is_valid_move(this, Position(j, i), p))
			{
				board[p.get_y()][p.get_x()] = tmp;
				return true;
			}
		}
	}

	board[p.get_y()][p.get_x()] = tmp;
	return false;
}

void Board::handle_pawn_move(Position from, Position to)
{
	if (board[from.get_y()][from.get_x()]->is_valid_move(this, from, to))
	{
		moves.emplace_back(board[from.get_y()][from.get_x()],
											 board[to.get_y()][to.get_x()],
											 from, to, false, false, false);
		board[to.get_y()][to.get_x()] = board[from.get_y()][from.get_x()];
		board[from.get_y()][from.get_x()]->add_move_counts();
		board[from.get_y()][from.get_x()] = nullptr;
	}
	else
	{
		//  en passant check
		if (moves.size() == 0)
		{
			throw GameError{"invalid move"};
		}
		Move last_move = moves.back();
		int step = (board[from.get_y()][from.get_x()]->get_color() == 'w' ? -1 : 1);
		if (last_move.get_piece()->get_piece_type() == 'p' &&
				last_move.get_from().distance_squared(last_move.get_to()) == 4 &&
				last_move.get_piece()->get_color() != board[from.get_y()][from.get_x()]->get_color() &&
				to.get_x() == last_move.get_to().get_x() && (to.get_y() == last_move.get_to().get_y() + step) &&
				(abs(to.get_x() - from.get_x()) == 1) && (to.get_y() - from.get_y() == step))
		{
			moves.emplace_back(board[from.get_y()][from.get_x()],
												 board[to.get_y()][to.get_x()],
												 from, to, true, false, false);
			board[to.get_y()][to.get_x()] = board[from.get_y()][from.get_x()];
			board[from.get_y()][from.get_x()]->add_move_counts();
			board[from.get_y()][from.get_x()] = nullptr;
			board[last_move.get_to().get_y()][last_move.get_to().get_x()] = nullptr;
		}
		else
		{
			throw GameError{"invalid move"};
		}
	}
	if ((board[to.get_y()][to.get_x()]->get_color() == 'w' && to.get_y() == 0) ||
			(board[to.get_y()][to.get_x()]->get_color() == 'b' && to.get_y() == 7))
	{
		if (board[to.get_y()][to.get_x()]->get_color() == 'w')
		{
			board[to.get_y()][to.get_x()] = make_shared<Queen>('Q');
			board[to.get_y()][to.get_x()]->add_move_counts();
		}
		else
		{
			board[to.get_y()][to.get_x()] = make_shared<Queen>('q');
			board[to.get_y()][to.get_x()]->add_move_counts();
		}
		moves.back().set_promotion(true);
	}
}

void Board::make_board_empty()
{
	for (int i = 0; i < board_size; i++)
	{
		vector<shared_ptr<Piece>> row;
		for (int j = 0; j < board_size; ++j)
		{
			row.push_back(nullptr);
		}
		board.push_back(row);
	}
}

vector<vector<shared_ptr<Piece>>> Board::get_board()
{
	return board;
}

void Board::add_player(string player, char color)
{
	players[color] = player;
}

void Board::start()
{
	if (players.size() != 2)
	{
		throw GameError{"two player is required"};
	}
	if (is_board_empty())
	{
		setup_standard();
		turn = 'w';
	}
	game_mode = "game";
	notifyObservers("n");
}

void Board::setup_add(shared_ptr<Piece> piece, Position p)
{
	board[p.get_y()][p.get_x()] = piece;
}

void Board::setup_remove(Position p)
{
	board[p.get_y()][p.get_x()] = nullptr;
}

void Board::setup_color(char color)
{
	turn = color;
}

bool Board::check_setup()
{
	return true;
}

void Board::setup_standard()
{
	setup_add(make_shared<Rook>('r'), Position(0, 0));
	setup_add(make_shared<Knight>('n'), Position(1, 0));
	setup_add(make_shared<Bishop>('b'), Position(2, 0));
	setup_add(make_shared<Queen>('q'), Position(3, 0));
	setup_add(make_shared<King>('k'), Position(4, 0));
	setup_add(make_shared<Bishop>('b'), Position(5, 0));
	setup_add(make_shared<Knight>('n'), Position(6, 0));
	setup_add(make_shared<Rook>('r'), Position(7, 0));
	for (int i = 0; i < board_size; ++i)
	{
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
	for (int i = 0; i < board_size; ++i)
	{
		setup_add(make_shared<Pawn>('P'), Position(i, 6));
	}
}

bool Board::is_board_empty()
{
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			if (board[i][j] != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}

void Board::change_turn()
{
	if (turn == 'w')
	{
		turn = 'b';
	}
	else
	{
		turn = 'w';
	}
}

Move Board::get_last_move()
{
	return moves[moves.size() - 1];
}

int Board::get_move_size()
{
	return moves.size();
}
