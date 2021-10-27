#ifndef SHELL_H
#define SHELL_H
#define _GNU_SOURCE

/* import standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* shell utils */
int non_interactive(char **av);
int interactive(char *av[], int count, char **env);
int print_env(char **env);
char *gets_env(char *name, char **env);
int creat_proc(char *av[], int count, char **env);
int f_exit(char *line, int status, char *av, int count);
int _atoi(char *array);
void _signal(int sig);
char *val_file(char *path_f, char *file);

/* mem/buff utils */
void *_alloc(unsigned int nmem, int size);
char *_memset(char *s, char a, unsigned int n);
unsigned int len_arr(char **p);

/* string utils */
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, char *s2);
char *_strtok(char *str, const char *delim);
int _strlen(const char *s);
int _strncmp(const char *s, const char *s2, size_t n);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);

#endif /* SHELL_H */
