#ifndef AFFICHAGE__H
#define AFFICHAGE__H

void clearTerminal();

void Affichage();

void privateShape(char *nomFichier, int * size1, int * size2);

void LireClePrive(char * nomFichier, int size1, int size2, int ** S, int ** G, int ** P);

void LireClePublique(char *nomfichier, int taille, int matrix[taille][taille]);

int nbligne(char * nomFichier);

#endif