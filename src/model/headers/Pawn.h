//
// Created by Tobias on 11/21/24.
//

#ifndef PAWN_H
#define PAWN_H



#include "Piece.h"

class Pawn:  public Piece{

public:
    explicit Pawn(PieceColor color);


    [[nodiscard]] std::string getPieceName() const override;
};



#endif //PAWN_H
