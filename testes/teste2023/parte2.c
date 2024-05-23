#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>



/*Exercicio 2*/

void conta(int n, char* imagens[n]){
    int pipefd[2];

    if(pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    if(pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO); // FLAG STDOUT_FILENO vai buscar o stdout do pipefd
        close(pipefd[1]);

        defeitos(imagens, n, 5); 
        exit(EXIT_SUCCESS);
    } 
    else {
        close(pipefd[1]);

        pid_t pid_wc = fork();
        if(pid_wc < 0){
            perror("fork2");
            exit(EXIT_FAILURE);
        } 
        else if(pid_wc == 0) {
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            execlp("wc", "wc", "-l", NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        } 
        else {
            close(pipefd[0]);
            int status;
            waitpid(pid, &status, 0);
            waitpid(pid_wc, &status, 0);
        } 
    }
}

/*Exercicio 1*/

void defeitos(int n, char* imagens[n], int max) {

    int processos = 0;
    int i = 0;

    while(i < n){
        if(processos < max){
            pid_t pid = fork();
            if(pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            } 
            else if(pid == 0){
                execl("detecAnom", imagens[i], NULL);
            }
        i++;
        processos++;
        } 
        else if(processos == max){
            int status;
            wait(&status);
            processos--;
        }
    }
}