#include "shell.h"

/**
 * main - main function
 * @ac: records the number of arguments
 * @av: array of arguments
 * @env: environment variable system
 * Return: status exit value
 */

int main(int ac, char *av[], char **env)
{
	int count = 1, status_exit = 0;

	_signal(SIGINT);

	if (ac > 1)
	{
		status_exit = non_interactive(av);
		return (status_exit);
	}
	status_exit = interactive(av, count, env);
	return (status_exit);
}
