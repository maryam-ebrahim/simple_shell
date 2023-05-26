/*
 * File: str_funcs22.c
 *
<<<<<<< HEAD
=======
 *
>>>>>>> bc5ffc7837b89442bf3033f477dd9ac934c73f79
 */

#include "shell.h"

char *_strchr(char *st, char c);
int _strspn(char *st, char *accepted);
int _strcmp(char *s_1, char *s_2);
int _strncmp(const char *s_1, const char *s_2, size_t n_si);

/**
 * _strchr - Locates a character in a string.
 * @st: The string to be searched.
 * @c: The character to be located.
 *
 * Return: If c is found - a pointer to the first occurence.
 *         If c is not found - NULL.
 */
char *_strchr(char *st, char c)
{
	int ind_ex;

	for (ind_ex = 0; st[ind_ex]; ind_ex++)
	{
		if (st[ind_ex] == c)
			return (st + ind_ex);
	}

	return (NULL);
}

/**
 * _strspn - a function that gets the lenn of a prefix substr.
 * @st: strrr to be sear_ched.
 * @accepted: da prefix to be measu_red.
 *
 * Return: The number of bytes_ in st which
 *         consist only of bytes_ from accepted.
 */

int _strspn(char *st, char *accepted)
{
	int bytes_ = 0;
	int ind_ex;

	while (*st)
	{
		for (ind_ex = 0; accepted[ind_ex]; ind_ex++)
		{
			if (*st == accepted[ind_ex])
			{
				bytes_++;
				break;
			}
		}
		st++;
	}
	return (bytes_);
}

/**
 * _strcmp - a function that compares two strrs.
 * @s_1: first str to be compa_red.
 * @s_2: second str to be compa_red.
 *
 * Return: Positive byte difference if s_1 > s_2
 *         0 if s_1 = s_2
 *         Negative byte difference if s_1 < s_2
 */

int _strcmp(char *s_1, char *s_2)
{
	while (*s_1 && *s_2 && *s_1 == *s_2)
	{
		s_1++;
		s_2++;
	}

	if (*s_1 != *s_2)
		return (*s_1 - *s_2);

	return (0);
}

/**
 * _strncmp - a function that compare two strrs.
 * @s_1: pntr to a str.
 * @s_2: pntr to a str.
 * @n_si: The first n_si bytes_ of the stri_ngs to comp_are.
 *
 * Return: Less than 0 if s_1 is shorter than s_2.
 *         0 if s_1 and s_2 match.
 *         Greater than 0 if s_1 is longer than s_2.
 */

int _strncmp(const char *s_1, const char *s_2, size_t n_si)
{
	size_t i;

	for (i = 0; s_1[i] && s_2[i] && i < n_si; i++)
	{
		if (s_1[i] > s_2[i])
			return (s_1[i] - s_2[i]);
		else if (s_1[i] < s_2[i])
			return (s_1[i] - s_2[i]);
	}
	if (i == n_si)
		return (0);
	else
		return (-15);
}
