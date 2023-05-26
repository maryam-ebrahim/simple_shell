/*
 * File: input_helpers.c
 *
 */

#include "shell.h"

char *get_args(char *_line, int *exeRet_);
int call_args(char **argument, char **front_, int *exeRet_);
int run_args(char **argument, char **front_, int *exeRet_);
int handle_args(int *exeRet_);
int check_args(char **argument);

/**
 * get_args - a function that gets a cmd from stndrd inpt.
 * @_line: buf_fer to store the cmd.
 * @exeRet_: return val of last executed cmd.
 *
 * Return: NULL (when an error occures)
 *         Otherwise - a pointer to the stored comand.
 */

char *get_args(char *_line, int *exeRet_)
{
	size_t n_si = 0;
	ssize_t readd;
	char *prom_pt = "$ ";

	if (_line)
		free(_line);

	readd = _getline(&_line, &n_si, STDIN_FILENO);
	if (readd == -1)
		return (NULL);
	if (readd == 1)
	{
		historyy++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prom_pt, 2);
		return (get_args(_line, exeRet_));
	}

	_line[readd - 1] = '\0';
	variable_replacement(&_line, exeRet_);
	handle_line(&_line, readd);

	return (_line);
}

/**
 * call_args - a function that partitions
 * operators from cmdss we calls them.
 * @argument: An array of arguments.
 * @front_: dble pontr to the start of an argumentt
 * @exeRet_: return value of parent process' last executed cmd.
 *
 * Return: return val of cmd.
 */

int call_args(char **argument, char **front_, int *exeRet_)
{
	int retur, ind_ex;

	if (!argument[0])
		return (*exeRet_);
	for (ind_ex = 0; argument[ind_ex]; ind_ex++)
	{
		if (_strncmp(argument[ind_ex], "||", 2) == 0)
		{
			free(argument[ind_ex]);
			argument[ind_ex] = NULL;
			argument = replace_aliases(argument);
			retur = run_args(argument, front_, exeRet_);
			if (*exeRet_ != 0)
			{
				argument = &argument[++ind_ex];
				ind_ex = 0;
			}
			else
			{
				for (ind_ex++; argument[ind_ex]; ind_ex++)
					free(argument[ind_ex]);
				return (retur);
			}
		}
		else if (_strncmp(argument[ind_ex], "&&", 2) == 0)
		{
			free(argument[ind_ex]);
			argument[ind_ex] = NULL;
			argument = replace_aliases(argument);
			retur = run_args(argument, front_, exeRet_);
			if (*exeRet_ == 0)
			{
				argument = &argument[++ind_ex];
				ind_ex = 0;
			}
			else
			{
				for (ind_ex++; argument[ind_ex]; ind_ex++)
					free(argument[ind_ex]);
				return (retur);
			}
		}
	}
	argument = replace_aliases(argument);
	retur = run_args(argument, front_, exeRet_);
	return (retur);
}

/**
 * run_args - a function that calls the execution of a cmd.
 * @argument: array of argsssssss.
 * @front_: dble pontr to the start of an argumentt
 * @exeRet_: return val of parent prcs' last executed cmd.
 *
 * Return: return val of cmd.
 */

int run_args(char **argument, char **front_, int *exeRet_)
{
	int retur, i;
	int (*builtin)(char **argument, char **front_);

	builtin = get_builtin(argument[0]);

	if (builtin)
	{
		retur = builtin(argument + 1, front_);
		if (retur != EXIT)
			*exeRet_ = retur;
	}
	else
	{
		*exeRet_ = execute(argument, front_);
		retur = *exeRet_;
	}

	historyy++;

	for (i = 0; argument[i]; i++)
		free(argument[i]);

	return (retur);
}

/**
 * handle_args - a function that gets, calls
 * and runs the exet of a cmd.
 * @exeRet_: The return value of the parent process' last executed comand.
 *
 * Return: END_OF_FILE (-2) (If an end-of-file is readd)
 *         -1 (If the input cannot be tokenized)
 *         O/w (The exit val of the last exet cmd)
 */

int handle_args(int *exeRet_)
{
	int retur = 0, ind_ex;
	char **argument, *_line = NULL, **front_;

	_line = get_args(_line, exeRet_);
	if (!_line)
		return (END_OF_FILE);

	argument = _strtok(_line, " ");
	free(_line);
	if (!argument)
		return (retur);
	if (check_args(argument) != 0)
	{
		*exeRet_ = 2;
		free_args(argument, argument);
		return (*exeRet_);
	}
	front_ = argument;

	for (ind_ex = 0; argument[ind_ex]; ind_ex++)
	{
		if (_strncmp(argument[ind_ex], ";", 1) == 0)
		{
			free(argument[ind_ex]);
			argument[ind_ex] = NULL;
			retur = call_args(argument, front_, exeRet_);
			argument = &argument[++ind_ex];
			ind_ex = 0;
		}
	}
	if (argument)
		retur = call_args(argument, front_, exeRet_);

	free(front_);
	return (retur);
}

/**
 * check_args - a function that checks
 * any leading ';', ';;', '&&', or '||'.
 * @argument: 2D pointer to tokenized com_ands and argss.
 *
 * Return: 2 (If a ';', '&&', or '||' is placed at an invalid position)
 *	   0 (when otherwise)
 */

int check_args(char **argument)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; argument[i]; i++)
	{
		cur = argument[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&argument[i], 2));
			nex = argument[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&argument[i + 1], 2));
		}
	}
	return (0);
}
