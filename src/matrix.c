#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
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
void PrintMatrixRect(int size1, int size2, float matrix[size1][size2], char * name) {
    printf("------------------------ %s\n", name);
    for(int i=0; i<size1;i++) {
        for(int j=0; j<size2;j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("------------------------\n");
}

void InvertMatrix(int size, float matrix[size][size]) {
	/*if(!isInversible(size, matrix)) {
		fprintf(stderr, "Matrice non inversible\n");
        exit(EXIT_FAILURE);
	}*/
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

void swapRows(int size, float matrix[size][size], int row1, int row2) {
    for (int col = 0; col < size; col++) {
        float temp = matrix[row1][col];
        matrix[row1][col] = matrix[row2][col];
        matrix[row2][col] = temp;
    }
}

void rowOperation(int size, float matrix[size][size], int sourceRow, int targetRow, float multiplier) {
    for (int col = 0; col < size; col++) {
        matrix[targetRow][col] += multiplier * matrix[sourceRow][col];
    }
}

float determinant(int size, float matrix[size][size]) {
    float det = 1.0;

    for (int i = 0; i < size; i++) {
        // Recherche du pivot non nul dans la colonne courante
        int pivotRow = -1;
        for (int j = i; j < size; j++) {
            if (matrix[j][i] != 0) {
                pivotRow = j;
                break;
            }
        }

        // Si aucun pivot n'est trouvé
        if (pivotRow == -1) {
            return 0.0;
        }

        // Échange des lignes pour placer le pivot en haut
        if (pivotRow != i) {
            swapRows(size, matrix, i, pivotRow);
            // Le déterminant change de signe lorsqu'on échange deux lignes
            det = -det;
        }

        // Élimination des éléments sous le pivot
        for (int j = i + 1; j < size; j++) {
            float multiplier = matrix[j][i] / matrix[i][i];
            rowOperation(size, matrix, i, j, -multiplier);
        }

        // Met à jour le déterminant avec le pivot
        det *= matrix[i][i];
    }

    return det;
}

int isInversible(int size, float matrix[size][size]) {
    float copy[size][size];

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            copy[j][i] = matrix[i][j];
        }
    }
    float det = determinant(size, copy);
    return det != 0.0;
}

void generateSecureMatrix(int size, float matrix[size][size]) {
    unsigned char buffer[size * size * sizeof(float)];

    // on génére pas avec le temps pour augmenter l'entropie de la génération des clés
    if (RAND_bytes(buffer, sizeof(buffer)) != 1) {
        fprintf(stderr, "Erreur lors de la génération aléatoire sécurisée.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int intValue;
            memcpy(&intValue, buffer + sizeof(int) * (i * size + j), sizeof(int));
            intValue=intValue>>15; // pour éviter l'érreur numérique : giga bancal comme méthode
            matrix[i][j] = (float)intValue;
        }
    }
}