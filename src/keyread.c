#include "keyread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void privateShape(char *nomFichier, int * size1, int * size2) {
    FILE *fichier;
    fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    fscanf(fichier, "%d %d", size1, size2);

    fclose(fichier);
}


void LireClePublique(char * fichiercle, int taille, int matrix[taille][taille], int verbose) {
    FILE *fichier;
    fichier = fopen(fichiercle, "r");

    if (fichier == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", fichiercle);
		exit(EXIT_FAILURE);
    }


    if(verbose==1) {
        printf("\e[45;37;1m  Clé publique :\e[0m\e[45;37m");
        for(int i=0;i<10;i++) printf(" ");
        printf("\e[35;47m\n██");
    }
	char caractere;
    char buffer[100];
    int index = 0;

    int i = 0;
    int j = 0;

    while ((caractere = fgetc(fichier)) != EOF) {
        if (caractere == ' ') {
            buffer[index] = '\0';

            if(buffer!="") {
            	int nombre = atof(buffer);
            	if(taille>0) {
            		matrix[i][j]=nombre;
            		j++;
            	}
            	//printf("%-10d", (int)nombre);
            	if(verbose==1) printf("%d", nombre);
            }

            index = 0;
            if(verbose==1) printf(" ");
        } else if(caractere == '\n') {
        	j=0;
        	i++;
        	if(verbose==1) printf("██\n██");
        } else {
            buffer[index++] = caractere;
        }
    }

    if(verbose==1) {
        for(int i=0;i<24;i++) printf("█");
   	printf("\e[0m");
    }
    fclose(fichier);
}

void LireClePrive(char * nomFichier, int size1, int size2, int ** S, int ** G, int ** P) {
}

int nbligne(char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    int nbligne = 0;
    char ligne[2000];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        nbligne++;
    }

    fclose(fichier);

    return nbligne;
}