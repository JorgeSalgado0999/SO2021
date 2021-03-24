#include <stdio.h>
#include <unistd.h>
#include <ctype.h>


int main(){
	char c;
	int lines = 0;
	while(read(0, &c, 1 )){
		if(c == '\n'){
			lines++;
		}	
	}
	
	if(c != '\n' && lines > 0){
		lines++;
	}
	
	printf("lineas  %d\n", lines);
	return 0;
}