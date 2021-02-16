#ifndef CHESS_ENGINE_KNIGHT_H
#define CHESS_ENGINE_KNIGHT_H


class Knight_move: public Move{

public:
    inline static int possibleKnightMoves[8] = {6, 10, 15, 17, -6, -10, -15, -17};
    Knight_move();
    static bool makeMove(Board *board, int initSquare, int endSquare);
};

#endif //CHESS_ENGINE_KNIGHT_H
