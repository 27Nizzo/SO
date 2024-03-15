#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {


    printf("bla\n");

    char *arr[3] = {"ls", "-l", NULL};

    

    // int rec = execl("bin/ls", "ls", "-l", NULL); //execl recebe o caminho absoluto e o final desse mesmo caminho que é o NULL
    // int rec = execlp("ls", "ls", "-l", NULL);
    int rec = execvp("ls", arr);

    //int rec = execv("/bin/ls", arr);

    if(rec == -1) {
        perror("Erro exec");
    }
   
    printf("%s\n", argv[0]);

    return 0;


}