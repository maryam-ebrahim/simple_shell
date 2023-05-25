#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *variab);

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: NULL (when an error occures)
 *         O/w (dble pntr to new cpy)
 */
 
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int ind_ex;

	for (size = 0; envirm[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (ind_ex = 0; envirm[ind_ex]; ind_ex++)
	{
		new_environ[ind_ex] = malloc(_strlen(envirm[ind_ex]) + 1);

		if (!new_environ[ind_ex])
		{
			for (ind_ex--; ind_ex >= 0; ind_ex--)
				free(new_environ[ind_ex]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[ind_ex], envirm[ind_ex]);
	}
	new_environ[ind_ex] = NULL;

	return (new_environ);
}

/**
 * free_env - a function that frees the envv copy
 */

void free_env(void)
{
	int ind_ex;

	for (ind_ex = 0; envirm[ind_ex]; ind_ex++)
		free(envirm[ind_ex]);
	free(envirm);
}

/**
 * _getenv - a function that gets an env
 * variable from the PATH.
 * @variab: name of the env variable to get
 *
 * Return: NULL (if the env var doesn't exst)
 *         otherwise (a pointer to the environmental variable)
 */

char **_getenv(const char *variab)
{
	int ind_ex, len;

	len = _strlen(variab);
	for (ind_ex = 0; envirm[ind_ex]; ind_ex++)
	{
		if (_strncmp(variab, envirm[ind_ex], len) == 0)
			return (&envirm[ind_ex]);
	}

	return (NULL);
}
