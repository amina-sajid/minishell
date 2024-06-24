/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:26:29 by asajid            #+#    #+#             */
/*   Updated: 2023/12/05 11:46:02 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_token_error(t_tools *tools)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (tools->list->token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	if (tools->list->token == OUTFILE)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	if (tools->list->token == INFILE)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	if (tools->list->token == APPEND)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	if (tools->list->token == HEREDOC)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	ft_clear_list(&tools->list);
	g_sig.exit_status = 1;
	return (0);
}

int	ft_error(t_tools *tools, int error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	if (error == 1)
		ft_putstr_fd("Unable to find the closing quote \n", STDERR_FILENO);
	free_pipe_list(&tools->pipe_node);
	g_sig.exit_status = 1;
	return (0);
}

void	parser_error(int error, t_tools *tools)
{
	ft_clear_list(&tools->list);
	ft_error(tools, error);
}
