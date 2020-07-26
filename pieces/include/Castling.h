#ifndef CHESS_ENGINE_CASTLING_H
#define CHESS_ENGINE_CASTLING_H

#include "Move.h"

class Castling: public Move{
public:
    Castling();
    // Castling is actually a special king's move, so initial and end squares are for king's positions
    static bool makeMove(Board *board, int initSquare, int endSquare, bool take = false);
};

#endif //CHESS_ENGINE_CASTLING_H
