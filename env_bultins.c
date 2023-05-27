#include "shell.h"

int shellby_env(char **argu, char __attribute__((__unused__)) **front_);
int shellby_setenv(char **argu, char __attribute__((__unused__)) **front_);
int shellby_unsetenv(char **argu, char __attribute__((__unused__)) **front_);

/**
 * shellby_env - a function that prints the current env environemnt.
 * @argu: array of argus passed to the shell
 * @front_: double pointer to the start of argu.
 *
 * Return: -1 (when error occures)
 *	   0 (when otherwise)
 *
 * Description: prints one variable in each line in the
 *              format 'variable'='value'.
 */

int shellby_env(char **argu, char __attribute__((__unused__)) **front_)
{
	int indx;
	char nnc = '\n';

	if (!envirm)
		return (-1);

	for (indx = 0; envirm[indx]; indx++)
	{
		write(STDOUT_FILENO, envirm[indx], _strlen(envirm[indx]));
		write(STDOUT_FILENO, &nnc, 1);
	}

	(void)argu;
	return (0);
}

/**
 * shellby_setenv - a function that changes or adds an env variable to the PATH
 * @argu: array of argus that is passed to the shell
 * @front_: double pointer to da beginning of argu
 * Description: argu[1] da name of new or an existing PATH variable
 *              argu[2] da value to set new or a changed variable to
 *
 * Return: -1 (when error occures)
 *         0 (when otherwise)
 */

int shellby_setenv(char **argu, char __attribute__((__unused__)) **front_)
{
	char **env_var = NULL, **new_envirm, *NewValue;
	size_t size;
	int indx;

	if (!argu[0] || !argu[1])
		return (create_error(argu, -1));

	NewValue = malloc(_strlen(argu[0]) + 1 + _strlen(argu[1]) + 1);
	if (!NewValue)
		return (create_error(argu, -1));
	_strcpy(NewValue, argu[0]);
	_strcat(NewValue, "=");
	_strcat(NewValue, argu[1]);

	env_var = _getenv(argu[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = NewValue;
		return (0);
	}
	for (size = 0; envirm[size]; size++)
		;

	new_envirm = malloc(sizeof(char *) * (size + 2));
	if (!new_envirm)
	{
		free(NewValue);
		return (create_error(argu, -1));
	}

	for (indx = 0; envirm[indx]; indx++)
		new_envirm[indx] = envirm[indx];

	free(envirm);
	envirm = new_envirm;
	envirm[indx] = NewValue;
	envirm[indx + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - a function that deletes an env variable from the PATH
 * @argu: array of args that is pased to shell
 * @front_: dble pontr to the start of an argut
 * Description: argu[1] is the PATH variable to remove
 *
 * Return: -1 (when error occures)
 *         0 (when otherwise)
 */

int shellby_unsetenv(char **argu, char __attribute__((__unused__)) **front_)
{
	char **env_var, **new_envirm;
	size_t size;
	int indx, indx2;

	if (!argu[0])
		return (create_error(argu, -1));
	env_var = _getenv(argu[0]);
	if (!env_var)
		return (0);

	for (size = 0; envirm[size]; size++)
		;

	new_envirm = malloc(sizeof(char *) * size);
	if (!new_envirm)
		return (create_error(argu, -1));

	for (indx = 0, indx2 = 0; envirm[indx]; indx++)
	{
		if (*env_var == envirm[indx])
		{
			free(*env_var);
			continue;
		}
		new_envirm[indx2] = envirm[indx];
		indx2++;
	}
	free(envirm);
	envirm = new_envirm;
	envirm[size - 1] = NULL;

	return (0);
}
