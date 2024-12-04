//
// Created by Tobias on 11/20/24.
//

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "headers/Piece.h"
#include "headers/PathUtil.h"

Piece::Piece(const PieceColor piece_color): piece_color(piece_color), width(50) {




}

PieceColor Piece::getColor() const {
    return piece_color;
}

void Piece::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Texture texture;

    if (!texture.loadFromFile(PathUtil::getPath(getPieceName(), piece_color))) {
        return;
    }
    texture.setSmooth(true);
    sf::Sprite sprite(texture);
    sprite.setPosition(position);

    auto const currentSize = sprite.getTextureRect().getSize();

    auto const newSize = sf::Vector2f(width / static_cast<float>(currentSize.x),
                                      width / static_cast<float>(currentSize.y));

    sprite.setScale(newSize);


    target.draw(sprite);
}
