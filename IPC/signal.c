#include <signal.h>
#include <stdio.h>
#include <unistd.h>


int globalStatus;

void signalHandler(int sig){
	printf("Recibe signal %d\n", sig);
	globalStatus = sig;
}

int main(){
	signal(2,signalHandler);
	while(1){
		printf("Trabajando...\n");
		if(globalStatus == 2 || globalStatus == 15){
			printf("Ya voy a terminar \n");
			break;
		}
		sleep(1);
	}

	return 0;
} 