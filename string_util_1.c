#include "shell.h"

/**
 * _strncmp - compares two strings
 * @s: first string
 * @s2: second string
 * @n: No of chars
 * Return: difference
 */

int _strncmp(const char *s, const char *s2, size_t n)
{
	int a = 0, b = 0;

	while (n && s[a] && (s[a] == s2[b]))
	{
		a++;
		b++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (s[a] - s2[b]);
}
