#ifndef SHELL_H
#define SHELL_H

#define TRUE 0
#define FALSE 1

typedef int bool;

#define MAX_HIS 4026
#define MAX_ARGS 50
#define INPUTVAL 512

void history(char *tokens[], char *history[], int count);
int hischeck(char *input, int count, char *history);
void hiswrite(char *filename, char *history[MAX_HIS]);


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
int print_env(char **str, list_t *env);
char *get_env(char *str, list_t *env);
int _atoi(char *array);
char *_atoi2(int number);
int __execv(char **s, list_t *env, int num);
int __exit(char **str, list_t *env, int num, char **command);
int _cd(char **str, list_t *env, int num);
void failed_cd(char *str, int c_n, list_t *env);
void _unavailable(char *str, int c_n, list_t *env);
void i_number(char *str, int c_n, list_t *env);
int prompt(char **en);
char *_which(char *str, list_t *env);
void free_linked_list(list_t *list);
void free_double_ptr(char **str);
int search_env(char *str, list_t *env);
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
char *c_strdup(char *str, int cs);
int t_strlen(char *str, int pos, char delm);


#endif /* SHELL_H */
