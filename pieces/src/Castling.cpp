#include <iostream>
#include "../include/Castling.h"

Castling::Castling(): Move(){};

// This is too shitty code, MUST be rewritten later in a smarter way

bool Castling::makeMove(Board& board, int initSquare, int endSquare) {
    if(endSquare%8 == 6){
        if(board.whiteOrder() && board.whiteShortCastle){
            if(!board.fieldIsAttacked(4) && !board.fieldIsAttacked(5) && !board.fieldIsAttacked(6) &&
               board.currentColorCheck(4) && board.kingCheck(4) &&
               board.currentColorCheck(7) && board.rookCheck(7) &&
               !board.currentColorCheck(5) && !board.currentColorCheck(6) &&
               !board.anotherColorCheck(5) && !board.anotherColorCheck(6))
            {
                board.updateCurrentColor(7, 5);
                board.updateCurrentColor(4, 6);
                board.rooks &= ~((uint64_t)1 << 7);
                board.rooks |= ((uint64_t)1 << 5);
                board.kings &= ~((uint64_t)1 << 4);
                board.kings |= ((uint64_t)1 << 6);
                board.passTheMove();
                board.whiteShortCastle = false;
                board.whiteLongCastle = false;
                return true;
            }
        }

        else if(!board.whiteOrder() && board.blackShortCastle){
            if(!board.fieldIsAttacked(60) && !board.fieldIsAttacked(61) && !board.fieldIsAttacked(62) &&
               board.currentColorCheck(60) && board.kingCheck(60) &&
               board.currentColorCheck(63) && board.rookCheck(63) &&
               !board.currentColorCheck(61) && !board.currentColorCheck(62) &&
               !board.anotherColorCheck(61) && !board.anotherColorCheck(62))
            {
                board.updateCurrentColor(63, 61);
                board.updateCurrentColor(60, 62);
                board.rooks &= ~((uint64_t)1 << 63);
                board.rooks |= ((uint64_t)1 << 61);
                board.kings &= ~((uint64_t)1 << 60);
                board.kings |= ((uint64_t)1 << 62);
                board.blackShortCastle = false;
                board.blackLongCastle = false;
                board.passTheMove();
                return true;
            }
        }
    }
    else if(endSquare%8 == 2){
        if(board.whiteOrder() && board.whiteLongCastle){
            if(!board.fieldIsAttacked(2) && !board.fieldIsAttacked(3) && !board.fieldIsAttacked(4) &&
               board.currentColorCheck(4) && board.kingCheck(4) &&
               board.currentColorCheck(0) && board.rookCheck(0) &&
               !board.currentColorCheck(1) && !board.currentColorCheck(2) && !board.currentColorCheck(3) &&
               !board.anotherColorCheck(1) && !board.anotherColorCheck(2) && !board.anotherColorCheck(3))
            {
                board.updateCurrentColor(0, 3);
                board.updateCurrentColor(4, 2);
                board.rooks &= ~((uint64_t)1 << 0);
                board.rooks |= ((uint64_t)1 << 3);
                board.kings &= ~((uint64_t)1 << 4);
                board.kings |= ((uint64_t)1 << 2);
                board.whiteShortCastle = false;
                board.whiteLongCastle = false;
                board.passTheMove();
                return true;
            }
        }

        else if(!board.whiteOrder() && board.blackLongCastle){
            if(!board.fieldIsAttacked(58) && !board.fieldIsAttacked(59) && !board.fieldIsAttacked(60) &&
               board.currentColorCheck(60) && board.kingCheck(60) &&
               board.currentColorCheck(56) && board.rookCheck(56) &&
               !board.currentColorCheck(57) && !board.currentColorCheck(58) && !board.currentColorCheck(59) &&
               !board.anotherColorCheck(57) && !board.anotherColorCheck(58) && !board.anotherColorCheck(59))
            {
                board.updateCurrentColor(56, 59);
                board.updateCurrentColor(60, 58);
                board.rooks &= ~((uint64_t)1 << 56);
                board.rooks |= ((uint64_t)1 << 59);
                board.kings &= ~((uint64_t)1 << 60);
                board.kings |= ((uint64_t)1 << 58);
                board.blackShortCastle = false;
                board.blackLongCastle = false;
                board.passTheMove();
                return true;
            }
        }
    }
    return false;
}
