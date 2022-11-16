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
	srand(getpid());
	return rand() % (max - min + 1) + min;
}

void handlerTecnico(int s)
{

	printf("Handler\n");

	exit(calculaAleatorios(0,1));
}

int main(int argc, char *argv[])
{
	int numas = atoi(argv[1]);
	pid_t tecnico, encargado, asistentes[numas];

	printf("Entrada\n");

	tecnico = fork();

	if (tecnico != 0)
	{
		encargado = fork();
	}

	if (tecnico == 0)
	{
		struct sigaction ss;
		ss.sa_handler = &handlerTecnico;
		ss.sa_flags = 0;
		sigemptyset(&ss.sa_mask);
		if (-1 == sigaction(SIGUSR1, &ss, NULL))
		{
			perror("TECNICO: sigaction\n");
			exit(-1);
		}
		pause();
	} else if (encargado != 0 && tecnico != 0)
	{

		sleep(1);

		kill(tecnico, SIGUSR1);

		int estado, valido;

		sleep(1);

		wait(&estado);
		valido = WEXITSTATUS(estado);

		printf("Coordinador\n");

		sleep(calculaAleatorios(3,6));

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
