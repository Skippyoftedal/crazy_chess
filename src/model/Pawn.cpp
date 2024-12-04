//
// Created by Tobias on 11/21/24.
//

#include "headers/Pawn.h"

Pawn::Pawn(const PieceColor color): Piece(color) {
}

std::string Pawn::getPieceName() const {
    return "pawn";
}