/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:41:17 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/08 09:53:36 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_redir_list(t_redir **redir_head)
{
	t_redir	*current;
	t_redir	*next;

	if (redir_head == NULL || *redir_head == NULL)
		return ;
	current = *redir_head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	*redir_head = NULL;
}

void	clean_parent(t_cmd *cmd)
{
	t_cmd	*next;
	t_cmd	*current;

	current = cmd;
	if (current->redir_fds)
		free(current->redir_fds);
	while (current)
	{
		next = current->next;
		ft_free(current->argv);
		if (current->redirs)
			clear_redir_list(&current->redirs);
		free(current);
		current = next;
	}
}

void	ft_clean(t_cmd *cmd)
{
	t_cmd	*next;
	t_cmd	*current;

	current = cmd;
	free_env(current->env);
	free_export(current->exp);
	if (current->redir_fds != NULL)
		free(current->redir_fds);
	while (current)
	{
		next = current->next;
		ft_free(current->argv);
		if (current->redirs)
			clear_redir_list(&current->redirs);
		free(current);
		current = next;
	}
}
