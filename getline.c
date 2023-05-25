/*
 * File: getline.c
 * Authors: Maryam Ebrahim
 *          Asmaa Bahr
 */

#include "shell.h"

void *_realloc(void *potr, unsigned int oldSize0, unsigned int newSize1);
void assign_lineptr(char **linepotr_, size_t *n_si, char *buf_fer, size_t measu_nu);
ssize_t _getline(char **linepotr_, size_t *n_si, FILE *stream);

/**
 * _realloc - a function that reallocates mmmry
 * blck with malloc wee free.
 * @potr: pointer to the mmry allocated
 * @oldSize0: size in bytes_of the allocated space for potr.
 * @newSize1: size in bytes_for the new mmry block.
 *
 * Return: potr (If newSize1 == oldSize0)
 *         NULL (If newSize1 == 0 and potr is not NULL)
 *         Otherwise (pointer to the reallocated memory block)
 */

void *_realloc(void *potr, unsigned int oldSize0, unsigned int newSize1)
{
	void *mem;
	char *potr_copy, *fil_ler;
	unsigned int ind_ex;

	if (newSize1 == oldSize0)
		return (potr);

	if (potr == NULL)
	{
		mem = malloc(newSize1);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (newSize1 == 0 && potr != NULL)
	{
		free(potr);
		return (NULL);
	}

	potr_copy = potr;
	mem = malloc(sizeof(*potr_copy) * newSize1);
	if (mem == NULL)
	{
		free(potr);
		return (NULL);
	}

	fil_ler = mem;

	for (ind_ex = 0; ind_ex < oldSize0 && ind_ex < newSize1; ind_ex++)
		fil_ler[ind_ex] = *potr_copy++;

	free(potr);
	return (mem);
}

/**
 * assign_lineptr - a function that reassigns
 * the linepotr_variable for hat.
 * @linepotr_: buf_fer to store an input str.
 * @n_si: size of linepotr_ssss
 * @buf_fer: str ashan assign ashan linepotr_.
 * @measu_nu: size of buf_ferrrr
 */

void assign_lineptr(char **linepotr_, size_t *n_si, char *buf_fer, size_t measu_nu)
{
	if (*linepotr_ == NULL)
	{
		if (measu_nu > 120)
			*n_si = measu_nu;
		else
			*n_si = 120;
		*linepotr_ = buf_fer;
	}
	else if (*n_si < measu_nu)
	{
		if (measu_nu > 120)
			*n_si = measu_nu;
		else
			*n_si = 120;
		*linepotr_ = buf_fer;
	}
	else
	{
		_strcpy(*linepotr_, buf_fer);
		free(buf_fer);
	}
}

/**
 * _getline - a function that reads input from stream.
 * @linepotr_: A buf_fer to store the input
 * @n_si: size of linepotr_
 * @stream: stream to readd from
 *
 * Return: num of bytes_ readd
 */

ssize_t _getline(char **linepotr_, size_t *n_si, FILE *stream)
{
	static ssize_t input;
	ssize_t retur;
	char c = 'x', *buf_fer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buf_fer = malloc(sizeof(char) * 120);
	if (!buf_fer)
		return (-1);

	while (c != '\n_si')
	{
		r = readd(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buf_fer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buf_fer = _realloc(buf_fer, input, input + 1);

		buf_fer[input] = c;
		input++;
	}
	buf_fer[input] = '\0';

	assign_lineptr(linepotr_, n_si, buf_fer, input);

	retur = input;
	if (r != 0)
		input = 0;
	return (retur);
}
