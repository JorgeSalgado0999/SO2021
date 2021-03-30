#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	
	if(argc == 1){
		printf("No diste valores \n");
		
	}else{
		
		for(int i=argc-1; i>0; i--){
		printf("%s ", argv[i]);
		
		}
		
	}
   return 0;
}