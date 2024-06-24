/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:10:57 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/08 10:24:13 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_child(t_cmd *cmd, int pipe_count, t_cmd *head)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (cmd->pipe_in != NULL)
			dup2(cmd->pipe_in[0], STDIN_FILENO);
		if (cmd->pipe_out != NULL)
			dup2(cmd->pipe_out[1], STDOUT_FILENO);
		if (cmd->fd_in > 2)
			dup2(cmd->fd_in, STDIN_FILENO);
		if (cmd->fd_out > 2)
			dup2(cmd->fd_out, STDOUT_FILENO);
		close_fds(cmd->fd_in, cmd->fd_out);
		close_redir_fds(head);
		free_pipes(cmd->pipes, pipe_count);
		run_childcommand(cmd, head);
	}
	close_fds(cmd->pipe_in[0], cmd->pipe_out[1]);
	close_fds(cmd->fd_in, cmd->fd_out);
}

int	handle_pipe_child(t_shell *shell, int **pipes)
{
	t_cmd	*current;
	int		status;
	int		j;

	current = shell->cmd;
	while (current != NULL)
	{
		if (current->fd_in == -1)
			return (perror("INPUT1"), -1);
		if (current->fd_out == -1)
			return (perror("OUTPUT1"), -1);
		pipe_child(current, shell->pipe_count, shell->cmd);
		current = current->next;
	}
	free_redir_fds(current);
	free_pipes(pipes, shell->pipe_count);
	j = 0;
	while (j < shell->cmd_count)
	{
		waitpid(-1, &status, 0);
		j++;
	}
	get_exit_status(status);
	return (0);
}

void	run_pipex(t_shell *shell)
{
	int	**pipes;

	pipes = make_pipes(shell->pipe_count, STDIN_FILENO, STDOUT_FILENO);
	if (pipes == NULL)
	{
		perror("make_pipes");
		exit(1);
	}
	pipe_commands(shell, pipes);
	if (set_io(shell) == -1)
		return ;
	if (handle_pipe_child(shell, pipes) == -1)
	{
		close_redir_fds(shell->cmd);
		free_pipes(pipes, shell->pipe_count);
	}
}
