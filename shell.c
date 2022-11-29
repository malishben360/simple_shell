#include "shell.h"

/**
 * main - Main function where everything starts
 *
 * @argc: Count the number of things that I pass
 * on the command line when I run this program
 * @argv: Array that contains the string values
 * of things that were entered on the command line
 * when I run this program
 *
 * Return: Always 0.
 */

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	char **av = NULL;
	char *i_stdin = NULL;
	int status = 1, e_status = 0;
	size_t size = 0;
	ssize_t n = 0;

	while (status && n != EOF)
	{
		size = 0;
		status = isatty(STDIN_FILENO);

		if (status)
			write(STDOUT_FILENO, "", 0);
		signal(SIGINT, sigintH); /* ignore Ctrl + c */
		n = getline(&i_stdin, &size, stdin);
		if (n == -1)
		{
			free(i_stdin);
			break;
		}
		if (validate_spaces(i_stdin))
		{
			free(i_stdin);
			continue;
		}
		av = hsh_tokenizer(i_stdin);
		if (*av[0] == '\0')
			continue;
		status = hsh_execute_builtins(av, i_stdin, argv, &e_status);
		free(i_stdin);
		free(av);
	}
	return (0);
}

/**
 * hsh_tokenizer - Function that splits commands with delimiters
 *
 * @input: string what comes from the input
 *
 * Return: double pointer to tokens
 */

char **hsh_tokenizer(char *input)
{
	int buffer_1 = 64, buffer_2 = 0, position = 0;
	char **tokens = malloc(buffer_1 * sizeof(char *));
	char **backup_tokens;
	char delimiters[] = " \n\t";

	if (!tokens)
	{
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	while ((tokens[position] = strtok(input, delimiters)) != NULL)
	{
		position++;

		if (position >= buffer_1)
		{
			buffer_2 = buffer_1 * 2;
			backup_tokens = tokens;
			tokens = _realloc(tokens, buffer_1, buffer_2 * sizeof(char *));
			if (!tokens)
			{
				free(backup_tokens);
				free(tokens);
				fprintf(stderr, "memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		input = NULL;
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * validate_input - Function that validate if path exists
 *
 * @arguments: arguments for command
 * @argv: Array that contains the string values
 * of things that were entered on the command line
 * when I run this program
 * Return: new arguments with complete path
 */

char *validate_input(char **arguments, char **argv)
{
	char *new_arguments, *first, *slash_argument = "/";
	char **tokens_path, holder_env[1024];
	int i = 0;

	if (arguments[0][0] == '/' || arguments[0][0] == '.')
	{
		new_arguments = arguments[0];
		if ((access(new_arguments, F_OK) == -1))
		{
			fprintf(stderr, "%s: No such file or directory\n", argv[0]);
			return ("Fail access");
		}
	}
	else
	{
		strcpy(holder_env, getenv("PATH"));
		tokens_path = tokenizer_path(holder_env);
		while (tokens_path[i])
		{
			first = str_concat(slash_argument, arguments[0]);
			new_arguments = str_concat(tokens_path[i], first);

			if ((access(new_arguments, F_OK) == -1))
			{
				free(new_arguments);
				free(first);
			}
			else
			{
				free(tokens_path);
				free(first);
				return (new_arguments);
			}
			i++;
		}
		free(tokens_path);
		fprintf(stderr, "%s: No such file or directory\n", argv[0]);
		return ("Fail access");
	}
	return (new_arguments);
}

/**
 * tokenizer_path - Function that tokenizer path
 *
 * @input: path
 *
 * Return: Double pointer to tokens of paths
 */

char **tokenizer_path(char *input)
{
	int buffer_1 = 64, buffer_2 = 0, position = 0;
	char **tokens_new = malloc(buffer_1 * sizeof(char *));
	char **backup_tokens_1;
	char delimiters[] = ":";

	if (!tokens_new)
	{
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	while ((tokens_new[position] = strtok(input, delimiters)) != NULL)
	{
		position++;

		if (position >= buffer_1)
		{
			buffer_2 = buffer_1 * 2;
			backup_tokens_1 = tokens_new;
			tokens_new = _realloc(tokens_new, buffer_1, buffer_2 * sizeof(char *));
			if (!tokens_new)
			{
				free(backup_tokens_1);
				free(tokens_new);
				fprintf(stderr, "memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		input = NULL;
	}
	tokens_new[position] = NULL;
	return (tokens_new);
}

/**
 * hsh_execute - Function that executes the commands
 *
 * @arguments: tokens that were previously separated with delimiters
 * @argv: argv
 * @exit_status: exit status
 * Return: Always 1 (success).
 *
 */

int hsh_execute(char **arguments, char **argv, int *exit_status)
{
	pid_t pid;
	int status;
	char *new_arguments;

	new_arguments = validate_input(arguments, argv);
	if (strcmp(new_arguments, "Fail access") == 0)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (execve(new_arguments, arguments, environ) == -1)
		{
			perror("execve fail");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Error forking");
		free(new_arguments);
		return (1);
	}
	else
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status))
			*exit_status = WEXITSTATUS(status);
		if (arguments[0][0] != '/' && arguments[0][0] != '.')
			free(new_arguments);
		return (1);
	}
	return (1);
}
