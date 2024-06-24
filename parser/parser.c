/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:13:33 by asajid            #+#    #+#             */
/*   Updated: 2023/12/07 19:11:44 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redirection_node(t_lexer *tmp, t_parser_list *parser_list)
{
	t_lexer	*redirection_node;
	int		index1;
	int		index2;

	redirection_node = ft_new_node(ft_strdup(tmp->next->str), tmp->token);
	if (!redirection_node)
		parser_error(0, parser_list->tools);
	ft_add_next_node(redirection_node, &parser_list->redirection);
	index1 = tmp->i;
	index2 = tmp->next->i;
	ft_del_one_node(&parser_list->list, index1);
	ft_del_one_node(&parser_list->list, index2);
	parser_list->red_num++;
}

int	create_redirection_list(t_parser_list *parser_list)
{
	t_lexer	*tmp;

	while (1)
	{
		tmp = parser_list->list;
		while (tmp && tmp->token == 0)
			tmp = tmp->next;
		if (!tmp || tmp->token == PIPE)
			return (1);
		if (!tmp->next)
			return (parser_error(0, parser_list->tools), 0);
		if (tmp->next->token)
			return (parser_error(0, parser_list->tools), 0);
		if ((tmp->token >= OUTFILE) && (tmp->token <= HEREDOC))
			ft_redirection_node(tmp, parser_list);
		else
		{
			parser_list->list = parser_list->list->next;
		}
	}
}

t_pipe	*create_arg_list(t_parser_list *parser_list)
{
	int		i;
	int		j;
	char	**str;
	t_lexer	*tmp;

	j = 0;
	i = count_args(parser_list->list);
	str = ft_calloc(i + 1, sizeof(char *));
	if (!str)
		parser_error(0, parser_list->tools);
	tmp = parser_list->list;
	while (i > 0)
	{
		if (tmp->str)
		{
			str[j++] = ft_strdup(tmp->str);
			ft_del_one_node(&parser_list->list, tmp->i);
			tmp = parser_list->list;
		}
		i--;
	}
	return (ft_new_pipe_node(str, parser_list->red_num,
			parser_list->redirection));
}

int	parser_fun(t_tools *tools, t_parser_list *parser_list)
{
	t_pipe			*pipe_node;

	if (!create_redirection_list(parser_list))
		return (0);
	pipe_node = create_arg_list(parser_list);
	if (!pipe_node)
		return (parser_error(0, tools), 0);
	if (!tools->pipe_node)
		tools->pipe_node = pipe_node;
	else
		ft_add_next_pipe_node(&tools->pipe_node, pipe_node);
	return (1);
}

int	parser(t_tools *tools)
{
	t_parser_list	parser_list;

	tools->pipe_node = NULL;
	ft_count_pipes(tools->list, tools);
	if (tools->list->token == PIPE)
		return (ft_token_error(tools));
	else
	{
		while (tools->list != NULL)
		{
			if (tools->list && tools->list->token == PIPE)
			{
				if (!tools->list->next)
					return (parser_error(0, tools), 0);
				ft_del_one_node(&tools->list, tools->list->i);
			}
			parser_list = ft_parser_node(tools);
			if (!parser_fun(tools, &parser_list))
				return (0);
			tools->list = parser_list.list;
		}
	}
	return (1);
}
