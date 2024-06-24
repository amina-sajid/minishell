/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:07:26 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 18:40:10 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**make_pipes(int pipes, int fd_in, int fd_out)
{
	int	**result;
	int	count;

	result = malloc(sizeof(int *) * (pipes));
	if (!result)
		return (NULL);
	count = 0;
	while (count < pipes)
	{
		result[count] = malloc(sizeof(int) * 2);
		if (!result[count])
			return (free_pipes(result, pipes));
		if (count != 0 && count != pipes - 1)
		{
			if (pipe(result[count]) == -1)
				return (free_pipes(result, count));
		}
		count++;
	}
	result[0][0] = fd_in;
	result[0][1] = -1;
	result[count - 1][1] = fd_out;
	result[count - 1][0] = -1;
	return (result);
}

void	assign_redir_fds(t_shell *shell, int *redirs, int counter)
{
	t_cmd	*current_cmd;

	current_cmd = shell->cmd;
	while (current_cmd)
	{
		current_cmd->redir_fds = redirs;
		current_cmd->count_fds = counter;
		current_cmd = current_cmd->next;
	}
}

int	set_io(t_shell *shell)
{
	int		counter;
	t_cmd	*current_cmd;
	int		*redirs;

	redirs = ft_calloc((shell->cmd_count * 2), sizeof(int));
	if (!redirs)
		return (-1);
	counter = 0;
	current_cmd = shell->cmd;
	while (current_cmd)
	{
		if (current_cmd->redirs != NULL)
		{
			current_cmd->fd_in = process_input(current_cmd->redirs,
					STDIN_FILENO);
			redirs[counter++] = current_cmd->fd_in;
			current_cmd->fd_out = process_output(current_cmd->redirs,
					STDOUT_FILENO);
			redirs[counter++] = current_cmd->fd_out;
		}
		current_cmd = current_cmd->next;
	}
	assign_redir_fds(shell, redirs, counter);
	return (0);
}

void	pipe_commands(t_shell *shell, int **pipes)
{
	t_cmd	*current;
	int		i;

	i = 0;
	current = shell->cmd;
	while (current != NULL)
	{
		current->pipes = pipes;
		if (i == shell->pipe_count)
		{
			current->pipe_in = pipes[i - 1];
			current->pipe_out = pipes[i];
		}
		else if (i >= 0)
		{
			current->pipe_in = pipes[i];
			current->pipe_out = pipes[i + 1];
		}
		i++;
		current = current->next;
	}
}
