
#include "headers/Bishop.h"


Bishop::Bishop(const PieceColor color): Piece(color) {
}

std::string Bishop::getPieceName() const {
    return "bishop";
}