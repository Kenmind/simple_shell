#include "shell.h"

/**
 * search_env - find given environmental variable in linked list
 * @env: environmental variable linked list
 * @str: variable name
 * Return: idx of node in linked list
 */
int search_env(char *str, list_t *env)
{
	int j = 0, index = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == str[j]) /* find desired env variable */
			j++;
		if (str[j] == '\0') /* if matches entirely, break, return idx */
			break;
		env = env->next;
		index++;
	}
	if (env == NULL)
		return (-1);
	return (index);
}


/**
 * failed_cd - write error ("sh: 2: cd: can't cd to xyz")
 * @str: user's typed argument after the cmd cd
 * @c_n: nth user's typed command
 * @env: bring in environmental variables linked list to write shell name
 */
void failed_cd(char *str, int c_n, list_t *env)
{
	int count = 0;
	char *shell, *num;

	shell = get_env("_", env);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = _atoi2(c_n);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "cd: can't cd to ", 16);
	count = 0;
	while (str[count] != '\0')
		count++;
	write(STDOUT_FILENO, str, count);
	write(STDOUT_FILENO, "\n", 1);
}
