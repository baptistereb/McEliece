#include "keygen.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void GenerateP(int size, int matrix[size][size], int nb_permutation) {
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            matrix[i][j]=(i==j); //1 si i=j sinon 0
        }
    }
    //pour le moment la matrix est l'identité
    unsigned char randomValue;
    int ligne1, ligne2;
    for(int iter=0; iter<nb_permutation;iter++) {
        if (RAND_bytes(&randomValue, sizeof(randomValue)) != 1) {
            fprintf(stderr, "Erreur lors de la génération de nombres aléatoires cryptographiques.\n");
            exit(EXIT_FAILURE);
        }
        ligne1 = randomValue%size;
        if (RAND_bytes(&randomValue, sizeof(randomValue)) != 1) {
            fprintf(stderr, "Erreur lors de la génération de nombres aléatoires cryptographiques.\n");
            exit(EXIT_FAILURE);
        }
        ligne2 = randomValue%size;

        swapRows(size, matrix, ligne1, ligne2); // on inverse ligne 1 et 2
    }
}

void GenerateS(int size, int matrix[size][size]) {
    int inverse[size][size];
    int different=1;
    int iter=0;
    while(different==1) {
        generateSecureMatrix(size, matrix);
        iter++;
        while(!isInversible(size,matrix)) {
            generateSecureMatrix(size, matrix);
            iter++;
        }
        for(int i=0; i<size;i++) {
            for(int j=0; j<size;j++) {
                inverse[i][j]=matrix[i][j];
            }
        }
        InvertMatrix(size, inverse);
        int result[size][size];
        multMatrix(size, size, size, matrix, inverse, result);
        different=0;
        for(int i=0; i<size;i++) {
            for(int j=0; j<size;j++) {
                if(result[i][j]!=((i == j) ? 1 : 0)) {
                    different=1;
                }
            }
        }
    }
    //printf("Nombre d'itérations : %d\n", iter);
}

void GenerateG(int size, int redondance, int matrix[size][size+redondance], int itermax) {
    int temp[size][size+redondance];

    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            matrix[i][j]=(i==j); //1 si i=j sinon 0
            temp[i][j]=(i==j);
        }
    }

    int maxdistance=0;
    srand(time(NULL));
    for(int iter=0;iter<itermax;iter++) {//on a l'identité sur le premier
        for(int i=0;i<size;i++) {
            for(int j=size;j<size+redondance;j++) {
                temp[i][j]=(int) (rand()%2); //1 si i=j sinon 0
            }
        }
        if(minimalHammingDistance(size,size+redondance, temp)>maxdistance){
            maxdistance=minimalHammingDistance(size,size+redondance, temp);
            for(int i=0;i<size;i++) {
                for(int j=0;j<size+redondance;j++) {
                    matrix[i][j]=temp[i][j];
                }
            }
        }
    }
}

void EcrireMatrice(FILE * fichier, int taille1, int taille2, int matrix[taille1][taille2]) {
    if (fichier == NULL) {
        perror("Erreur : Impossible d'ouvrir le fichier.");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < taille1; i++) {
        for (int j = 0; j < taille2; j++) {
            fprintf(fichier, "%d", matrix[i][j]);

            fprintf(fichier, " ");
        }
        fprintf(fichier, "\n");
    }
}

void KeyGen(int size, int redondance) {
    char folderName[]="./.mceliece";
    char publicKeyFile[] = ".public_key";
    char privateKeyFile[] = ".private_key";

    // Créer le dossier ".mceliece"
    if (mkdir(folderName, 0700) == -1) {
        perror("Erreur lors de la création du répertoire .mceliece");
        exit(EXIT_FAILURE);
    }    

    if (chdir(folderName) == -1) {
        perror("Erreur lors du changement de répertoire .mceliece");
        exit(EXIT_FAILURE);
    }

    int P[size+redondance][size+redondance];
    int S[size][size];
    int G[size][size+redondance];
    int SG[size][size+redondance];
    int SGP[size][size+redondance];
    GenerateP(size+redondance, P, 15);
    GenerateS(size, S);
    GenerateG(size, redondance, G, 10000);

    multMatrix(size, size, size+redondance, S, G, SG);
    //PrintMatrixRect(size, size+redondance, SG, "SG");
    multMatrix(size, size+redondance, size+redondance, SG, P, SGP);

    FILE* publicFile = fopen(publicKeyFile, "w");
    if (publicFile == NULL) {
        perror("Erreur lors de la création du fichier .public_key");
        exit(EXIT_FAILURE);
    }
    EcrireMatrice(publicFile, size+redondance, size+redondance, SGP);
    fclose(publicFile);

    FILE* privateFile = fopen(privateKeyFile, "w");
    if (privateFile == NULL) {
        perror("Erreur lors de la création du fichier .private_key");
        exit(EXIT_FAILURE);
    }
    fprintf(publicFile, "%d %d\n", size, size+redondance);
    fprintf(publicFile, "########################### S\n");
    EcrireMatrice(privateFile, size, size, S);
    fprintf(publicFile, "########################### G\n");
    EcrireMatrice(privateFile, size, size+redondance, G);
    fprintf(publicFile, "########################### P\n");
    EcrireMatrice(privateFile, size+redondance, size+redondance, P);
    fclose(privateFile);

    if (chdir("..") == -1) {
        perror("Erreur lors du retour au répertoire d'origine");
        exit(EXIT_FAILURE);
    }
}