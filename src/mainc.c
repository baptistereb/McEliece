#include "main.h"
#include "matrix.h"
#include "keygen.h"
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


float test3[5][5];

float test5[3][3];
float test6[5][5];
float test10[5][7];

int main(int argc, char * argv[]) {
	//generateSecureMatrix(5, test3);
	//PrintMatrix(5, test3, "Matrice généré\0");
	//GeneratePermutation(5,test3,10);
	GenerateS(5,test6);
	PrintMatrix(5,test6, "S");
	InvertMatrix(5,test6);
	PrintMatrix(5,test6, "S-1");
	InvertMatrix(5,test6);
	PrintMatrix(5,test6, "S");

	//KeyGen(".");
	return 0;
}