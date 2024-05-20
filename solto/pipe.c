#include<stdio.h>

int main() {
    char c;
    unsigned int contador = 0;

    while (c != EOF) // EOF -> End Of File
    {
        c = getchar();
        if(c == 'c') {
            contador++;
        }
    }

    printf("Encontrei %d letras c\n", contador);
    return 0;
 //apos dar o input para contar tem que se dar CNTRL+D   
}