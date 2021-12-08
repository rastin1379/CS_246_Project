#include "queen.h"

using namespace std;

Queen::Queen(char type): Piece{type} {}

bool Queen::is_valid_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) {
	if (abs(from.get_y() - to.get_y()) == abs(from.get_x() - to.get_x()) &&
              (board[to.get_y()][to.get_x()] == nullptr ||
               board[to.get_y()][to.get_x()]->get_color() != get_color())) {
                return is_diagonal(board, from, to);
        }
 	if ((from.get_x() == to.get_x() || from.get_y() == to.get_y()) &&
              (board[to.get_y()][to.get_x()] == nullptr ||
               board[to.get_y()][to.get_x()]->get_color() != get_color())) {
                return is_straight(board, from, to);
        }
	return false;	
}

bool Queen::is_diagonal(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) {
	int step_x = 1;
        int step_y = 1;
        if (to.get_y() < from.get_y()) { step_y = -1; }
        if (to.get_x() < from.get_x()) { step_x = -1; }
        int j = from.get_x() + step_x;
        for (int i = from.get_y() + step_y; i != to.get_y(); i += step_y) {
                if (board[i][j] != nullptr) { return false; }
                j += step_x;
        }
        return true;
}

bool Queen::is_straight(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) {
	if (from.get_x() == to.get_x()) {
                for (int i = min(from.get_y(), to.get_y()) + 1;
                                i < max(from.get_y(), to.get_y()); ++i) {
                        if (board[i][from.get_x()] != nullptr) {
                                return false;
                        }
                }
        }
        else {
                for (int i = min(from.get_x(), to.get_x()) + 1;
                                i < max(from.get_x(), to.get_x()); ++i) {
                        if (board[from.get_y()][i] != nullptr) {
                                return false;
                        }
                }
        }
	return true;
}





