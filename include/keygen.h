
#ifndef KEYGEN__H
#define KEYGEN__H

void KeyGen(char * rep);

void GenerateP(int size, float matrix[size][size], int nb_permutation); //génére des matrices de permutations

void GenerateS(int size, float matrix[size][size]);

#endif