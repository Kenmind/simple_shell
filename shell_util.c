#include "shell.h"

/**
 * _signal - checks the parameters/arguments
 * @sig: signal index
 * Return: void
 */

void _signal(int sig)
{
	if (sig)
		write(STDIN_FILENO, "\n#shell$ ", 9);
}

/**
 * val_file - checks if the file exists int a directory
 * @path_f: environment variable path
 * @file: command name
 * Return: the path to the file
 */

char *val_file(char *path_f, char *file)
{
	struct stat st;
	char *path_name, *tok = NULL;
	int i = 0;

	tok = strtok(path_f, ":");

	while (tok != NULL)
	{
		path_name = malloc((_strlen(tok) + _strlen(file) + 2) * sizeof(char));
		if (path_name == NULL)
		{
			free(path_name);
			return (file);
		}
		_strcpy(path_name, tok);
		_strcat(path_name, "/");
		_strcat(path_name, file);
		if (stat(path_name, &st) == 0)
		{
			return (path_name);
		}
		free(path_name);
		tok = strtok(NULL, ":");
		i++;
	}
	return (NULL);
}

/**
 * _which - fleshes out command by appending it to a matching PATH directory
 * @str: first command user typed into shell (e.g. "ls" if user typed "ls -l")
 * @env: environmental variable
 * Return: a copy of fleshed out command (e.g. "/bin/ls" if originally "ls")
 */
char *_which(char *str, list_t *env)
{
	int pth = 0;
	char **toks, *cat = NULL, *pth2 = NULL;
	int i = 0;

	/* get and tokenize PATH directories, then free original string */
	pth = get_env("PATH", env);
	pth2 = _atoi2(pth);
	toks = _strtok(pth2, ":");
	free(pth2);

	/* append "/cmd" to each token to see it's legit */
	i = 0;
	while (toks[i] != NULL)
	{
		if (toks[i][0] == '\0')
			cat = getcwd(cat, 0);
		else
			cat = _strdup(toks[i]);
		cat = _strcat(cat, "/");
		cat = _strcat(cat, str);
		if (access(cat, F_OK) == 0)
		{
			/* free tokens before returning legit fleshed path */
			free_double_ptr(toks);
			return (cat);
		}
		free(cat); /* free concatenated string if cmd is never found */
		i++;
	}
	free_double_ptr(toks);
	return (str); /* return string if not found; won't pass execve */
}


/**
 * numlen - counts number of 0s in a tens power number
 * @n: number
 * Return: returns count of digits
 */
int numlen(int n)
{
	int count = 0;
	int num = n;

	while (num > 9 || num < -9)
	{
		num /= 10;
		count++;
	}
	return (count);
}
/**
 * _atoi2 - turns an int into a string
 * @number: int
 * Return: returns the int as a string. returns NULL if failed
 */

char *_atoi2(int number)
{
	int digits, tens, i = 0, t = 0, x;
	char *res;

	digits = number;
	tens = 1;

	if (number < 0)
		t = 1;
	res = malloc(sizeof(char) * (numlen(digits) + 2 + t));
	if (res == NULL)
		return (NULL);
	if (number < 0)
	{
		res[i] = '-';
		i++;
	}
	for (x = 0; digits > 9 || digits < -9; x++)
	{
		digits /= 10;
		tens *= 10;
	}
	for (digits = number; x >= 0; x--)
	{
		if (digits < 0)
		{
			res[i] = (digits / tens) * -1 + '0';
			i++;
		}
		else
		{
			res[i] = (digits / tens) + '0';
			i++;
		}
		digits %= tens;
		tens /= 10;
	}
	res[i] = '\0';
	return (res);
}
