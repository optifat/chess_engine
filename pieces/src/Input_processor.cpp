#include <iostream>
#include "../include/Input_processor.h"
#include "../include/Pawn_move.h"
#include "../include/Rook_move.h"
#include "../include/Knight_move.h"
#include "../include/Bishop_move.h"
#include "../include/Queen_move.h"
#include "../include/Castling.h"
#include "../include/King_move.h"

void Input_processor::readMove(Board *board, std::string move) {

    if (move[0] == 'O') {
        Castling nextMove;
        if(move.compare("0-0-0")){
            nextMove.makeMove(board, 56*!board->whiteOrder()+4, 56*!board->whiteOrder()+6);
        }
        if(move.compare("0-0")){
            nextMove.makeMove(board, 56*!board->whiteOrder()+4, 56*!board->whiteOrder()+2);
        }

        board->editEnPassant(-1);
        return;
    }

    char pieceType;
    if(move.length() == 6){
        pieceType = move[0];
        move = move.substr(1, 5);
    }
    else if(move.length() == 5){
        pieceType = 'p';
    }
    else{
        std::cerr << "Wrong move input (length) \n";
        return;
    }

    bool take;
    if(move[2] == 'x'){
        take = true;
    }
    else if(move[2] == '-'){
        take = false;
    }
    else{
        std::cerr << "Wrong move input (not - or x)\n";
        return;
    }

    int initSquare = move[0] - 'a' + 8*(move[1] - '1');
    int endSquare = move[3] - 'a' + 8*(move[4] - '1');

    if(initSquare == endSquare){
        std::cerr << "Impossible move: squares must be different\n";
        return;
    }

    if(move[0]>'h' || move[0]<'a' || move[3]>'h' || move[3]<'a' || move[1]>'8' || move[1]<'1' || move[4]>'8' || move[4]<'1'){
        std::cerr << "Wrong input\n";
        return;
    }

    std::cout << "Init: " << initSquare << ", end: " << endSquare << ", piece type: " << pieceType << ", take: " << take << std::endl;

    if (pieceType == 'p') {
        Pawn_move nextMove;
        if(nextMove.openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->pawnCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No pawn on " << move[0] << move[1] << " square\n";
            return;
        }
        nextMove.makeMove(board, initSquare, endSquare, take);
    }
    else if (pieceType == 'R') {
        Rook_move nextMove;
        if(nextMove.openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->rookCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No rook on " << move[0] << move[1] << " square\n";
            return;
        }
        nextMove.makeMove(board, initSquare, endSquare, take);
        board->editEnPassant(-1);

    }
    else if (pieceType == 'N') {
        Knight_move nextMove;
        if(nextMove.openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->knightCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No knight on " << move[0] << move[1] << " square\n";
            return;
        }
        nextMove.makeMove(board, initSquare, endSquare, take);
        board->editEnPassant(-1);
    }
    else if (pieceType == 'B') {
        Bishop_move nextMove;
        if(nextMove.openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->bishopCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No bishop on " << move[0] << move[1] << " square\n";
            return;
        }
        if(abs(initSquare%8 - endSquare%8) != abs(initSquare/8-endSquare/8)){
            std::cerr << "Impossible move\n";
            return;
        }
        nextMove.makeMove(board, initSquare, endSquare, take);
        board->editEnPassant(-1);
    }
    else if (pieceType == 'Q') {
        Queen_move nextMove;
        if(nextMove.openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->queenCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No queen on " << move[0] << move[1] << " square\n";
            return;
        }
        nextMove.makeMove(board, initSquare, endSquare, take);
        board->editEnPassant(-1);
    }
    else if (pieceType == 'K') {
        King_move nextMove;
        if(!board->kingCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No king on " << move[0] << move[1] << " square\n";
            return;
        }
        nextMove.makeMove(board, initSquare, endSquare, take);
        board->editEnPassant(-1);
    }
    else{
        std::cerr << "Wrong input: there is no such piece\n";
        return;
    }
}
