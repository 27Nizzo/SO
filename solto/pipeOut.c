#include<stdio.h>
#include<unistd.h>


int main() {
    FILE *fp;
    char c;

    __pid_t filho = fork();


    unsigned int contador = 0;

    

    fp = popen("cat > teste.txt", "w"); // "w" flag write para escrever em ficheiros

    fprintf(fp, "Pipeout executou\n");
    pclose(fp);

    return 0;
}

//Nota: Tem que se eliminar o ficheiro teste.txt sempre que se executa o programa