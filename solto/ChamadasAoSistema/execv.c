#include<unistd.h>

int main(){
    
    char *bin_path = "/bin/ls";
    char *args[] = {bin_path, "-a", "-s", NULL};
    execv(bin_path,args);

    return 0;
}