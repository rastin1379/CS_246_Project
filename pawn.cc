#include "pawn.h"

using namespace std;

Pawn::Pawn(char type): Piece{type} {}

bool Pawn::is_valid_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) {
	int step = ((get_color() == 'w') ? -1 : 1);
        if (to.get_x() == from.get_x() && to.get_y() == from.get_y() + step 
			&& board[to.get_y()][to.get_x()] == nullptr) {
		return true;
	}
	if (to.get_x() == from.get_x() && to.get_y() == from.get_y() + step * 2
                        && board[to.get_y()][to.get_x()] == nullptr
			&& board[to.get_y() - step][to.get_x()] == nullptr
			&& get_move_counts() == 0) {
                return true;
        }
	return false;
}
