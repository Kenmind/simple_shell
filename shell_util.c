#include <shell.h>

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
		path_name = malloc((_strlen(token) + _strlen(file) + 2) * sizeof(char));
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
 * gets_env - gets the varriable environment
 * @name: names the varriable environment
 * @env: the global environment
 * Return: char env
 */

char *gets_env(char *name, char **env)
{
	char *tok1 = NULL, *tok2 = NULL, *env_name = NULL, *cur_env = NULL;
	int i = 0;

	env_name = _strdup(name);

	while (env[i] && env)
	{
		cur_env = NULL;
		tok2 = NULL;
		cur_env = _strdup(env[i]);
		tok1 = strtok(cur_env, "=");
		tok2 = _strdup(strtok(NULL, "="));
		if (_strcmp(env_name, tok1) == 0)
		{
			break;
		}
		free(cur_env);
		free(tok2);
		i++;
	}
	free(cur_env);
	cur_env = NULL;
	free(env_name);
	return (tok2);
}

/**
 * creat_proc - creates and executes a child process
 * @av: ptr to array of args from the input buffer
 * @count: counts all executions at each position
 * @env: varriable environment
 * Return: 0
 */

int creat_proc(char *av[], int count, char **env)
{
	char *path = NULL, *file = NULL, error_msg[100];
	int sta = 0, found = 0, alloc = 0, exit_status = 0;
	pid_t child_pid;
	struct stat st;

	if (stat(av[1], &st) == 0)
		found = 1, file = av[1];
	else
	{
		path = gets_env("PATH", env), file = val_file(path, av[1]);
		if (file != NULL)
			found = 1, alloc = 1;
		free(path);
	}
	if (found)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			if ((execve(file, (av + 1), env)) == -1)
			{
				sprintf(error_msg, "%s: %d: %s: not found\n", av[0], count, av[1]);
				write(2, error_msg, _strlen(error_msg));
				(alloc == 1) ? free(file) : (void) alloc;
			}
		}
		waitpid(child_pid, &sta, 0), (alloc == 1) ? free(file) : (void) alloc;
		if (WIFEXITED(sta))
		{
			exit_status = WEXITSTATUS(sta);
			return (exit_status);
		}
	} else
	{
		sprintf(error_msg, "%s: %d: %s: not found\n", av[0], count, av[1]);
		write(2, error_msg, _strlen(error_msg));
		return (127);
	}
	return (0);
}

/**
 * print_env - prints environment global variable
 * @env: variable to print
 * Return: EXIT SUCCESS
 */

int print_env(char **env)
{
	int i = 0;

	for (i = 0; env[i] != NULL; i++)
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
