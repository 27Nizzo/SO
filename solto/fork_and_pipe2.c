#include<stdio.h>
#include<unistd.h>

int main() {
    int fd[2];
    __pid_t pid;

    //Cria pipe:
    pipe(fd);

    pid = fork();

    if(pid == 0) {
        char s[] = "Olá Filho!\n";
        write(fd[1], s, sizeof(s));
    } else {
        char buffer[20];
        read(fd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
    }

    return 0;
}