#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {


   __pid_t pid = fork();
   switch (pid)
   {
   case -1:
    perror("Erro no fork");
       break;

   case 0: {
    int rec = execlp("ls", "ls", "-l", NULL);
   }

   default:
    break;
   }

    return 0;


}


