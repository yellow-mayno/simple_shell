#include "shell.h"

/**
 * get_history_file - the function returns history
 * @struc: var struct info containig informations.
 * Return: a string with histroy
 */

char *get_history_file(info_t *struc)
{
	char *ch1, *ch2;

	ch2 = _getenv(struc, "HOME=");
	if (!ch2)
		return (NULL);
	ch1 = malloc(sizeof(char) * (_strlen(ch2) + _strlen(HIST_FILE) + 2));
	if (!ch1)
		return (NULL);
	ch1[0] = 0;
	_strcpy(ch1, ch2);
	_strcat(ch1, "/");
	_strcat(ch1, HIST_FILE);
	return (ch1);
}

/**
 * write_history - the function writes the file containing history
 * @struc: var struct info containig informations.
 * Return: 1 on success -1 otherwise
 */
int write_history(info_t *struc)
{
	ssize_t fd;
	char *path = get_history_file(struc);
	list_t *node = NULL;

	if (!path)
		return (-1);

	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(path);
	if (fd == -1)
		return (-1);
	for (node = struc->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @struc: var struct info containig informations.
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *struc)
{
	int x, last = 0, cnt = 0;
	ssize_t fd, lenght, size = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(struc);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		size = st.st_size;
	if (size < 2)
		return (0);
	buf = malloc(sizeof(char) * (size + 1));
	if (!buf)
		return (0);
	lenght = read(fd, buf, size);
	buf[size] = 0;
	if (lenght <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < size; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			build_history_list(struc, buf + last, cnt++);
			last = x + 1;
		}
	if (last != x)
		build_history_list(struc, buf + last, cnt++);
	free(buf);
	struc->histcount = cnt;
	while (struc->histcount-- >= HIST_MAX)
		delete_node_at_index(&(struc->history), 0);
	renumber_history(struc);
	return (struc->histcount);
}

/**
 * build_history_list - the function creates entry to a history
 * @stru: var struct info containig informations.
 * @buffer: buffer
 * @cnt: linecount
 *
 * Return: Always 0
 */
int build_history_list(info_t *stru, char *buffer, int cnt)
{
	list_t *node = NULL;

	if (stru->history)
		node = stru->history;
	add_node_end(&node, buffer, cnt);

	if (!stru->history)
		stru->history = node;
	return (0);
}

/**
 * renumber_history - the function renumbers the history
 * @stru: var struct info containig informations.
 * Return: the count
 */
int renumber_history(info_t *stru)
{
	list_t *node = stru->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (stru->histcount = x);
}


