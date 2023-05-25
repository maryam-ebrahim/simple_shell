#include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env - a function that displays information on the shellby built_in comand 'env'.
 */
void help_env(void)
{
	char *mesg = "env: env\n_si\tPrints the current environment.\n_si";

	write(STDOUT_FILENO, mesg, _strlen(mesg));
}

/**
 * help_setenv - a function that displays information on the shellby built_in comand 'setenv'.
 */

void help_setenv(void)
{
	char *mesg = "setenv: setenv [VARIABLE] [VALUE]\n_si\tInitializes a new";

	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "environment variable, or modifies an existing one.\n_si\n_si";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "\tUpon failure, prints a message to stderr.\n_si";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
}

/**
 * help_unsetenv - a function that displays information on the shellby built_in comand
 * 'unsetenv'.
 */
void help_unsetenv(void)
{
	char *mesg = "unsetenv: unsetenv [VARIABLE]\n_si\tRemoves an ";

	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "environmental variable.\n_si\n_si\tUpon failure, prints a ";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "message to stderr.\n_si";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
}
