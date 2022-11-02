#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char*argv[]){

	int opcion;
	bool bucle = true;

	char Sys[1000];

	char dir[1000];

	int numdir;
	
	if(argv[1] != 0){
		strncpy(dir, argv[1], 1000);
	} else{
		getcwd(dir, 1000);
	}


	sprintf(Sys, "test -d %s", dir);

	int isDir = system(Sys);

	if(isDir == 0){
		printf("%s\n", dir);
	} else{
		printf("No hay directorio\n");
	}
	

	while(bucle == true){
		printf("1) Numero de archivos\n");
                printf("2) Numero de subdirectorios\n");
                printf("3) Ficheros mas grande\n");
		printf("4) Fichero mas pequeño\n");
		printf("5) Espacio total ocupado\n");
		printf("6) Numero de ficheros con permiso de lectura para el usuario que ejecuta el script\n");
		printf("7) Numero de ficheros con permiso de escritura para el usuario que ejecuta el script\n");
		printf("8) Numero de ficheros con permiso de ejecucion para el usuario que ejecuta el script\n");
		printf("9) Ficheros con perimiso de ejecucion para todos los usuarios\n");
		printf("10) Salir\n");

	scanf("%d", &opcion);

	switch(opcion){
		case 1:
			sprintf(Sys, "ls -l %s | grep ^- | wc -l", dir);
			system(Sys);
			break;
		case 2:
			sprintf(Sys, "ls -l %s | grep ^d | wc -l", dir);
			system(Sys);
			break;
		case 3:
			sprintf(Sys, "du -a %s | sort -n -r | head -n 1", dir);
			system(Sys);
			break;
		case 4:
			sprintf(Sys, "du -a %s | sort -n | head -n 1", dir);
			system(Sys);
			break;
		case 5:
			sprintf(Sys, "du -h %s --max-depth 0", dir);
			system(Sys);
			break;
		case 6:
			sprintf(Sys, "ls -l %s | grep ^.r.. | wc -l", dir);
			system(Sys);
			break;
		case 7:
			sprintf(Sys, "ls -l %s | grep ^..w. | wc -l", dir);
			system(Sys);
			break;
		case 8:
			sprintf(Sys, "ls -l %s | grep ^...x | wc -l", dir);
			system(Sys);
			break;
		case 9:
			sprintf(Sys, "ls -l -h %s | grep ^.........x");
			system(Sys);
			break;
		case 10:
			bucle = false;
			break;

    	}
	
}

return 0;
}
