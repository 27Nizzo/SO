#include "mysystem.h"


// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {

	int res = -1;

	// Estamos a assumir numero maximo de argumentos
	// isto teria de ser melhorado com realloc por exemplo
	char *exec_args[20];
	char *string, *cmd, *tofree;
	int i=0;
	tofree = cmd = strdup(command);
	while((string = strsep(&cmd," "))!=NULL){
	   exec_args[i]=string;
	   i++;
	}
	exec_args[i]=NULL;

	// ---------
	//   TO DO
	// ---------

	pid_t pid = fork();

	if(pid == -1) {
		perror("Erro ao criar processo filho");
		return -1;
	}

	if(pid == 0) {
		int ret = execvp(exec_args[0], exec_args);
		_exit(ret);
	} else {
		int status;
		waitpid(pid, &status, 0);

		if(WIFEXITED(status)) {
		res = WEXITSTATUS(status);
	}
}

	free(tofree);

	return res;
}