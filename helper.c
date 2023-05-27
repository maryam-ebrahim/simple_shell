/*
 * File: helper.c
 *
 *
 */

#include "shell.h"

void free_args(char **argu, char **front_);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **argu, int *exeRet_);

/**
 * free_args - Frees up memory taken by argu.
 * @argu: A null-terminated double pointer containing comands/arguments.
 * @front_: dble pontr to the start of an argumentt
 */
void free_args(char **argu, char **front_)
{
	size_t i;

	for (i = 0; argu[i] || argu[i + 1]; i++)
		free(argu[i]);

	free(front_);
}

/**
 * get_pid - a function that gets the current id prc
 * Description: open the stat file, a space-delimited file containing
 *              information about the crnt prc. The P_I_D is the
 *              first word in the file. The function reads the P_I_D into
 *              a bufer then replace the space at the end with a \0 byte.
 *
 * Return: current process I_D or NU_LL on failure.
 */

char *get_pid(void)
{
	size_t i = 0;
	char *bufer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant readd file");
		return (NULL);
	}
	bufer = malloc(120);
	if (!bufer)
	{
		close(file);
		return (NULL);
	}
	readd(file, bufer, 120);
	while (bufer[i] != ' ')
		i++;
	bufer[i] = '\0';

	close(file);
	return (bufer);
}

/**
 * get_env_value - a function that gets the value
 * corresponding to env var
 * @beginning: env var to search for.
 * @len: len of the envv varr to search for
 *
 * Return: an empty string (If the variable is not found)
 *         Otherwise (the value of the env var)
 *
 * Description: varss stored in the format VARIABLE=VALUE
 */

char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replace_ment = NULL, *_temp, *variab;

	variab = malloc(len + 1);
	if (!variab)
		return (NULL);
	variab[0] = '\0';
	_strncat(variab, beginning, len);

	var_addr = _getenv(variab);
	free(variab);
	if (var_addr)
	{
		_temp = *var_addr;
		while (*_temp != '=')
			_temp++;
		_temp++;
		replace_ment = malloc(_strlen(_temp) + 1);
		if (replace_ment)
			_strcpy(replace_ment, _temp);
	}

	return (replace_ment);
}

/**
 * variable_replacement - a function that handle varr replace_ment
 * @_line: dbl pntr contain the cmd and argsssss
 * @exeRet_: pntr to return val of last executed cmd.
 *
 * Description: Replaces $$ with the current P_I_D, $? with the return value
 *              of the last executed program, and env varrs
 *              preceded by $ with their corresponding value.
 */

void variable_replacement(char **_line, int *exeRet_)
{
	int j, k = 0, len;
	char *replace_ment = NULL, *old_line = NULL, *newLine;

	old_line = *_line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replace_ment = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replace_ment = _itoa(*exeRet_);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replace_ment = get_env_value(&old_line[j + 1], len);
			}
			newLine = malloc(j + _strlen(replace_ment)
					  + _strlen(&old_line[k]) + 1);
			if (!_line)
				return;
			newLine[0] = '\0';
			_strncat(newLine, old_line, j);
			if (replace_ment)
			{
				_strcat(newLine, replace_ment);
				free(replace_ment);
				replace_ment = NULL;
			}
			_strcat(newLine, &old_line[k]);
			free(old_line);
			*_line = newLine;
			old_line = newLine;
			j = -1;
		}
	}
}

