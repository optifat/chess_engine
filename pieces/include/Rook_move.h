#ifndef CHESS_ENGINE_ROOK_MOVE_H
#define CHESS_ENGINE_ROOK_MOVE_H

// Rook move has a "Ra1-h1" representation.
// Rook capturing is similar to pawn capturing e.g. "Rh1xh8".

#include "Move.h"

class Rook_move: public Move{

public:
    Rook_move();
    void makeMove(Board *board, std::string move) override;
};

#endif //CHESS_ENGINE_ROOK_MOVE_H
