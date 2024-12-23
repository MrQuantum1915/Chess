#include <stdio.h>
// Made by Mr.Quantum (Darshan Patel)

#ifdef _WIN32
#include <windows.h>
void setupWindowsConsole()
{
    // Set the console output to UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // Optional: Enable virtual terminal processing for better Unicode support
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

#include "validate.h"
#include "check.h"

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

#define white 1 // here I am maping int to defining whose move
#define black 2
#define yes 1 // just defined return value of 0 or 1 with more understandable format.
#define no 0

int gameNumber = 0;

struct player
{
    char name[30];
    // int rating1;
} player1, player2; // defined here as global variable , for access from every where in code, to prevent uneccesary passing of variables everytime

struct kingPosition
{
    int row;
    int column;
} trackWhiteKing, trackBlackKing;

void Instructions();
void fillInitialMatrix(char matrix[8][8]);
void printBoard(char matrix[8][8]);
int mapCharToInt(char Column);
void storeNameHistory(char player1[30], char player2[30]);
void storeMoveHistory(char player[30], char InitialColumn, int InitialRow, char FinalColumn, int FinalRow);
void storeResultHistory(int whoWon, int exit);

int main()
{
#ifdef _WIN32
    setupWindowsConsole();
#endif

    int check = no;
    int exit = no; // taken exit in middle

    Instructions();
    printf("Enter name of Player 1 : ");
    scanf("%29[^\n]s", player1.name); // the 29 prevents overflow by limiting input to 29 chars
    getchar();
    printf("\nEnter name of Player 2 : ");
    scanf("%29[^\n]s", player2.name);
    storeNameHistory(player1.name, player2.name);
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

    fillInitialMatrix(matrix);
    printBoard(matrix);

    int result = no;
    int whoseMove = black;

    while (result != yes)
    {
        char InitialColumn;
        int InitialRow;
        char FinalColumn;
        int FinalRow;
        int validMove = no;

        if (whoseMove == black)
        {
            whoseMove = white;
            int InitialColumn_int, FinalColumn_int;
            char piece;
            while (validMove == no)
            {
                printf("Check = %d", check);
                if (check == yes)
                {
                    printf("Caution White Kings is in Check !");
                }

                printf("\nIt's %s's turn. Enter the Coordintes of the Move : ", player1.name);
                scanf("%c%d %c%d", &InitialColumn, &InitialRow, &FinalColumn, &FinalRow);
                if (InitialColumn == '0' && InitialRow == 0 && FinalColumn == '0' && FinalRow == 0)
                {
                    exit = yes;
                    goto exit;
                }

                getchar();
                InitialColumn_int = mapCharToInt(InitialColumn);
                FinalColumn_int = mapCharToInt(FinalColumn);
                piece = matrix[8 - InitialRow][InitialColumn_int - 1]; // to scan what the piece is at the position mentioned by user

                int possibleEnpassant = no;

                validMove = validate(whoseMove, matrix, piece, InitialRow, InitialColumn_int, FinalRow, FinalColumn_int, possibleEnpassant, &check);

                if (check == yes)
                {
                    printf("\n King is Under Check, Can't make this move.");
                }

                if (validMove == no)
                {
                    printf("\nPlease Enter Valid Move");
                }
            }
            if (piece == whiteKing)
            {
                trackWhiteKing.row = FinalRow;
                trackBlackKing.column = FinalColumn_int;
            }

            matrix[8 - InitialRow][InitialColumn_int - 1] = ' ';
            matrix[8 - FinalRow][FinalColumn_int - 1] = piece;
            printf("\033[H\033[2J\033[3J"); // to clear the terminal, to reprint the canvas
            checkCheck(black, matrix, trackBlackKing.row, trackBlackKing.column, &check);
            printBoard(matrix);
            storeMoveHistory(player1.name, InitialColumn, InitialRow, FinalColumn, FinalRow);
        }

        else
        {
            whoseMove = black;
            int InitialColumn_int, FinalColumn_int;
            char piece;
            while (validMove == no)
            {
                printf("\nIt's %s's turn. Enter the Coordintes of the Move : ", player2.name);
                scanf("%c%d %c%d", &InitialColumn, &InitialRow, &FinalColumn, &FinalRow);
                if (InitialColumn == '0' && InitialRow == 0 && FinalColumn == '0' && FinalRow == 0)
                {
                    exit = yes;
                    goto exit;
                }

                getchar();
                InitialColumn_int = mapCharToInt(InitialColumn);
                FinalColumn_int = mapCharToInt(FinalColumn);
                piece = matrix[8 - InitialRow][InitialColumn_int - 1]; // to scan what the piece is at the position mentioned by user

                int possibleEnpassant = 0;

                validMove = validate(whoseMove, matrix, piece, InitialRow, InitialColumn_int, FinalRow, FinalColumn_int, possibleEnpassant, &check);

                if (check == yes)
                {
                    printf("\n King is Under Check, Can't make this move.");
                }

                if (validMove == no)
                {
                    printf("\nPlease Enter Valid Move");
                }
            }

            matrix[8 - InitialRow][InitialColumn_int - 1] = ' ';
            matrix[8 - FinalRow][FinalColumn_int - 1] = piece;
            printf("\033[H\033[2J\033[3J"); // to clear the terminal, to reprint the canvas
            printBoard(matrix);
            checkCheck(white, matrix, trackWhiteKing.row, trackWhiteKing.column, &check);
            storeMoveHistory(player2.name, InitialColumn, InitialRow, FinalColumn, FinalRow);
        }
    }
exit:
    int whoWon; // 0,1,2 (0=draw, no win);
    if (exit == 1)
    {
        whoWon = 0;
    }
    else
    {
        whoWon = whoseMove;
    }
    storeResultHistory(whoWon, exit);
    getchar();
    printf("\nPress any key to exit...");
    getchar(); // added this If the user wanna runs this in windows cmd instead of standard terminal, than user has a time to see the result
    return 0;
}

void Instructions()
{
    printf("\n\n1. Enter the Coordinates (from-->to) format exactly like this : a2 a4\n"
           "2. Zoom the terminal if chess pieces and board not visible clearly.\n"
           "3. To Exit the game in middle of the game , just type 00 00 when asked to enter the coordinates.\n"
           "4. Donot kill the terminal from middle. Instead write the above exit code and close the program properly, to avoid log errors while storing history."
           "\n\n");
}

void printBoard(char matrix[8][8])
{
    printf("\n\n\t\t\t   ");
    for (int k = 0; k < 8; k++)
    {
        printf("  %c", k + 97);
    }
    printf("\n\n");
    char piece;

    for (int i = 0; i < 8; i++)
    {
        printf("\t\t\t");
        for (int j = 0; j < 8; j++)
        {
            piece = matrix[i][j];
            if (j == 0)
            {
                printf("%d   ", 8 - i);
            }
            switch (piece)
            {
            case blackPawn:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;90m\033[48;5;255m \u265F \033[0m");
                }
                else
                {
                    printf("\033[1;90m\033[48;5;0m \u265F \033[0m");
                }
                break;
            case whitePawn:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;97m\033[48;5;255m \u2659 \033[0m");
                }
                else
                {
                    printf("\033[1;97m\033[48;5;0m \u2659 \033[0m");
                }
                break;
            case blackRook:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;90m\033[48;5;255m \u265C \033[0m");
                }
                else
                {
                    printf("\033[1;90m\033[48;5;0m \u265C \033[0m");
                }
                break;
            case whiteRook:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;97m\033[48;5;255m \u2656 \033[0m");
                }
                else
                {
                    printf("\033[1;97m\033[48;5;0m \u2656 \033[0m");
                }
                break;
            case blackKnight:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;90m\033[48;5;255m \u265E \033[0m");
                }
                else
                {
                    printf("\033[1;90m\033[48;5;0m \u265E \033[0m");
                }
                break;
            case whiteKnight:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;97m\033[48;5;255m \u2658 \033[0m");
                }
                else
                {
                    printf("\033[1;97m\033[48;5;0m \u2658 \033[0m");
                }
                break;
            case blackBishop:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;90m\033[48;5;255m \u265D \033[0m");
                }
                else
                {
                    printf("\033[1;90m\033[48;5;0m \u265D \033[0m");
                }
                break;
            case whiteBishop:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;97m\033[48;5;255m \u2657 \033[0m");
                }
                else
                {
                    printf("\033[1;97m\033[48;5;0m \u2657 \033[0m");
                }
                break;
            case blackQueen:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;90m\033[48;5;255m \u265B \033[0m");
                }
                else
                {
                    printf("\033[1;90m\033[48;5;0m \u265B \033[0m");
                }
                break;
            case whiteQueen:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;97m\033[48;5;255m \u2655 \033[0m");
                }
                else
                {
                    printf("\033[1;97m\033[48;5;0m \u2655 \033[0m");
                }
                break;
            case blackKing:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;90m\033[48;5;255m \u265A \033[0m");
                }
                else
                {
                    printf("\033[1;90m\033[48;5;0m \u265A \033[0m");
                }
                break;
            case whiteKing:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[1;97m\033[48;5;255m \u2654 \033[0m");
                }
                else
                {
                    printf("\033[1;97m\033[48;5;0m \u2654 \033[0m");
                }
                break;
            default:
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    printf("\033[48;5;255m   \033[0m");
                }
                else
                {
                    printf("\033[48;5;0m   \033[0m");
                }
                break;
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

void fillInitialMatrix(char matrix[8][8])
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

void storeNameHistory(char player1[30], char player2[30])
{
    // to put update th game number, my idea is to write the last game number at end of file everytime and than next time use it for incrementing the number acccordingly
    FILE *fptr0;
    fptr0 = fopen("gameHistory.txt", "r+");
    if (fptr0 == NULL)
    {
        printf("Game History Cannot be saved because file cannot be opened");
    }

    fseek(fptr0, 0, SEEK_END);
    char str[100];

    while (fgetc(fptr0) != '\n') // read the last line from end, till encounter a \n character, and then place the pointer there.
    {
        fseek(fptr0, -2, SEEK_CUR);
    }

    fgets(str, 100, fptr0); // now read the whole line, and store it in a buffer string str

    sscanf(str, "%d", &gameNumber); // converting hte string to integer for performing increment
    gameNumber++;
    fclose(fptr0);

    FILE *fptr2;
    fptr2 = fopen("gameHistory.txt", "a");

    if (fptr2 == NULL)
    {
        printf("Game History Cannot be saved because file cannot be opened");
    }

    fprintf(fptr2, "\n\n{\n"
                   "\tGame No : %d\n"
                   "\tPlayer 1 : %s\n"
                   "\tPlayer 2 : %s\n"
                   "\n"
                   "\tMoves\n\t {",
            gameNumber, player1, player2);
    fclose(fptr2);
}

void storeMoveHistory(char player[30], char InitialColumn, int InitialRow, char FinalColumn, int FinalRow)
{
    FILE *fptr1;
    fptr1 = fopen("gameHistory.txt", "a");

    if (fptr1 == NULL)
    {
        printf("Move History Cannot be saved because file cannot be opened");
    }

    fprintf(fptr1, "\n"
                   "\t\t%s 's move : "
                   "\t%c%d %c%d"
                   "\n",
            player, InitialColumn, InitialRow, FinalColumn, FinalRow);
    fclose(fptr1);
}

void storeResultHistory(int whoWon, int exit)
{
    char *player;
    if (whoWon == 1)
    {
        player = player1.name;
    }

    else if (whoWon == 2)
    {
        player = player2.name;
    }

    else if (whoWon == 0 && exit == 1)
    {
        player = "No Winner (Exit)";
    }

    else
    {
        player = "Draw";
    }

    FILE *fptr1;
    fptr1 = fopen("gameHistory.txt", "a");

    if (fptr1 == NULL)
    {
        printf("Result can't be stored because file can't be opened");
    }

    fprintf(fptr1, "\n\t}\n\n"
                   ""
                   "\tResult"
                   "\n\t{\n"
                   "\t\t"
                   "Winner: %s"
                   "\n\t}\n}\n%d",
            player, gameNumber);
    fclose(fptr1);
}