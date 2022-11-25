#include "main.h"

/**
  * main - Simple UNIX command line interpreter
  * entry point
  * @ac: length of argv array
  * @av: array of arguments passed to main
  *
  * Return: Always 0.
  */
int main(int ac, char *av[])
{
	char *stream, *token;
	char *argv[] = {NULL, NULL};
	struct stat st;
	size_t line;
	ssize_t read;
	int exit_status = 0, status_return = 1;
	(void)ac;

	while (status_return && read != EOF)
	{
		stream = NULL, line = 0;
		status_return = isatty(STDIN_FILENO);
		read = getline(&stream, &line, stdin);
		if (read == -1)
		{
			free(stream);
			break;
		}

		token = strtok(stream, "'\n'");
		if (token == NULL)
		{
			free(stream);
			continue;
		}
		if (stat(token, &st) == -1)
		{
			printf("%s: 1: %s: not found\n", av[0], token);
		}
		else
		{
			argv[0] = token;
			status_return = shell_execute(argv, av, &exit_status);
			free(stream);
		}
	}

	return (0);
}
