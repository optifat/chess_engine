#ifndef CHESS_ENGINE_KING_MOVE_H
#define CHESS_ENGINE_KING_MOVE_H

#include "Move.h"

class King_move: public Move{
public:
    King_move();
    static bool makeMove(Board& board, int initSquare, int endSquare);

};

#endif //CHESS_ENGINE_KING_MOVE_H
