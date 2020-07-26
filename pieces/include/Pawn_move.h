#ifndef CHESS_ENGINE_PAWN_MOVE_H
#define CHESS_ENGINE_PAWN_MOVE_H

#include "Move.h"

class Pawn_move: public Move{

public:
    Pawn_move();
    static bool makeMove(Board *board, int initSquare, int endSquare, bool take);

private:
    static void promotion(Board *board, int endSquare);
};

#endif //CHESS_ENGINE_PAWN_MOVE_H
