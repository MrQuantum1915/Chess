

int validate(int whoseMove, char matrix[8][8], char piece, int InitialRow, int InitialColumn_int, int FinalRow, int FinalColumn_int, int possibleEnpassant, int *check);

void pawnCheck(int *check, int whichKing, int Row, int Column, char matrix[8][8]);

void checkCheck(int whichKing, char matrix[8][8], int Row, int Column, int *check);

void pawnCheck(int *check, int whichKing, int Row, int Column, char matrix[8][8]);