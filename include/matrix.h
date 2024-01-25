#ifndef MATRIX__H
#define MATRIX__H

void PrintMatrix(int size, float matrix[size][size], char * name);

void InvertMatrix(int size, float matrix[size][size]);

void TransverseMatrix(int size, float matrix[size][size]);

void swapRows(int size, float matrix[size][size], int row1, int row2);

void rowOperation(int size, float matrix[size][size], int sourceRow, int targetRow, float multiplier);

float determinant(int size, float matrix[size][size]);

int isInversible(int size, float matrix[size][size]);

#endif