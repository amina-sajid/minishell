/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:13:01 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:30:13 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_keymap	*find_key(t_keymap *head, char *key)
{
	t_keymap	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	add_env(t_keymap **head, char *key, char *val)
{
	t_keymap	*new_keymap;
	t_keymap	*current;

	new_keymap = malloc(sizeof(t_keymap));
	if (!new_keymap)
	{
		perror("Memory allocation error");
		return ;
	}
	new_keymap->key = ft_strdup(key);
	if (val != NULL)
		new_keymap->val = ft_strdup(val);
	else
		new_keymap->val = NULL;
	new_keymap->next = NULL;
	if (*head == NULL)
		*head = new_keymap;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_keymap;
	}
}

void	update_or_add_keymap(t_keymap **head, char *key, char *val)
{
	t_keymap	*existing_keymap;

	existing_keymap = find_key(*head, key);
	if (existing_keymap != NULL)
	{
		if (existing_keymap->val)
			free(existing_keymap->val);
		existing_keymap->val = ft_strdup(val);
	}
	else
		add_env(head, key, val);
}
