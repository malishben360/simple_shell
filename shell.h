#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

/**
  * struct choos_builtin - Validate the builtin command
  *
  * @name_builtin: name of builtiin command
  *
  * @func_builtin: Pointer to the function of builtin command
  */

typedef struct choose_builtin
{
	char *name_builtin;
	int (*func_builtin)(char **, char *, int *);
} choose_builtins_t;

extern char **environ;

int validate_spaces(char *input);
char **tokenizer_path(char *input);
char *validate_input(char **arguments, char **argv);
char *str_tok(char *buffer, char *d);
int hsh_execute(char **arguments, char **argv, int *exit_status);
char **hsh_tokenizer(char *input);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *str_concat(char *s1, char *s2);
int hsh_exit(char **args, char *input_stdin, int *exit_status);
int hsh_execute_builtins(char **args, char *input_stdin, char **argv, int *exit_status);
int hsh_env(char **args, char *input_stdin, int *exit_status);
int hsh_cd(char **args, char *input_stdin, int *exit_status);
int hsh_setenv(char **args,  char *input_stdin, int *exit_status);
int hsh_unsetenv(char **args,  char *input_stdin, int *exit_status);
char *_getenv(char *name);
void sigintH(int signum);
char *str_concat(char *s1, char *s2);

#endif /* MAIN_H */
