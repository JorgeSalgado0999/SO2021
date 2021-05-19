// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = { "sh", 0 };

int
main(void)
{
  int pid, wpid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
	 // Cuando cambio "init: starting sh\n" por "STARTING JARVIS!" se muestra mi mensaje antes de iniciar
	 // nuestro  init.c
    printf(1, "STARTING JARVIS!");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
		//Cuando corre sh todo sale normal y podemos entrar a ejecutar todo
		//Cuando se cambia sh por ls se genera un bucle 
		//infinito de ls o sea muestra los documentos una y otra vez y se ejecuta el mensaje de "STARTING JARVIS!"
		//Cuando se cambia por "no hay problema" surge el mensaje modificado muchas veces mas init: exec sh failed\n
		//Cuando cambio todo de regreso funciona perfecto como en un principio
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
