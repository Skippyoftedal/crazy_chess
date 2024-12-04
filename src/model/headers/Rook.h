//
// Created by Tobias on 11/21/24.
//

#ifndef ROOK_H
#define ROOK_H



#include "Piece.h"

class Rook:  public Piece{

public:
    explicit Rook(PieceColor color);


    [[nodiscard]] std::string getPieceName() const override;
};



#endif //ROOK_H
