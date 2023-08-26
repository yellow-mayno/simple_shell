#include "shell.h"

/**
 * _myenv - the funciotn display information of environement
 * @struc: var struct info containig informations.
 * Return: 0
 */
int _myenv(info_t *struc)
{
	print_list_str(struc->env);
	return (0);
}

/**
 * _getenv - the function retrieves an environement variable
 * @struc: var struct info containig informations.
 * @var: Name of environement variable
 * Return: a string
 */
char *_getenv(info_t *struc, const char *var)
{
	list_t *node = struc->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - the function change a var of env
 * @struc: var struct info containig informations.
 * Return: 0
 */
int _mysetenv(info_t *struc)
{
	if (struc->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(struc, struc->argv[1], struc->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - the function deletes a variable
 * @struc: var struct info containig informations.
 * Return: 0
 */
int _myunsetenv(info_t *struc)
{
	int x;

	if (struc->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= struc->argc; x++)
		_unsetenv(struc, struc->argv[x]);

	return (0);
}

/**
 * populate_env_list - fills the env array**
  * @struc: var struct info containig informations.
 * Return: 0
 */
int populate_env_list(info_t *struc)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_node_end(&node, environ[x], 0);
	struc->env = node;
	return (0);
}

