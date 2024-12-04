//
// Created by Tobias on 11/21/24.
//

#ifndef KNIGHT_H
#define KNIGHT_H



#include "Piece.h"

class Knight:  public Piece{

public:
    explicit Knight(PieceColor color);


    [[nodiscard]] std::string getPieceName() const override;
};



#endif //KNIGHT_H
