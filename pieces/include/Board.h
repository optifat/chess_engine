#ifndef CHESS_ENGINE_BOARD_H
#define CHESS_ENGINE_BOARD_H

#include <string>
#include <cinttypes>
#include <sstream>
#include <vector>

class Board{

    friend class Move;
    friend class Bishop_move;
    friend class Castling;
    friend class King_move;
    friend class Knight_move;
    friend class Pawn_move;
    friend class Queen_move;
    friend class Rook_move;
    friend class Evaluator;
    friend class Node;

private:
/* These integers are called bitboards and represent a board
 * Each bit of integer - true or false
 * True means that represented square has a piece mentioned in name of array
 * bool whiteToMove - if true - white to move, else - black
 * enPassant variable shows, if this move is possible. Its values are field index where pawn moves after enPassant
 * as input data we use Forsyth–Edwards Notation (FEN)
 * for more info:       https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 * "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq" (default input FEN) - chess starting position
*/
    uint64_t whitePieces = 0;
    uint64_t blackPieces = 0;
    uint64_t rooks = 0;
    uint64_t knights = 0;
    uint64_t bishops = 0;
    uint64_t queens = 0;
    uint64_t kings = 0;
    uint64_t pawns = 0;
    int enPassant = -1;
    bool whiteToMove = true;
    bool whiteLongCastle;
    bool blackLongCastle;
    bool whiteShortCastle;
    bool blackShortCastle;

public:
    Board(std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
    Board(const Board &copy);
    Board& operator=(const Board &board);
    bool operator==(const Board &board);
    ~Board();
    std::string pieceOnSquare(std::string square);
    std::string sideToMove();
    std::string whiteCastle();
    std::string blackCastle();
    bool whitePieceCheck(int square);
    bool blackPieceCheck(int square);
    bool anotherColorCheck(int square);
    bool currentColorCheck(int square);
    bool rookCheck(int square);
    bool knightCheck(int square);
    bool bishopCheck(int square);
    bool queenCheck(int square);
    bool kingCheck(int square);
    bool pawnCheck(int square);
    bool whiteOrder();
    void passTheMove();
    void editEnPassant(int index);
    int possibleEnPassant();
    void showBoard();
    bool fieldIsAttacked(int position, int ignore = -1);
    bool fieldIsDefended(int position);
    std::vector<int> fieldAttackers(int position, int ignore = -1);
    std::vector<int> fieldDefenders(int position);
    std::vector<int> piecesAbleToMoveHere(int position);
    bool isPinned(int position);
    void updateCurrentColor(int initSquare, int endSqure);
    void updateAnotherColor(int initSquare, int endSqure);
    void printInfo();
    bool checkmate();
    bool stalemate();
    int currentColorKingPosition();
    int anotherColorKingPosition();
    uint64_t currentColor();
};

#endif //CHESS_ENGINE_BOARD_H
