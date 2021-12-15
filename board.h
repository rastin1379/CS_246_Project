#ifndef BOARD_H
#define BOARD_H

#include "subject.h"
#include <memory>
#include <map>
#include <vector>
#include "move.h"
#include "position.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "computerplayer.h"
#include <string>

const int board_size = 8;

class GameError
{
private:
	std::string message;

public:
	GameError(std::string message) : message{message} {}
	std::string get_message() { return message; }
};

class Board : public Subject
{
private:
	std::map<char, std::shared_ptr<ComputerPlayer>> computers;
	std::vector<Move> moves;
	std::map<char, std::string> players;
	std::map<std::string, int> scores;
	std::vector<std::vector<std::shared_ptr<Piece>>> board;
	char turn;
	void setup_standard();
	bool is_board_empty();
	void make_board_empty();
	void handle_king_move(Position from, Position to);
	void handle_pawn_move(Position from, Position to);
	void add_castle_move(Position king_from, Position king_to, Position rook_from, Position rook_to);
	void promote(Position from, Position to, char promoted);
	void handle_next_turn(std::string message = "");
	bool is_piece_blockable(Position p);
	bool is_stalemate(char color);
	bool can_piece_move(Position p);
	std::string game_mode;
	void change_turn();
	void clean_board();
public:
	~Board();
	Board();
	std::vector<std::vector<std::shared_ptr<Piece>>> get_board();
	void add_player(std::string player, char color);
	void start();
	void setup_add(std::shared_ptr<Piece> piece, Position p);
	void setup_remove(Position p);
	void setup_color(char color);
	void setup_done();
	void move(Position from, Position to, bool is_temp_move);
	void computer_move();
	bool is_position_check(Position p, char color);
	void move_promotion(Position from, Position to, char promoted);
	std::string analyze_state();
	void undo();
	void full_undo();
	std::map<std::string, int> get_scores();
	void set_game_mode(std::string mode);
	std::string get_game_mode();
	Move get_last_move();
	int get_move_size();
	void setup();
	int piece_counts();
	void resign();
	char get_turn();
	Position get_position_piece(char name);
};

#endif
