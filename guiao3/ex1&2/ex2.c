#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int agrc, char* argv[]){

    __pid_t pid = fork();

    switch(pid){
        case -1:{
            perror("Erro no fork");
            break;
        }
        case 0:{
            int ret = execlp("ls","ls","-l",NULL);
            _exit(ret);
            break;
        }
        default:{
            int status;
            wait(&status);
            if(WIFEXITED(status)){
                printf("%d\n", WEXITSTATUS(status));
            }
            else {
                perror("Filho interrompido");
            }
            break;
        }
    }
    
    return 0;
}