#include "main.h"

/**
 * main - a very simple shell
 *
 * Return: 0 when successful
 */
int main(int __attribute__((unused)) ac, char __attribute__((unused)) **av, char **env)
{
	char *inputstr = NULL;
	char *fraginputstr[100];
	size_t len = 0;
	char delim[] = " ";
	int i, j, status ;
	ssize_t Firstwrite, nread;
	pid_t my_pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			Firstwrite = write(1, "($) ", 4);
			if (Firstwrite < 0)
				perror("write failed");
		}
		nread = getline(&inputstr, &len, stdin);
		if (nread == -1)
		{
			free(inputstr);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (inputstr[i])
		{
			if (inputstr[i] == '\n')
				inputstr[i] = 0;
			i++;
		}
		
		j = 0;
		fraginputstr[j] = strtok(inputstr, delim);
		while (fraginputstr[j])
		{
			j++;
			fraginputstr[j] = strtok(NULL, delim);
		}

		my_pid = fork();
		if (my_pid == -1)
		{
			free(inputstr);
			exit(EXIT_FAILURE);
		}
		if (my_pid == 0)
		{
			if (execve(fraginputstr[0], fraginputstr, env) == -1)
				perror("./hsh");
		}

		else
		{
			wait(&status);
		}
	}
	return (0);
}
