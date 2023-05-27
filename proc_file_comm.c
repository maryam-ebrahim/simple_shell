/*
 * File: proc_file_comm.c
 *
 *
 */

#include "shell.h"

int cant_open(char *filePath_);
int proc_file_comands(char *filePath_, int *exeRet_);

/**
 * cant_open - If the file doesn't exist or lacks proper
 * permissions, print
 * a canttt open error.
 * @filePath_: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *filePath_)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(historyy);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(filePath_) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, filePath_);
	_strcat(error, "\n_si");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * proc_file_comands - a function that takes a file
 * and attempts to run the cmds stored
 * within.
 * @filePath_: a path to the file.
 * @exeRet_: Return val of the last executed cmd.
 *
 * Return: 127 (If file couldn't be opened)
 *	   -1 (If malloc fails)
 *	   Otherwise (the return value of the last comand ran)
 */

int proc_file_comands(char *filePath_, int *exeRet_)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int oldSize0 = 120;
	char *_line, **argu, **front_;
	char bufer[120];
	int retur;

	historyy = 0;
	file = open(filePath_, O_RDONLY);
	if (file == -1)
	{
		*exeRet_ = cant_open(filePath_);
		return (*exeRet_);
	}
	_line = malloc(sizeof(char) * oldSize0);
	if (!_line)
		return (-1);
	do {
		b_read = read(file, bufer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exeRet_);
		bufer[b_read] = '\0';
		line_size += b_read;
		_line = _realloc(_line, oldSize0, line_size);
		_strcat(_line, bufer);
		oldSize0 = line_size;
	} while (b_read);
	for (i = 0; _line[i] == '\n'; i++)
		_line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (_line[i] == '\n')
		{
			_line[i] = ';';
			for (i += 1; i < line_size && _line[i] == '\n'; i++)
				_line[i] = ' ';
		}
	}
	variable_replacement(&_line, exeRet_);
	handle_line(&_line, line_size);
	argu = _strtok(_line, " ");
	free(_line);
	if (!argu)
		return (0);
	if (check_args(argu) != 0)
	{
		*exeRet_ = 2;
		free_args(argu, argu);
		return (*exeRet_);
	}
	front_ = argu;

	for (i = 0; argu[i]; i++)
	{
		if (_strncmp(argu[i], ";", 1) == 0)
		{
			free(argu[i]);
			argu[i] = NULL;
			retur = call_args(argu, front_, exeRet_);
			argu = &argu[++i];
			i = 0;
		}
	}

	retur = call_args(argu, front_, exeRet_);

	free(front_);
	return (retur);
}

