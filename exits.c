#include "shell.h"

/**
 **_strncpy - the function copies a contains of char *
 *@str1: string1
 *@str2: string2
 *@nbr: number of characters
 *Return: result
 */
char *_strncpy(char *str1, char *str2, int nbr)
{
	int x, y;
	char *s = str1;

	x = 0;
	while (str2[x] != '\0' && x < nbr - 1)
	{
		str1[x] = str2[x];
		x++;
	}
	if (x < nbr)
	{
		y = x;
		while (y < nbr)
		{
			str1[y] = '\0';
			y++;
		}
	}
	return (s);
}

/**
 **_strncat - the function cats two char *
 *@str1: string1
 *@str2: string2
 *@nbr: number of chars
 *Return: the result string
 */
char *_strncat(char *str1, char *str2, int nbr)
{
	int x, y;
	char *s = str1;

	x = 0;
	y = 0;
	while (str1[x] != '\0')
		x++;
	while (str2[y] != '\0' && y < nbr)
	{
		str1[x] = str2[y];
		x++;
		y++;
	}
	if (y < nbr)
		str1[x] = '\0';
	return (s);
}

/**
 **_strchr - the function search for a char
 *@str1: string1
 *@ch: char to look for
 *Return: pointer to ch if found in str1
 */
char *_strchr(char *str1, char ch)
{
	do {
		if (*str1 == ch)
			return (str1);
	} while (*str1++ != '\0');

	return (NULL);
}


