#include "rook.h"
#include <algorithm>

using namespace std;

Rook::Rook(char type): Piece{type} {}

bool Rook::is_valid_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) {
        if ((from.get_x() == to.get_x() || from.get_y() == to.get_y()) &&
              (board[to.get_y()][to.get_x()] == nullptr ||
               board[to.get_y()][to.get_x()]->get_color() != get_color())) {
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
        else {
                return false;
        }
}
