#include "pawn.h"

Pawn::Pawn(char type): Piece{type} {}

bool Pawn::is_valied_move(std::vector<std::vector<std::shared_ptr<Piece>>> board,
             Position from,Position to) {
        return true;
}
