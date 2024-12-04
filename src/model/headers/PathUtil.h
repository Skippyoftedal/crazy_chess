//
// Created by Tobias on 11/21/24.
//

#ifndef PATHUTIL_H
#define PATHUTIL_H
#include <string>
#include <__format/format_functions.h>


class PathUtil{
public:
  static std::string getPath(std::string pieceName, PieceColor color) {
    std::string colorString = color == Black ? "black" : "white";
    return std::format("../src/resources/images/{}_{}.png",  pieceName, colorString);
  }
};

#endif //PATHUTIL_H
