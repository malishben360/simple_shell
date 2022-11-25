#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;
int shell_execute(char **args, char **argv, int *exit_status);

#endif /* MAIN_H */
