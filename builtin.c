/*
 * File: builtin.c
 * Authors: Asmaa BAHR and Maryam Ebrahim
 */
#include "shell.h"
int (*get_builtin(char *comand))(char **argu, char **front_);
int shellby_exit(char **argu, char **front_);
int shellby_cd(char **argu, char __attribute__((__unused__)) **front_);
int shellby_help(char **argu, char __attribute__((__unused__)) **front_);

/**
 * get_builtin - a function that matches a comand with a corresponding
 *               shellby built_in function.
 * @comand: to match.
 *
 * Return: A pointer function to the corresponding built_in.
 */
int (*get_builtin(char *comand))(char **argu, char **front_)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{ "cd", shellby_cd },
		{ "alias", shellby_alias },
		{ "help", shellby_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, comand) == 0)
			break;
	}
	return (funcs[i].func);
}

/**
 * shellby_exit - a function that causes normal process termination
 *                for the shell_by shell.
 * @argu: array of arguments that contain the value of the exit.
 * @front_: dble pontr to the start of an argumentt
 *
 * Return: -3 (If there is no arguments).
 *         2 (If the given exit value is invalid).
 *         O/w (exits with the given status value).
 *
 * Description: when returning -3, the program exits
 * and goes back to the main function.
 */

int shellby_exit(char **argu, char **front_)
{
	int i, LengthOfInt = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (argu[0])
	{
		if (argu[0][0] == '+')
		{
			i = 1;
			LengthOfInt++;
		}
		for (; argu[0][i]; i++)
		{
			if (i <= LengthOfInt && argu[0][i] >= '0' && argu[0][i] <= '9')
				num = (num * 10) + (argu[0][i] - '0');
			else
				return (create_error(--argu, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--argu, 2));

	argu -= 1;
	free_args(argu, front_);
	free_env();
	free_alias_list(alias22);
	exit(num);
}

/**
 * shellby_cd - function changes current directory of the shell_by process
 * @argu: array of arguments.
 * @front_: double pointer to da beginning of argu.
 *
 * Return: 2 (If the given string is not a directory)
 *         -1 (If an error occurs)
 *         0 (Otherwise)
 */

int shellby_cd(char **argu, char __attribute__((__unused__)) **front_)
{
	char **direcInfo_, *newLine = "\n";
	char *old_pwd = NULL, *pwd = NULL;
	struct stat direc;

	old_pwd = getcwd(old_pwd, 0);
	if (!old_pwd)
		return (-1);

	if (argu[0])
	{
		if (*(argu[0]) == '-' || _strcmp(argu[0], "--") == 0)
		{
			if ((argu[0][1] == '-' && argu[0][2] == '\0') ||
					argu[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(old_pwd);
				return (create_error(argu, 2));
			}
		}
		else
		{
			if (stat(argu[0], &direc) == 0 && S_ISDIR(direc.st_mode)
					&& ((direc.st_mode & S_IXUSR) != 0))
				chdir(argu[0]);
			else
			{
				free(old_pwd);
				return (create_error(argu, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	direcInfo_ = malloc(sizeof(char *) * 2);
	if (!direcInfo_)
		return (-1);

	direcInfo_[0] = "OLDPWD";
	direcInfo_[1] = old_pwd;
	if (shellby_setenv(direcInfo_, direcInfo_) == -1)
		return (-1);

	direcInfo_[0] = "PWD";
	direcInfo_[1] = pwd;
	if (shellby_setenv(direcInfo_, direcInfo_) == -1)
		return (-1);
	if (argu[0] && argu[0][0] == '-' && argu[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, newLine, 1);
	}
	free(old_pwd);
	free(pwd);
	free(direcInfo_);
	return (0);
}

/**
 * shellby_help - a function that displays information
 * about shell_by built_in commands.
 * @argu: array of arguments.
 * @front_: pointer to da beginning of argu.
 *
 * Return: -1 (when an error occurs)
 *         0 (when Otherwise)
 */

int shellby_help(char **argu, char __attribute__((__unused__)) **front_)
{
	if (!argu[0])
		help_all();
	else if (_strcmp(argu[0], "alias") == 0)
		help_alias();
	else if (_strcmp(argu[0], "cd") == 0)
		help_cd();
	else if (_strcmp(argu[0], "exit") == 0)
		help_exit();
	else if (_strcmp(argu[0], "env") == 0)
		help_env();
	else if (_strcmp(argu[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(argu[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(argu[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
