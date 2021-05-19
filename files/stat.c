#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

//Oscar Gutiérrez Godoy A01635648
//Oscar Fernandez Moreno A07013362
//Carlos Raúl Armenta Pérez A01635371

int main(int argvnum, char **argv){
    char *pathOriginal = argv[1];
    char *pathNuevo = argv[2];
    struct stat sb;
    struct stat sb2;

    if(stat(pathOriginal, &sb) == -1){
        printf("El primer archivo que escribiste no existe \n");
        return -1;
    }


    if(stat(pathNuevo, &sb2) == -1){
        //Renombra
        link(pathOriginal, pathNuevo);
        unlink(pathOriginal);
    }else if(S_ISDIR(sb2.st_mode)){
        //El segundo path corresponde al directorio, lo mueve dentro de el 
        char pathDir[100];
        sprintf(pathDir, "%s/%s",pathNuevo,pathOriginal);
        printf("%s \n",pathDir);
        link(pathOriginal,pathDir);
        unlink(pathOriginal);
    }else{
        printf("El segundo archivo ya existe \n");
        return -1;
    }

/*
    if(stat(path, &sb) == -1){
        printf("Error el archivo no existe \n");
        return -1;
    }
    if(S_ISDIR(sb.st_mode)){
        printf("Es un directorio \n");
    } 
    if(S_ISREG(sb.st_mode)){
        printf("Es un archivo normal \n");
    }
*/

    return 1;
}