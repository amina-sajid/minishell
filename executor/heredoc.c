/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 08:58:59 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/08 10:39:55 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_new_line_only(char *buffer)
{
	int	len;

	if (!buffer)
		return (0);
	len = ft_strlen(buffer);
	if (len == 0)
		return (0);
	return (len == 1 && buffer[0] == '\n');
}

int	fill_heredoc(int *heredoc, char *limiter)
{
	char	*buffer;

	g_sig.heredoc_fd = dup(STDIN_FILENO);
	buffer = NULL;
	while ((!buffer || is_new_line_only(buffer) || ft_strncmp(buffer, limiter,
				ft_strlen(buffer) - 1)))
	{
		if (buffer)
		{
			write(heredoc[1], buffer, ft_strlen(buffer));
			free(buffer);
		}
		write(1, "heredoc> ", 9);
		buffer = get_next_line(g_sig.heredoc_fd);
		if (!buffer)
			return (1);
	}
	close(heredoc[1]);
	close(g_sig.heredoc_fd);
	free(buffer);
	return (0);
}

int	*add_heredoc(char *limiter)
{
	int	*heredoc;

	heredoc = malloc(sizeof(int) * 2);
	if (!heredoc)
		return (NULL);
	if (pipe(heredoc) == -1)
		return (free(heredoc), NULL);
	if (fill_heredoc(heredoc, limiter))
		return (close(heredoc[0]), close(heredoc[1]), free(heredoc), NULL);
	return (heredoc);
}
