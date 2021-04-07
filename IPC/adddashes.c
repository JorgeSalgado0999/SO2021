#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv){
	//execl("/bin/ls", "ls", "-l", "-a", NULL);
	//printf("esto no será ejecutado \n");
	
	int fd[2];
	int pid;
	pipe(fd); //este pipe es único 
	pid = fork();
	
	if(pid == 0){
		//hijo -> entrada es 0
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execl("/usr/bin/tr", "tr", "' '", "-", NULL);
	}
	if(pid > 0){
		//padre -> salida es 1
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execl("/bin/cat", "cat", NULL);
	}
	
	return 0;
}