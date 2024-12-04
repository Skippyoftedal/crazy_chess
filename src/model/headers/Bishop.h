//
// Created by Tobias on 11/21/24.
//

#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop:  public Piece{

public:
    explicit Bishop(PieceColor color);


    [[nodiscard]] std::string getPieceName() const override;
};



#endif //BISHOP_H
