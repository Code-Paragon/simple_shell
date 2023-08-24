#include "main.h"
int create_process(char *fraginputstr[], char *const envp[]);
char **tok_inputstr(char *inputstr, char *fraginputstr[]);
/**
 * main - a very simple shell
 *
 * Return: 0 when successful
 */
int main(void)
{
	char inputstr[1000], *const envp[] = {NULL};
	char *fraginputstr[1000];

	while (1)
	{
		tok_inputstr(inputstr, fraginputstr);
		create_process(fraginputstr, envp);
	}
	return (0);
}
/**
 * tok_inputstr - prints prompt and tokenise inputstr
 * @inputstr: input string
 * @fraginputstr: array of input string
 *
 * Return: fraginputstr on success
 */
char **tok_inputstr(char *inputstr, char *fraginputstr[])
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
	nread = read(0, inputstr, sizeof(inputstr));
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
		free(inputstr);
		write(1, "\n", 1);
		exit(0);
	}
	free(inputstr);
	return (fraginputstr);
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

	my_pid = fork();
	if (my_pid == -1)
	{
		perror("fork failed");
		return (0);
	}
	else if (my_pid == 0)
	{
		if (execve(fraginputstr[0], fraginputstr, envp) != -1)
			perror("./hsh");
		free(fraginputstr);
		exit(0);
	}
	else
		wait(NULL);
	return (0);
}
