#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int paiParaFilho() {
    int fds[2];

    // Creating a pipe
    if (pipe(fds) == -1) {
        perror("pipe");
        return -1;
    }

    int fork_res = fork();  

    switch (fork_res) {
        case -1: {
            perror("Erro no fork");
            return -1;
            break;
        }

        case 0: {  
            close(fds[1]);  
            int value_read;
            printf("FILHO | vou ler um inteiro\n");
            int bytes_read = read(fds[0], &value_read, sizeof(int));
            if (bytes_read < 0) {
                perror("read");
                _exit(1); 
            }
            printf("FILHO | li %d bytes\n", bytes_read);
            close(fds[0]); 
            printf("FILHO || terminei!\n");
            _exit(0);  
        }

        default: {  
            close(fds[0]);  
            int value = 1000;
            printf("PAI | vou escrever o valor %d\n", value);
            int bytes_written = write(fds[1], &value, sizeof(int));  
            if (bytes_written < 0) {
                perror("write");
                return -1;
            }
            printf("PAI | escrevi %d bytes\n", bytes_written);
            close(fds[1]);  

            int status;
            int wait_res = wait(&status);  
            if (wait_res == -1) {
                perror("wait");
                return -1;
            }
            if (WIFEXITED(status)) {
                printf("PAI | o filho terminou com %d\n", WEXITSTATUS(status));  
            } else {
                printf("PAI | o filho terminou de forma anormal\n");
            }
            break;
        }
    }
    return 0;
}

int main(void) {
    int res = paiParaFilho();
    return res;
}
