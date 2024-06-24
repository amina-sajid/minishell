/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redircmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:07:42 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 18:40:00 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_parent_redircmd(t_cmd *cmd, int fd_in, int fd_out)
{
	g_sig.exit_status = 0;
	if (ft_strequals(cmd->argv[0], "exit"))
	{
		close_fds(fd_in, fd_out);
		if (ft_exit(cmd, cmd->argv) == -1)
			return (g_sig.exit_status = 1, (void) NULL);
	}
	else if (ft_strequals(cmd->argv[0], "cd"))
		ft_cd(cmd->env, cmd->argv[1]);
	else if (ft_strequals(cmd->argv[0], "export"))
		ft_export(cmd->env, cmd->exp, cmd->argv);
	else if (ft_strequals(cmd->argv[0], "unset"))
		ft_unset(cmd->env, cmd->exp, cmd->argv);
}

void	redir_child(t_cmd *cmd, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (fd_in > 2)
			dup2(fd_in, STDIN_FILENO);
		if (fd_out > 2)
			dup2(fd_out, STDOUT_FILENO);
		if (fd_in > 2)
			close(fd_in);
		if (fd_out > 2)
			close(fd_out);
		run_childcommand(cmd, cmd);
	}
}

void	run_redir_cmd(t_cmd *cmd, int fd_in, int fd_out)
{
	int	last_fd_in;
	int	last_fd_out;
	int	status;

	status = 0;
	last_fd_in = process_input(cmd->redirs, -1);
	if (last_fd_in == -1)
		return (perror("INPUT"), (void) NULL);
	fd_in = last_fd_in;
	last_fd_out = process_output(cmd->redirs, -1);
	if (last_fd_out == -1)
		return (perror("OUTPUT"), (void) NULL);
	fd_out = last_fd_out;
	if (parent_builtin(cmd))
		run_parent_redircmd(cmd, fd_in, fd_out);
	else if (cmd->argv[0] != NULL)
		redir_child(cmd, fd_in, fd_out);
	close_fds(fd_in, fd_out);
	waitpid(-1, &status, 0);
	get_exit_status(status);
}
