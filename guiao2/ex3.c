#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (){
    
    for(int i = 0; i < 10; i++){
        __pid_t pid = fork();

        if(pid == 0){
            printf("Filho nº: %d\n", i);
            _exit(i);
        } else {
            int status;
            __pid_t wait_pid = wait(&status);

            printf("Wait: %d\n\n", wait_pid);
        }
    return 0;
}
