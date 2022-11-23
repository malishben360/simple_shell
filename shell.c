#include "main.h"

/**
  * main - Simple UNIX command line interpreter
  * entry point
  * @ac: length of argv array
  * @av: array of arguments passed to main
  * @env: main environment variables
  *
  * Return: Always 0.
  */
int main(int ac, char *av[])
{
	int status, read;
	size_t line;
	char *stream, *token;
	char *argv[] = {NULL, NULL};
	struct stat st;
	pid_t pid;
	(void)ac;

	do {
		stream = NULL, line = 0;
		read = getline(&stream, &line, stdin);
		if (read == -1)
			return (0);

		token = strtok(stream, "'\n'");
		if (token == NULL)
			return (1);
		if (stat(token, &st) == -1)
		{
			printf("%s: 1: %s: not found\n", av[0], token);
		}
		else
		{
			argv[0] = token;
			pid = fork();
			if (pid == -1)
				return (1);
			if (pid == 0)
			{
				execve(argv[0], argv, environ);
				free(stream);
				return (0);
			}
			free(stream);
			wait(&status);
		}
	} while (1);

	return (0);
}
