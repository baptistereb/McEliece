#include "matrix.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <openssl/rand.h>

void bitFlipRandom(int rows, int column, int mG[rows][column]) {
    unsigned char rand_byte;
    for (int i = 0; i < rows; ++i) {
        if (RAND_bytes(&rand_byte, 1) != 1) {
            fprintf(stderr, "Erreur lors de la génération de nombres aléatoires cryptographiques.\n");
            exit(EXIT_FAILURE);
        }
        int index = rand_byte % column; // Générer un index aléatoire
        mG[i][index] ^= 1; // Inverser le bit à l'index aléatoire
    }
}

char * encrypt(int size, char msg[size], int public_size, int public[public_size][public_size]) {
    int* binaryMsg = (int*)malloc(size * 8 * sizeof(int)); // chaque char est sur 8 bits
    for(int i=0; i<size; ++i) {
        for(int j=7; j>=0; --j) {
            binaryMsg[i * 8 + (7 - j)] = (msg[i] & (1 << j)) ? 1 : 0;
        }
    }

    //for(int i=0;i<size*8;i++) printf("%d ", binaryMsg[i]);
   	//printf("\n");


	int numRows = (int)ceil((double)(8 * size) / public_size);
    int message[numRows][public_size];

    for(int i=0; i<numRows; i++) {
        for(int j=0; j<public_size; j++) {
        	if(i*public_size+j<8*size) {
            	message[i][j] = binaryMsg[i * public_size + j];
            } else {
            	message[i][j]=0;
            }
        }
    }

    //PrintMatrixRect(numRows, public_size,message, "matrice message");

    int mG[numRows][public_size];
	multMatrix(numRows,public_size,public_size, message, public, mG);

    //PrintMatrixRect(numRows, public_size,mG, "matrice mG");

	bitFlipRandom(numRows, public_size, mG);

    //PrintMatrixRect(numRows, public_size,mG, "matrice mG avec bitflip");

    char * result = malloc((numRows*public_size+1)*sizeof(char));
    for(int i=0;i<numRows;i++) {
    	for(int j=0;j<public_size;j++) result[i*public_size+j]=(char) (mG[i][j] + '0');//pour convertir 0 ou 1 en '0' ou '1'
    }
	result[numRows*public_size+1]='\0';

	return result;
}