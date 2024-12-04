//
// Created by Tobias on 11/21/24.
//

#include "headers/Knight.h"
Knight::Knight(const PieceColor color): Piece(color) {
}

std::string Knight::getPieceName() const {
    return "knight";
}