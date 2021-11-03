#include "shell.h"

/**
 * main - main function for creating a shell
 * @ac: records the number of arguments
 * @av: array of arguments
 * @env: environment variable system
 * Return: 0
 */

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	prompt(env);

	return (0);
}
