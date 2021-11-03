#include "shell.h"

/**
 * _atoi - converts string to int
 * @array: string to convert
 * Return: converted array
 */

int _atoi(char *array)
{
	int i = 0, conv = 0;

	for (i = 0; array[i] != '\0'; i++)
	{
		conv = conv * 10 + array[i] - '0';
	}
	return (conv);
}

/**
 * c_ignore - custom ignores spaces and newlines
 * (e.g. echo "ls\n ls" | ./a.out)
 * @str: envrionmental variables
 * Return: new string
 */
char *c_ignore(char *str)
{
	while (*str == ' ' || *str == '\n')
		str++;
	return (str);
}

/**
 * non_interactive - handles when user pipes commands into shell via pipeline
 * (e.g. echo "ls/nls -al/n" | ./a.out)
 * @env: envrionmental variables
 */
void non_interactive(list_t *env)
{
	size_t i = 0, n = 0;
	int command_line_no = 0, exit_stat = 0;
	char *command = NULL, *n_command = NULL, **n_line, **token;

	i = get_line(&command);
	if (i == 0)
	{
		free(command);
		exit(0);
	}
	n_command = command;
	command = c_ignore(command);
	n_line = _strtok(command, "\n"); /* tokenize each command string */
	if (n_command != NULL)
		free(n_command);
	n = 0;
	while (n_line[n] != NULL)
	{
		command_line_no++;
		token = NULL; /* tokenize each command in array of commands */
		token = _strtok(n_line[n], " ");
		exit_stat = built_in(token, env, command_line_no, n_line);
		if (exit_stat)
		{
			n++;
			continue;
		}
		exit_stat = __execv(token, env, command_line_no);
		n++;
	}
	free_double_ptr(n_line);
	free_linked_list(env);
	exit(exit_stat);
}


/**
 * get_line - stores into malloced buffer the user's command into shell
 * @str: buffer
 * Return: number of characters read
 */
size_t get_line(char **str)
{
	ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
	char buff[1024];

	/* read while there's stdin greater than buffsize; -1 to add a '\0' */
	while (t2 == 0 && (i = read(STDIN_FILENO, buff, 1024 - 1)))
	{
		if (i == -1) /* check if read errored */
			return (-1);

		buff[i] = '\0'; /* terminate buff with \0 to use with _strcat */

		n = 0; /* last loop if \n is found in the stdin read */
		while (buff[n] != '\0')
		{
			if (buff[n] == '\n')
				t2 = 1;
			n++;
		}

		/* copy what's read to buff into get_line's buffer */
		if (t == 0) /* malloc the first time */
		{
			i++;
			*str = malloc(sizeof(char) * i);
			*str = _strcpy(*str, buff);
			size = i;
			t = 1;
		}
		else /* _realloc via _strcat with each loop */
		{
			size += i;
			*str = _strcat(*str, buff);
		}
	}
	return (size);
}

/**
 * free_double_ptr - free malloced arrays
 * @str: array of strings
 */
void free_double_ptr(char **str)
{
	int i = 0;

	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
