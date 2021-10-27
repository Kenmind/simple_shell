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
 * f_exit - returns an exit value
 * @line: buffer
 * @status: status process value
 * @count: counts arguments and executions
 * @av: programme name
 * Return: exit value
 */

int f_exit(char *line, int status, char *av, int count)
{
	char *arg[3], *tmp = NULL, *tok = NULL, msg[100];
	char a = 'a', z = 'z', u_a = 'A', u_z = 'Z', chr = '\0', *args = NULL;
	int ret = 0, i = 0;

	tmp = _strdup(line);
	free(line);
	tok = strtok(tmp, " \t\n\r");

	for (i = 0; tok != NULL; i++)
	{
		arg[i] = tok;
		tok = strtok(NULL, " \t\n\r");
	}
	arg[i] = NULL;
	if (arg[1] == NULL)
	{
		free(tmp);
		return (status);
	}
	args = _strdup(arg[1]);
	if (args)
		chr = *arg[1];
	if ((chr >= a && chr <= z) ||
			(chr >= u_a && chr <= u_z) || (_atoi(args)) < 0)
	{
		sprintf(msg, "%s: %d: exit: Illegal number: %s\n", av, count, arg[1]);
		write(2, msg, _strlen(msg));
		free(tmp), free(args);
		return (2);
	}
	if (args)
	{
		ret = _atoi(arg[1]);
		free(tmp), free(args);
		return (ret);
	}
	free(args);
	free(tmp);
	return (status);
}

/**
 * interactive - gets command line by getline in interactive mode
 * @av: pointer to string with function to execute on the first position
 * @count: counts the number of times a command is executed
 * @env: environmenta variable environment
 * Return: status process value
 */

int interactive(char *av[], int count, char **env)
{
	int interact = 1, status_proc = 0, i = 0, read = 0, ext = 0;
	size_t len = 0;
	char *line = NULL, *arg[32], *tok = NULL;

	isatty(STDIN_FILENO) == 0 ? interact = 0 : interact;
	while (1)
	{
		interact == 1 ? write(STDIN_FILENO, "#shell$ ", 8) : interact;
		read = getline(&line, &len, stdin);
		if (read == EOF)
		{
			free(line), write(STDIN_FILENO, "\n", 1);
			return (status_proc);
		}
		else if (_strncmp(line, "exit\n", 4) == 0)
		{
			ext = f_exit(line, status_proc, av[0], count);
			return (ext);
		}
		else
		{
			if (_strncmp(line, "env\n", 3) == 0)
				status_proc = print_env(env), count++;
			else if (read > 1)
			{
				tok = strtok(line, " \t\n\r"), arg[0] = av[0];
				for (i = 1; i < 32 && tok != NULL; i++)
					arg[i] = tok, tok = strtok(NULL, " \t\n\r"),
					arg[i] = NULL;
				if (arg[i])
					status_proc = creat_proc(arg, count, env);
			}
			count++;
		}
	}
	return (status_proc);
}

/**
 * non_interactive - checks if there is input from the keyboard
 * @av: pointer to string of all arguments from each position of input
 * Return: void
 */

int non_interactive(char **av)
{
	char error_msg[120];

	sprintf(error_msg, "%s: 0: Can't open %s\n", av[0], av[1]);
	write(2, error_msg, _strlen(error_msg));
	return (127);
}


