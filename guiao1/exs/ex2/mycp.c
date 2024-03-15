#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUFFER_SIZE 1024

void copyFile(const char *sourcePath, const char *destinationPath, size_t bufferSize) {
    FILE *sourceFile = fopen(sourcePath, "rb");
    FILE *destinationFile = fopen(destinationPath, "wb");

    if (sourceFile == NULL || destinationFile == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char *buffer = (char *)malloc(bufferSize);
    size_t bytesRead;

    clock_t start_time = clock();

    while ((bytesRead = fread(buffer, 1, bufferSize, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    clock_t end_time = clock();

    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Tempo gasto: %.6f segundos\n", elapsed_time);

    fclose(sourceFile);
    fclose(destinationFile);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <origem> <destino> <tamanho_buffer>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *sourcePath = argv[1];
    const char *destinationPath = argv[2];
    size_t bufferSize = atoi(argv[3]);

    copyFile(sourcePath, destinationPath, bufferSize);

    return 0;
}
