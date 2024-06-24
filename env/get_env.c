/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:09:32 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:34:25 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_keymap	*create_keymap(const char *key, const char *val)
{
	t_keymap	*new_keymap;

	new_keymap = (t_keymap *)malloc(sizeof(t_keymap));
	if (!new_keymap)
	{
		perror("Memory allocation error");
		exit(1);
	}
	new_keymap->key = ft_strdup(key);
	if (val)
		new_keymap->val = ft_strdup(val);
	else
		new_keymap->val = NULL;
	new_keymap->next = NULL;
	return (new_keymap);
}

void	add_keymap(t_keymap **head, t_keymap *new_keymap)
{
	t_keymap	*current;

	if (*head == NULL)
	{
		*head = new_keymap;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_keymap;
	}
}

void	update_shlevl(t_keymap **keymap)
{
	t_keymap	*current;
	int			shlvl;

	current = *keymap;
	while (current)
	{
		if (ft_strcmp(current->key, "SHLVL") == 0)
		{
			shlvl = atoi(current->val);
			shlvl++;
			free(current->val);
			current->val = ft_itoa(shlvl);
			return ;
		}
		current = current->next;
	}
}

t_env	*get_env(char **env)
{
	t_keymap	*head;
	size_t		i;
	char		**split_env;
	t_keymap	*new_keymap;
	t_env		*new_env;

	head = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		split_env = ft_split(env[i], '=');
		if (!split_env)
			return (perror("Memory allocation error"), NULL);
		new_keymap = create_keymap(split_env[0], split_env[1]);
		add_keymap(&head, new_keymap);
		ft_free(split_env);
		i++;
	}
	update_shlevl(&head);
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (perror("Memory allocation error"), NULL);
	new_env->keymap = head;
	return (new_env);
}
