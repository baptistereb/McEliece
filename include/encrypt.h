#ifndef ENCRYPT__H
#define ENCRYPT__H

void bitFlipRandom(int rows, int column, int mG[rows][column]);

char * encrypt(int size, char msg[size], int public_size, int public[size][size]);

#endif