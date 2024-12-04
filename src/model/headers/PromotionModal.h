//
// Created by Tobias on 11/27/24.
//

#ifndef PROMOTIONMODAL_H
#define PROMOTIONMODAL_H
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Bishop.h"
#include "Knight.h"
#include "PieceColor.h"
#include "Queen.h"
#include "Rook.h"


class PromotionModal: public sf::Drawable{
    sf::RectangleShape background_shape;
    PieceColor color;
    std::vector<std::unique_ptr<Piece>> pieces;

public:
    PromotionModal(): color(Black) {
        background_shape = sf::RectangleShape();

        auto size = sf::Vector2f(300, 300);

        background_shape.setPosition((800 - size.x) / 2, (800 - size.y) / 2);
        background_shape.setSize(size);
        background_shape.setFillColor(sf::Color::Yellow);

        auto q = std::make_unique<Queen>(color);
        q->set_position(background_shape.getPosition() + sf::Vector2f(50, 50));
        pieces.push_back(std::move(q));

        auto k = std::make_unique<Knight>(color);
        k->set_position(background_shape.getPosition() + sf::Vector2f(150, 50));
        pieces.push_back(std::move(k));

        auto b = std::make_unique<Bishop>(color);
        b->set_position(background_shape.getPosition() + sf::Vector2f(50, 150));
        pieces.push_back(std::move(b));

        auto r = std::make_unique<Rook>(color);
        r->set_position(background_shape.getPosition() + sf::Vector2f(150, 150));
        pieces.push_back(std::move(r));
    };



private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override{
        target.draw(background_shape);

        for (const auto& piece: pieces) {
            piece->draw(target, states);

        }

    }
};

#endif //PROMOTIONMODAL_H
