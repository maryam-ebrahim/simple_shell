#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **new_envirm;
	size_t size;
	int index;

	for (size = 0; envirm[size]; size++)
		;

	new_envirm = malloc(sizeof(char *) * (size + 1));
	if (!new_envirm)
		return (NULL);

	for (index = 0; envirm[index]; index++)
	{
		new_envirm[index] = malloc(_strlen(envirm[index]) + 1);

		if (!new_envirm[index])
		{
			for (index--; index >= 0; index--)
				free(new_envirm[index]);
			free(new_envirm);
			return (NULL);
		}
		_strcpy(new_envirm[index], envirm[index]);
	}
	new_envirm[index] = NULL;

	return (new_envirm);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int index;

	for (index = 0; envirm[index]; index++)
		free(envirm[index]);
	free(envirm);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *var)
{
	int index, len;

	len = _strlen(var);
	for (index = 0; envirm[index]; index++)
	{
		if (_strncmp(var, envirm[index], len) == 0)
			return (&envirm[index]);
	}

	return (NULL);
}
