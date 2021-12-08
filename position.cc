#include "position.h"

Position::Position(int x, int y): x{x}, y{y} {}

int Position::get_x() { return x; }

int Position::get_y() { return y; }

int Position::distance_squared(Position p) {
	return (p.get_x() - x) * (p.get_x() - x) + 
		(p.get_y() - y) * (p.get_y() - y);
}
