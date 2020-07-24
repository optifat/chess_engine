#ifndef CHESS_ENGINE_KNIGHT_H
#define CHESS_ENGINE_KNIGHT_H


class Knight_move: public Move{

public:
    Knight_move();
    void makeMove(Board *board, int initSquare, int endSquare, bool take) override;
};

#endif //CHESS_ENGINE_KNIGHT_H
