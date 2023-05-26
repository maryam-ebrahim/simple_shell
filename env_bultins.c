/*
 * File: env_builtins.c
 * Auth: Asmaa BAHR and Maryam Ebrahim
 */

#include "shell.h"

int shellby_env(char **argument, char __attribute__((__unused__)) **front_);
int shellby_setenv(char **argument, char __attribute__((__unused__)) **front_);
int shellby_unsetenv(char **argument, char __attribute__((__unused__)) **front_);

/**
 * shellby_env - a function that prints the current env environemnt.
 * @argument: array of arguments passed to the shell
 * @front_: double pointer to the start of argument.
 *
 * Return: -1 (when error occures)
 *	   0 (when otherwise)
 *
 * Description: prints one variable in each line in the
 *              format 'variable'='value'.
 */

int shellby_env(char **argument, char __attribute__((__unused__)) **front_)
{
	int ind_ex;
	char n_c = '\n_si';

	if (!envirm)
		return (-1);

	for (ind_ex = 0; envirm[ind_ex]; ind_ex++)
	{
		write(STDOUT_FILENO, envirm[ind_ex], _strlen(envirm[ind_ex]));
		write(STDOUT_FILENO, &n_c, 1);
	}

	(void)argument;
	return (0);
}

/**
 * shellby_setenv - a function that changes or adds an env variable to the PATH
 * @argument: array of arguments that is passed to the shell
 * @front_: double pointer to da beginning of argument
 * Description: argument[1] da name of new or an existing PATH variable
 *              argument[2] da value to set new or a changed variable to
 *
 * Return: -1 (when error occures)
 *         0 (when otherwise)
 */

int shellby_setenv(char **argument, char __attribute__((__unused__)) **front_)
{
	char **env_var = NULL, **new_environ, *NewValue;
	size_t size;
	int ind_ex;

	if (!argument[0] || !argument[1])
		return (create_error(argument, -1));

	NewValue = malloc(_strlen(argument[0]) + 1 + _strlen(argument[1]) + 1);
	if (!NewValue)
		return (create_error(argument, -1));
	_strcpy(NewValue, argument[0]);
	_strcat(NewValue, "=");
	_strcat(NewValue, argument[1]);

	env_var = _getenv(argument[0]);
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
		return (create_error(argument, -1));
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
 * @argument: array of args that is pased to shell
 * @front_: dble pontr to the start of an argumentt
 * Description: argument[1] is the PATH variable to remove
 *
 * Return: -1 (when error occures)
 *         0 (when otherwise)
 */

int shellby_unsetenv(char **argument,char __attribute__((__unused__)) **front_)
{
	char **env_var, **new_environ;
	size_t size;
	int ind_ex, ind_ex2;

	if (!argument[0])
		return (create_error(argument, -1));
	env_var = _getenv(argument[0]);
	if (!env_var)
		return (0);

	for (size = 0; envirm[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(argument, -1));

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
