/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 12:56:02 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:08:09 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_env_keymap(t_env *env, char *key)
{
	t_keymap	*current;
	t_keymap	*prev;

	current = env->keymap;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				env->keymap = current->next;
			free(current->key);
			free(current->val);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	del_export_keymap(t_export *exp, char *key)
{
	t_keymap	*current;
	t_keymap	*prev;

	current = exp->keymap;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				exp->keymap = current->next;
			free(current->key);
			free(current->val);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_unset(t_env *env, t_export *exp, char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		del_env_keymap(env, argv[i]);
		del_export_keymap(exp, argv[i]);
		i++;
	}
}
