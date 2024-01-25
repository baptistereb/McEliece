#include "main.h"
#include "matrix.h"
#include <stdio.h>

float test[3][3] = {
    {3,5,6},
    {-1,2,2},
    {1,-1,1}
};
float test2[3][3] = { //non inversible
    {1,2,3},
    {5,6,7},
    {9,10,11}
};


int main() {
	PrintMatrix(3, test, "Matrice initiale\0");
	InvertMatrix(3, test2);
	PrintMatrix(3, test, "Matrice inverse\0");
	return 0;
}