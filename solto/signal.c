#include<signal.h>
#include<stdio.h>
#include<unistd.h>

void sigQuit() {
    printf("Recebi um sinal para terminar\n");
    sleep(1);
    printf("Adeus\n");
    _exit(0);
}


int main() {
    __pid_t filho;
    int a = 0;
    filho = fork();
    
    if(filho < -1) {
        perror("Fork Failed");
    }

    if(filho == 0){
        signal(SIGQUIT, sigQuit);

        while (1){
            printf("Processo filho: \n");
            sleep(1);
        }
    } else {
        printf("Processo filho tem PID: %d\n", filho);
    }

    do
    {   
        printf("Processo Pai: a = %d\n", a);
        sleep(1);
        a++;
        if(a == 3) {
            kill(filho, SIGQUIT);
        }
    } while (a < 6);
    waitpid(filho, 0, 0);

    return 0;
}