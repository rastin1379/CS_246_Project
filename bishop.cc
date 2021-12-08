#include "bishop.h"

Bishop::Bishop(char type): Piece{type} {}

bool Bishop::is_valied_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) {
        return true;
}
