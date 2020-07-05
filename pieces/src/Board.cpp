#include <string>
#include <iostream>
#include <cmath>

#include "../include/Board.h"


Board::Board(std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq"){
    int index = 55;
    int i = 0;
    bool flag = false;
    for(i; i < FEN.length(); i++){
        index++;
        if(FEN[i] < '9' and FEN[i] > '0'){
            index += FEN[i] - '1';
            continue;
        } else if(FEN[i] == '/'){
            index -= 17;
            continue;
        } else{
            switch(FEN[i]){
                case 'P':
                    whitePieces += powl(2, index);
                    pawns += powl(2, index);
                    break;
                case 'p':
                    blackPieces += powl(2, index);
                    pawns += powl(2, index);
                    break;
                case 'R':
                    whitePieces += powl(2, index);
                    rooks += powl(2, index);
                    break;
                case 'r':
                    blackPieces += powl(2, index);
                    rooks += powl(2, index);
                    break;
                case 'B':
                    whitePieces += powl(2, index);
                    bishops += powl(2, index);
                    break;
                case 'b':
                    blackPieces += powl(2, index);
                    bishops += powl(2, index);
                    break;
                case 'N':
                    whitePieces += powl(2, index);
                    knights += powl(2, index);
                    break;
                case 'n':
                    blackPieces += powl(2, index);
                    knights += powl(2, index);
                    break;
                case 'Q':
                    whitePieces += powl(2, index);
                    queens += powl(2, index);
                    break;
                case 'q':
                    blackPieces += powl(2, index);
                    queens += powl(2, index);
                    break;
                case 'K':
                    whitePieces += powl(2, index);
                    kings += powl(2, index);
                    break;
                case 'k':
                    blackPieces += powl(2, index);
                    kings += powl(2, index);
                    break;
                default:
                    flag = true;
                    break;                 //the iteration will always be stopped on space symbol
            }
        }
        if (flag)
            break;
    }
    for(i; i < FEN.length(); i++){
        switch (FEN[i]){
            case 'w':
                whiteToMove = true;
                break;
            case 'b':
                whiteToMove = false;
                break;
            case 'K':
                whiteShortCastle = true;
                break;
            case 'Q':
                whiteLongCastle = true;
                break;
            case 'k':
                blackShortCastle = true;
                break;
            case 'q':
                blackLongCastle = true;
                break;
            default:
                if(FEN[i]<='h' and FEN[i] >= 'a'){
                    if(FEN[i+1]=='3'){
                        enPassant = FEN[i] - 'a';
                    } else if(FEN[i+1] == '6'){
                        enPassant = 8 + FEN[i] - 'a';
                    }
                }
        }
    }
}

Board::~Board() = default;

std::string Board::pieceOnSquare(std::string square){
    if(square.length() > 2)
        return "Wrong input, input should contain two symbols";
    else if(square[0] > 'h' or square[0] < 'a')
        return "Wrong input, verticals are a-h";
    else if(square[1] > '8' or square[1]<'1')
        return "Wrong input, horizontals are 1-8";
    else{
        int index = square[0] - 'a' + 8*(square[1] - '1');
        std::string piece;
        if(whitePieceCheck(index)){
            piece += "White ";
            if(rookCheck(index))
                piece += "rook";
            if(knightCheck(index))
                piece += "knight";
            if(bishopCheck(index))
                piece += "bishop";
            if(pawnCheck(index))
                piece += "pawn";
            if(queenCheck(index))
                piece += "queen";
            if(kingCheck(index))
                piece += "king";
        } else if(blackPieceCheck(index)){
            piece += "Black ";
            if(rookCheck(index))
                piece += "rook";
            if(knightCheck(index))
                piece += "knight";
            if(bishopCheck(index))
                piece += "bishop";
            if(pawnCheck(index))
                piece += "pawn";
            if(queenCheck(index))
                piece += "queen";
            if(kingCheck(index))
                piece += "king";
        } else{
            piece += "Empty";
        }
        return piece;
    }
}

//fieldIsAttacked function checks fields for king in order to prevent impossible moves
bool Board::fieldIsAttacked(int position, int ignore){
    //if (!kings[position] && this->showCurrentColor()[position]){
    //    std::cerr << "This field is occupied by allied piece which is not a king. Returning false.";
    //    return false;
    //}

    //checking files
    for(int i = -1; i <= 1; i+=2){
        for(int j = 1; j <= 7; j++){
            int checkedField = 8*j*i + position;
            if(checkedField > 63 || checkedField < 0){
                continue;
            }
            else if(this->anotherColorCheck(checkedField) &&
                    ((this->queenCheck(checkedField) || this->rookCheck(checkedField)) ||
                     (j == 1 && this->kingCheck(checkedField)))){
                return true;
            }
            else if ((this->currentColorCheck(checkedField) || this->anotherColorCheck(checkedField)) && ignore != checkedField){
                break;
            }
        }
    }

    //checking line
    for(int i = -1; i <= 1; i+=2){
        for(int j = 1; j <= 7; j++){
            int checkedField = j*i + position;
            if(checkedField/8 != position/8){
                continue;
            }
            else if(this->anotherColorCheck(checkedField) &&
                    ((this->queenCheck(checkedField) || this->rookCheck(checkedField)) ||
                     (j == 1 && this->kingCheck(checkedField)))){
                return true;
            }
            else if ((this->currentColorCheck(checkedField) || this->anotherColorCheck(checkedField)) && ignore != checkedField){
                break;
            }
        }
    }

    //checking diagonals
    for(int i = -1; i <= 1; i+=2){
        for(int j = -1; j <= 1; j+=2){
            for(int k = 1; k <= 7; k++){
                int checkedField = (8+i)*j*k + position;
                if(checkedField > 63 || checkedField < 0 || abs(checkedField%8-position%8) != abs(checkedField/8-position/8)){
                    continue;
                } else if(this->anotherColorCheck(checkedField) &&
                        (this->queenCheck(checkedField) || this->bishopCheck(checkedField) ||
                         (k == 1 && ((this->pawnCheck(checkedField) && j == -1+2*this->whiteOrder())
                                                                  || this->kingCheck(checkedField)))
                        )){
                    return true;
                } else if ((this->currentColorCheck(checkedField) || this->anotherColorCheck(checkedField)) && ignore != checkedField){
                    break;
                }
            }
        }
    }

    int possibleKnightMoves[8] = {6, 10, 15, 17, -6, -10, -15, -18};

    for(auto move: possibleKnightMoves){
        int checkedField = position + move;
        if(checkedField < 0 || checkedField > 63 || abs(checkedField/8-position/8)+abs(checkedField%8-position%8) != 3){
            continue;
        }
        if(this->anotherColorCheck(checkedField) && this->knightCheck(checkedField)){
            return true;
        }
    }
    return false;
}

std::string Board::sideToMove(){
    if(whiteToMove)
        return "White to whiteToMove";
    else
        return "Black to whiteToMove";
}

std::string Board::whiteCastle(){
    if(whiteLongCastle && whiteShortCastle)
        return "White have long and short castle";
    else if (whiteLongCastle)
        return "White have only long castle";
    else if (whiteShortCastle)
        return "White have only short castle";
    else
        return "White have no castle";
}

std::string Board::blackCastle(){
    if(blackLongCastle && blackShortCastle)
        return "Black have long and short castle";
    else if (blackLongCastle)
        return "Black have only long castle";
    else if (blackShortCastle)
        return "Black have only short castle";
    else
        return "Black have no castle";
}

bool Board::whitePieceCheck(int square) {
    return (whitePieces >> square)%2;
}

bool Board::blackPieceCheck(int square) {
    return (blackPieces >> square)%2;
}

bool Board::anotherColorCheck(int square){
    if(whiteToMove)
        return blackPieceCheck(square);
    else
        return whitePieceCheck(square);
}

bool Board::currentColorCheck(int square){
    if(!whiteToMove)
        return blackPieceCheck(square);
    else
        return whitePieceCheck(square);
}

bool Board::rookCheck(int square){
    return (rooks >> square)%2;
}

bool Board::knightCheck(int square){
    return (knights >> square)%2;
}

bool Board::bishopCheck(int square){
    return (bishops >> square)%2;
}

bool Board::queenCheck(int square){
    return (queens >> square)%2;
}

bool Board::kingCheck(int square){
    return (kings >> square)%2;
}

bool Board::pawnCheck(int square){
    return (pawns >> square)%2;
}

bool Board::whiteOrder(){
    return whiteToMove;
}

void Board::passTheMove(){
    whiteToMove = !whiteToMove;
}

void Board::editEnPassant(int index){
    enPassant = index;
}

int Board::possibleEnPassant(){
    return enPassant;
}

bool Board::isPinned(int position){
    int kingPos = -1;
    for(int i = 0; i <= 63; i++){
        if(this->kingCheck(i) && this->currentColorCheck(i)){
            kingPos = i;
            break;
        }
    }
    return this->fieldIsAttacked(kingPos, position);
}

void Board::showBoard() {
    for (int i = 56; i >= 0; i++) {
        if( (pawns >> i)%2 ) {
            if ((blackPieces >> i)%2 )
                std::cout << "p";
            else std::cout << "P";
        } else if( (rooks >> i)%2 ) {
            if ( (blackPieces >> i)%2 )
                std::cout << "r";
            else std::cout << "R";
        } else if ( (bishops >> i)%2 ) {
            if ( (blackPieces >> i)%2 )
                std::cout << "b";
            else std::cout << "B";
        } else if ( (knights >> i)%2 ) {
            if ( (blackPieces >> i)%2 )
                std::cout << "n";
            else std::cout << "N";
        } else if ((queens >> i)%2 ) {
            if ( (blackPieces >> i)%2 )
                std::cout << "q";
            else std::cout << "Q";
        } else if ( (kings >> i)%2 ) {
            if ( (blackPieces >> i)%2 )
                std::cout << "k";
            else std::cout << "K";
        } else std::cout << "*";

        if ((i+1)%8 == 0) {
            i-=16;
            std::cout << std::endl;
        }
    }
}

void Board::updateCurrentColor(int initSquare, int endSquare){
    if(whiteToMove){
        whitePieces &= ~((uint64_t)1 << initSquare);
        if(endSquare>= 0) {
            whitePieces |= ((uint64_t) 1 << endSquare);
        }
    }
    else{
        blackPieces &= ~((uint64_t)1 << initSquare);
        if(endSquare>= 0) {
            blackPieces |= ((uint64_t) 1 << endSquare);
        }
    }
}

void Board::updateAnotherColor(int initSquare, int endSquare){
    if(!whiteToMove){
        whitePieces &= ~((uint64_t)1 << initSquare);
        if(endSquare >= 0) {
            whitePieces |= ((uint64_t) 1 << endSquare);
        }
    }
    else{
        blackPieces &= ~((uint64_t)1 << initSquare);
        if(endSquare >= 0) {
            blackPieces |= ((uint64_t) 1 << endSquare);
        }
    }
}
