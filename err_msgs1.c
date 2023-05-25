#include "shell.h"

char *error_env(char **argument);
char *error_1(char **argument);
char *error_2_exit(char **argument);
char *error_2_cd(char **argument);
char *error_2_syntax(char **argument);

/**
 * error_env - a function that creates an error message
 * for shellby_env errors.
 * @argument: array of argss that is passed to the cmd.
 *
 * Return: error string
 */

char *error_env(char **argument)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	argument--;
	len = _strlen(name) + _strlen(hist_str) + _strlen(argument[0]) + 45;
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
	_strcat(error, ": Unable to add/remove from environment\n_si");

	free(hist_str);
	return (error);
}

/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @argument: array of argss that is passed to the cmd
 *
 * Return: error strng
 */

char *error_1(char **argument)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(argument[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, argument[0]);
	_strcat(error, " not found\n_si");

	return (error);
}

/**
 * error_2_exit - a function that creates error message
 * for shell_by_exit errors.
 * @argument: array of argss that is passed to the cmd.
 *
 * Return: error strng
 */

char *error_2_exit(char **argument)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(argument[0]) + 27;
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
	_strcat(error, argument[0]);
	_strcat(error, "\n_si");

	free(hist_str);
	return (error);
}

/**
 * error_2_cd - a function that creates error message
 * for shell_by_cd errors.
 * @argument: array of argss passed to the cmd
 *
 * Return: error strng
 */

char *error_2_cd(char **argument)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	if (argument[0][0] == '-')
		argument[0][2] = '\0';
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
	if (argument[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, argument[0]);
	_strcat(error, "\n_si");

	free(hist_str);
	return (error);
}

/**
 * error_2_syntax - a function that creates
 * error message for syntax errors.
 * @argument: array of argss that is passed to the comand.
 *
 * Return: error strng
 */

char *error_2_syntax(char **argument)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(argument[0]) + 33;
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
	_strcat(error, argument[0]);
	_strcat(error, "\" unexpected\n_si");

	free(hist_str);
	return (error);
}
