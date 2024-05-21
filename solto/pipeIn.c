#include<stdio.h>

int main() {
    FILE *fp;
    char c;

    unsigned int contador = 0;

    fp = popen("ls", "r"); // "r" é a flag read, para ler os ficheiros

    while (c != EOF)
    {
        c = fgetc(fp);
        if(c == 'c') {
            contador++;
        }
    }
    pclose(fp);
    printf("Encontrei %d letras c\n", contador);

    return 0;
}