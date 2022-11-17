#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Calcula un número aleatorio entre min y max
int calculaAleatorios(int min, int max)
{
	srand(getpid());
	return rand() % (max - min + 1) + min;
}

// Manejadora del Técnico. Devuelve 0 si el vuelo es viable o 0 si no lo es.
void handlerTecnico(int s)
{

	printf("TECNICO: Calculando si el vuelo es viable.\n");

	sleep(calculaAleatorios(3, 6));
	exit(calculaAleatorios(0, 1));
}

// Manejadora del Encargado. Devuelve 1 si hay overbooking y 0 si no lo hay.
void handlerEncargado(int s)
{

	printf("ENCARGADO: Calculando si hay overbooking.\n");

	sleep(2);
	exit(calculaAleatorios(0, 1));
}

// Manejadora del Asistente. Devuelve un número de pasajeros entre 20 y 30.
void handlerAsistente(int s)
{
	sleep(calculaAleatorios(3, 6));
	exit(calculaAleatorios(20, 30));
}

// Crea a los asistentes de vuelo, que esperan hasta recibir una señal de coordinador
void crearAsistentes(pid_t p *asistentes, int n)
{
	pid_t p;

	for (int i = 0; i < n; i++)
	{
		p = fork();

		if (p != 0)
		{
			asistentes[i] = p;
			printf("COORDINADOR: Asistente %d creado.\n", i + 1);
		}
		else
		{
			struct sigaction ss;
			ss.sa_handler = &handlerAsistente;
			ss.sa_flags = 0;
			sigemptyset(&ss.sa_mask);
			if (-1 == sigaction(SIGUSR2, &ss, NULL))
			{
				perror("ASISTENTE: sigaction error\n");
				exit(-1);
			}
			pause();
		}
	}
}

int main(int argc, char *argv[])
{

	int num_asistentes = atoi(argv[1]);
	pid_t *asistentes = malloc(sizeof(int) * num_asistentes);
	pid_t tecnico, encargado;

	printf("COORDINADOR: Inciando simulación.\n");

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
			perror("TECNICO: sigaction error\n");
			exit(-1);
		}
		pause();
	}
	else if (encargado == 0)
	{
		struct sigaction ss;
		ss.sa_handler = &handlerEncargado;
		ss.sa_flags = 0;
		sigemptyset(&ss.sa_mask);
		if (-1 == sigaction(SIGUSR1, &ss, NULL))
		{
			perror("ENCARGADO: sigaction error\n");
			exit(-1);
		}
		pause();
	}
	else if (encargado != 0 && tecnico != 0)
	{

		sleep(1);

		kill(tecnico, SIGUSR1);

		int estado, valido, overbooking, pasajeros = 0;

		sleep(1);

		wait(&estado);
		valido = WEXITSTATUS(estado);

		if (valido == 1)
		{
			printf("COORDINADOR: El vuelo es viable.\n");
			kill(encargado, SIGUSR1);

			wait(&estado);
			overbooking = WEXITSTATUS(estado);

			if (overbooking == 1)
			{
				printf("ENCARGADO: Hay overbooking.\n");
			}

			crearAsistentes(asistentes, num_asistentes);
			sleep(2);

			for (int i = 0; i < num_asistentes; i++)
			{
				kill(asistentes[i], SIGUSR2);
			}

			for (int i = 0; i < num_asistentes; i++)
			{
				wait(&estado);
				pasajeros = pasajeros + WEXITSTATUS(estado);
			}

			if (overbooking == 1)
				pasajeros = pasajeros - 10;

			printf("COORDINADOR: El número de pasajeros es %d\n\n", pasajeros);
		}
		else if (valido == 0)
		{
			printf("COORDINADOR: El vuelo no es viable.\n");
			kill(tecnico, SIGKILL);
			kill(encargado, SIGKILL);
		}
	}

	return 0;
}
