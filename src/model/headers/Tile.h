//
// Created by Tobias on 11/21/24.
//

#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Piece.h"



class Tile: public sf::Drawable{
    Piece* piece = nullptr;
    sf::RectangleShape tileShape;
    sf::Color default_color;

    //Pos is just for debugging
    bool has_moved_ = false;
    bool selected = false;
    bool available = false;
    std::string pos;

public:
    explicit Tile(sf::RectangleShape tileShape, sf::Color default_color, std::string text);


    Tile() = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void set_piece(Piece * piece);

    Piece* get_piece() const;

    bool has_piece() const;

    void set_selected(bool selected);

    bool is_selected() const;

    bool is_available() const;

    void set_available(bool possible);


};




#endif //TILE_H
