#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (){
    __pid_t pid = fork();

    if(pid == 0){
        printf("F_PID: %d\n", getpid());
        printf("F_PPID: %d\n\n", getppid());

        _exit(1);
    }
    
    else{
        printf("P_PID: %d\n", getpid());
        printf("P_PPID: %d\n\n", getppid());

        int status;
        __pid_t wait_pid = wait(&status);

        printf("Wait: %d\n\n", wait_pid);

        if(WIFEXITED(status)){
            printf("Valor exit: %d\n", WEXITSTATUS(status));
        }else printf("ERROR\n");
    }

    return 0;
}