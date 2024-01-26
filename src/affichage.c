#include "matrix.h"
#include "keygen.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

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

void Affichage() {

	char userInput;
	char buffer[100];

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
			        printf("\e[31;47m Le .mceliece existe déjà, souhaitez-vous l'écraser ? \e[41;05;37m [o/n] \e[0m ");
				    scanf(" %c", &userInput);
				    switch (userInput) {
						case 'o':
							remove(".mceliece/.private_key");
							remove(".mceliece/.public_key");
							remove(".mceliece/");
							printf("\e[5;97;49mKeygen...\e[0m\n");
							KeyGen(4,3);
							break;
						default:
							break;
					}
			    } else {
					printf("\e[5;97;49mKeygen...\e[0m\n");
					KeyGen(4,3);
			    }
				break;
			case 'c':
				printf("Ecrire :");
				break;
			case 'd':
				printf("Lecture...\n");
			default:
				break;
		}
	}
}