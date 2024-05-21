#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

#define NUM_EXECUTE 10

int get_vm_peak(pid_t pid) {
    char filename[256];
    FILE *file;
    char line[256];
    int vm_peak = -1;

    sprintf(filename, "/proc/%d/status", pid);
    file = fopen(filename, "r");
    if(!file){
        perror("fopen");
        return -1;
    }

    while (fgets(line, sizeof(line), file)) 
    {
        if(strncmp(line, "VmPeak", 7) == 0) {
            sscanf(line, "VmPeak: %d kB", &vm_peak);
            break;
        }
    }
    fclose(file);
    return vm_peak;
}

void run_and_measure(char *program[], int *vm_peaks) {
    pid_t pid;
    int status;

    pid = fork();
    if(pid < 0){
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    } 
    else if(pid == 0) {
        execvp(program[0], program);
        perror("execvp");
        exit(1);
    } else {
        usleep(100000); // 100ms
        int vm_peak = get_vm_peak(pid);
        waitpid(pid, &status, 0);
        if(WIFEXITED(status)) {
            *vm_peaks = vm_peak;
        } else {
            *vm_peaks = -1;
        }
    }
}

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Usage: %s <program> [arg1 .. argN]\n", argv[0]);
        exit(1);
    }
    int vm_peaks[NUM_EXECUTE];
    
    for (int i = 0; i < NUM_EXECUTE; i++)
    {
        run_and_measure(&argv[1], &vm_peaks[i]);
    }

    int min_vm = __INT_MAX__;
    int max_vm = 0;
    int sum_vm = 0;
    int valid_count = 0;

    for(int i = 0; i < NUM_EXECUTE; i++){
        if(vm_peaks[i] != -1){
        if(vm_peaks[i] < min_vm) min_vm = vm_peaks[i];
        if(vm_peaks[i] > max_vm) max_vm = vm_peaks[i];
        sum_vm += vm_peaks[i];
        valid_count++;
    }
}

    if(valid_count > 0){
        int avg_vm = sum_vm / valid_count;
        printf("memória: %d %d %d\n", min_vm, avg_vm, max_vm);
    } else {
        fprintf(stderr, "Failed to measure memory usage.\n");
    }
    return 0;
}