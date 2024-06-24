/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:55:25 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/08 11:59:56 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_input(t_redir *redirs, int **heredoc, t_redir **temp, int *fd_in)
{
	if (redirs->token == HEREDOC)
	{
		if (heredoc && *heredoc != NULL)
			close_pipe_fd(*heredoc);
		*heredoc = add_heredoc(redirs->str);
		if (*heredoc == NULL)
			return (close_pipe_fd(*heredoc), -1);
		*temp = redirs;
	}
	if (redirs->token == INFILE)
	{
		*fd_in = open(redirs->str, O_RDONLY);
		if (*fd_in == -1)
			return (-1);
		close(*fd_in);
		*temp = redirs;
	}
	return (0);
}

static int	check_inputmode(t_redir *temp, int *heredoc)
{
	int	fd_in;

	fd_in = STDIN_FILENO;
	if (temp && temp->str && temp->token == HEREDOC)
	{
		close(heredoc[1]);
		fd_in = heredoc[0];
		free(heredoc);
	}
	else if (temp && temp->str && temp->token == INFILE)
	{
		if (heredoc)
			close_pipe_fd(heredoc);
		fd_in = open(temp->str, O_RDONLY);
	}
	return (fd_in);
}

int	process_input(t_redir *redirs, int last_fd)
{
	int		fd_in;
	t_redir	*temp;
	int		*heredoc;

	fd_in = STDIN_FILENO;
	temp = NULL;
	heredoc = NULL;
	while (redirs != NULL)
	{
		if (handle_input(redirs, &heredoc, &temp, &fd_in) == -1)
			return (close_pipe_fd(heredoc), -1);
		redirs = redirs->next;
	}
	last_fd = check_inputmode(temp, heredoc);
	return (last_fd);
}
