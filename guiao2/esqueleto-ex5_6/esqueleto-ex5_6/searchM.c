#include "matrix.h"


int main(int argc, char *argv[]) {

    // generate random matrix
    int **matrix = createMatrix();

    // print matrix
    printMatrix(matrix);

    // TO DO
    int needle = atoi(argv[1]);
    int res = valueExists(matrix, needle);
    if(res == 1) {
        printf("Encontrei: %d\n", needle);
    } else {
        printf("Não encontrei: %d\n", needle);
    }

    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}