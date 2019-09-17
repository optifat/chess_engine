#include <string>
#include <iostream>

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
                    whitePieces[index] = true;
                    pawns[index] = true;
                    break;
                case 'p':
                    blackPieces[index] = true;
                    pawns[index] = true;
                    break;
                case 'R':
                    whitePieces[index] = true;
                    rooks[index] = true;
                    break;
                case 'r':
                    blackPieces[index] = true;
                    rooks[index] = true;
                    break;
                case 'B':
                    whitePieces[index] = true;
                    bishops[index] = true;
                    break;
                case 'b':
                    blackPieces[index] = true;
                    bishops[index] = true;
                    break;
                case 'N':
                    whitePieces[index] = true;
                    knights[index] = true;
                    break;
                case 'n':
                    blackPieces[index] = true;
                    knights[index] = true;
                    break;
                case 'Q':
                    whitePieces[index] = true;
                    queens[index] = true;
                    break;
                case 'q':
                    blackPieces[index] = true;
                    queens[index] = true;
                    break;
                case 'K':
                    whitePieces[index] = true;
                    kings[index] = true;
                    break;
                case 'k':
                    blackPieces[index] = true;
                    kings[index] = true;
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
        if(whitePieces[index]){
            piece += "White ";
            if(rooks[index])
                piece += "rook";
            if(knights[index])
                piece += "knight";
            if(bishops[index])
                piece += "bishop";
            if(pawns[index])
                piece += "pawn";
            if(queens[index])
                piece += "queen";
            if(kings[index])
                piece += "king";
        } else if(blackPieces[index]){
            piece += "Black ";
            if(rooks[index])
                piece += "rook";
            if(knights[index])
                piece += "knight";
            if(bishops[index])
                piece += "bishop";
            if(pawns[index])
                piece += "pawn";
            if(queens[index])
                piece += "queen";
            if(kings[index])
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

    //checking vertical
    for(int i = -1; i <= 1; i+=2){
        for(int j = 1; j <= 7; j++){
            int checkedField = 8*j*i + position;
            if(checkedField > 63 || checkedField < 0){
                continue;
            }
            else if(this->showAnotherColor()[checkedField] &&
                    ((this->showQueens()[checkedField] || this->showRooks()[checkedField]) ||
                     (j == 1 && this->showKings()[checkedField]))){
                return true;
            }
            else if ((this->showCurrentColor()[checkedField] || this->showAnotherColor()[checkedField]) && ignore != checkedField){
                break;
            }
        }
    }

    //checking horizontals
    for(int i = -1; i <= 1; i+=2){
        for(int j = 1; j <= 7; j++){
            int checkedField = j*i + position;
            if(checkedField/8 != position/8){
                continue;
            }
            else if(this->showAnotherColor()[checkedField] &&
                    ((this->showQueens()[checkedField] || this->showRooks()[checkedField]) ||
                     (j == 1 && this->showKings()[checkedField]))){
                return true;
            }
            else if ((this->showCurrentColor()[checkedField] || this->showAnotherColor()[checkedField]) && ignore != checkedField){
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
                } else if(this->showAnotherColor()[checkedField] &&
                        (this->showQueens()[checkedField] || this->showBishops()[checkedField] ||
                         (k == 1 && ((this->showPawns()[checkedField] && j == -1+2*this->whiteOrder())
                                                                  || this->showKings()[checkedField]))
                        )){
                    return true;
                } else if ((this->showCurrentColor()[checkedField] || this->showAnotherColor()[checkedField]) && ignore != checkedField){
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
        if(this->showAnotherColor()[checkedField] && this->showKnights()[checkedField]){
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

bool* Board::showAnotherColor(){
    if(whiteToMove)
        return blackPieces;
    else
        return whitePieces;
}

bool* Board::showCurrentColor(){
    if(!whiteToMove)
        return blackPieces;
    else
        return whitePieces;
}

const bool* Board::showRooks(){
    return rooks;
}

const bool* Board::showKnights(){
    return knights;
}

const bool* Board::showBishops(){
    return bishops;
}

const bool* Board::showQueens(){
    return queens;
}

const bool* Board::showKings(){
    return kings;
}

const bool* Board::showPawns(){
    return pawns;
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
        if(this->kings[i] && this->showCurrentColor()[i]){
            kingPos = i;
            break;
        }
    }
    return this->fieldIsAttacked(kingPos, position);
}

void Board::showBoard() {
    for (int i = 56; i >= 0; i++) {
        if(pawns[i]) {
            if (blackPieces[i])
                std::cout << "p";
            else std::cout << "P";
        }else if(rooks[i]) {
            if (blackPieces[i])
                std::cout << "r";
            else std::cout << "R";
        }else if (bishops[i]) {
            if (blackPieces[i])
                std::cout << "b";
            else std::cout << "B";
        }else if (knights[i]) {
            if (blackPieces[i])
                std::cout << "n";
            else std::cout << "N";
        }else if (queens[i]) {
            if (blackPieces[i])
                std::cout << "q";
            else std::cout << "Q";
        }else if (kings[i]) {
            if (blackPieces[i])
                std::cout << "k";
            else std::cout << "K";
        }else std::cout << "*";

        if ((i+1)%8 == 0) {
            i-=16;
            std::cout << std::endl;
        }
    }
}
