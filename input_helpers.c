/*
 * File: input_helpers.c
 *
 *
 */

#include "shell.h"

char *get_args(char *_line, int *exeRet_);
int call_args(char **argu, char **front_, int *exeRet_);
int run_args(char **argu, char **front_, int *exeRet_);
int handle_args(int *exeRet_);
int check_args(char **argu);

/**
 * get_args - a function that gets a cmd from stndrd inpt.
 * @_line: bufer to store the cmd.
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
 * @argu: An array of arguments.
 * @front_: dble pontr to the start of an argumentt
 * @exeRet_: return value of parent process' last executed cmd.
 *
 * Return: return val of cmd.
 */

int call_args(char **argu, char **front_, int *exeRet_)
{
	int retur, ind_ex;

	if (!argu[0])
		return (*exeRet_);
	for (ind_ex = 0; argu[ind_ex]; ind_ex++)
	{
		if (_strncmp(argu[ind_ex], "||", 2) == 0)
		{
			free(argu[ind_ex]);
			argu[ind_ex] = NULL;
			argu = replace_aliases(argu);
			retur = run_args(argu, front_, exeRet_);
			if (*exeRet_ != 0)
			{
				argu = &argu[++ind_ex];
				ind_ex = 0;
			}
			else
			{
				for (ind_ex++; argu[ind_ex]; ind_ex++)
					free(argu[ind_ex]);
				return (retur);
			}
		}
		else if (_strncmp(argu[ind_ex], "&&", 2) == 0)
		{
			free(argu[ind_ex]);
			argu[ind_ex] = NULL;
			argu = replace_aliases(argu);
			retur = run_args(argu, front_, exeRet_);
			if (*exeRet_ == 0)
			{
				argu = &argu[++ind_ex];
				ind_ex = 0;
			}
			else
			{
				for (ind_ex++; argu[ind_ex]; ind_ex++)
					free(argu[ind_ex]);
				return (retur);
			}
		}
	}
	argu = replace_aliases(argu);
	retur = run_args(argu, front_, exeRet_);
	return (retur);
}

/**
 * run_args - a function that calls the execution of a cmd.
 * @argu: array of argsssssss.
 * @front_: dble pontr to the start of an argumentt
 * @exeRet_: return val of parent prcs' last executed cmd.
 *
 * Return: return val of cmd.
 */

int run_args(char **argu, char **front_, int *exeRet_)
{
	int retur, i;
	int (*builtin)(char **argu, char **front_);

	builtin = get_builtin(argu[0]);

	if (builtin)
	{
		retur = builtin(argu + 1, front_);
		if (retur != EXIT)
			*exeRet_ = retur;
	}
	else
	{
		*exeRet_ = execute(argu, front_);
		retur = *exeRet_;
	}

	historyy++;

	for (i = 0; argu[i]; i++)
		free(argu[i]);

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
	char **argu, *_line = NULL, **front_;

	_line = get_args(_line, exeRet_);
	if (!_line)
		return (END_OF_FILE);

	argu = _strtok(_line, " ");
	free(_line);
	if (!argu)
		return (retur);
	if (check_args(argu) != 0)
	{
		*exeRet_ = 2;
		free_args(argu, argu);
		return (*exeRet_);
	}
	front_ = argu;

	for (ind_ex = 0; argu[ind_ex]; ind_ex++)
	{
		if (_strncmp(argu[ind_ex], ";", 1) == 0)
		{
			free(argu[ind_ex]);
			argu[ind_ex] = NULL;
			retur = call_args(argu, front_, exeRet_);
			argu = &argu[++ind_ex];
			ind_ex = 0;
		}
	}
	if (argu)
		retur = call_args(argu, front_, exeRet_);

	free(front_);
	return (retur);
}

/**
 * check_args - a function that checks
 * any leading ';', ';;', '&&', or '||'.
 * @argu: 2D pointer to tokenized com_ands and argss.
 *
 * Return: 2 (If a ';', '&&', or '||' is placed at an invalid position)
 *	   0 (when otherwise)
 */

int check_args(char **argu)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; argu[i]; i++)
	{
		cur = argu[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&argu[i], 2));
			nex = argu[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&argu[i + 1], 2));
		}
	}
	return (0);
}

