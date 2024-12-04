//
// Created by Tobias on 11/20/24.
//
#ifndef QUEEN_H
#define QUEEN_H

#include <SFML/Graphics/RenderTarget.hpp>

#include "Piece.h"

class Queen:  public Piece{

public:
  explicit Queen(PieceColor color);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  std::string getPieceName() const override;
};


#endif //QUEEN_H
