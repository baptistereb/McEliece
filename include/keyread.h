#ifndef KEYREAD__H
#define KEYREAD__H

void privateShape(char *nomFichier, int * size1, int * size2);

void LireClePrive(char * nomFichier, int size1, int size2, int ** S, int ** G, int ** P);

void LireClePublique(char *nomfichier, int taille, int matrix[taille][taille], int verbose);

int nbligne(char * nomFichier);

#endif