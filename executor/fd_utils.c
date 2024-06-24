/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:16:35 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/08 09:50:34 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(int fd_in, int fd_out)
{
	if (fd_in > 2)
		close(fd_in);
	if (fd_out > 2)
		close(fd_out);
}

void	close_redir_fds(t_cmd *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = cmd->count_fds;
	while (i < (len))
	{
		if (cmd->redir_fds[i] > 2)
			close(cmd->redir_fds[i]);
		i++;
	}
}

void	free_redir_fds(t_cmd *cmd)
{
	while (cmd)
	{
		close_redir_fds(cmd);
		free(cmd->redir_fds);
		cmd = cmd->next;
	}
}

void	close_pipe_fd(int *pipe)
{
	if (pipe && pipe[0] > 2)
		close(pipe[0]);
	if (pipe && pipe[1] > 2)
		close(pipe[1]);
	if (pipe)
		free(pipe);
}
