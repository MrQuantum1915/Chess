// header file to check the validity of the move
#include <stdio.h>
#include <stdlib.h>
#include "fxns.h"
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

int validate(int whoseMove, char matrix[8][8], char piece, int InitialRow, int InitialColumn_int, int FinalRow, int FinalColumn_int, int possibleEnpassant, int *check)
{
    if (matrix[8 - InitialRow][InitialColumn_int - 1] == ' ')
    {
        printf("Error400");
        return no;
    }

    else if (whoseMove == white)
    {
        if (piece != whiteKing && piece != whitePawn && piece != whiteBishop && piece != whiteRook && piece != whiteKnight && piece != whiteQueen)
        {
            printf("Error401");
            return no;
        }

        else if (FinalRow > 8 || FinalRow < 1 || FinalColumn_int > 8 || FinalColumn_int < 1)
        {
            printf("Error402");
            return no;
        }

        else if (piece == whitePawn)
        {
            if (InitialRow == 2)
            {
                if (FinalRow == 3 || FinalRow == 4)
                {
                    return yes;
                }
                else
                {
                    printf("Error403");
                    return no;
                }
            }

            else if (((((InitialColumn_int + 1) < 8) && (FinalColumn_int == (InitialColumn_int + 1)) && (matrix[8 - InitialRow][InitialColumn_int + 1] == blackPawn)) || (((InitialColumn_int - 1) > 0) && (FinalColumn_int == (InitialColumn_int - 1)) && (matrix[8 - InitialRow][InitialColumn_int - 1] == blackPawn))) && (possibleEnpassant == 1)) // Enpassant
            {
                return yes;
            }

            else if (
                ((FinalColumn_int == (InitialColumn_int + 1)) &&
                     ((InitialColumn_int + 1) < 8) ||
                 (FinalColumn_int == (InitialColumn_int - 1)) &&
                     ((InitialColumn_int - 1) >= 0) &&
                     (FinalRow == (InitialRow + 1))) &&

                (matrix[8 - FinalRow][FinalColumn_int - 1 - 1] == blackPawn ||
                 matrix[8 - FinalRow][FinalColumn_int - 1 - 1] == blackBishop ||
                 matrix[8 - FinalRow][FinalColumn_int - 1 - 1] == blackRook ||
                 matrix[8 - FinalRow][FinalColumn_int - 1 - 1] == blackKnight ||
                 matrix[8 - FinalRow][FinalColumn_int - 1 - 1] == blackQueen ||
                 matrix[8 - FinalRow][FinalColumn_int - 1 - 1] == blackKing)) // capture piece
            {
                return yes;
            }

            else if ((FinalRow == (InitialRow + 1)) && (matrix[InitialRow + 1][InitialColumn_int - 1] == ' ')) // simple move
            {
                return yes;
            }

            else
            {
                printf("Error404");
                return no;
            }
        }

        else if (piece == whiteBishop)
        {
            int rowDiff = abs(FinalRow - InitialRow);
            int columnDiff = abs(FinalColumn_int - InitialColumn_int);

            if (rowDiff != columnDiff)
            {
                printf("Error405");
                return no;
            }

            int rowStep = (FinalRow - InitialRow) / rowDiff;                  //-1,+1
            int colStep = (FinalColumn_int - InitialColumn_int) / columnDiff; //-1,+1   determines the direction in whihc it is to be moved

            int currentRow = InitialRow + rowStep;
            int currentCol = InitialColumn_int + colStep;

            while (currentRow != FinalRow && currentCol != FinalColumn_int)
            {
                if (matrix[8 - currentRow][currentCol - 1] != ' ') // here checking if theres any obstacle while the pieces travels from initial to final postion, as if path is not clear the piece can't go to final box.
                {
                    printf("Error406");
                    return no;
                }
                currentRow += rowStep;
                currentCol += colStep;
            }

            if (matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == blackPawn ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == blackBishop ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == blackRook ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == blackKnight ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == blackQueen ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == blackKing)
            {
                return yes;
            }
            else
            {
                printf("Error407");
                return no;
            }
        }

        else if (piece == whiteRook)
        {
            int rowDiff = abs(FinalRow - InitialRow);
            int colDiff = abs(FinalColumn_int - InitialColumn_int);

            if (rowDiff == 0 || colDiff == 0)
            {
                int rowStep = (rowDiff != 0) ? (FinalRow - InitialRow) / rowDiff : 0;
                int colStep = (colDiff != 0) ? (FinalColumn_int - InitialColumn_int) / colDiff : 0;

                int currentRow = InitialRow + rowStep;
                int currentCol = InitialColumn_int + colStep;

                while (currentRow != FinalRow || currentCol != FinalColumn_int)
                {
                    if (matrix[8 - currentRow][currentCol - 1] != ' ')
                    {
                        printf("Error408");
                        return no;
                    }
                    currentRow += rowStep;
                    currentCol += colStep;
                }

                if (matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackPawn ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackBishop ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackRook ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackKnight ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackQueen ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackKing)
                {
                    return yes;
                }
                else
                {
                    printf("Error300");
                    return no;
                }
            }
            else
            {
                printf("Error301");
                return no;
            }
        }

        else if (piece == whiteKnight)
        {
            int rowDiff = abs(FinalRow - InitialRow);
            int columnDiff = abs(FinalColumn_int - InitialColumn_int);

            // check for the L shape move
            if ((rowDiff == 2 && columnDiff == 1) || (rowDiff == 1 && columnDiff == 2))
            {
                if (matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackPawn ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackBishop ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackRook ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackKnight ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackQueen ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == blackKing)
                {
                    return yes;
                }
            }

            else
            {
                printf("Error302");
                return no;
            }
        }

        else if (piece == whiteQueen)
        {
            int rowDiff = abs(FinalRow - InitialRow);
            int columnDiff = abs(FinalColumn_int - InitialColumn_int);

            if ((InitialRow == FinalRow) || (InitialColumn_int == FinalColumn_int) || (rowDiff == columnDiff))
            {
                // rook
                if ((InitialRow == FinalRow) || (InitialColumn_int == FinalColumn_int))
                {
                    int rowDiff = abs(FinalRow - InitialRow);
                    int colDiff = abs(FinalColumn_int - InitialColumn_int);

                    if (rowDiff == 0 || colDiff == 0)
                    {
                        int rowStep = (rowDiff != 0) ? (FinalRow - InitialRow) / rowDiff : 0;
                        int colStep = (colDiff != 0) ? (FinalColumn_int - InitialColumn_int) / colDiff : 0;

                        int currentRow = InitialRow + rowStep;
                        int currentCol = InitialColumn_int + colStep;

                        while (currentRow != FinalRow || currentCol != FinalColumn_int)
                        {
                            if (matrix[8 - currentRow][currentCol - 1] != ' ')
                            {
                                printf("Error408");
                                return no;
                            }
                            currentRow += rowStep;
                            currentCol += colStep;
                        }

                        if (matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == blackPawn ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == blackBishop ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == blackRook ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == blackKnight ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == blackQueen ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == blackKing)
                        {
                            return yes;
                        }
                        else
                        {
                            printf("Error300");
                            return no;
                        }
                    }
                    else
                    {
                        printf("Error301");
                        return no;
                    }
                }
                // bishop
                else
                {
                    int rowDiff = abs(FinalRow - InitialRow);
                    int columnDiff = abs(FinalColumn_int - InitialColumn_int);

                    if (rowDiff != columnDiff)
                    {
                        printf("Error405");
                        return no;
                    }

                    int rowStep = (FinalRow - InitialRow) / rowDiff;                  //-1,+1
                    int colStep = (FinalColumn_int - InitialColumn_int) / columnDiff; //-1,+1   determines the direction in whihc it is to be moved

                    int currentRow = InitialRow + rowStep;
                    int currentCol = InitialColumn_int + colStep;

                    while (currentRow != FinalRow && currentCol != FinalColumn_int)
                    {
                        if (matrix[8 - currentRow][currentCol - 1] != ' ') // here checking if theres any obstacle while the pieces travels from initial to final postion, as if path is not clear the piece can't go to final box.
                        {
                            printf("Error406");
                            return no;
                        }
                        currentRow += rowStep;
                        currentCol += colStep;
                    }

                    if (matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == blackPawn ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == blackBishop ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == blackRook ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == blackKnight ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == blackQueen ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == blackKing)
                    {
                        return yes;
                    }
                    else
                    {
                        printf("Error407");
                        return no;
                    }
                }
            }

            else
            {
                printf("Error411");

                return no;
            }
        }

        else if (piece == whiteKing)
        {
            int rowDiff = abs(FinalRow - InitialRow);
            int colDiff = abs(FinalColumn_int - InitialColumn_int);

            if ((rowDiff <= 1) && (colDiff <= 1))
            {
                if ((matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                     matrix[8 - FinalRow][FinalColumn_int - 1] == blackPawn ||
                     matrix[8 - FinalRow][FinalColumn_int - 1] == blackBishop ||
                     matrix[8 - FinalRow][FinalColumn_int - 1] == blackRook ||
                     matrix[8 - FinalRow][FinalColumn_int - 1] == blackKnight ||
                     matrix[8 - FinalRow][FinalColumn_int - 1] == blackQueen))
                {
                    return yes;
                }
            }
            else
            {
                return no;
            }
        }
    }

    else
    {
        if (piece != blackKing && piece != blackPawn && piece != blackBishop && piece != blackRook && piece != blackKnight && piece != blackQueen)
        {
            printf("Error413");
            return no;
        }

        else if (FinalRow > 8 || FinalRow < 1 || FinalColumn_int > 8 || FinalColumn_int < 1)
        {
            printf("Error414");

            return no;
        }
        else if (piece == blackPawn)
        {
            if (InitialRow == 7)
            {
                if ((FinalRow == 6 || FinalRow == 5))
                {
                    return yes;
                }
                else
                {
                    printf("Error415");
                    return no;
                }
            }

            else if (((((InitialColumn_int + 1) < 8) && (FinalColumn_int == (InitialColumn_int + 1)) && (matrix[8 - InitialRow][InitialColumn_int + 1] == blackPawn)) || (((InitialColumn_int - 1) > 0) && (FinalColumn_int == (InitialColumn_int - 1)) && (matrix[8 - InitialRow][InitialColumn_int - 1] == blackPawn))) && (possibleEnpassant == 1)) // Enpassant
            {
                return yes;
            }

            else if (
                ((FinalColumn_int == (InitialColumn_int + 1)) &&
                     ((InitialColumn_int + 1) < 8) ||
                 (FinalColumn_int == (InitialColumn_int - 1)) &&
                     ((InitialColumn_int - 1) > 0) &&
                     (FinalRow == (InitialRow - 1))) &&

                (matrix[8 - FinalRow][FinalColumn_int - 1] == whitePawn ||
                 matrix[8 - FinalRow][FinalColumn_int - 1] == whiteBishop ||
                 matrix[8 - FinalRow][FinalColumn_int - 1] == whiteRook ||
                 matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKnight ||
                 matrix[8 - FinalRow][FinalColumn_int - 1] == whiteQueen ||
                 matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKing)) // capture piece
            {
                return yes;
            }

            else if ((FinalRow == (InitialRow - 1)) && (matrix[InitialRow + 1][InitialColumn_int - 1] == ' ')) // simple move
            {
                return yes;
            }

            else
            {
                printf("Error416");
                return no;
            }
        }

        else if (piece == blackBishop)
        {
            int rowDiff = abs(FinalRow - InitialRow);
            int columnDiff = abs(FinalColumn_int - InitialColumn_int);

            if (rowDiff != columnDiff)
            {
                return no;
            }

            int rowStep = (FinalRow - InitialRow) / rowDiff;                  //-1,+1
            int colStep = (FinalColumn_int - InitialColumn_int) / columnDiff; //-1,+1   determines the direction in whihc it is to be moved

            int currentRow = InitialRow + rowStep;
            int currentCol = InitialColumn_int + colStep;

            while (currentRow != FinalRow && currentCol != FinalColumn_int)
            {
                if (matrix[8 - currentRow][currentCol - 1] != ' ') // here checking if theres any obstacle while the pieces travels from initial to final postion, as if path is not clear the piece can't go to final box.
                {
                    return no;
                }
                currentRow += rowStep;
                currentCol += colStep;
            }

            if (matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == whitePawn ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == whiteBishop ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == whiteRook ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKnight ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == whiteQueen ||
                matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKing)
            {
                return yes;
            }
            else
            {
                return no;
            }
        }

        else if (piece == blackRook)
        {
            int rowDiff = abs(FinalRow - InitialRow);
            int colDiff = abs(FinalColumn_int - InitialColumn_int);

            if (rowDiff == 0 || colDiff == 0)
            {
                int rowStep = (rowDiff != 0) ? (FinalRow - InitialRow) / rowDiff : 0;
                int colStep = (colDiff != 0) ? (FinalColumn_int - InitialColumn_int) / colDiff : 0;

                int currentRow = InitialRow + rowStep;
                int currentCol = InitialColumn_int + colStep;

                while (currentRow != FinalRow || currentCol != FinalColumn_int)
                {
                    if (matrix[8 - currentRow][currentCol - 1] != ' ')
                    {
                        printf("Error408");
                        return no;
                    }
                    currentRow += rowStep;
                    currentCol += colStep;
                }

                if (matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whitePawn ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whiteBishop ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whiteRook ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKnight ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whiteQueen ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKing)
                {
                    return yes;
                }
                else
                {
                    printf("Error300");
                    return no;
                }
            }
            else
            {
                printf("Error301");
                return no;
            }
        }

        else if (piece == blackKnight)
        {
            int rowDiff = abs(FinalRow - InitialRow);
            int columnDiff = abs(FinalColumn_int - InitialColumn_int);

            // check for the L shape move
            if ((rowDiff == 2 && columnDiff == 1) || (rowDiff == 1 && columnDiff == 2))
            {
                if (matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whitePawn ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whiteBishop ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whiteRook ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKnight ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whiteQueen ||
                    matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKing)
                {
                    return yes;
                }
            }
            else
            {
                printf("Error421");
                return no;
            }
        }

        else if (piece == whiteQueen)
        {
            int rowDiff = abs(FinalRow - InitialRow);
            int columnDiff = abs(FinalColumn_int - InitialColumn_int);

            if ((InitialRow == FinalRow) || (InitialColumn_int == FinalColumn_int) || (rowDiff == columnDiff))
            {
                // rook
                if ((InitialRow == FinalRow) || (InitialColumn_int == FinalColumn_int))
                {
                    int rowDiff = abs(FinalRow - InitialRow);
                    int colDiff = abs(FinalColumn_int - InitialColumn_int);

                    if (rowDiff == 0 || colDiff == 0)
                    {
                        int rowStep = (rowDiff != 0) ? (FinalRow - InitialRow) / rowDiff : 0;
                        int colStep = (colDiff != 0) ? (FinalColumn_int - InitialColumn_int) / colDiff : 0;

                        int currentRow = InitialRow + rowStep;
                        int currentCol = InitialColumn_int + colStep;

                        while (currentRow != FinalRow || currentCol != FinalColumn_int)
                        {
                            if (matrix[8 - currentRow][currentCol - 1] != ' ')
                            {
                                printf("Error408");
                                return no;
                            }
                            currentRow += rowStep;
                            currentCol += colStep;
                        }

                        if (matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == whitePawn ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == whiteBishop ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == whiteRook ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKnight ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == whiteQueen ||
                            matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKing)
                        {
                            return yes;
                        }
                        else
                        {
                            printf("Error300");
                            return no;
                        }
                    }
                    else
                    {
                        printf("Error301");
                        return no;
                    }
                }
                // bishop
                else
                {
                    int rowDiff = abs(FinalRow - InitialRow);
                    int columnDiff = abs(FinalColumn_int - InitialColumn_int);

                    if (rowDiff != columnDiff)
                    {
                        printf("Error405");
                        return no;
                    }

                    int rowStep = (FinalRow - InitialRow) / rowDiff;                  //-1,+1
                    int colStep = (FinalColumn_int - InitialColumn_int) / columnDiff; //-1,+1   determines the direction in whihc it is to be moved

                    int currentRow = InitialRow + rowStep;
                    int currentCol = InitialColumn_int + colStep;

                    while (currentRow != FinalRow && currentCol != FinalColumn_int)
                    {
                        if (matrix[8 - currentRow][currentCol - 1] != ' ') // here checking if theres any obstacle while the pieces travels from initial to final postion, as if path is not clear the piece can't go to final box.
                        {
                            printf("Error406");
                            return no;
                        }
                        currentRow += rowStep;
                        currentCol += colStep;
                    }

                    if (matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == whitePawn ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == whiteBishop ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == whiteRook ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKnight ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == whiteQueen ||
                        matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKing)
                    {
                        return yes;
                    }
                    else
                    {
                        printf("Error407");
                        return no;
                    }
                }
            }

            else
            {
                printf("Error411");

                return no;
            }
        }

        else if (piece == blackKing)
        {
            int rowDiff = abs(FinalRow - InitialRow);
            int colDiff = abs(FinalColumn_int - InitialColumn_int);

            if ((rowDiff <= 1) && (colDiff <= 1))
            {
                if ((matrix[8 - FinalRow][FinalColumn_int - 1] == ' ' ||
                     matrix[8 - FinalRow][FinalColumn_int - 1] == whitePawn ||
                     matrix[8 - FinalRow][FinalColumn_int - 1] == whiteBishop ||
                     matrix[8 - FinalRow][FinalColumn_int - 1] == whiteRook ||
                     matrix[8 - FinalRow][FinalColumn_int - 1] == whiteKnight ||
                     matrix[8 - FinalRow][FinalColumn_int - 1] == whiteQueen))
                {
                    return yes;
                }
            }
            else
            {
                return no;
            }
        }
    }
}
