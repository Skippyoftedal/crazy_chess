//
// Created by Tobias on 11/21/24.
//

#ifndef KING_H
#define KING_H

#include "Piece.h"

class King:  public Piece{

public:
    explicit King(PieceColor color);


    [[nodiscard]] std::string getPieceName() const override;
};



#endif //KING_H
