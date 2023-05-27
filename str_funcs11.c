/*
 * File: str_funcs11.c
 *
 *
 */

#include "shell.h"

int _strlen(const char *st);
char *_strcpy(char *dest, const char *source);
char *_strcat(char *dest, const char *source);
char *_strncat(char *dest, const char *source, size_t n_si);

/**
 * _strlen - a function that returns the len of a string.
 * @st: pntr to the charsss str.
 *
 * Return: The lenn of the charr strr.
 */

int _strlen(const char *st)
{
	int length = 0;

	if (!st)
		return (length);
	for (length = 0; st[length]; length++)
		;
	return (length);
}

/**
 * _strcpy - a function that copies the string pointed
 * to by source, including the terminating null
 * by_te, to the bufer pointed by des.
 * @dest: pntr to the desti_nation of cop_ied strr.
 * @source: pntr to the sou_rce of the sour_ce str.
 *
 * Return: Pointer to dest.
 */

char *_strcpy(char *dest, const char *source)
{
	size_t i;

	for (i = 0; source[i] != '\0'; i++)
		dest[i] = source[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - a function that concantenates 2 strrs.
 * @dest: pnt to destin_ation str.
 * @source: pntr to sou_rce str.
 *
 * Return: Pointer to destination string.
 */

char *_strcat(char *dest, const char *source)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  source;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - a function that concantenates
 * 2 strings where n_si num of bytes_ are copied mn src
 * @dest: pntr to desti_nation str.
 * @source: pntr to sour_ce str.
 * @n_si: n_si bytes_ to copy from so_urce.
 *
 * Return: Pointer to destination string.
 */

char *_strncat(char *dest, const char *source, size_t n_si)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n_si && source[i] != '\0'; i++)
		dest[dest_len + i] = source[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
