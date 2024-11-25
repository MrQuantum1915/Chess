#include <stdio.h>
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

void fillCanvas(char matrix[8][8]);
void printCanvas(char matrix[8][8]);
int mapCharToInt(char Column);
void simulateMove(char piece, int InitialRow, int InitialColumn_int, int FinalRow, int FinalColumn_int);

int main()
{

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

  int whoseMove = white;

  char InitialColumn;
  int InitialRow;
  char FinalColumn;
  int FinalRow;

  printf("Enter the Coordintes of block : ");
  scanf("%c%d %c%d", &InitialColumn, &InitialRow, &FinalColumn, &FinalRow);
  int InitialColumn_int = mapCharToInt(InitialColumn);
  int FinalColumn_int = mapCharToInt(FinalColumn);

  // printf("%d %d %d %d", InitialRow,InitialColumn_int,FinalRow,FinalColumn_int);

  char piece = matrix[InitialRow][InitialColumn_int]; // To scan what the piece is at the position mentioned by user

  simulateMove(piece, InitialRow, InitialColumn_int, FinalRow, FinalColumn_int);

  printf("\nPress any key to exit...");
  getchar(); // Added this If the user wanna runs this in windows terminal instead, than user has a time to see the result
  return 0;
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

// void simulateMove(char piece, int InitialRow, int InitialColumn_int, int FinalRow, int FinalColumn_int) // I Implemented ANSI escape seqeunce to update specific part of canvas
// {
//   printf("\033[%d;%dH", (8-InitialRow), (InitialColumn_int+1));
//   printf("%c",piece);
//   fflush(stdout);
// }

void simulateMove(char piece, int InitialRow, int InitialColumn_int, int FinalRow, int FinalColumn_int)
{
  // Clear the previous position
  printf("\033[%d;%dH", 10+8 - InitialRow, InitialColumn_int + 29);
  
  printf("\033[48;5;255m ");
  getchar();
  getchar();
  // Move the piece to the new position
  printf("\033[%d;%dH%c", 10+8 - FinalRow, FinalColumn_int + 29, piece);

  // Reset cursor position to avoid overwriting
  printf("\033[29;0H"); // Example reset (row 9, column 0)
}
