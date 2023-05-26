/*
 * File: split.c
 *
 *
 */

#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *_line, char *delim);

/**
 * token_len - a function that locates da delimiter
 * ind_ex marking the end
 * of the first token contained within a string.
 * @str: strrg to be searched.
 * @delim: dedlimm charrrr.
 *
 * Return: The delimiter ind_ex marking the end of
 *         the intitial token pointed to be str.
 */

int token_len(char *str, char *delim)
{
	int ind_ex = 0, len = 0;

	while (*(str + ind_ex) && *(str + ind_ex) != *delim)
	{
		len++;
		ind_ex++;
	}

	return (len);
}

/**
 * count_tokens - a function that counts the num of delimited
 * words contained within a str.
 * @str: str to be searched.
 * @delim: delimiter charr.
 *
 * Return: The number of words contained within str.
 */

int count_tokens(char *str, char *delim)
{
	int ind_ex, tokens = 0, len = 0;

	for (ind_ex = 0; *(str + ind_ex); ind_ex++)
		len++;

	for (ind_ex = 0; ind_ex < len; ind_ex++)
	{
		if (*(str + ind_ex) != *delim)
		{
			tokens++;
			ind_ex += token_len(str + ind_ex, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - a function that tokenizes a str.
 * @_line: string.
 * @delim: delimiter character to tokenize the str by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */

char **_strtok(char *_line, char *delim)
{
	char **potr;
	int ind_ex = 0, tokens, t, letters, l;

	tokens = count_tokens(_line, delim);
	if (tokens == 0)
		return (NULL);

	potr = malloc(sizeof(char *) * (tokens + 2));
	if (!potr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (_line[ind_ex] == *delim)
			ind_ex++;

		letters = token_len(_line + ind_ex, delim);

		potr[t] = malloc(sizeof(char) * (letters + 1));
		if (!potr[t])
		{
			for (ind_ex -= 1; ind_ex >= 0; ind_ex--)
				free(potr[ind_ex]);
			free(potr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			potr[t][l] = _line[ind_ex];
			ind_ex++;
		}

		potr[t][l] = '\0';
	}
	potr[t] = NULL;
	potr[t + 1] = NULL;

	return (potr);
}
