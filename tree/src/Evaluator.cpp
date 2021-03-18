#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcountl __popcnt64
#endif

#include "../include/Evaluator.h"
#include <iostream>

int Evaluator::evaluatePosition(Board &position) {
    int positionValue = 0;
    if (position.checkmate()) {
        return position.whiteOrder() ? -MAX_POS_VAL : MAX_POS_VAL; // float isn't precise enough, so FLT_MAX - 1 == FLT_MAX 
    }
    /* doesn't work right now
    if (position.stalemate()) {
        return 0;
    }*/
    // counting material
    positionValue += 9 * __builtin_popcountl(position.queens & position.whitePieces);
    positionValue -= 9 * __builtin_popcountl(position.queens & position.blackPieces);
    positionValue += 5 * __builtin_popcountl(position.rooks & position.whitePieces);
    positionValue -= 5 * __builtin_popcountl(position.rooks & position.blackPieces);
    positionValue += 3 * __builtin_popcountl(position.bishops & position.whitePieces);
    positionValue -= 3 * __builtin_popcountl(position.bishops & position.blackPieces);
    positionValue += 3 * __builtin_popcountl(position.knights & position.whitePieces);
    positionValue -= 3 * __builtin_popcountl(position.knights & position.blackPieces);
    positionValue += __builtin_popcountl(position.pawns & position.whitePieces);
    positionValue -= __builtin_popcountl(position.pawns & position.blackPieces);
    return positionValue;
}