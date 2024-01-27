
#ifndef KEYGEN__H
#define KEYGEN__H

#include <stdio.h>

void EcrireMatrice(FILE * fichier, int taille1, int taille2, int matrix[taille1][taille2]);

void KeyGen(int size, int redondance);

void GenerateP(int size, int matrix[size][size], int nb_permutation); //génére des matrices de permutations

void GenerateS(int size, int matrix[size][size]);

void GenerateG(int size, int redondance, int matrix[size][size+redondance], int itermax);
#endif