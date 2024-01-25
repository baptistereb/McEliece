#include "main.h"
#include "matrix.h"

float test[3][3] = {
        {1., 2., 3.},
        {5., 6., 7.},
        {9., 10., 11.}
    };


int main() {
	PrintMatrix(3, test, "yolo\0");
	return 0;
}