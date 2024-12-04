//
// Created by Tobias on 11/21/24.
//

#include "headers/King.h"

King::King(const PieceColor color): Piece(color) {
}

std::string King::getPieceName() const {
    return "king";
}
