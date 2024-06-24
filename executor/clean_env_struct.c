/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_env_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:38:16 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:36:27 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env *env)
{
	t_keymap	*current;
	t_keymap	*next;

	current = env->keymap;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->val);
		free(current);
		current = next;
	}
	free(env);
}

void	free_export(t_export *exp)
{
	t_keymap	*current;
	t_keymap	*next;

	current = exp->keymap;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->val);
		free(current);
		current = next;
	}
	free(exp);
}
