#include "shell.h"

/**
 * _which - fleshes out command by appending it to a matching PATH directory
 * @str: first command user typed into shell (e.g. "ls" if user typed "ls -l")
 * @env: environmental variable
 * Return: a copy of fleshed out command (e.g. "/bin/ls" if originally "ls")
 */
char *_which(char *str, list_t *env)
{
	char *pth, **toks, *cat = NULL;
	int i = 0;

	/* get and tokenize PATH directories, then free original string */
	pth = get_env("PATH", env);
	toks = _strtok(pth, ":");
	free(pth);

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

/**
 * c_strdup - custom string duplication; excludes beginning bytes
 * @str: string to duplicate (e.g. environmental variable PATH=/bin:/bin/ls)
 * @cs: number of bytes to exclude (e.g. excludes "PATH=")
 * Return: string (e.g. /bin:/bin/ls)
 */
char *c_strdup(char *str, int cs)
{
	char *duplicate_str;
	int i, len = 0;

	if (str == NULL) /* validate str input */
		return (NULL);

	/* calculate len + null terminator to malloc */
	while (*(str + len))
		len++;
	len++;

	/* allocate memory but exclude environmental variable title (PATH) */
	duplicate_str = malloc(sizeof(char) * (len - cs));
	if (duplicate_str == NULL)
		return (NULL);

	i = 0;
	while (i < (len - cs))
	{
		*(duplicate_str + i) = *(str + cs + i);
		i++;
	}
	return (duplicate_str);
}
