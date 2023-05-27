#include "shell.h"

char *error_env(char **argu);
char *error_1(char **argu);
char *error_2_exit(char **argu);
char *error_2_cd(char **argu);
char *error_2_syntax(char **argu);

/**
 * error_env - a function that creates an error message
 * for shellby_env errors.
 * @argu: array of argss that is passed to the cmd.
 *
 * Return: error string
 */

char *error_env(char **argu)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	argu--;
	len = _strlen(name) + _strlen(hist_str) + _strlen(argu[0]) + 45;
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
	_strcat(error, ": Unable to add/remove from environment\n_si");

	free(hist_str);
	return (error);
}

/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @argu: array of argss that is passed to the cmd
 *
 * Return: error strng
 */

char *error_1(char **argu)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(argu[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, argu[0]);
	_strcat(error, " not found\n_si");

	return (error);
}

/**
 * error_2_exit - a function that creates error message
 * for shell_by_exit errors.
 * @argu: array of argss that is passed to the cmd.
 *
 * Return: error strng
 */

char *error_2_exit(char **argu)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(argu[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, argu[0]);
	_strcat(error, "\n_si");

	free(hist_str);
	return (error);
}

/**
 * error_2_cd - a function that creates error message
 * for shell_by_cd errors.
 * @argu: array of argss passed to the cmd
 *
 * Return: error strng
 */

char *error_2_cd(char **argu)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	if (argu[0][0] == '-')
		argu[0][2] = '\0';
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
	if (argu[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, argu[0]);
	_strcat(error, "\n_si");

	free(hist_str);
	return (error);
}

/**
 * error_2_syntax - a function that creates
 * error message for syntax errors.
 * @argu: array of argss that is passed to the comand.
 *
 * Return: error strng
 */

char *error_2_syntax(char **argu)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(argu[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, argu[0]);
	_strcat(error, "\" unexpected\n_si");

	free(hist_str);
	return (error);
}

