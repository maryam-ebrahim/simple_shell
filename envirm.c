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
	char **new_envirm;
	size_t size;
	int indx;

	for (size = 0; envirm[size]; size++)
		;

	new_envirm = malloc(sizeof(char *) * (size + 1));
	if (!new_envirm)
		return (NULL);

	for (indx = 0; envirm[indx]; indx++)
	{
		new_envirm[indx] = malloc(_strlen(envirm[indx]) + 1);

		if (!new_envirm[indx])
		{
			for (indx--; indx >= 0; indx--)
				free(new_envirm[indx]);
			free(new_envirm);
			return (NULL);
		}
		_strcpy(new_envirm[indx], envirm[indx]);
	}
	new_envirm[indx] = NULL;

	return (new_envirm);
}

/**
 * free_env - a function that frees the envv copy
 */

void free_env(void)
{
	int indx;

	for (indx = 0; envirm[indx]; indx++)
		free(envirm[indx]);
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
	int indx, len;

	len = _strlen(variab);
	for (indx = 0; envirm[indx]; indx++)
	{
		if (_strncmp(variab, envirm[indx], len) == 0)
			return (&envirm[indx]);
	}

	return (NULL);
}
