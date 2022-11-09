#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int calculaAleatorios(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void handlerTecnico(int s)
{
	
		sleep(calculaAleatorios(3, 6));
		if (calculaAleatorios(0, 1) == 1)
		{
			exit(1);
		}
		else
		{
			exit(0);
		}
}

int main(int argc, char *argv[])
{
	pid_t p;
	int numas = atoi(argv[1]);
	int tecnico, encargado, asistentes[numas];
	struct sigaction ss;

	srand(time(NULL));

	printf("Entrada\n");

	tecnico = fork();

	if (tecnico != 0)
	{
		encargado = fork();
	}
	
	if (tecnico == 0)
	{
		printf("Tecnico");

		ss.sa_handler = handlerTecnico;
		if (-1 == sigaction(SIGUSR1, &ss, NULL))
	{
		perror("TECNICO: sigaction\n");
		exit(-1);
	}
		pause();
	}

	if (encargado != 0 && tecnico != 0)
	{
		printf("Coordinador\n");

		kill(tecnico, SIGUSR1);

		int estado, valido;

		wait(&estado);
		valido = WEXITSTATUS(estado);

		if (valido == 1)
		{
			printf("El vuelo es viable.\n");
			kill(encargado, SIGUSR1);
		}
		else if (valido == 0)
		{
			printf("El vuelo no es viable.\n");
			kill(tecnico, SIGKILL);
			kill(encargado, SIGKILL);
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
