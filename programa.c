#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handler (int s)
{
	pritf("Estoy en la manejadora.\n");
}

int calculaAleatorios(int min, int max) {
	return rand() % (max-min+1) + min;
}

int main(int argc, char*argv[])
{
	pid_t p;	
	int numas = atoi(argv[1]);
	int tecnico, encargado, asistentes[numas];
	struct sigaction ss;

	srand(time(NULL));


	tecnico = fork();

	if(tecnico != 0){
		encargado = fork();
	}

	if(tecnico!=0 && encargado==0){
		ss.sa_handler=handler;
		if(-1==sigaction(SIGUSR1,&ss,NULL)){
			perror("TECNICO: sigaction");
			return 1;
		} else{
			printf("Tecnico durmiendo...");
			sleep(calculaAleatorio(3,6));
			if(==1){
				printf("El vuelo es viable.");
				exit(1);
			} else{
				printf("El vuelo no es viable.");
				exit(0);
			}
		}
	}

	if(encargado==0 && tecnico==0){
		if(WEXITSTATUS()==1){
			printf("El vuelo no es valido.")
			kill(SIGKILL, tecnico);
			kill(SIGKILL, encargado);
		} else{
			kill(SIGUSR1, encargado);
		}

	}

	/*
	for (int i = 0; i < numas; i++)
	{
		p = fork();

		if(p != 0){
			asistentes[i] = p;
		}else{
			printf("Asistente %d creado.\n", i);
		}
	}
	*/

	return 0;

}
