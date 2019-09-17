#ifndef CHESS_ENGINE_BOARD_H
#define CHESS_ENGINE_BOARD_H

#include <string>

class Board{

    friend class Move;
    friend class Bishop_move;
    friend class Castling;
    friend class King_move;
    friend class Knight_move;
    friend class Pawn_move;
    friend class Queen_move;
    friend class Rook_move;

private:
/* These arrays called bitboards represent a board
 * Each element of array - True or False
 * True means that represented square has a piece mentioned in name of array
 * bool whiteToMove - if true - white to move, else - black
 * as input data we use Forsyth–Edwards Notation (FEN)
 * for more info:       https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 * "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq" (default input FEN) - chess starting position
 * enPassant variable shows, if this move is possible. Its values is field index where pawn moves after enPassant
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
    bool whiteToMove = false;
    bool whiteLongCastle;
    bool blackLongCastle;
    bool whiteShortCastle;
    bool blackShortCastle;

public:
    Board(std::string FEN);

    ~Board();

    std::string pieceOnSquare(std::string square);

    std::string sideToMove();

    std::string whiteCastle();

    std::string blackCastle();

    bool* showAnotherColor();

    bool* showCurrentColor();

    const bool* showRooks();

    const bool* showKnights();

    const bool* showBishops();

    const bool* showQueens();

    const bool* showKings();

    const bool* showPawns();

    bool whiteOrder();

    void passTheMove();

    void editEnPassant(int index);

    int possibleEnPassant();

    void showBoard();

    bool fieldIsAttacked(int position, int ignore = -1);

    bool isPinned(int position);

};

#endif //CHESS_ENGINE_BOARD_H
