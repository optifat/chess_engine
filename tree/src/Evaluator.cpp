#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcountl __popcnt64
#endif

#include "../include/Evaluator.h"
#include <iostream>

float Evaluator::evaluatePosition(Board &position) {
    float positionValue = 0;

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
    std::cout << "value " << (position.queens & position.blackPieces) << std::endl;
    return positionValue;
}