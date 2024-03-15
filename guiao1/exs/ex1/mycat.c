#include "mycat.h"

int mycat() {
    // ler do stdin
    ssize_t bytes_lidos, bytes_escritos;
    char buffer[BUFFER_SIZE];

    // escrever para o 
    bytes_lidos = read(0, buffer, BUFFER_SIZE);
    printf("li %ld bytes\n", bytes_lidos);

    //validar que o que lemos foi o que escrevemos
    bytes_escritos = write(1, buffer, bytes_lidos);
    printf("escrevi %ld bytes\n", bytes_escritos);

    //return 0;
    if (bytes_lidos != bytes_escritos) return 1;
    else return 0;

}
