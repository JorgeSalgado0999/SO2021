#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUMTHREADS 1000
int total;
pthread_mutex_t lock;

void *suma(void *datos) { 
    printf("Hello world desde un hilo %d\n", *(int *)datos); 
	
	/* Inicia area critica*/
	pthread_mutex_lock(&lock);
    total += 100;
	pthread_mutex_unlock(&lock);
	/* termina area critica*/
	
    /*sleep(3);
    printf("otra caso\n");
	*/
    pthread_exit(NULL);
}

int main() { 
    pthread_t myThreads[NUMTHREADS];
    int tIds[NUMTHREADS];
	
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_unlock(&lock);
	
    total = 0;
    for(int i = 0; i< NUMTHREADS; i++){
        tIds[i] = i;
        pthread_create(&myThreads[i],NULL,suma, &tIds[i]);
    }
	
	printf("suma %d\n", total);
	
	/* esto va a esperar a que todos terminen*/
	for(int i = 0; i< NUMTHREADS; i++){
        pthread_join(myThreads[i], NULL);
    }
    /// wait
    printf("suma %d\n", total);
    pthread_exit(NULL);

    
}