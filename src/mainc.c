#include "main.h"
#include "matrix.h"

float test[3][3] = {
    {3,5,6},
    {-1,2,2},
    {1,-1,1}
};


int main() {
	PrintMatrix(3, test, "Matrice initiale\0");
	TransverseMatrix(3,test);
	PrintMatrix(3, test, "Matrice transposé\0");
	InvertMatrix(3, test);
	PrintMatrix(3, test, "Matrice inverse\0");
	return 0;
}