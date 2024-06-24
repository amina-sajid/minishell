/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:32:46 by asajid            #+#    #+#             */
/*   Updated: 2023/12/07 18:38:28 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_pipe_list(t_pipe **lst)
{
	t_pipe	*tmp;
	t_lexer	*red;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		red = (*lst)->redirection;
		ft_clear_list(&red);
		if ((*lst)->cmd)
			free_double((*lst)->cmd);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_pipe	*ft_new_pipe_node(char **str, int red_num, t_lexer *redirection)
{
	t_pipe	*final_list;

	final_list = (t_pipe *)malloc(sizeof(t_pipe));
	if (!final_list)
		return (0);
	final_list->cmd = ft_copy_commands(str);
	final_list->redirection = redirection;
	final_list->red_num = red_num;
	final_list->next = NULL;
	free_double(str);
	return (final_list);
}

void	ft_add_next_pipe_node(t_pipe **lst, t_pipe *new)
{
	t_pipe	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_parser_list	ft_parser_node(t_tools *tools)
{
	t_parser_list	parser_list;

	parser_list.list = tools->list;
	parser_list.redirection = NULL;
	parser_list.red_num = 0;
	parser_list.tools = tools;
	return (parser_list);
}
