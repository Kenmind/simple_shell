#include "shell.h"

/**
 * env_list - creates a linked list from environmental variables
 * @env: environmental variables
 * Return: linked list
 */
list_t *env_list(char **env)
{
	list_t *head;
	int i = 0;

	head = NULL;
	while (env[i] != NULL)
	{
		add_enode(&head, env[i]);
		i++;
	}
	return (head);
}

/**
 * print_env - prints environmental variables
 * @str: user's command into shell
 * @env: environmental variables
 * Return: 0 on success
 */
int print_env(char **str, list_t *env)
{
	free_double_ptr(str); /* frees user input */
	print_list(env); /* prints env */
	return (0);
}


/**
 * get_env - find given environmental variable in linked list
 * @env: environmental variable linked list
 * @str: variable name
 * Return: idx of node in linked list
 */
char *get_env(char *str, list_t *env)
{
	int j = 0, index = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == str[j]) /* find desired env variable */
			j++;
		if (str[j] == '\0' && (env->var)[j] == '=')
			/* if matches entirely, break, return idx */
			break;
		env = env->next;
	}
	while (str[index] != '\0')
		index++;
	index++;
	return (c_strdup(env->var, index));
}

/**
 * _unsetenv - remove node in environmental linked list
 * @env: linked list
 * @str: user's typed in command
 * Return: 0 on success
 */
int _unsetenv(list_t **env, char **str)
{
	int index = 0, j = 0;

	if (str[1] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_ptr(str);
		return (-1);
	}
	index = search_env(str[1], *env); /* get idx of node to delete */
	free_double_ptr(str);
	if (index == -1) /* check if index errored */
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	j = delete_node_index(env, index); /* delete node */
	if (j == -1)
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	return (0);
}

/**
 * _setenv - create or modify existing environmental variable in linked list
 * @env: linked list
 * @str: user's typed in command (e.g. "setenv USER Superman")
 * Return: 0 on success, 1 on fail
 */
int _setenv(list_t **env, char **str)
{
	int index = 0, j = 0;
	char *cat;
	list_t *holder;

	if (str[1] == NULL || str[2] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_ptr(str);
		return (-1);
	}
	cat = _strdup(str[1]); /* concatenate strings to be new node data */
	cat = _strcat(cat, "=");
	cat = _strcat(cat, str[2]);
	index = search_env(str[1], *env); /* find idx to traverse to node */
	if (index == -1)
	{
		add_enode(env, cat); /* doesn't exist? create env var */
	}
	else
	{
		holder = *env;
		while (j < index)
		{
			holder = holder->next;
			j++;
		}
		free(holder->var); /* else free malloced data */
		holder->var = _strdup(cat); /* assign to new malloced data */
	}
	free(cat);
	free_double_ptr(str);
	return (0);
}
