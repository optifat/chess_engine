#ifndef CHESS_ENGINE_MOVE_H
#define CHESS_ENGINE_MOVE_H

#include <string>

#include "Board.h"


class Move{

public:
    Move();
    static bool openingPin(Board board, int initSquare, int endSquare);
};


#endif //CHESS_ENGINE_MOVE_H
