/*
 * File: helpers_2.c
 *
<<<<<<< HEAD
=======
 *
>>>>>>> bc5ffc7837b89442bf3033f477dd9ac934c73f79
 */

#include "shell.h"

void handle_line(char **_line, ssize_t readd);
ssize_t get_new_len(char *_line);
void logical_ops(char *_line, ssize_t *new_len);

/**
 * handle_line - a function that partitions a _line
 * readd from stndrd input when needed.
 * @_line: pointer to a _line readd frm stndrd inpt
 * @readd: len of _line
 *
 * Description: Spaces inserted to separate ";", "||", and "&&".
 *              Replaces "#" wi_th '\0'.
 */

void handle_line(char **_line, ssize_t readd)
{
	char *old_line, *newLine;
	char previous, current, to_next;
	size_t i, j;
	ssize_t new_len;

	new_len = get_new_len(*_line);
	if (new_len == readd - 1)
		return;
	newLine = malloc(new_len + 1);
	if (!newLine)
		return;
	j = 0;
	old_line = *_line;
	for (i = 0; old_line[i]; i++)
	{
		current = old_line[i];
		to_next = old_line[i + 1];
		if (i != 0)
		{
			previous = old_line[i - 1];
			if (current == ';')
			{
				if (to_next == ';' && previous != ' ' && previous != ';')
				{
					newLine[j++] = ' ';
					newLine[j++] = ';';
					continue;
				}
				else if (previous == ';' && to_next != ' ')
				{
					newLine[j++] = ';';
					newLine[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					newLine[j++] = ' ';
				newLine[j++] = ';';
				if (to_next != ' ')
					newLine[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (to_next == '&' && previous != ' ')
					newLine[j++] = ' ';
				else if (previous == '&' && to_next != ' ')
				{
					newLine[j++] = '&';
					newLine[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (to_next == '|' && previous != ' ')
					newLine[j++]  = ' ';
				else if (previous == '|' && to_next != ' ')
				{
					newLine[j++] = '|';
					newLine[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				newLine[j++] = ' ';
			newLine[j++] = ';';
			if (to_next != ' ' && to_next != ';')
				newLine[j++] = ' ';
			continue;
		}
		newLine[j++] = old_line[i];
	}
	newLine[j] = '\0';

	free(*_line);
	*_line = newLine;
}

/**
 * get_new_len - a function that gets new len of _line parttnd
 *               by ";", "||", "&&&", or "#".
 * @_line: _line to check.
 *
 * Return: new len of _line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *_line)
{
	size_t i;
	ssize_t new_len = 0;
	char current, to_next;

	for (i = 0; _line[i]; i++)
	{
		current = _line[i];
		to_next = _line[i + 1];
		if (current == '#')
		{
			if (i == 0 || _line[i - 1] == ' ')
			{
				_line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (to_next == ';' && _line[i - 1] != ' ' && _line[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (_line[i - 1] == ';' && to_next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (_line[i - 1] != ' ')
					new_len++;
				if (to_next != ' ')
					new_len++;
			}
			else
				logical_ops(&_line[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && _line[i - 1] != ' ')
				new_len++;
			if (to_next != ' ' && to_next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * logical_ops - a function checks a line for logical operators "||" or "&&"
 * @_line: pntr to the character to check in the _line
 * @new_len: pointer to new_len in get_new_len function.
 */

void logical_ops(char *_line, ssize_t *new_len)
{
	char previous, current, to_next;

	previous = *(_line - 1);
	current = *_line;
	to_next = *(_line + 1);

	if (current == '&')
	{
		if (to_next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && to_next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (to_next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && to_next != ' ')
			(*new_len)++;
	}
}
