#include "bishop.h"
#include <cmath> 

Bishop::Bishop(char type): Piece{type} {}

bool Bishop::is_valid_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) {
	if (abs(from.get_y() - to.get_y()) == abs(from.get_x() - to.get_x()) &&
              (board[to.get_y()][to.get_x()] == nullptr ||
               board[to.get_y()][to.get_x()]->get_color() != get_color())) {
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
        else {
                return false;
        }
}


