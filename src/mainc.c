#include "main.h"
#include "affichage.h"
#include "keygen.h"
#include "keyread.h"
#include "encrypt.h"
#include "decrypt.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#define MAX_LENGTH 255

int main(int argc, char * argv[]) {
	if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("Utilisation :\n");
        printf("pour générer une clé : %s --keygen \n", argv[0]);
        printf("pour chiffrer sans préciser la clé : %s -e \"message\"\n", argv[0]);
        printf("pour chiffrer en précisant la clé : %s -e \"message\" -k /path/to/the/key \n", argv[0]);
        printf("pour déchiffrer en précisant la clé : %s -e \"message\" -k /path/to/the/key \n", argv[0]);
    } else if(argc ==2 && strcmp(argv[1], "--keygen") == 0) {
		struct stat st;
    	if (stat(".mceliece", &st) == 0) {
			remove(".mceliece/.private_key");
			remove(".mceliece/.public_key");
			remove(".mceliece/");
	    }
		KeyGen(8,3);
    } else if ((argc == 5 || argc == 3) && strcmp(argv[1], "-e") == 0) {
    	char buffer[256];
    	if(argc == 5 && strcmp(argv[3], "-k") == 0) {
			strcpy(buffer, argv[4]);
    	} else {
			strcpy(buffer, ".mceliece/.public_key");
		}
		
		int sz=nbligne(buffer);
	    if(sz>0) {
	    	int public_key[sz][sz];
	    	LireClePublique(buffer, sz, public_key, 0);
	    	fprintf(stdout, encrypt(strlen(argv[2])-1,argv[2], sz, public_key));
	    	fprintf(stdout, "\n");
	    }
	} else {
		Affichage();
    }
	return 0;
}