#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>


struct RegistoF
{
    char nome[20];
    char cargo[20];
    int salario;
};

/*Exercicio 1
int validaSalarios(char* ficheiro, char cargo) {
    int r = 0;
    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {
        
        close(pipefd[0]);
        close(pipefd[1]);
        dup2(pipefd[1], STDOUT_FILENO);
        execlp("filtraCargo", "filtraCargo", ficheiro, cargo, NULL);
        _exit(0);

    }

    pid_t p = fork();

    if(p == 0) {
        close(pipefd[0]);
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        execl("valorMin", "valorMin", NULL);
    }
    int status;
    if(WIFEXITED(status)) {
        int e = WEEXITSTATUS(status);
        if(e == -1) {
            perror("Erro de execução");
        } else {
            r = e;
        }
    }
    return r;
}
*/

int validaSalarios(char* ficheiros, char* cargos) {
    int r = 0;
    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();

    if(pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {
        close(pipefd[0]);
        close(pipefd[1]);
        dup2(pipefd[1], STDOUT_FILENO);
        execlp("filtraCargo", "filtraCargo", ficheiros, cargos, NULL);
        _exit(0);
    }

    pid_t p = fork();
    if(p < 0){
        perror("fork2");
        exit(EXIT_FAILURE);
    }
    else if(p == 0) {
        close(pipefd[0]);
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        execl("valorMin", "valorMin", NULL);
        _exit(0);
    }

    int status;
    if(WIFEXITED(status)) {
        int e = WEXITEDSTATUS(status);
        if(e == -1){
            perror("Erro de execução");
            _exit(0);
        } else {
            r = e;
        }
    }
    return r;
}





/*Exercicio 2*/

int validaSalarios(char* ficheiro, char* cargo){
    int pipefd[2];
    if(pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }   

    pid_t pid = fork();

    if(pid < 0){

        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if(pid == 0) {

        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execlp("./filtraCargo", "./filtraCargo", ficheiro, cargo, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);

    pid_t pid_valid = fork();
    if(pid_valid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid_valid == 0) {

        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        execlp("./validMin", "./validMin", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    int status;
    waitpid(pid, &status, 0);
    waitpid(pid_valid, &status, 0);
    
    if(WIFEXITED(status) && WEXITSTATUS(status) == 1) {
        return 1;
    }
    return 0;
}








