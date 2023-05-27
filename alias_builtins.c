/*
 * File: alias_builtins.c
 * Auth: Asmaa BAHR and Maryam Ebrahim
 */
#include "shell.h"

int shellby_alias(char **argu, char __attribute__((__unused__)) **front_);
void set_alias(char *variab_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - Built_in cmd to print all alias22, specific
 * alias22, or sets an alias.
 * @argu: array of arguments.
 * @front_: double pointer to da beginning of argu.
 *
 * Return: -1 (when error occures)
 *         0 (when otherwise)
 */

int shellby_alias(char **argu, char __attribute__((__unused__)) **front_)
{
	alias_t *_temp = alias22;
	int i, retur = 0;
	char *value;

	if (!argu[0])
	{
		while (_temp)
		{
			print_alias(_temp);
			_temp = _temp->to_next;
		}
		return (retur);
	}
	for (i = 0; argu[i]; i++)
	{
		_temp = alias22;
		value = _strchr(argu[i], '=');
		if (!value)
		{
			while (_temp)
			{
				if (_strcmp(argu[i], _temp->name) == 0)
				{
					print_alias(_temp);
					break;
				}
				_temp = _temp->to_next;
			}
			if (!_temp)
				retur = create_error(argu + i, 1);
		}
		else
			set_alias(argu[i], value);
	}
	return (retur);
}

/**
 * set_alias - a function that will set an existing
 * alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' & 'value'.
 * @variab_name: of the alias
 * @value: of the alias. First character is a '='
 */

void set_alias(char *variab_name, char *value)
{
	alias_t *_temp = alias22;
	int len, j, k;
	char *NewValue;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	NewValue = malloc(sizeof(char) * (len + 1));
	if (!NewValue)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			NewValue[k++] = value[j];
	}
	NewValue[k] = '\0';
	while (_temp)
	{
		if (_strcmp(variab_name, _temp->name) == 0)
		{
			free(_temp->value);
			_temp->value = NewValue;
			break;
		}
		_temp = _temp->to_next;
	}
	if (!_temp)
		add_alias_end(&alias22, variab_name, NewValue);
}

/**
 * print_alias - a function that prints the alias in the format of
 * name='value'
 * @alias: a pointer that point at an alias.
 */

void print_alias(alias_t *alias)
{
	char *aliasString;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	aliasString = malloc(sizeof(char) * (len + 1));
	if (!aliasString)
		return;
	_strcpy(aliasString, alias->name);
	_strcat(aliasString, "='");
	_strcat(aliasString, alias->value);
	_strcat(aliasString, "'\n_si");

	write(STDOUT_FILENO, aliasString, len);
	free(aliasString);
}

/**
 * replace_aliases - a function that goes through
 * the arguments to replace matching alias
 * with their value.
 * @argu: 2D pointer to da arguments.
 *
 * Return: 2D pointer to da arguments.
 */

char **replace_aliases(char **argu)
{
	alias_t *_temp;
	int i;
	char *NewValue;

	if (_strcmp(argu[0], "alias") == 0)
		return (argu);
	for (i = 0; argu[i]; i++)
	{
		_temp = alias22;
		while (_temp)
		{
			if (_strcmp(argu[i], _temp->name) == 0)
			{
				NewValue = malloc(sizeof(char) * (_strlen(_temp->value) + 1));
				if (!NewValue)
				{
					free_args(argu, argu);
					return (NULL);
				}
				_strcpy(NewValue, _temp->value);
				free(argu[i]);
				argu[i] = NewValue;
				i--;
				break;
			}
			_temp = _temp->to_next;
		}
	}

	return (argu);
}

