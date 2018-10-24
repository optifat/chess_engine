## chess_engine

# Board.h
Board class has private arrays called bitboards, which in summary represent a board.  
Each element of array - True or False.  
True means that represented square has a piece mentioned in name of array.  
Bool move - if true - white to move, else - black.  
As input data we use Forsyth–Edwards Notation (FEN).  
For more info:       <link>https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation  
"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq" (default input FEN) - chess starting position.  
enPassant array shows, if this move is possible. First 8 cells - move to the third horizontal, other 8 - sixth horizontal.  

# Moves.h
Function "readMove" will be define by the first letter, which piece should move and pass it over  
to the next function (pawnMove, queenMove an so on).  

# Pawn_Move.h
Function "pawnMove" moves the pawn.  
k variable is defined by the side to move: 1 if white and -1 if black.
All the white pawns are going up the board while black vice versa.
That means for us, that the difference between end and initial pawn squares is positive in case of white
and negative in case of black.
Also, in case of A or H verticals, the possible takes are only to vertical B and G respectively.
As example for A vertical:
      white pawn move: A(i) x B(i+1), the difference between end and initial pawn squares is 9
      black pawn move: A(i) x B(i-1), the difference between end and initial pawn squares is -7
So the possible difference can be defined as (8 + k)*k
Similarly for H vertical with change of previous equation to (8 - k)*k

