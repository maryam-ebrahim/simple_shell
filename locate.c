/*
 * File: locate.c
 *
 *
 */

#include "shell.h"

char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * get_location - a function that locates a cmd in the PATH.
 * @comand: cmd to locate.
 *
 * Return: NULL (If an error occurs or the comand cannot be located)
 *         Otherwise (the full pathname of the comand)
 */

char *get_location(char *comand)
{
	char **path, *_temp;
	list_t *dirs, *_head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	_head = dirs;

	while (dirs)
	{
		_temp = malloc(_strlen(dirs->direc) + _strlen(comand) + 2);
		if (!_temp)
			return (NULL);

		_strcpy(_temp, dirs->direc);
		_strcat(_temp, "/");
		_strcat(_temp, comand);

		if (stat(_temp, &st) == 0)
		{
			free_list(_head);
			return (_temp);
		}

		dirs = dirs->to_next;
		free(_temp);
	}

	free_list(_head);

	return (NULL);
}

/**
 * fill_path_dir - a function that copies path but
 * also replaces leading/sandwiched/trailing
 *		   colons (:) w crnt working dirrrr.
 * @path: The colon-separated li_st of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */

char *fill_path_dir(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - a function that tokenizes a colon-separated list of
 *                direct_ories into a list_s linked list.
 * @path: colon-separated list of direc_tories.
 *
 * Return: pntr to the initialized lin_ked list.
 */

list_t *get_path_dir(char *path)
{
	int ind_ex;
	char **dirs, *path_copy;
	list_t *_head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (ind_ex = 0; dirs[ind_ex]; ind_ex++)
	{
		if (add_node_end(&_head, dirs[ind_ex]) == NULL)
		{
			free_list(_head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (_head);
}
