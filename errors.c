#include "shell.h"

/**
 * _eputs - the function prints an input string
 * @str: The string that must be printed
 * Return: Nothing
 */

void _eputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}

/**
 * _eputchar - the function writes the character c to stderr
 * @c: The character that must be printed
 * Return: on success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * _putfd - the function writes the character c to given filedescriptor
 * @c: The character that must be printed
 * @fd: The filedescriptor to be writed to
 * Return: on success 1
 * On error, -1 is returned, and errno is set appropriately
 */

int _putfd(char c, int fd)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * _putsfd - the function prints an input string
 * @str: The string that must be printed
 * @fd: The filedescriptor to be writed to
 * Return: The number of charcters put
 */

int _putsfd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += _putfd(*str++, fd);
	}
	return (x);
}

