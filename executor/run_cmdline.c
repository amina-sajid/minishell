/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmdline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:50:03 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/07 19:50:20 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strequals(char *s1, char *s2)
{
	if (s1 == s2)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return (0);
	return (s1 && s2 && ft_strlen(s1) == ft_strlen(s2) && !ft_strncmp(s1, s2,
			ft_strlen(s1)));
}

void	run_command(t_cmd *cmd, int fd_in, int fd_out)
{
	int	status;

	status = 0;
	if (ft_strequals(cmd->argv[0], "exit"))
	{
		if (ft_exit(cmd, cmd->argv) == -1)
			return (g_sig.exit_status = 1, (void) NULL);
	}
	else if (ft_strequals(cmd->argv[0], "cd"))
		ft_cd(cmd->env, cmd->argv[1]);
	else if (ft_strequals(cmd->argv[0], "env"))
		ft_env(cmd->env);
	else if (ft_strequals(cmd->argv[0], "pwd"))
		get_pwd(cmd->env);
	else if (ft_strequals(cmd->argv[0], "echo"))
		ft_echo(cmd->argv);
	else if (ft_strequals(cmd->argv[0], "export"))
		ft_export(cmd->env, cmd->exp, cmd->argv);
	else if (ft_strequals(cmd->argv[0], "unset"))
		ft_unset(cmd->env, cmd->exp, cmd->argv);
	else
		child_execute(cmd, fd_in, fd_out);
	waitpid(-1, &status, 0);
	get_exit_status(status);
}

void	run_childcommand(t_cmd *cmd, t_cmd *head)
{
	if (ft_strequals(cmd->argv[0], "exit"))
		ft_exit_child(head, cmd->argv);
	else if (is_builtin(cmd) == 1)
	{
		if (ft_strequals(cmd->argv[0], "cd"))
			ft_cd(cmd->env, cmd->argv[1]);
		else if (ft_strequals(cmd->argv[0], "env"))
			ft_env(cmd->env);
		else if (ft_strequals(cmd->argv[0], "pwd"))
			get_pwd(cmd->env);
		else if (ft_strequals(cmd->argv[0], "echo"))
			ft_echo(cmd->argv);
		else if (ft_strequals(cmd->argv[0], "export"))
			ft_export(cmd->env, cmd->exp, cmd->argv);
		else if (ft_strequals(cmd->argv[0], "unset"))
			ft_unset(cmd->env, cmd->exp, cmd->argv);
		ft_clean(head);
		exit(EXIT_SUCCESS);
	}
	else
		execute_cmd(head, cmd->argv, cmd->env);
}

void	run_cmdline(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	if (shell->cmd_count > 1)
		run_pipex(shell);
	else if (cmd->redirs)
		run_redir_cmd(cmd, cmd->fd_in, cmd->fd_out);
	else
		run_command(cmd, cmd->fd_in, cmd->fd_out);
	clean_parent(cmd);
	if (g_sig.heredoc_fd > 2)
	{
		close(g_sig.heredoc_fd);
		g_sig.heredoc_fd = STDIN_FILENO;
	}
}
