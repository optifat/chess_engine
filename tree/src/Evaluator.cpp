#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcountl __popcnt64
#endif

#include "../include/Evaluator.h"
#include <iostream>

int Evaluator::evaluatePosition(Node &node) {
    int positionValue = 0;
    Board position = *node.position.get();

    if (!node.hasChildren) {
        if (position.fieldIsAttacked(position.currentColorKingPosition())){
            return position.whiteOrder() ? -MAX_POS_VAL : MAX_POS_VAL;
        }
        return 0;
    }

    // counting material
    positionValue += 900 * __builtin_popcountl(position.queens & position.whitePieces);
    positionValue -= 900 * __builtin_popcountl(position.queens & position.blackPieces);
    positionValue += 500 * __builtin_popcountl(position.rooks & position.whitePieces);
    positionValue -= 500 * __builtin_popcountl(position.rooks & position.blackPieces);
    positionValue += 300 * __builtin_popcountl(position.bishops & position.whitePieces);
    positionValue -= 300 * __builtin_popcountl(position.bishops & position.blackPieces);
    positionValue += 300 * __builtin_popcountl(position.knights & position.whitePieces);
    positionValue -= 300 * __builtin_popcountl(position.knights & position.blackPieces);
    positionValue += 100 * __builtin_popcountl(position.pawns & position.whitePieces);
    positionValue -= 100 * __builtin_popcountl(position.pawns & position.blackPieces);
    return positionValue;
}