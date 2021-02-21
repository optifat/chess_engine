#ifndef CHESS_ENGINE_QUEEN_MOVE_H
#define CHESS_ENGINE_QUEEN_MOVE_H

#include "Move.h"

class Queen_move: public Move{

public:
    Queen_move();
    static bool makeMove(Board& board, int initSquare, int endSquare);
};

#endif //CHESS_ENGINE_QUEEN_MOVE_H
