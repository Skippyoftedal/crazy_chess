//
// Created by Tobias on 11/21/24.
//

#include "headers/Rook.h"
Rook::Rook(const PieceColor color): Piece(color) {
}

std::string Rook::getPieceName() const {
    return "rook";
}