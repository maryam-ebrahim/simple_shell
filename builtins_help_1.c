#include "shell.h"

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

/**
 * help_all - A function that displays all possible built_in shellby comands.
 */
void help_all(void)
{
	char *mesg = "Shellby\nThese shell comands are defined internally.\n_si";

	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "out more about the function 'name'.\n_si\n_si  alias   \t";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "alias [NAME[='VALUE'] ...]\n_si  cd    \tcd   ";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "[DIRECTORY]\n_si  exit    \texit [STATUS]\n_si  env     \tenv";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "\n_si  setenv  \tsetenv [VARIABLE] [VALUE]\n_si  unsetenv\t";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "unsetenv [VARIABLE]\n_si";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
}

/**
 * help_alias - a fnction that displays info on the shellby built_in cmd alias
*/

void help_alias(void)
{
	char *mesg = "alias: alias [NAME[='VALUE'] ...]\n_si\tHandles alias22.\n_si";

	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "\n_si\talias: Prints a list of all alias22, one per _line, in ";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "the format NAME='VALUE'.\n_si\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = " the alias22 name, name2, etc. one per _line, in the ";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "form NAME='VALUE'.\n_si\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "is already an alias, replace its value with VALUE.\n_si";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
}

/**
 * help_cd - a fnction that displays info on the shellby built_in cmd cd.
 */

void help_cd(void)
{
	char *mesg = "cd: cd [DIRECTORY]\n_si\tChanges the current directory of the";

	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = " process to DIRECTORY.\n_si\n_si\tIf no argument is given, the ";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "comand is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = " given, the comand is interpreted as cd $OLDPWD.\n_si\n_si";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "after a change of directory.\n_si";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
}

/**
 * help_exit - a function that displays info on the shellby built_in cmd exit
*/

void help_exit(void)
{
	char *mesg = "exit: exit [STATUS]\n_si\tExits the shell.\n_si\n_si\tThe ";

	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = " If no argument is given, the comand is interpreted as";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = " exit 0.\n_si";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
}

/**
 * help_help - a functoin that displays info on the shellby built_in cmd help.
 */

void help_help(void)
{
	char *mesg = "hlp: hlp\n_si\tSee all pssbl Shellby builtin cmds.\n_si";

	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "\n_si help [BUILTIN NAME]\n_si\tSee specific info on each ";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
	mesg = "builtin comand.\n_si";
	write(STDOUT_FILENO, mesg, _strlen(mesg));
}