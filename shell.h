#ifndef _SHELL_H_
#define _SHELL_H_

/*
 * File: shell.h
 * Authors: Asmaa Bahr
 *          Maryam Ebrahim
 */

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global env */
extern char **envirm;
/* glbl program name */
char *name;
/* glbl history cntr */
int historyy;

/**
 * struct listS - A new struct type that defines a linked list.
 * @dir: directory path.
 * @next: pointer to a second struct listS.
 */

typedef struct list_s
{
	char *direc;
	struct list_s *to_next;
} list_t;

/**
 * struct builtinS - A new struct type that defines built in commands.
 * @name: of the built in command.
 * @f: pointer function to the function of the built in command.
 */

typedef struct builtin_s
{
	char *name;
	int (*func)(char **arg_v, char **front_);
} builtin_t;

/**
 * struct aliasS - A new struct that defines aliases.
 * @name: of the alias.
 * @value: of the alias.
 * @next: A pointer to a second struct aliasS.
 */

typedef struct alias_ss
{
	char *name;
	char *value;
	struct alias_ss *to_next;
} alias_t;

/* Glbl alias22 lnkd list */
alias_t *alias22;

/* Main Helpers */
ssize_t _getline(char **linptr_, size_t *n_si, FILE *stream);
void *_realloc(void *potr, unsigned int oldSize0, unsigned int newSize1);
char **_strtok(char *_line, char *delim);
char *get_location(char *comand);
list_t *get_path_dir(char *path);
int execute(char **argu, char **front_);
void free_list(list_t *_head);
char *_itoa(int mNu);

/* Input Helpers */
void handle_line(char **_line, ssize_t readd);
void variable_replacement(char **argu, int *exeRet_);
char *get_args(char *_line, int *exeRet_);
int call_args(char **argu, char **front_, int *exeRet_);
int run_args(char **argu, char **front_, int *exeRet_);
int handle_args(int *exeRet_);
int check_args(char **argu);
void free_args(char **argu, char **front_);
char **replace_aliases(char **argu);

/* String functions */
int _strlen(const char *st);
char *_strcat(char *dest, const char *source);
char *_strncat(char *dest, const char *source, size_t n_si);
char *_strcpy(char *dest, const char *source);
char *_strchr(char *st, char c);
int _strspn(char *st, char *accepted);
int _strcmp(char *s_1, char *s_2);
int _strncmp(const char *s_1, const char *s_2, size_t n_si);

/* Builtins */
int (*get_builtin(char *comand))(char **argu, char **front_);
int shellby_exit(char **argu, char **front_);
int shellby_env(char **argu, char __attribute__((__unused__)) **frnt);
int shellby_setenv(char **argu, char __attribute__((__unused__)) **frnt);
int shellby_unsetenv(char **argu, char __attribute__((__unused__)) **frnt);
int shellby_cd(char **argu, char __attribute__((__unused__)) **front_);
int shellby_alias(char **argu, char __attribute__((__unused__)) **front_);
int shellby_help(char **argu, char __attribute__((__unused__)) **front_);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *variab);

/* Error Handling */
int create_error(char **argu, int err_or);
char *error_env(char **argu);
char *error_1(char **argu);
char *error_2_exit(char **argu);
char *error_2_cd(char **argu);
char *error_2_syntax(char **argu);
char *error_126(char **argu);
char *error_127(char **argu);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **_head, char *name, char *value);
void free_alias_list(alias_t *_head);
list_t *add_node_end(list_t **_head, char *direc);
void free_list(list_t *_head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int proc_file_comands(char *filePath_, int *exeRet_);
#endif /* _SHELL_H_ */

