#include "shell.h"

/**
 * hiswrite - writes the history to a text file
 * @filename: file to write to
 * @history: array of history to write from
 */

void hiswrite(char *filename, char *history[MAX_HIS])
{
	int i;
	FILE *filewrite; /* open and write file in purge && write mode */

	filename = _strcat(filename, "$HOME/.simple_shell_history");
	filewrite = fopen(filename, "w");

	if (filewrite == NULL)
		printf("Error opening history file!\n"), exit(1);
	i = 0;
	while (history[i] != 0)
	{
		fprintf(filewrite, "%s\n", history[i]);
		i++;
		if (1 == MAX_HIS)
			break;
	}
	fclose(filewrite);
}

/**
 * hischeck - checks for history command in input
 * @input: array of input commands
 * @count: history counter
 * @history: history to check
 * Return: total history
 */

int hischeck(char *input, int count, char *history)
{
	if (strstr(input, "\n"))
	{
	}
	else
	{
		if (_strncmp("!", input, 1) != 0 && _strncmp("history", input, 512) != 0)
		{
			if (count == MAX_HIS)
			{
				int i = 0;

				while (i < (count - 1))
				{
					history[i] = history[i + 1];
					i++;
				}
				history = _strdup(input);
			}
			else
			{
				history = _strdup(input);
				count = count + 1;
			}
		}
		else
		{
			if (_strncmp("!!", input, 512) == 0)
			{
				if (history[0] != 0)
					_strcpy(input, history);
				else
					_strcpy(input, history);
			}
			else
				printf("There is no history to run\n");
		}
	}
	return (count);
}

/**
 * history - displays the user command history
 * @tokens: array of command arguments
 * @history: array of history commands
 * @count: history counter
 */

void history(char *tokens[], char *history[], int count)
{
	int j = 0;

	history = malloc(sizeof(char));

	(void)count;

	if (tokens[1] == 0)
	{
		if (history[0] == 0)
			printf("history is empty.\n");
		else
		{
			int k = 0;

			while (history[k] != 0)
			{
				k++;
				if (k == (MAX_HIS))
					break;
			}
			while (history[j] != 0)
			{
				printf("%d. %s\n", (k), history[j]);
				j++;
				k--;
				if (j == MAX_HIS)
					break;
			}
		}
	}
	else
		printf("History does not take parameters\n");
}
