#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
  * main - Simple UNIX command line interpreter
  * entry point
  * @ac: length of argv array
  * @av: array of arguments passed to main
  * @env: main environment variables
  *
  * Return: Always 0.
  */
int main(int ac, char *av[], char *env[])
{
	int status, read;
	size_t line = 0;
	char *stream = NULL, *token;
	char *argv[] = {NULL, NULL};
	struct stat st;
	pid_t pid;
	(void)ac, (void)av;

	do {
		read = getline(&stream, &line, stdin);
		if (read == -1)
			exit(EXIT_FAILURE);

		token = strtok(stream, "'\n'");
		if (token == NULL)
			exit(EXIT_FAILURE);
		if (stat(token, &st) == -1)
		{
			printf("./shell: No such file or directory\n");
		}
		else
		{
			argv[0] = token;
			pid = fork();
			if (pid == -1)
				exit(EXIT_FAILURE);
			if (pid == 0)
			{
				execve(argv[0], argv, env);
				exit(EXIT_FAILURE);
			}
			free(stream);
			wait(&status);
		}
	} while (stream);

	exit(EXIT_SUCCESS);
}
