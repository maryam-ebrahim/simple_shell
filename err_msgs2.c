#include "shell.h"

char *error_126(char **argu);
char *error_127(char **argu);

/**
 * error_126 - Creates an error message for permission denied failures.
 * @argu: array of argss that is passed to the cmd
 *
 * Return: error strng
 */

char *error_126(char **argu)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(argu[0]) + 24;
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
	_strcat(error, argu[0]);
	_strcat(error, ": Permission denied\n_si");

	free(hist_str);
	return (error);
}

/**
 * error_127 - a function that creates an error message
 * for cmd not found failures.
 * @argu: array of argss that is passed to the cmd
 *
 * Return: error strng
 */

char *error_127(char **argu)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(argu[0]) + 16;
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
	_strcat(error, argu[0]);
	_strcat(error, ": not found\n_si");

	free(hist_str);
	return (error);
}

