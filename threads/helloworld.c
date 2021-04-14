#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUMTHREADS 20

void *printHelloWorld(void *datos) { 
    printf("Hello world desde un hilo %d\n", *(int *)datos); 
	sleep(3);
	printf("otra cosa \n");
	pthread_exit(NULL);
}

int main() { 
    pthread_t myThread[NUMTHREADS];
	
	int tIds[NUMTHREADS]; /* esto se hace para pasar una direccion de memoria diferente de lo contrario									todos imprimiran lo mismo*/
	
	/*crearemos 20 hilos*/
	for(int i=0; i<NUMTHREADS; i++){
		tIds[i] = i;
		pthread_create(&myThread[i], NULL, printHelloWorld, &tIds[i] ); /*cambiamos NULL por i*/
	}
    
	/* sleep(1); 	/* esto es para que tenga tiempo sufiecente para ejecutarlo*/
	
    pthread_exit(NULL); /* cierra TODOS los hilos y el código principal*/
}
/* 
	para compilar escribimos: 
	gcc -o helloworld helloworld.c -lpthread
	porque debo agregar la libreria
*/