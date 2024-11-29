// header file to check the validity of the move
#include <math.h>
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

#define white 1 // Here I am maping int to defining whose move
#define black 2

int validate(int whoseMove, char matrix[8][8], char piece, int InitialRow, int InitialColumn_int, int FinalRow, int FinalColumn_int, int possibleEnpassant)
{
if (matrix[8-InitialRow][InitialColumn_int]==' ')
{
    return 0;
}

    if (whoseMove == white)
    {
        if (FinalRow > 8 || FinalRow < 1 || FinalColumn_int > 8 || FinalColumn_int < 1)
        {
            return 0;
        }

        else if (piece == whitePawn)
        {
            if (InitialRow == 2)
            {
                if (FinalRow == 3 || FinalRow == 4)
                {
                    return 1;
                }
                else{
                    return 0;
                }
            }

            else if (((((InitialColumn_int + 1) < 8) && (FinalColumn_int == (InitialColumn_int + 1)) && (matrix[8 - InitialRow][InitialColumn_int + 1] == blackPawn)) || (((InitialColumn_int - 1) > 0) && (FinalColumn_int == (InitialColumn_int - 1)) && (matrix[8 - InitialRow][InitialColumn_int - 1] == blackPawn))) && (possibleEnpassant == 1)) // Enpassant
            {
                return 1;
            }

            else if (((FinalColumn_int == (InitialColumn_int + 1)) && ((InitialColumn_int + 1) < 8) || (FinalColumn_int == (InitialColumn_int - 1)) && ((InitialColumn_int - 1) > 0)) && (FinalRow == (InitialRow + 1))) // Capture Piece
            {
                return 1;
            }

            else if ((FinalRow == (InitialRow + 1)) && (matrix[InitialRow + 1][InitialColumn_int] == ' ')) // simple move
            {
                return 1;
            }

            else
            {
                return 0;
            }
        }

        else if (piece == whiteBishop)
        {
            int rowDiff = abs(FinalRow - InitialRow);
            int columnDiff = abs(FinalColumn_int - InitialColumn_int);

            if (rowDiff != columnDiff)
            {
                return 0;
            }

            int direction = 0;

            // 3 1
            // 4 2
            if ((FinalColumn_int - InitialColumn_int) > 0 && (FinalRow - InitialRow) > 0)
            {
                direction = 1;
            }
            else if ((FinalColumn_int - InitialColumn_int) > 0 && (FinalRow - InitialRow) < 0)
            {
                direction = 2;
            }

            else if ((FinalColumn_int - InitialColumn_int) < 0 && (FinalRow - InitialRow) > 0)
            {
                direction = 3;
            }

            else if ((FinalColumn_int - InitialColumn_int) < 0 && (FinalRow - InitialRow) < 0)
            {
                direction = 4;
            }

            int obstacleFlag = 1;

            for (int i = 0; i < rowDiff; i++)
            {
                if (direction == 1)
                {
                    if (matrix[8 - (FinalRow - i - 1)][FinalColumn_int - i - 1] != ' ')
                    {
                        obstacleFlag = 0;
                    }
                }

                else if (direction == 2)
                {
                    if (matrix[8 - (FinalRow + i + 1)][FinalColumn_int - i - 1] != ' ')
                    {
                        obstacleFlag = 0;
                    }
                }

                else if (direction == 3)
                {
                    if (matrix[8 - (FinalRow - i - 1)][FinalColumn_int + i + 1] != ' ')
                    {
                        obstacleFlag = 0;
                    }
                }

                else if (direction == 4)
                {
                    if (matrix[8 - (FinalRow + i + 1)][FinalColumn_int + i + 1] != ' ')
                    {
                        obstacleFlag = 0;
                    }
                }
            }

            if ((rowDiff == columnDiff) && (obstacleFlag != 0))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        else if (piece == whiteRook)
        {
            if (InitialRow == FinalRow || InitialColumn_int == FinalColumn_int)
            {
                int direction = 0;

                   // 1
                // 4     3
                 //   2
                if (FinalRow > InitialRow)
                {
                    direction = 1;
                }
                else if (FinalRow < InitialRow)
                {
                    direction = 2;
                }
                else if (FinalColumn_int > InitialColumn_int)
                {
                    direction = 3;
                }
                else if (FinalColumn_int < InitialColumn_int)
                {
                    direction = 4;
                }

                int obstacleFlag = 1;

                // check for obstacles in the path
                if (direction == 1)
                {
                    for (int i = InitialRow + 1; i < FinalRow; i++)
                    {
                        if (matrix[8 - i][InitialColumn_int] != ' ')
                        {
                            obstacleFlag = 0;
                            break;
                        }
                    }
                }
                else if (direction == 2)
                {
                    for (int i = InitialRow - 1; i > FinalRow; i--)
                    {
                        if (matrix[8 - i][InitialColumn_int] != ' ')
                        {
                            obstacleFlag = 0;
                            break;
                        }
                    }
                }
                else if (direction == 3)
                {
                    for (int i = InitialColumn_int + 1; i < FinalColumn_int; i++)
                    {
                        if (matrix[8 - InitialRow][i] != ' ')
                        {
                            obstacleFlag = 0;
                            break;
                        }
                    }
                }
                else if (direction == 4)
                {
                    for (int i = InitialColumn_int - 1; i > FinalColumn_int; i--)
                    {
                        if (matrix[8 - InitialRow][i] != ' ')
                        {
                            obstacleFlag = 0;
                            break;
                        }
                    }
                }

                if (obstacleFlag==1)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }

        else if (piece == whiteKnight)
        {
            if (1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (piece == whiteQueen)
        {
            if (1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (piece == whiteKing)
        {
            if (1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }

    else
    {
        int temp = 0;
        if (FinalRow > 8 || FinalRow < 1 || FinalColumn_int > 8 || FinalColumn_int < 1)
        {
            return 0;
        }

        else if (piece == blackPawn)
        {
            if (1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        else if (piece == blackBishop)
        {
            if (1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        else if (piece == blackRook)
        {
            if (1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (piece == blackKnight)
        {
            if (1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (piece == blackQueen)
        {
            if (1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (piece == blackKing)
        {
            if (1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}
