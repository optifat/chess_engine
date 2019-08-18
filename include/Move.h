#ifndef CHESS_ENGINE_MOVE_H
#define CHESS_ENGINE_MOVE_H

#include <string>

#include "Board.h"


class Move{

public:
    Move();

    virtual void makeMove(Board *board, std::string move);

};


#endif //CHESS_ENGINE_MOVE_H
