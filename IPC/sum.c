#include <stdio.h>
#include<stdlib.h>
 
int main(int argc, char *argv[]){
     int sum = 0;

     for(int i=1; i<argc; i++){
		 
		int x = atoi(argv[i]);
		 sum += x;
     }

     printf("El resultado de la suma es = %d\n", sum);

     return 0;
}