//
// Created by Tobias on 11/21/24.
//

#include "headers/Queen.h"
#include <iostream>
#include <SFML/Graphics/Texture.hpp>


Queen::Queen(const PieceColor color): Piece(color) {
}

void Queen::draw(sf::RenderTarget &target, sf::RenderStates const states) const {
    Piece::draw(target, states);
}

std::string Queen::getPieceName() const {
    return "queen";
}
