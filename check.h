// // header file to check check or checkmate

#include <stdio.h>
#include <stdlib.h>

#define blackKing 'k'
#define blackQueen 'q'
#define blackPawn 'p'
#define blackBishop 'b'
#define blackKnight 'n'
#define blackRook 'r'

#define whiteKing 'K'
#define whiteQueen 'Q'
#define whitePawn 'P'
#define whiteBishop 'B'
#define whiteKnight 'N'
#define whiteRook 'R'
#define yes 1
#define no 0
#define white 1 // here i am maping int to defining whose move
#define black 2

void pawnCheck(int *check, int whichKing, int Row, int Column, char matrix[8][8]);
// void bishopCheck(int *check, int whichKing, int Row, int Column, char matrix[8][8]);
// void rookCheck(int *check, int whichKing, int Row, int Column, char matrix[8][8]);
// void knightCheck(int *check, int whichKing, int Row, int Column, char matrix[8][8]);
// void queenCheck(int *check, int whichKing, int Row, int Column, char matrix[8][8]);

void checkCheck(int whichKing, char matrix[8][8], int Row, int Column, int *check)
{
    matrix[8 - Row][Column - 1];
    if (whichKing == white)
    {
        pawnCheck(check, white, Row, Column, matrix);
        // bishopCheck(check, white, Row, Column, matrix);
        // rookCheck(check, white, Row, Column, matrix);
        // knightCheck(check, white, Row, Column, matrix);
        // queenCheck(check, white, Row, Column, matrix);
    }
}

void pawnCheck(int *check, int whichKing, int Row, int Column, char matrix[8][8])
 {
    if (whichKing == white) {
        if ((Row == 1 && ((matrix[8 - Row + 1][Column - 1 + 1] == blackPawn) ||
                           (matrix[8 - Row + 1][Column - 1 - 1] == blackPawn))) ||
            (matrix[8 - Row + 1][Column - 1 + 1] == blackPawn) ||
            (matrix[8 - Row + 1][Column - 1 - 1] == blackPawn) ||
            (matrix[8 - Row - 1][Column - 1 + 1] == blackPawn) ||
            (matrix[8 - Row - 1][Column - 1 - 1] == blackPawn)) {
            *check = yes;
        }
    }
 }
// void checkCheckmate()
// {
//     printf("s");
// }
