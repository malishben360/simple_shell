#include "shell.h"

/**
 * sigintH - handles SIGINT (CTRL + C)
 * @signum: signal number caught by signal, 2 for SIGINIT
 * Return: void
 **/

void sigintH(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n#Shell_CL$ ", 11);
	}
}

/**
 * _getenv - Search in environment variable to find a specific variable name
 * @name: environment variable
 * Return: pointer to the corresponding value string
 */

char *_getenv(char *name)
{
	int i = 0;

	while (environ[i])
	{
		if (strcmp(environ[i], name) == 0)
			return (environ[i]);
		++i;
	}
	return (NULL);
}

/**
 *str_concat - funcion that concatenates two strings
 * @s1: array number 1
 * @s2: array number 2
 * Return: pointer to two strings concatenates
 */

char *str_concat(char *s1, char *s2)
{
	char *s;
	unsigned int i;
	unsigned int j;
	unsigned int k;

	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	for (i = 0; s1[i] != '\0'; i++)
		continue;

	for (j = 0; s2[j] != '\0'; j++)
		continue;

	j = j + 1;
	s = malloc((i + j) * sizeof(char));
	if (s == NULL)
		return (0);

	for (k = 0; k < (i + j) ; k++)
	{
		if (k < i)
			s[k] = s1[k];
		if (k >= i)
			s[k] = s2[k - i];
	}
	return (s);
}
