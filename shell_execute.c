#include "main.h"

/**
  * shell_execute - executes commands
  * @args: shell command and flags in interactive mode
  * @argv: shell command and flags in non interactive mode
  * @exit_status: exit status
  *
  * Return: Always 1 (success).
  */

int shell_execute(char *args[], char *argv[], int *exit_status)
{
	pid_t pid;
	int status;
	(void)argv;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("execve fail");
			free(args);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Error: forking");
		free(args);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (WEXITSTATUS(status))
			*exit_status = WEXITSTATUS(status);
		return (1);
	}
	return (1);
}
