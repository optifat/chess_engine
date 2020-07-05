#ifndef CHESS_ENGINE_MOVE_READER_H
#define CHESS_ENGINE_MOVE_READER_H

#include <iostream>

#include "../include/Board.h"
#include "../include/Pawn_move.h"

Pawn_move::Pawn_move(): Move(){};

void Pawn_move::promotion(Board *board, int endSquare){
    std::cout << "Choose the piece for pawn promotion (Q, R, N, B): ";
    char promotion;
    while(true){
        std::cin >> promotion;
        switch(promotion) {
            case 'Q':
                board->pawns &= ~((uint64_t)1 << endSquare);
                board->queens |= ((uint64_t)1 << endSquare);
                return;
            case 'R':
                board->pawns &= ~((uint64_t)1 << endSquare);
                board->rooks |= ((uint64_t)1 << endSquare);
                return;
            case 'B':
                board->pawns &= ~((uint64_t)1 << endSquare);
                board->bishops |= ((uint64_t)1 << endSquare);
                return;
            case 'N':
                board->pawns &= ~((uint64_t)1 << endSquare);
                board->knights |= ((uint64_t)1 << endSquare);
                return;
            default:
                std::cerr << "Impossible promotion";
        }
    }
}

void Pawn_move::makeMove(Board *board, int initSquare, int endSquare, bool take){

    /* k variable is defined by the side to move: 1 if white and -1 if black.
     * All the white pawns are going up the board while black vice versa.
     * That means for us, that the difference between end and initial pawn squares is positive in case of white
     * and negative in case of black.
     * Also, in case of A or H verticals, the possible takes are only to vertical B and G respectively.
     * As example for A vertical:
     *      white pawn move: A(i) x B(i+1), the difference between end and initial pawn squares is 9
     *      black pawn move: A(i) x B(i-1), the difference between end and initial pawn squares is -7
     * So the possible difference can be defined as (8 + k)*k
     * Similarly for H vertical with change of previous equation to (8 - k)*k
     */

    int k = -1 + 2*board->whiteOrder();

    /* e variable shows if en passant take is possible.
     * If it is we should remove the opponent's pawn on adjacent square on the vertical you move to.
     * It is achieved by subtracting e*k
     * If e == 0 nothing changes otherwise we move to current-k vertical when removing the opponent's pawn
     */

    int e = 0;
    if(endSquare == board->possibleEnPassant())
        e = 8;

    if(!take){
        if((initSquare/8 == 1 && endSquare - initSquare == 16*k) || (initSquare/8 == 6 && endSquare - initSquare == 16*k)
           and !board->currentColorCheck(endSquare) and !board->currentColorCheck(endSquare-8*k)
           and !board->anotherColorCheck(endSquare) and !board->anotherColorCheck(endSquare-8*k)){
            board->updateCurrentColor(initSquare, endSquare);
            board->pawns &= ~((uint64_t)1 << initSquare);
            board->pawns |= ((uint64_t)1 << endSquare);
            board->editEnPassant(endSquare-8*k);
            board->passTheMove();
            return;
        } else if(endSquare - initSquare == 8*k
                  and !board->currentColorCheck(endSquare) and !board->anotherColorCheck(endSquare)){
            board->updateCurrentColor(initSquare, endSquare);
            board->pawns &= ~((uint64_t)1 << initSquare);
            board->pawns |= ((uint64_t)1 << endSquare);
            board->editEnPassant(-1);

            if((k == 1 and endSquare/8 == 7) or (k == -1 and endSquare/8 == 0)){
                this->promotion(board, endSquare);
            }

            board->passTheMove();
            return;
        } else{
            std::cerr << "Impossible move \n";
            return;
        }
    } else if(!board->anotherColorCheck(endSquare) and endSquare != board->possibleEnPassant()){
        std::cerr << "Nothing to take on there\n";
        return;
    } else{
        if (abs(initSquare/8-endSquare/8) == abs(initSquare%8-endSquare%8)) {
            board->updateCurrentColor(initSquare, endSquare);
            board->updateAnotherColor(endSquare, -1);
            board->pawns &= ~((uint64_t)1 << initSquare);
            board->pawns |= ((uint64_t)1 << endSquare);
            if(endSquare == board->possibleEnPassant()){
                board->pawns &= ~((uint64_t)1 << (endSquare-8*k));
            }
            board->bishops &= ~((uint64_t)1 << endSquare);
            board->rooks &= ~((uint64_t)1 << endSquare);
            board->knights &= ~((uint64_t)1 << endSquare);
            board->queens &= ~((uint64_t)1 << endSquare);
            board->editEnPassant(-1);

            if((k == 1 and endSquare/8 == 7) or (k == -1 and endSquare/8 == 0)){
                this->promotion(board, endSquare);
            }

            board->passTheMove();
            return;
        } else{
            std::cerr << "Impossible take \n";
            return;
        }
    }
}


#endif //CHESS_ENGINE_MOVE_READER_H
