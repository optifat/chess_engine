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

    if (move[0] == '0') {
        if(!move.compare("0-0")){
            Castling::makeMove(board, 56*!board->whiteOrder()+4, 56*!board->whiteOrder()+6);
        }
        else if(!move.compare("0-0-0")){
            Castling::makeMove(board, 56*!board->whiteOrder()+4, 56*!board->whiteOrder()+2);
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

    if(move[0]>'h' || move[0]<'a' || move[3]>'h' || move[3]<'a' || move[1]>'8' || move[1]<'1' || move[4]>'8' || move[4]<'1'){
        std::cerr << "Wrong input\n";
        return;
    }

    int initSquare = move[0] - 'a' + 8*(move[1] - '1');
    int endSquare = move[3] - 'a' + 8*(move[4] - '1');

    if(initSquare == endSquare){
        std::cerr << "Impossible move: squares must be different\n";
        return;
    }

    int kingPos = -1;
    for(int i = 0; i <= 63; i++){
        if(board->kingCheck(i) && board->currentColorCheck(i)){
            kingPos = i;
            break;
        }
    }

    if(board->fieldAttackers(kingPos).size() >= 2 && pieceType != 'K'){
        std::cerr << "King is checked 1" << std::endl;
        return;
    }
    else if(board->fieldAttackers(kingPos).size() == 1 && pieceType != 'K'){
        if(endSquare != board->fieldAttackers(kingPos)[0]){
            board->updateCurrentColor(initSquare, endSquare);
            if(board->fieldIsAttacked(kingPos)){
                board->updateCurrentColor(initSquare, endSquare);
                std::cerr << "King is checked" << std::endl;
                return;
            }
            board->updateCurrentColor(endSquare, initSquare);
        }
    }

    std::cout << "Init: " << initSquare << ", end: " << endSquare << ", piece type: " << pieceType << ", take: " << take << std::endl;

    if (pieceType == 'p') {
        if(Move::openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->pawnCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No pawn on " << move[0] << move[1] << " square\n";
            return;
        }
        Pawn_move::makeMove(board, initSquare, endSquare, take);
    }
    else if (pieceType == 'R') {
        if(Move::openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->rookCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No rook on " << move[0] << move[1] << " square\n";
            return;
        }
        Rook_move::makeMove(board, initSquare, endSquare, take);
        board->editEnPassant(-1);

    }
    else if (pieceType == 'N') {
        if(Move::openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->knightCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No knight on " << move[0] << move[1] << " square\n";
            return;
        }
        Knight_move::makeMove(board, initSquare, endSquare, take);
        board->editEnPassant(-1);
    }
    else if (pieceType == 'B') {
        if(Move::openingPin(board, initSquare, endSquare)){
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
        Bishop_move::makeMove(board, initSquare, endSquare, take);
        board->editEnPassant(-1);
    }
    else if (pieceType == 'Q') {
        if(Move::openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->queenCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No queen on " << move[0] << move[1] << " square\n";
            return;
        }
        Queen_move::makeMove(board, initSquare, endSquare, take);
        board->editEnPassant(-1);
    }
    else if (pieceType == 'K') {
        if(!board->kingCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No king on " << move[0] << move[1] << " square\n";
            return;
        }
        King_move::makeMove(board, initSquare, endSquare, take);
        board->editEnPassant(-1);
    }
    else{
        std::cerr << "Wrong input: there is no such piece\n";
        return;
    }
}
