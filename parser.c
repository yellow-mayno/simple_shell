#include "shell.h"

/**
 * is_cmd - the function determines if a file is an executable command
 * @info: The info structure
 * @path: The path to file
 * Return: 1 if true, 0 otherwise
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - the function duplicates characters
 * @pathstr: The path to string
 * @start: The starting index
 * @stop: The stopping index
 * Return: pointer to new buffer
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int x = 0, z = 0;

	for (z = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buf[z++] = pathstr[x];
	buf[z] = 0;
	return (buf);
}

/**
 * find_path - the function finds this command in the path string
 * @info: The info structure
 * @pathstr: The path string
 * @cmd: The command to be found
 * Return: Full path command if found or NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int x = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			path = dup_chars(pathstr, curr_pos, x);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[x])
				break;
			curr_pos = x;
		}
		x++;
	}
	return (NULL);
}
