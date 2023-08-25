#include "main.h"
int create_process(char *fraginputstr[], char *const envp[]);

/**
 * main - a very simple shell
 *
 * Return: 0 when successful
 */
int main(void)
{
	char *inputstr, *const envp[] = {NULL};
	char *fraginputstr[1000];
	size_t len = 100;

	while (1)
	{
		char delim[] = " \n\t";
		int y = 0, nread;
		ssize_t Firstwrite;

		if (isatty(STDIN_FILENO) || isatty(STDOUT_FILENO))
		{
			Firstwrite = write(1, "($) ", 4);
			if (Firstwrite < 0)
				perror("write failed");
		}
		nread = getline(&inputstr, &len, stdin);
		if (nread > 0)
		{
			y = 0;
			fraginputstr[y] = strtok(inputstr, delim);
			while (fraginputstr[y] != NULL)
			{
				y++;
				fraginputstr[y] = strtok(NULL, delim);
			}
		}
		else /* Check for custom EOF i.e Crtl+D */
		{
			write(1, "\n", 1);
			exit(0);
		}

		if (create_process(fraginputstr, envp) != 0)
			perror("./hsh");
		else
			wait(NULL);
	}
	return (0);
}

/**
 * create_process - creates a child process
 * @fraginputstr: fragmented input string
 * @envp: process environ
 *
 * Return: 1 error, 0 success
 */
int create_process(char *fraginputstr[], char *const envp[])
{
	pid_t my_pid = 1;
	int u = 0;
	char *arr[] = {NULL};

	my_pid = fork();
	if (my_pid == -1)
	{
		perror("fork failed");
		return (0);
	}
	else if (my_pid == 0)
	{
		while (fraginputstr[u] != NULL)
		{
			u++;
		}
		if (u == 1)
		{
			if (execve(fraginputstr[0], arr, envp) < 0)
				perror("./hsh");
		}
		else if (execve(fraginputstr[0], fraginputstr, envp) < 0)
			perror("./hsh");
		exit(0);
	}

	return (0);
}
