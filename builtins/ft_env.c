/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 01:27:43 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:02:46 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_env(t_env *env)
{
	t_keymap	*current;

	if (!env)
		perror("ENV NOT FOUND!\n");
	current = env->keymap;
	while (current != NULL)
	{
		printf("%s=", current->key);
		if (current->val != NULL)
		{
			printf("%s", current->val);
		}
		else
		{
			printf("%s", "");
		}
		printf("\n");
		current = current->next;
	}
}

void	ft_env(t_env *env)
{
	print_env(env);
}
