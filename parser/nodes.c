/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:21:07 by asajid            #+#    #+#             */
/*   Updated: 2023/11/30 15:23:11 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_new_node(char *str, int token)
{
	t_lexer		*new;
	static int	i = 0;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = str;
	new->token = token;
	new->i = i++;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_add_next_node(t_lexer *new_list, t_lexer **old_list)
{
	t_lexer	*tmp;

	tmp = *old_list;
	if (*old_list == NULL)
	{
		*old_list = new_list;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new_list;
	new_list->prev = tmp;
}

int	add_to_list(char *str, t_token token, t_lexer **old_list)
{
	t_lexer	*node;

	node = ft_new_node(str, token);
	if (!node)
	{
		return (0);
	}
	ft_add_next_node(node, old_list);
	return (1);
}
