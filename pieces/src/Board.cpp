#ifdef _MSC_VER
#  include <intrin.h>
#  define clz(x) (63-__lzcnt64(x))
#endif

#ifdef __GNUC__
#  define clz(x) x?(x?__builtin_clz(x):64)
#endif

#include <string>
#include <iostream>
#include <cmath>

#include "../include/Board.h"


Board::Board(std::string FEN){
    int index = 55;
    int i = 0;
    bool flag = false;
    for(; i < (int)FEN.length(); i++){
        index++;
        if(FEN[i] < '9' && FEN[i] > '0'){
            index += FEN[i] - '1';
            continue;
        } else if(FEN[i] == '/'){
            index -= 17;
            continue;
        } else{
            switch(FEN[i]){
                case 'P':
                    whitePieces += (uint64_t)1 << index;//powl(2, index);
                    pawns += (uint64_t)1 << index;//powl(2, index);
                    break;
                case 'p':
                    blackPieces += (uint64_t)1 << index;//powl(2, index);
                    pawns += (uint64_t)1 << index;//powl(2, index);
                    break;
                case 'R':
                    whitePieces += (uint64_t)1 << index;//powl(2, index);
                    rooks += (uint64_t)1 << index;//powl(2, index);
                    break;
                case 'r':
                    blackPieces += (uint64_t)1 << index;//powl(2, index);
                    rooks += (uint64_t)1 << index;//powl(2, index);
                    break;
                case 'B':
                    whitePieces += (uint64_t)1 << index;//powl(2, index);
                    bishops += (uint64_t)1 << index;//powl(2, index);
                    break;
                case 'b':
                    blackPieces += (uint64_t)1 << index;//powl(2, index);
                    bishops += (uint64_t)1 << index;//powl(2, index);
                    break;
                case 'N':
                    whitePieces += (uint64_t)1 << index;//powl(2, index);
                    knights += (uint64_t)1 << index;//powl(2, index);
                    break;
                case 'n':
                    blackPieces += (uint64_t)1 << index;//powl(2, index);
                    knights += (uint64_t)1 << index;//powl(2, index);
                    break;
                case 'Q':
                    whitePieces += (uint64_t)1 << index;//powl(2, index);
                    queens += (uint64_t)1 << index;//powl(2, index);
                    break;
                case 'q':
                    blackPieces += (uint64_t)1 << index;//powl(2, index);
                    queens += (uint64_t)1 << index;//powl(2, index);
                    break;
                case 'K':
                    whitePieces += (uint64_t)1 << index;//powl(2, index);
                    kings += (uint64_t)1 << index;//powl(2, index);
                    break;
                case 'k':
                    blackPieces += (uint64_t)1 << index;//powl(2, index);
                    kings += (uint64_t)1 << index;//powl(2, index);
                    break;
                default:
                    flag = true;
                    break;                 //the iteration will always be stopped on space symbol
            }
        }
        if (flag)
            break;
    }
    for(; i < (int)FEN.length(); i++){
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
                if(FEN[i]<='h' && FEN[i] >= 'a'){
                    if(FEN[i+1]=='3'){
                        enPassant = FEN[i] - 'a';
                    } else if(FEN[i+1] == '6'){
                        enPassant = 8 + FEN[i] - 'a';
                    }
                }
        }
    }
}

Board::Board(const Board &copy) {
    whitePieces = copy.whitePieces;
    blackPieces = copy.blackPieces;
    rooks = copy.rooks;
    knights = copy.knights;
    bishops = copy.bishops;
    queens = copy.queens;
    kings = copy.kings;
    pawns = copy.pawns;
    enPassant = copy.enPassant;
    whiteToMove = copy.whiteToMove;
    whiteLongCastle = copy.whiteLongCastle;
    blackLongCastle = copy.blackLongCastle;
    whiteShortCastle = copy.whiteShortCastle;
    blackShortCastle = copy.blackShortCastle;
}

Board& Board::operator=(const Board &board) = default;

Board::~Board() = default;

std::string Board::pieceOnSquare(std::string square){
    if(square.length() > 2)
        return "Wrong input, input should contain two symbols";
    else if(square[0] > 'h' || square[0] < 'a')
        return "Wrong input, verticals are a-h";
    else if(square[1] > '8' || square[1]<'1')
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
            if(checkedField/8 != position/8 || checkedField > 63 || checkedField < 0){
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

    int possibleKnightMoves[8] = {6, 10, 15, 17, -6, -10, -15, -17};

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

bool Board::fieldIsDefended(int position){
    this->passTheMove();
    bool result = fieldIsAttacked(position);
    this->passTheMove();
    return result;
}

std::vector<int> Board::fieldAttackers(int position, int ignore) {
    //if (!kings[position] && this->showCurrentColor()[position]){
    //    std::cerr << "This field is occupied by allied piece which is not a king. Returning false.";
    //    return false;
    //}
    //checking files

    std::vector<int> attackers;
    attackers.reserve(5);

    for(int i = -1; i <= 1; i+=2){
        for(int j = 1; j <= 7; j++){
            int checkedField = 8*j*i + position;
            if(checkedField > 63 || checkedField < 0){
                continue;
            }
            else if(this->anotherColorCheck(checkedField) &&
                    ((this->queenCheck(checkedField) || this->rookCheck(checkedField)) ||
                     (j == 1 && this->kingCheck(checkedField)))){
                attackers.push_back(checkedField);
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
            if(checkedField/8 != position/8 || checkedField > 63 || checkedField < 0){
                continue;
            }
            else if(this->anotherColorCheck(checkedField) &&
                    ((this->queenCheck(checkedField) || this->rookCheck(checkedField)) ||
                     (j == 1 && this->kingCheck(checkedField)))){
                attackers.push_back(checkedField);
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
                    attackers.push_back(checkedField);
                } else if ((this->currentColorCheck(checkedField) || this->anotherColorCheck(checkedField)) && ignore != checkedField){
                    break;
                }
            }
        }
    }

    int possibleKnightMoves[8] = {6, 10, 15, 17, -6, -10, -15, -17};

    for(auto move: possibleKnightMoves){
        int checkedField = position + move;
        if(checkedField < 0 || checkedField > 63 || abs(checkedField/8-position/8)+abs(checkedField%8-position%8) != 3){
            continue;
        }
        if(this->anotherColorCheck(checkedField) && this->knightCheck(checkedField)){
            attackers.push_back(checkedField);
        }
    }
    return attackers;
}

std::vector<int> Board::fieldDefenders(int position){
    this->passTheMove();
    auto result = fieldAttackers(position);
    this->passTheMove();
    return result;
}

std::string Board::sideToMove(){
    if(whiteToMove)
        return "White to move";
    else
        return "Black to move";
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
    bool currentColor = currentColorCheck(position);
    int kingPos = -1;
    for(int i = 0; i <= 63; i++){
        if(this->kingCheck(i) && this->currentColorCheck(i)){
            kingPos = i;
            break;
        }
    }
    // The piece is pinned if after taking it off the board the number of king field attackers increases
    int initialAttackersNumber = fieldAttackers(kingPos).size();
    int endAttackersNumber = fieldAttackers(kingPos, position).size();
    return endAttackersNumber > initialAttackersNumber;
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
        if(initSquare >= 0) {
            whitePieces &= ~((uint64_t) 1 << initSquare);
        }
        if(endSquare >= 0) {
            whitePieces |= ((uint64_t) 1 << endSquare);
        }
    }
    else{
        if(initSquare >= 0) {
            blackPieces &= ~((uint64_t) 1 << initSquare);
        }
        if(endSquare >= 0) {
            blackPieces |= ((uint64_t) 1 << endSquare);
        }
    }
}

void Board::updateAnotherColor(int initSquare, int endSquare){
    if(!whiteToMove){
        if(initSquare >= 0) {
            whitePieces &= ~((uint64_t) 1 << initSquare);
        }
        if(endSquare >= 0) {
            whitePieces |= ((uint64_t) 1 << endSquare);
        }
    }
    else{
        if(initSquare >= 0) {
            blackPieces &= ~((uint64_t) 1 << initSquare);
        }
        if(endSquare >= 0) {
            blackPieces |= ((uint64_t) 1 << endSquare);
        }
    }
}

void Board::printInfo(){
    std::cout << "White: " << whitePieces << ", Black: " << blackPieces << std::endl;
    std::cout << "Queens: " << queens << ", Kings: " << kings << std::endl;
    std::cout << "Rooks: " << rooks << ", Bishops: " << bishops << std::endl;
    std::cout << "Knights: " << knights << ", Pawns: " << pawns << std::endl;
}

bool Board::checkmate() {
    int kingPos = this->currentColorKingPosition();
   
    for(int i = -1; i<=1; i++){
        for(int j = -1; j<=1; j++){
            int newKingPos = kingPos + 8*i + j;
            if(newKingPos <= 63 && newKingPos >= 0 && abs(kingPos/8-newKingPos/8) <= 1 && abs(kingPos%8-newKingPos%8) <= 1){
                if(!(this->fieldIsAttacked(newKingPos, kingPos) || (this->currentColorCheck(newKingPos) && !this->kingCheck(newKingPos)))){
                    return false;
                }
            }
        }
    }
    
    std::vector<int> attackers = this-> fieldAttackers(kingPos);
    // it's impossible to cover from double check
    if(attackers.size() >= 2){
        return true;
    }
    
    for(auto defender: this->fieldDefenders(attackers[0])){
        if(!this->isPinned(defender) && defender != kingPos){
            return false;
        }
    }

    if(attackers[0]/8 == kingPos/8){
        int k = 2*(attackers[0] > kingPos) - 1;
        for(int i = kingPos+k; i != attackers[0]+k; i+=k){
            for(auto defender: this->fieldDefenders(i)){
                if(!this->isPinned(defender) && defender != kingPos){
                    return false;
                }
            }
        }
    }
    else if(attackers[0]%8 == kingPos%8){
        int k = 8*(2*(attackers[0] > kingPos)-1);
        for(int i = kingPos+k; i != attackers[0]+k; i+=k){
            for(auto defender: this->fieldDefenders(i)){
                std::cout << defender << " " << this->isPinned(defender) << std::endl;
                if(!this->isPinned(defender) && defender != kingPos){
                    std::cout << "here" << std::endl;
                    return false;
                }
            }
        }
    }
    else if(abs(attackers[0]%8 - kingPos%8) == abs(attackers[0]/8-kingPos/8)){
        int k = 8*(2*(attackers[0]/8 > kingPos/8)-1) + 2*((attackers[0]%8 > kingPos%8))-1;
        for(int i = kingPos+k; i != attackers[0]+k; i+=k){
            for(auto defender: this->fieldDefenders(i)){
                if(!this->isPinned(defender) && defender != kingPos){
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::stalemate(){
    int kingPos = -1;
    for(int i = 0; i <= 63; i++){
        if(this->kingCheck(i) && this->currentColorCheck(i)){
            kingPos = i;
            break;
        }
    }

    if(this->fieldIsAttacked(kingPos)){
        return false;
    }

    for(int i = -1; i<=1; i++){
        for(int j = -1; j<=1; j++){
            int newKingPos = kingPos + 8*i + j;
            if(newKingPos <= 63 && newKingPos >= 0 && abs(kingPos/8-newKingPos/8) <= 1 && abs(kingPos%8-newKingPos%8) <= 1){
                if(!this->fieldIsAttacked(newKingPos) && newKingPos != kingPos){
                    return false;
                }
            }
        }
    }

    for(int i = 0; i <= 63; i++){
        if(this->currentColorCheck(i) && !this->isPinned(i)){
            /*
             * For queens, rooks and bishops it's enough to check only neighbour fields where this piece could move on an empty board
             * If there is no piece of the same color there, then it's not a stalemate
             */
            if(this->queenCheck(i)){
                for(int j = -1; j<=1; j++){
                    for(int k = -1; k<=1; k++){
                        int checkPos = i + 8*j+k;
                        if(abs(i/8-checkPos/8) <= 1 && abs(i%8-checkPos%8) <= 1 && !this->currentColorCheck(checkPos)){
                            return false;
                        }
                    }
                }
            }
            else if(this->rookCheck(i)){
                for(int j = -1; j<=1; j+=2){
                    int checkPos = i + 8*j;
                    if(!this->currentColorCheck(checkPos)){
                        return false;
                    }
                    checkPos = i+j;
                    if(!this->currentColorCheck(checkPos) && i/8 == checkPos/8){
                        return false;
                    }
                }
            }
            else if(this->bishopCheck(i)){
                for(int j = -1; j<=1; j+=2){
                    for(int k = -1; k<=1; k+=2){
                        int checkPos = i + 8*j+k;
                        if(abs(i/8-checkPos/8) == 1 && abs(i%8-checkPos%8) == 1 && !this->currentColorCheck(checkPos)){
                            return false;
                        }
                    }
                }
            }
            else if(this->pawnCheck(i)){
                for(int j = 7; j <= 9; j++){
                    int checkPos = i + j * (2*this->whiteOrder()-1);
                    if(abs(checkPos/8 - i/8) != 1){
                        continue;
                    }
                    if(j == 8 && !this->currentColorCheck(checkPos)){
                        return false;
                    }
                    if(j != 8 && (this->anotherColorCheck(checkPos) || checkPos == enPassant)){
                        return false;
                    }
                }
            } else if(this->knightCheck(i)){
                std::vector<int> possibleDeltas = {-17, -15, -10, -6, 6, 10, 15, 17};
                for(auto delta: possibleDeltas){
                    int checkPos = i+delta;
                    if(checkPos >=0 && checkPos <= 63 &&abs(i/8-checkPos/8)+abs(i%8-checkPos%8) == 3
                                    && this->currentColorCheck(checkPos)){
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

int Board::currentColorKingPosition() {
    return this->whiteToMove ? clz(this->whitePieces & this->kings) : clz(this->blackPieces & this->kings);
}

int Board::anotherColorKingPosition() {
    return !this->whiteToMove ? clz(this->whitePieces & this->kings) : clz(this->blackPieces & this->kings);
}