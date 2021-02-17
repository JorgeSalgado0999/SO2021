#include <stdio.h>

int main(int argc, char *argv[]) {
	/* En la funcion si pusiera **argv seria lo mismo */
	
	for(int i=1; i<argc; i++){
		printf("Hello, World! %s \n", argv[i]);
	}
	/* empieza por 1 porque hello world es el argumento 0 */
  
	
   return 0;
}