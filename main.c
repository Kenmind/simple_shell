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
	char *filename;
	char cwd[256];
	char *history[MAX_HIS];
	int hiscount = 0;
	FILE *fileread;

	(void)ac;
	(void)av;
	(void)history;
	filename = _strcat(getcwd(cwd, sizeof(cwd)), "/.simple_shell_history");
	fileread = fopen(filename, "r");
	hiscount = hischeck(*env, hiscount, *history);

	if (fileread)
	{
		char line[512];

		while ((fgets(line, sizeof(line), fileread) != NULL) && (hiscount < 4026))
		{
			char **str = _strtok(line, "\n");

			history[hiscount] = _strdup(*str);
			hiscount++;
		}
		fclose(fileread);
	}
	prompt(env);
	hiswrite(filename, history);
	return (0);
}
