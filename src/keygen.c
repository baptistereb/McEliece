#include "keygen.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void GenerateP(int size, float matrix[size][size], int nb_permutation) {
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

void GenerateS(int size, float matrix[size][size]) {
    generateSecureMatrix(size, matrix);
    while(!isInversible(size,matrix)) {
        generateSecureMatrix(size, matrix);
    }
}

void KeyGen(char rep[]) {
    char folderName[200];
    strcpy(folderName,rep);
    strcat(folderName,"/.mceliece");
    char publicKeyFile[] = ".public_key";
    char privateKeyFile[] = ".private_key";

    // Créer le dossier ".mceliece"
    if (mkdir(folderName, 0700) == -1) {
        perror("Erreur lors de la création du répertoire .mceliece");
        exit(EXIT_FAILURE);
    }

    if (chdir(folderName) == -1) {
        perror("Erreur lors du changement de répertoire .mcelice");
        exit(EXIT_FAILURE);
    }

    FILE* publicFile = fopen(publicKeyFile, "w");
    if (publicFile == NULL) {
        perror("Erreur lors de la création du fichier .public_key");
        exit(EXIT_FAILURE);
    }
    fclose(publicFile);

    FILE* privateFile = fopen(privateKeyFile, "w");
    if (privateFile == NULL) {
        perror("Erreur lors de la création du fichier .private_key");
        exit(EXIT_FAILURE);
    }
    fclose(privateFile);

    if (chdir("..") == -1) {
        perror("Erreur lors du retour au répertoire d'origine");
        exit(EXIT_FAILURE);
    }
}