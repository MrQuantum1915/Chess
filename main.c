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

void fillCanvas(char matrix[8][8]);
void printCanvas(char matrix[8][8]);

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

  printf("\nPress any key to exit...");
  getchar(); // If the user runs this in windows terminal instead, than user has a time to see the result
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