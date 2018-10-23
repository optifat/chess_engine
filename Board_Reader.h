#ifndef CHESS_ENGINE_BOARD_H
#define CHESS_ENGINE_BOARD_H

#include "string"

class Board_Reader{
private:
/* These arrays called bitboards represent a board
 * Each element of array - True or False
 * True means that represented square has a piece mentioned in name of array
 * bool move - if true - white to move, else - black
 * as input data we use Forsyth–Edwards Notation (FEN)
 * for more info:       https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 * "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq" (default input FEN) - chess starting position
*/
    bool whitePieces[64] = {};
    bool blackPieces[64] = {};
    bool rooks[64] = {};
    bool knights[64] = {};
    bool bishops[64] = {};
    bool queens[64] = {};
    bool kings[64] = {};
    bool pawns[64] = {};
    bool whiteLongCastle;
    bool blackLongCastle;
    bool whiteShortCastle;
    bool blackShortCastle;
    bool move = false;

public:
    Board_Reader(std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq"){
        int index = 55;
        int i = 0;
        for(i; i < FEN.length(); i++){
            index ++;
            bool flag = false;
            if(FEN[i] < '9' and FEN[i] > '0'){
                index += FEN[i] - '1';
            }
            else if(FEN[i] == '/'){
                index -= 17;
                continue;
            }
            else{
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
                    move = true;
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
                    continue;
            }
        }
    }

    ~Board_Reader(){};

    std::string pieceOnSquare(std::string square){
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
            }
            else if(blackPieces[index]){
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
            }
            else{
                piece += "Empty";
            }
            return piece;
        }
    }

    std::string sideToMove(){
        if(move)
            return "White to move";
        else
            return "Black to move";
    }

    std::string whiteCastle(){
        if(whiteLongCastle && whiteShortCastle)
            return "White have long and short castle";
        else if (whiteLongCastle)
            return "White have only long castle";
        else if (whiteShortCastle)
            return "White have only short castle";
        else
            return "White have no castle";
    }

    std::string blackCastle(){
        if(blackLongCastle && blackShortCastle)
            return "Black have long and short castle";
        else if (blackLongCastle)
            return "Black have only long castle";
        else if (blackShortCastle)
            return "Black have only short castle";
        else
            return "Black have no castle";
    }

};

#endif //CHESS_ENGINE_BOARD_H
