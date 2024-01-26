#ifndef AFFICHAGE__H
#define AFFICHAGE__H

void clearTerminal();

void Affichage();

void LireClePublique(char *nomfichier, int taille, float matrix[taille][taille]);

int nbligne(char * nomFichier);

#endif