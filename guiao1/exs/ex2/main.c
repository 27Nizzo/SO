#include <mycp.h>

int main (int argc, char *argv[]) {
    for(int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return mycp(argv[1],argv[2]);
}