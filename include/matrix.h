// sudo apt-get install libgsl-dev
// ou sur fedora : sudo dnf install gsl-devel

#ifndef MATRIX__H
#define MATRIX__H

void PrintMatrix(int size, int matrix[size][size], char * name);

void PrintMatrixRect(int size1, int size2, int matrix[size1][size2], char * name);

void InvertMatrix(int size, int matrix[size][size]);

void TransverseMatrix(int size, int matrix[size][size]);

void swapRows(int size, int matrix[size][size], int row1, int row2);

void rowOperation(int size, int matrix[size][size], int sourceRow, int targetRow, int multiplier);

int determinant(int size, int matrix[size][size]);

int isInversible(int size, int matrix[size][size]);

void generateSecureMatrix(int size, int matrix[size][size]);

int minimalHammingDistance(int size1, int size2, int matrix[size1][size2]);

void multMatrix(int taille1, int taille2, int taille3, int matrix1[taille1][taille2], int matrix2[taille2][taille3], int result[taille1][taille3]);

#endif