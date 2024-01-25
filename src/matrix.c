#include "matrix.h"
#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

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

void InvertMatrix(int size, float matrix[size][size]) {
    gsl_matrix *matrice = gsl_matrix_alloc(size, size);
    gsl_matrix *inverse = gsl_matrix_alloc(size, size); 
    gsl_matrix *copie = gsl_matrix_alloc(size, size); //copie de la matrice d'origine (car gsl_linalg_invert_modifie la matrice d'entrée)

	for(int i=0; i<size;i++) {
		for(int j=0; j<size;j++) {
			gsl_matrix_set(matrice, i, j, matrix[i][j]);
		}
	}

    gsl_matrix_memcpy(copie, matrice);

    // Déclaration d'un vecteur de permutation (nécessaire pour gsl_linalg_LU_decomp)
    gsl_permutation *p = gsl_permutation_alloc(size);
    int signum;

    // Décomposition LU
    gsl_linalg_LU_decomp(copie, p, &signum);

    // Inversion de la matrice
    gsl_linalg_LU_invert(copie, p, inverse);

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            matrix[i][j]=gsl_matrix_get(inverse, i, j);
        }
    }

    gsl_matrix_free(matrice);
    gsl_matrix_free(inverse);
    gsl_matrix_free(copie);
    gsl_permutation_free(p);
}

void TransverseMatrix(int size, float matrix[size][size]) {
    float temp[size][size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            temp[j][i] = matrix[i][j];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = temp[i][j];
        }
    }
}