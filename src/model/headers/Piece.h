

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include "PieceColor.h"

class Piece : public sf::Drawable{

protected:
    PieceColor piece_color;
    sf::Vector2f position;
    bool has_moved_ = false;
    int width;
public:
    explicit Piece(const PieceColor piece_color);

    void set_position(const sf::Vector2f &position) {
        this->position = position;
    }

    [[nodiscard]] PieceColor getColor() const;

    ~Piece() override = default;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    [[nodiscard]] virtual std::string getPieceName() const = 0;

    [[nodiscard]] bool has_moved() const {
        return has_moved_;
    }

    void set_has_moved(bool has_moved) {
        has_moved_ = has_moved;
    }

};



#endif //PLAYER_H
