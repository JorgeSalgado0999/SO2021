#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int globalStatus;
char str[40];
int x, y, puntos;
float jump;

//funcion hecha para captar la señal de ctrl + c
void signalHandler(int sig){
		//printf("\nDiste click ctrl+C %d\n", sig);
		globalStatus = sig;
		if(globalStatus == 2 || globalStatus == 15){
			printf("Has finalizado el proceso \n");
			exit(1);
		}
	}
// funcion para pedir los datos al usuario; regresa el areglo de los puntos a evaluar
float* pedirDatos(){
	scanf("%s", str); // pido la función 
	while((fgetc(stdin)) != '\n'); //limpio buffer

	scanf("%d %d %d", &x, &y, &puntos); // pido los intervalos
	while((fgetc(stdin)) != '\n'); //limpio buffer

	jump = ((y*1.0-x*1.0)/puntos*1.0); // encuentro el valor en el que avanzará cada intervalo

	float* intervals = (float*) calloc(puntos, sizeof(float)); // inicializo el arreglo 

	printf("\nla funcion a evaluar es: %s\n", str);
	printf("el intervalo 1 es: %d, el intervalo 2 es: %d, y avanzara cada: %d\n", x, y, puntos);
	printf("jump: %f\n", jump);
	//printf("Los intervalos seran:\n");
	
	//este for llena el arreglo con los puntos que vamos a evaluar
	for(int i=0; i< puntos; i++){
		intervals[i] = x + (jump*(i+1)); //
	}

	/* este for imprime los intervalos
	for(int i=0; i< puntos; i++){
		printf("%f\n", intervals[i]);
	}
	*/
	
	printf("\n");
	fflush(stdout);
	
	return intervals;
}


int main(){
	signal(2,signalHandler);
	
	while(1){
		// from parent to child, parent write, child read
		int pp2c[2];
		// from child to parent, child write, parent read
		int pc2p[2];

		pipe(pp2c);
		pipe(pc2p);
		
		 switch (fork()) {
        // fork failed
        case -1:
            break;
        // child
        case 0: 
            // connect pp2c to stdin
            close(pp2c[1]);
            dup2(pp2c[0], STDIN_FILENO);
            close(pp2c[0]);
            // connect pc2p to stdout
            close(pc2p[0]);
            dup2(pc2p[1], STDOUT_FILENO);
            close(pc2p[1]);

            // exec "rev" to reverse lines
            execlp("bc", "bc", "-l", (char*) NULL);
          break;
        // parent
        default:
            // close unnecessary pipes
            close(pp2c[0]);
            close(pc2p[1]);
            // open pipes as stream
           // this is need to use fprintf/scanf to write/read from the pipes
            FILE *out = fdopen(pp2c[1], "w");
            FILE *in = fdopen(pc2p[0], "r"); 
			
			
			float* intervals = pedirDatos();
            float suma = 0;
            float promedio = 0;
            float cont;
            char result[24];


            for(int i=0; i< puntos; i++){
                fprintf(out, "x=%f\n", intervals[i]);
                fprintf(out, "%s\n", str);
            }

            fclose(out);

            for(int i=0; i< puntos; i++){
                fscanf(in, "%s", result);
                printf("el resultado resultado con %f: %s\n", intervals[i], result);
				suma += atof(result);
            }
			promedio = suma/puntos;
			printf("\nel promedio es: promedio: %f\n\n", promedio);

            fclose(in);
            wait(NULL);
            free(intervals);
            break;
    	}
	}

	return 0;
} 