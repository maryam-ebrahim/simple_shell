/*
 * File: main.c
 *
 *
 */

#include "shell.h"

void sig_handler(int sign_al);
int execute(char **argument, char **front_);

/**
 * sig_handler - a function that prints
 * a new prom_pt upon a signal.
 * @sign_al: signal
 */

void sig_handler(int sign_al)
{
	char *NewPrompt = "\n_si$ ";

	(void)sign_al;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, NewPrompt, 3);
}

/**
 * execute - a function that execute a cmd in a chld process
 * @argument: arr_ay of argss
 * @front_: dble pontr to the start of an argumentt
 *
 * Return: a corresponding error code (If an error occurs)
 *         O/w (The exit value of the last executed comand)
 */

int execute(char **argument, char **front_)
{
	pid_t child_pid;
	int status, flag = 0, retur = 0;
	char *comand = argument[0];

	if (comand[0] != '/' && comand[0] != '.')
	{
		flag = 1;
		comand = get_location(comand);
	}

	if (!comand || (access(comand, F_OK) == -1))
	{
		if (errno == EACCES)
			retur = (create_error(argument, 126));
		else
			retur = (create_error(argument, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(comand);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(comand, argument, envirm);
			if (errno == EACCES)
				retur = (create_error(argument, 126));
			free_env();
			free_args(argument, front_);
			free_alias_list(alias22);
			_exit(retur);
		}
		else
		{
			wait(&status);
			retur = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(comand);
	return (retur);
}

/**
 * main - a function that a simple UNIX cmd interpreter
 * @arg_c: num of argss supplied to the program.
 * @arg_v: array of pntrs to the argss.
 *
 * Return: return val of cmd.
 */

int main(int arg_c, char *arg_v[])
{
	int retur = 0, retn;
	int *exeRet_ = &retn;
	char *prom_pt = "$ ", *newLine = "\n_si";

	name = arg_v[0];
	historyy = 1;
	alias22 = NULL;
	signal(SIGINT, sig_handler);

	*exeRet_ = 0;
	envirm = _copyenv();
	if (!envirm)
		exit(-100);

	if (arg_c != 1)
	{
		retur = proc_file_comands(arg_v[1], exeRet_);
		free_env();
		free_alias_list(alias22);
		return (*exeRet_);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (retur != END_OF_FILE && retur != EXIT)
			retur = handle_args(exeRet_);
		free_env();
		free_alias_list(alias22);
		return (*exeRet_);
	}

	while (1)
	{
		write(STDOUT_FILENO, prom_pt, 2);
		retur = handle_args(exeRet_);
		if (retur == END_OF_FILE || retur == EXIT)
		{
			if (retur == END_OF_FILE)
				write(STDOUT_FILENO, newLine, 1);
			free_env();
			free_alias_list(alias22);
			exit(*exeRet_);
		}
	}

	free_env();
	free_alias_list(alias22);
	return (*exeRet_);
}
