#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>




void send_email(const char* aluno, const char* nota){
    pid_t pid = fork();
    if(pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if(pid == 0) {
        char email[50];
        execl("/bin/sh", "sh", "-c", )
    }
}


