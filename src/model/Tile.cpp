//
// Created by Tobias on 11/22/24.
//
#include "headers/Tile.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "FontLoader.h"


Tile::Tile(sf::RectangleShape tileShape, sf::Color default_color, std::string text): tileShape(std::move(tileShape)),
    default_color(default_color),
    pos(std::move(text)) {
    this->tileShape.setFillColor(default_color);
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(tileShape);

    if (piece != nullptr) {
        target.draw(*piece);
    }

    auto t = sf::Text(pos, FontLoader::getInstance().get_font());
    t.setPosition(tileShape.getPosition());
    t.setFillColor(sf::Color::Magenta);
    //target.draw(t);
}

void Tile::set_piece(Piece *piece) {
    this->piece = piece;
    if (piece != nullptr) {
        this->piece->set_position(tileShape.getPosition());
    }
}

Piece *Tile::get_piece() const {
    return piece;
}

bool Tile::has_piece() const {
    return piece != nullptr;
}


bool Tile::is_selected() const {
    return selected;
}

bool Tile::is_available() const {
    return available;
}


void Tile::set_selected(bool const selected) {
    //std::cout << "Selecting tile " << pos << std::endl;
    if (selected) {
        tileShape.setFillColor(sf::Color::Cyan);
    } else {
        tileShape.setFillColor(default_color);
    }
    this->selected = selected;
}

void Tile::set_available(const bool possible) {
    if (possible) {
        tileShape.setFillColor(sf::Color::Green);
    } else {
        tileShape.setFillColor(default_color);
    }
    this->available = possible;
}
