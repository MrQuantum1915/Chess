#include <stdio.h>
#include "validate.h"

// Made by Mr.Quantum (Darshan Patel)

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

struct player
{
    char name[30];
    // int rating1;
} player1, player2;

void Instructions();
void fillCanvas(char matrix[8][8]);
void printCanvas(char matrix[8][8]);
int mapCharToInt(char Column);
void simulateMove(char piece, int InitialRow, int InitialColumn_int, int FinalRow, int FinalColumn_int);

int main()
{

    Instructions();
    printf("Enter name of Player 1 : ");
    scanf("%29[^\n]s", player1.name); // the 29 prevents overflow by limiting input to 29 chars
    getchar();
    printf("\nEnter name of Player 2 : ");
    scanf("%29[^\n]s", player2.name);
    printf("\n%s is assigned white, while %s is assigned black", player1.name, player2.name);
    getchar();
    char matrix[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            matrix[i][j] = ' ';
        }
    }

    fillCanvas(matrix);
    printCanvas(matrix);

    int result = 0;
    int whoseMove = black;

    while (result != 1)
    {
        char InitialColumn;
        int InitialRow;
        char FinalColumn;
        int FinalRow;
        int validMove = 0;

        if (whoseMove == black)
        {
            whoseMove = white;
            int InitialColumn_int, FinalColumn_int;
            char piece;
            while (validMove == 0)
            {
                printf("\nIt's %s's turn. Enter the Coordintes of the Move : ", player1.name);
                scanf("%c%d %c%d", &InitialColumn, &InitialRow, &FinalColumn, &FinalRow);
                getchar();
                InitialColumn_int = mapCharToInt(InitialColumn);
                FinalColumn_int = mapCharToInt(FinalColumn);
                piece = matrix[8 - InitialRow][InitialColumn_int - 1]; // To scan what the piece is at the position mentioned by user

                int possibleEnpassant = 0;

                validMove = validate(whoseMove, matrix, piece, InitialRow, InitialColumn_int, FinalRow, FinalColumn_int, possibleEnpassant);

                if (validMove == 0)
                {
                    printf("\nPlease Enter Valid Move");
                }
            }

            printf("\033[H\033[2J\033[3J"); // to clear the terminal, to reprint the canvas

            // simulateMove(piece, InitialRow, InitialColumn_int, FinalRow, FinalColumn_int);
            matrix[8 - InitialRow][InitialColumn_int - 1] = ' ';
            matrix[8 - FinalRow][FinalColumn_int - 1] = piece;
            printCanvas(matrix);
        }

        else
        {
            whoseMove = black;
            int InitialColumn_int, FinalColumn_int;
            char piece;
            while (validMove == 0)
            {
                printf("\nIt's %s's turn. Enter the Coordintes of the Move : ", player2.name);
                scanf("%c%d %c%d", &InitialColumn, &InitialRow, &FinalColumn, &FinalRow);
                getchar();
                InitialColumn_int = mapCharToInt(InitialColumn);
                FinalColumn_int = mapCharToInt(FinalColumn);
                piece = matrix[8 - InitialRow][InitialColumn_int - 1]; // To scan what the piece is at the position mentioned by user

                int possibleEnpassant = 0;

                validMove = validate(whoseMove, matrix, piece, InitialRow, InitialColumn_int, FinalRow, FinalColumn_int, possibleEnpassant);

                if (validMove == 0)
                {
                    printf("\nPlease Enter Valid Move");
                }
            }

            printf("\033[H\033[2J\033[3J"); // to clear the terminal, to reprint the canvas

            // simulateMove(piece, InitialRow, InitialColumn_int, FinalRow, FinalColumn_int);
            matrix[8 - InitialRow][InitialColumn_int - 1] = ' ';
            matrix[8 - FinalRow][FinalColumn_int - 1] = piece;
            printCanvas(matrix);
        }
    }

    printf("\nPress any key to exit...");
    getchar(); // added this If the user wanna runs this in windows terminal instead, than user has a time to see the result
    return 0;
}

void Instructions()
{
    printf("1. Enter the Coordinates (from-->to) format exactly like this : a2 a4\n"
           "2. \n"
           "3. \n");
}
void printCanvas(char matrix[8][8])
{
    printf("\n\n\t\t\t   ");
    for (int k = 0; k < 8; k++)
    {
        printf("  %c", k + 97);
    }
    printf("\n\n");

    for (int i = 0; i < 8; i++)
    {
        printf("\t\t\t");
        for (int j = 0; j < 8; j++)
        {
            if (j == 0)
            {
                printf("%d   ", 8 - i);
            }

            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
            {
                printf("\033[1;90m\033[48;5;255m %c \033[0m", matrix[i][j]);
            }
            else
            {
                printf("\033[1;97m\033[48;5;236m %c \033[0m", matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

void fillCanvas(char matrix[8][8])
{
    matrix[1][0] = matrix[1][1] = matrix[1][2] = matrix[1][3] = matrix[1][4] = matrix[1][5] = matrix[1][6] = matrix[1][7] = blackPawn;
    matrix[0][0] = matrix[0][7] = blackRook;
    matrix[0][1] = matrix[0][6] = blackKnight;
    matrix[0][2] = matrix[0][5] = blackBishop;
    matrix[0][3] = blackQueen;
    matrix[0][4] = blackKing;

    matrix[6][0] = matrix[6][1] = matrix[6][2] = matrix[6][3] = matrix[6][4] = matrix[6][5] = matrix[6][6] = matrix[6][7] = whitePawn;
    matrix[7][0] = matrix[7][7] = whiteRook;
    matrix[7][1] = matrix[7][6] = whiteKnight;
    matrix[7][2] = matrix[7][5] = whiteBishop;
    matrix[7][3] = whiteQueen;
    matrix[7][4] = whiteKing;
}

int mapCharToInt(char Column)
{
    switch (Column)
    {
    case 'a':
        return 1;
        break;

    case 'b':
        return 2;
        break;

    case 'c':
        return 3;
        break;

    case 'd':
        return 4;
        break;

    case 'e':
        return 5;
        break;

    case 'f':
        return 6;
        break;

    case 'g':
        return 7;
        break;

    case 'h':
        return 8;
        break;
    }
}

void simulateMove(char piece, int InitialRow, int InitialColumn_int, int FinalRow, int FinalColumn_int) // configuring this to board required so many frustrating try runs and adjusting the values
{
    printf("\033[%d;%dH", (7 + 8 - InitialRow), ((InitialColumn_int - 1) * 3) + 30); // moving the cursor to the peice which is to be moved
    if ((InitialRow % 2 == 0 && InitialColumn_int % 2 != 0) || (InitialRow % 2 != 0 && InitialColumn_int % 2 == 0))
    {
        printf("\033[48;5;255m \033[0m"); // print space at thes position to simulate disappearance
    }
    else
    {
        printf("\033[48;5;236m \033[0m");
    }
    printf("\033[%d;%dH", (7 + 8 - FinalRow), ((FinalColumn_int - 1) * 3 + 29));
    if ((FinalRow % 2 == 0 && FinalColumn_int % 2 != 0) || (FinalRow % 2 != 0 && FinalColumn_int % 2 == 0))
    {
        printf("\033[1;90m\033[48;5;255m %c \033[0m", piece);
    }
    else
    {
        printf("\033[1;97m\033[48;5;236m %c \033[0m", piece);
    }

    printf("\033[25;0H"); // these resets the cursor position to15,0 to avoid other overwrite for next instructions.
}

// fflsuh(stdout);
/* I had to apply this function because there were some problems  coming randomly when shifting the piece (like printing new at somewhere else). This function pushes the items in buffer to the terminal forcing to print anything in buffer that's waiting for either of (newline,buffer full, end of program). These clears any buffer Essential to be used especially in ANSI escapse commands*/
