#ifndef SHELL_H
#define SHELL_H

#define TRUE 1
#define FALSE !TRUE

/**
 * struct list - linked list for environmental variables
 * @var: holds environmental variable string
 * @next: points to next node
 */
typedef struct list
{
	char *var;
	struct list *next;

} list_t;


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
void non_interactive(list_t *env);
int interactive(char *av[], int count, char **env);
int print_env(char **str, list_t *env);
int get_env(char *str, list_t *env);
int creat_proc(char *av[], int count, char **env);
int _atoi(char *array);
char *_atoi2(int number);
void _signal(int sig);
char *val_file(char *path_f, char *file);
int manageEnviron(char *args[], int option);
int __execv(char **s, list_t *env, int num);
int __exit(char **str, list_t *env, int num, char **command);
int _cd(char **str, list_t *env, int num);
int prompt(char **en);
char *_which(char *str, list_t *env);
void free_linked_list(list_t *list);
void free_double_ptr(char **str);
int _setenv(list_t **env, char **str);
int _unsetenv(list_t **env, char **str);
size_t print_list(list_t *h);
list_t *add_enode(list_t **head, char *str);
int delete_node_index(list_t **head, int index);
int built_in(char **token, list_t *env, int num, char **command);
list_t *env_linked_list(char **env);
size_t get_line(char **str);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* string utils */
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, char *s2);
char **_strtok(char *str, char *delim);
int _strlen(const char *s);
int _strncmp(const char *s, const char *s2, size_t n);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
char *ignore_delm(char *str, char delm);
char **c_str_tok(char *str, char *delm);
int t_strlen(char *str, int pos, char delm);


#endif /* SHELL_H */
