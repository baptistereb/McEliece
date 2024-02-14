#include "matrix.h"
#include "keygen.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <encrypt.h>
#include <decrypt.h>
#define MAX_LENGTH 255

void clearTerminal() {
    #ifdef _WIN32
        system("cls"); // Pour Windows
    #else
        system("clear"); // Pour Linux/Unix et macOS
    #endif
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

void LireClePublique(char * fichiercle, int taille, int matrix[taille][taille]) {
    FILE *fichier;
    fichier = fopen(fichiercle, "r");

    if (fichier == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", fichiercle);
		exit(EXIT_FAILURE);
    }


    printf("\e[45;37;1m  Clé publique :\e[0m\e[45;37m");
    for(int i=0;i<10;i++) printf(" ");
    printf("\e[35;47m\n██");
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
            	printf("%d", nombre);
            }

            index = 0;
            printf(" ");
        } else if(caractere == '\n') {
        	j=0;
        	i++;
        	printf("██\n██");
        } else {
            buffer[index++] = caractere;
        }
    }

    for(int i=0;i<24;i++) printf("█");
   	printf("\e[0m");
    fclose(fichier);
}

void LireClePrive(char * nomFichier, int size1, int size2, int ** S, int ** G, int ** P) {
}

void Affichage() {

	char userInput;

	while("c vrai") {
		clearTerminal();
		printf("\e[92;1m█████████████████████████████\e[0m\n");
	    printf("\e[92;1m██\e[30;47m k : KeyGen              \e[92;1m██\e[0m\n");
	    printf("\e[92;1m██\e[30;47m c : Ecrire un message   \e[92;1m██\e[0m\n");
	    printf("\e[92;1m██\e[30;47m d : Decoder un message  \e[92;1m██\e[0m \n");
		printf("\e[92;1m█████████████████████████████\e[0m\n\n");
	    scanf(" %c", &userInput);

		switch (userInput) {
			case 'k':
				clearTerminal();
				printf("\e[92;1m█████████████████████████████\e[0m\n");
			    printf("\e[92;1m██\e[37;40m k : KeyGen              \e[92;1m██\e[0m\n");
			    printf("\e[92;1m██\e[30;47m c : Ecrire un message   \e[92;1m██\e[0m\n");
			    printf("\e[92;1m██\e[30;47m d : Decoder un message  \e[92;1m██\e[0m \n");
				printf("\e[92;1m█████████████████████████████\e[0m\n\n");

			    /*printf("Ou souhaitez vous enregistrer vos clés ? ");

			    clearInputBuffer();
			    fgets(buffer, sizeof(buffer), stdin);
			    printf("Vous avez saisi : %s\n", buffer);
				*/
				struct stat st;
			    if (stat(".mceliece", &st) == 0) {
			    	int factice[0][0];
			        LireClePublique(".mceliece/.public_key", 0, factice);

			        printf("\n\n");
			        printf("\e[31;47m Le .mceliece existe déjà, souhaitez-vous l'écraser ? \e[41;05;37m [o/n] \e[0m ");
				    scanf(" %c", &userInput);
				    switch (userInput) {
						case 'o':
							remove(".mceliece/.private_key");
							remove(".mceliece/.public_key");
							remove(".mceliece/");
							printf("\e[5;97;49mKeygen...\e[0m\n");
							KeyGen(8,3);
							break;
						default:
							break;
					}
			    } else {
					printf("\e[5;97;49mKeygen...\e[0m\n");
					KeyGen(8,3);
			    }
				break;
			case 'c':
				clearTerminal();
				printf("\e[92;1m█████████████████████████████\e[0m\n");
			    printf("\e[92;1m██\e[30;47m k : KeyGen              \e[92;1m██\e[0m\n");
			    printf("\e[92;1m██\e[37;40m c : Ecrire un message   \e[92;1m██\e[0m\n");
			    printf("\e[92;1m██\e[30;47m d : Decoder un message  \e[92;1m██\e[0m \n");
				printf("\e[92;1m█████████████████████████████\e[0m\n\n");

				char buffer[256];
				printf("Ou se trouve la clé publique de votre destinataire ? ('-' pour utilier la votre) ");
			    scanf("%s", buffer);
			   	

			    if (buffer[0]=='-') {
					strcpy(buffer, ".mceliece/.public_key");
			    }			    

			    int sz=nbligne(buffer);
			    char msg[MAX_LENGTH];
			    while (getchar() != '\n');
			    if(sz>0) {
			    	int public_key[sz][sz];
			    	printf("\n");
			    	LireClePublique(buffer, sz, public_key);
			    	printf("\n\n");
			    	printf("Que souhaitez-vous chiffrer ? ");
			    	fgets(msg, sizeof(msg), stdin);
			    	printf("Chiffré : %s", encrypt(strlen(msg)-1,msg, sz, public_key)); //strlen(msg)-1 car on compte pas le fin de chaine
			    	while (getchar() != '\n');
			    }
			    break;
			case 'd':
				clearTerminal();
				printf("\e[92;1m█████████████████████████████\e[0m\n");
			    printf("\e[92;1m██\e[30;47m k : KeyGen              \e[92;1m██\e[0m\n");
			    printf("\e[92;1m██\e[30;47m c : Ecrire un message   \e[92;1m██\e[0m\n");
			    printf("\e[92;1m██\e[37;40m d : Decoder un message  \e[92;1m██\e[0m \n");
				printf("\e[92;1m█████████████████████████████\e[0m\n\n");

		    	int size1,size2;
		    	privateShape(".mceliece/.private_key", &size1, &size2);
		    	int ** S = malloc(size1 * sizeof(int*));
		    	int ** G = malloc(size1 * sizeof(int*));
		    	int ** P = malloc(size2 * sizeof(int*));
		    	for(int i=0;i<size1;i++) S[i]=malloc(size1*sizeof(int));
		    	for(int i=0;i<size1;i++) G[i]=malloc(size2*sizeof(int));
		    	for(int i=0;i<size2;i++) P[i]=malloc(size2*sizeof(int));
		    	LireClePrive(".mceliece/.private_key", size1, size2, S, G, P);

		    	char chiffr[8*MAX_LENGTH];
		    	printf("Que souhaitez-vous dechiffrer ? ");
		    	fgets(chiffr, sizeof(chiffr), stdin);
		    	//printf("Clair : %s", decrypt(strlen(chiffr)-1,chiffr, size1, size2, S,G,P)); //strlen(msg)-1 car on compte pas le fin de chaine
		    	while (getchar() != '\n');

			    break;
			default:
				break;
		}
	}
}