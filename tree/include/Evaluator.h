#ifndef CHESS_ENGINE_EVALUATOR_H
#define CHESS_ENGINE_EVALUATOR_H

constexpr int MAX_POS_VAL = 100000;

#include "../../pieces/include/Board.h"

class Evaluator {
public:
    static int evaluatePosition(Board &position);
};


#endif //CHESS_ENGINE_EVALUATOR_H
