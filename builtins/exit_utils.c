/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:52:30 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 19:26:41 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_exit(t_cmd *cmd)
{
	clear_redir_list(&cmd->redirs);
	free_env(cmd->env);
	free_export(cmd->exp);
	free(cmd->redir_fds);
	free(cmd);
}

void	clean_child_exit(t_cmd *cmd)
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
		if (current->redirs)
			clear_redir_list(&current->redirs);
		current = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->argv)
			ft_free(cmd->argv);
		free(cmd);
		cmd = next;
	}
}

void	panic(char *message, int status, char **argv)
{
	perror(message);
	ft_free(argv);
	exit(status);
}

void	panic_child(char *message, int status, t_cmd *cmd)
{
	perror(message);
	free_cmd(cmd);
	exit(status);
}
