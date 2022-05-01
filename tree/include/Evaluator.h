#ifndef CHESS_ENGINE_EVALUATOR_H
#define CHESS_ENGINE_EVALUATOR_H

constexpr int MAX_POS_VAL = 100000;

#include "../../pieces/include/Board.h"
#include "./Node.h"

class Evaluator {
public:
    static int evaluatePosition(Node &node);
};


#endif //CHESS_ENGINE_EVALUATOR_H
