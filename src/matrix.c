#include "matrix.h"
#include <stdio.h>

void PrintMatrix(int size, float matrix[size][size], char * name) {
	printf("------------------------ %s\n", name);
	for(int i=0; i<size;i++) {
		for(int j=0; j<size;j++) {
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("------------------------\n");
}