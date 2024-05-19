#include<stdio.h>
#include<unistd.h>

int main() {
    
    __pid_t pid = getpid();

    __pid_t pidd = getpidd(); 

    printf("PID do processo: %d\n", pid);
    printf("PID do processo pai: %d\n", pidd);

    return 0;
}