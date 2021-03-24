#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>


void signalHandler(int sig){
	int pidHijoTermino = wait(NULL);
	printf("Mi hijo termino %d\n", pidHijoTermino);
}

int main(){
	signal(17,signalHandler);
	int pid = fork();
	if(pid== 0){
		printf("Soy el proceso hijo\n");
	}else{
		printf("Soy el proceso padre y mi hijo es %d\n", pid);
		//
		while(1){
			printf("Trabajando \n");
			sleep(1);
		}

	}
	printf("Terminando \n");
	return  0;
} 