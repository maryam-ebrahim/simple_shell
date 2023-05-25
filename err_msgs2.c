#include "shell.h"

char *error_126(char **argument);
char *error_127(char **argument);

/**
 * error_126 - Creates an error message for permission denied failures.
 * @argument: array of argss that is passed to the cmd
 *
 * Return: error strng
 */

char *error_126(char **argument)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(argument[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, argument[0]);
	_strcat(error, ": Permission denied\n_si");

	free(hist_str);
	return (error);
}

/**
 * error_127 - a function that creates an error message
 * for cmd not found failures.
 * @argument: array of argss that is passed to the cmd
 *
 * Return: error strng
 */

char *error_127(char **argument)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(argument[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, argument[0]);
	_strcat(error, ": not found\n_si");

	free(hist_str);
	return (error);
}
