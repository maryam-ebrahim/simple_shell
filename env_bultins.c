#include "shell.h"

int shellby_env(char **argu, char __attribute__((__unused__)) **frnt);
int shellby_setenv(char **argu, char __attribute__((__unused__)) **frnt);
int shellby_unsetenv(char **argu, char __attribute__((__unused__)) **frnt);

/**
 * shellby_env - a function that prints the current env environemnt.
 * @argu: array of argus passed to the shell
 * @frnt: double pointer to the start of argu.
 *
 * Return: -1 (when error occures)
 *	   0 (when otherwise)
 *
 * Description: prints one variable in each line in the
 *              format 'variable'='value'.
 */

int shellby_env(char **argu, char __attribute__((__unused__)) **frnt)
{
	int ind_ex;
	char n_c = '\n';

	if (!envirm)
		return (-1);

	for (ind_ex = 0; envirm[ind_ex]; ind_ex++)
	{
		write(STDOUT_FILENO, envirm[ind_ex], _strlen(envirm[ind_ex]));
		write(STDOUT_FILENO, &n_c, 1);
	}

	(void)argu;
	return (0);
}

/**
 * shellby_setenv - a function that changes or adds an env variable to the PATH
 * @argu: array of argus that is passed to the shell
 * @frnt: double pointer to da beginning of argu
 * Description: argu[1] da name of new or an existing PATH variable
 *              argu[2] da value to set new or a changed variable to
 *
 * Return: -1 (when error occures)
 *         0 (when otherwise)
 */

int shellby_setenv(char **argu, char __attribute__((__unused__)) **frnt)
{
	char **env_var = NULL, **new_environ, *NewValue;
	size_t size;
	int ind_ex;

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

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(NewValue);
		return (create_error(argu, -1));
	}

	for (ind_ex = 0; envirm[ind_ex]; ind_ex++)
		new_environ[ind_ex] = envirm[ind_ex];

	free(envirm);
	envirm = new_environ;
	envirm[ind_ex] = NewValue;
	envirm[ind_ex + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - a function that deletes an env variable from the PATH
 * @argu: array of args that is pased to shell
 * @frnt: dble pontr to the start of an argut
 * Description: argu[1] is the PATH variable to remove
 *
 * Return: -1 (when error occures)
 *         0 (when otherwise)
 */

int shellby_unsetenv(char **argu, char __attribute__((__unused__)) **frnt)
{
	char **env_var, **new_environ;
	size_t size;
	int ind_ex, ind_ex2;

	if (!argu[0])
		return (create_error(argu, -1));
	env_var = _getenv(argu[0]);
	if (!env_var)
		return (0);

	for (size = 0; envirm[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(argu, -1));

	for (ind_ex = 0, ind_ex2 = 0; envirm[ind_ex]; ind_ex++)
	{
		if (*env_var == envirm[ind_ex])
		{
			free(*env_var);
			continue;
		}
		new_environ[ind_ex2] = envirm[ind_ex];
		ind_ex2++;
	}
	free(envirm);
	envirm = new_environ;
	envirm[size - 1] = NULL;

	return (0);
}
