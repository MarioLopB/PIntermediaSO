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

	printf("[TECNICO] Calculando si el vuelo es viable.\n");

	sleep(calculaAleatorios(3, 6));
	exit(calculaAleatorios(0, 1));
}

// Manejadora del Encargado. Devuelve 1 si hay overbooking y 0 si no lo hay.
void handlerEncargado(int s)
{

	printf("[ENCARGADO] Calculando si hay overbooking.\n");

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
void crearAsistentes(pid_t *asistentes, int n)
{
	pid_t p;

	for (int i = 0; i < n; i++)
	{
		p = fork();

		if (p != 0)
		{
			asistentes[i] = p;
			printf("[COORDINADOR] Asistente %d creado.\n", i + 1);
		}
		else
		{
			struct sigaction ss;
			ss.sa_handler = &handlerAsistente;
			ss.sa_flags = 0;
			sigemptyset(&ss.sa_mask);
			if (-1 == sigaction(SIGUSR2, &ss, NULL))
			{
				perror("[ASISTENTE] ERROR: Sigaction error\n");
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

	printf("[COORDINADOR] Inciando simulación.\n");

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
			perror("[TECNICO] sigaction error\n");
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
			perror("[ENCARGADO] sigaction error\n");
			exit(-1);
		}
		pause();
	}
	else if (encargado != 0 && tecnico != 0)
	{

		sleep(1);

		// Envía una señal al técnico
		kill(tecnico, SIGUSR1);

		int estado, valido, overbooking, pasajeros, totalpasajeros = 0;

		sleep(1);

		//Espera a que el técnico termine.
		wait(&estado);
		valido = WEXITSTATUS(estado);

		// Si el vuelo no es valdio termina los procesos técnico y encargado.
		// En caso contrario, continua el proceso.
		if (valido == 1)
		{
			printf("[COORDINADOR] El vuelo es viable.\n");
			// Envía una señal al encargado.
			kill(encargado, SIGUSR1);

			// Espera a que el encargado termine.
			wait(&estado);
			overbooking = WEXITSTATUS(estado);

			if (overbooking == 1)
			{
				printf("[ENCARGADO] Hay overbooking.\n");
			}
			else
			{
				printf("[ENCARGADO] No hay overbooking\n");
			}

			crearAsistentes(asistentes, num_asistentes);
			sleep(2);

			for (int i = 0; i < num_asistentes; i++)
			{
				kill(asistentes[i], SIGUSR2);
			}

			// Espera a que los asistentes terminen el embarque e imprime los pasajeros
			// por asistente y los pasajeros totales.
			for (int i = 0; i < num_asistentes; i++)
			{
				pid_t currentpid = wait(&estado);
				pasajeros = WEXITSTATUS(estado);
				int currentasis = 0;

				for (int j = 0; j < num_asistentes; j++)
				{
					if (currentpid == asistentes[j])
					{
						currentasis = j;
					}
				}

				printf("[COORDINADOR] EL asistente %d a embarcado %d pasajeros\n", currentasis + 1, pasajeros);

				totalpasajeros = totalpasajeros + pasajeros;
			}

			if (overbooking == 1)
				totalpasajeros = totalpasajeros - 10;

			printf("[COORDINADOR] El número de pasajeros es %d\n\n", totalpasajeros);
		}
		else if (valido == 0)
		{
			printf("[COORDINADOR] El vuelo no es viable.\n");
			kill(tecnico, SIGKILL);
			kill(encargado, SIGKILL);
		}
	}

	return 0;
}
