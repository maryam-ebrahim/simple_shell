#include "shell.h"

int num_len(int measu_nu);
char *_itoa(int measu_nu);
int create_error(char **argument, int err_or);

/**
 * num_len - a function that counts digit length of a num
 * @measu_nu: num to measure
 *
 * Return: dgt len
 */

int num_len(int measu_nu)
{
	unsigned int num_1;
	int len = 1;

	if (measu_nu < 0)
	{
		len++;
		num_1 = measu_nu * -1;
	}
	else
	{
		num_1 = measu_nu;
	}
	while (num_1 > 9)
	{
		len++;
		num_1 /= 10;
	}

	return (len);
}

/**
 * _itoa - a function that converts int to str.
 * @measu_nu: integer.
 *
 * Return: converted str.
 */

char *_itoa(int measu_nu)
{
	char *buf_fer;
	int len = num_len(measu_nu);
	unsigned int num_1;

	buf_fer = malloc(sizeof(char) * (len + 1));
	if (!buf_fer)
		return (NULL);

	buf_fer[len] = '\0';

	if (measu_nu < 0)
	{
		num_1 = measu_nu * -1;
		buf_fer[0] = '-';
	}
	else
	{
		num_1 = measu_nu;
	}

	len--;
	do {
		buf_fer[len] = (num_1 % 10) + '0';
		num_1 /= 10;
		len--;
	} while (num_1 > 0);

	return (buf_fer);
}


/**
 * create_error - a function that wr custom err message to stderr.
 * @argument: array of argss
 * @err_or: err value
 *
 * Return: err value
 */
int create_error(char **argument, int err_or)
{
	char *error;

	switch (err_or)
	{
	case -1:
		error = error_env(argument);
		break;
	case 1:
		error = error_1(argument);
		break;
	case 2:
		if (*(argument[0]) == 'e')
			error = error_2_exit(++argument);
		else if (argument[0][0] == ';' || argument[0][0] == '&' || argument[0][0] == '|')
			error = error_2_syntax(argument);
		else
			error = error_2_cd(argument);
		break;
	case 126:
		error = error_126(argument);
		break;
	case 127:
		error = error_127(argument);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err_or);

}
