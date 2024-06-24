/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:03:39 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 19:25:59 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_shell(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*current;

	current = shell->cmd;
	while (current->next != NULL)
		current = current->next;
	current->next = cmd;
}

void	fill_struct(t_shell *shell, t_pipe *pipe, t_env *env, t_export *exp)
{
	t_cmd	*new_cmd;

	new_cmd = NULL;
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return ;
	new_cmd->id = shell->cmd_count;
	new_cmd->env = env;
	new_cmd->exp = exp;
	new_cmd->pipe_in = NULL;
	new_cmd->pipe_out = NULL;
	new_cmd->redir_fds = NULL;
	new_cmd->pipes = NULL;
	new_cmd->fd_in = STDIN_FILENO;
	new_cmd->fd_out = STDOUT_FILENO;
	new_cmd->argv = ft_copy_commands(pipe->cmd);
	new_cmd->redirs = copy_redirs(pipe->redirection);
	new_cmd->next = NULL;
	if (shell->cmd == NULL)
		shell->cmd = new_cmd;
	else
		fill_shell(shell, new_cmd);
}
