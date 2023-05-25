/*
 * File:linkedlist.c
 *
 *
 */

#include "shell.h"

alias_t *add_alias_end(alias_t **_head, char *name, char *value);
void free_alias_list(alias_t *_head);
list_t *add_node_end(list_t **_head, char *direc);
void free_list(list_t *_head);

/**
 * add_alias_end - a function that adds a node
 * to the end of a alias_t lnkdlst
 * @_head: pointer to the _head of the list_t list.
 * @name: name of the new alias tooo beee added.
 * @value: value of the new alias tooo beee added.
 *
 * Return: NULL (when an error occures)
 *         Otherwise ((a pointer to the new node))
 */

alias_t *add_alias_end(alias_t **_head, char *name, char *value)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);

	new_node->to_next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_strcpy(new_node->name, name);

	if (*_head)
	{
		last = *_head;
		while (last->to_next != NULL)
			last = last->to_next;
		last->to_next = new_node;
	}
	else
		*_head = new_node;

	return (new_node);
}

/**
 * add_node_end - a function that adds node
 * to the end of a list_t lnkdlst.
 * @_head: pointer to the _head of the list_t list.
 * @direc: directory path for the new no_de t_o contain.
 *
 * Return: NULL (when an error occures)
 *         Otherwise (a pointer to the new node)
 */

list_t *add_node_end(list_t **_head, char *direc)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->direc = direc;
	new_node->to_next = NULL;

	if (*_head)
	{
		last = *_head;
		while (last->to_next != NULL)
			last = last->to_next;
		last->to_next = new_node;
	}
	else
		*_head = new_node;

	return (new_node);
}

/**
 * free_alias_list - a function that frees a alias_t linked list.
 * @_head: THe _head of the alias_t list.
 */

void free_alias_list(alias_t *_head)
{
	alias_t *to_next;

	while (_head)
	{
		to_next = _head->to_next;
		free(_head->name);
		free(_head->value);
		free(_head);
		_head = to_next;
	}
}

/**
 * free_list - a function that frees a list_t linked list.
 * @_head: The _head of the list_t list.
 */

void free_list(list_t *_head)
{
	list_t *to_next;

	while (_head)
	{
		to_next = _head->to_next;
		free(_head->direc);
		free(_head);
		_head = to_next;
	}
}
