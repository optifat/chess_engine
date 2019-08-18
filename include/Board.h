#ifndef CHESS_ENGINE_BOARD_H
#define CHESS_ENGINE_BOARD_H

class Board{
private:
/* These arrays called bitboards represent a board
 * Each element of array - True or False
 * True means that represented square has a piece mentioned in name of array
 * bool whiteToMove - if true - white to move, else - black
 * as input data we use Forsyth–Edwards Notation (FEN)
 * for more info:       https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 * "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq" (default input FEN) - chess starting position
 * enPassant array shows, if this move is possible. First 8 cells - move to the third horizontal, other 8 - sixth horizontal
*/
    bool whitePieces[64] = {};
    bool blackPieces[64] = {};
    bool rooks[64] = {};
    bool knights[64] = {};
    bool bishops[64] = {};
    bool queens[64] = {};
    bool kings[64] = {};
    bool pawns[64] = {};
    int enPassant = -1;
    bool whiteLongCastle;
    bool blackLongCastle;
    bool whiteShortCastle;
    bool blackShortCastle;
    bool whiteToMove = false;

public:
    Board(std::string FEN);

    ~Board();

    std::string pieceOnSquare(std::string square);

    std::string sideToMove();

    std::string whiteCastle();

    std::string blackCastle();

    bool* showAnotherColor();

    bool* showCurrentColor();

    bool* showRooks();

    bool* showKnights();

    bool* showBishops();

    bool* showQueens();

    bool* showKings();

    bool* showPawns();

    bool whiteOrder();

    void passTheMove();

    void editEnPassant(int index);

    int possibleEnPassant();

    void showBoard();

    bool fieldIsAttacked(int position);

    bool areOneDiagonal(int field1, int field2);

};

#endif //CHESS_ENGINE_BOARD_H
