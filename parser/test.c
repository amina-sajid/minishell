/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:58:04 by asajid            #+#    #+#             */
/*   Updated: 2023/12/03 21:16:08 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append(t_redir **head, int index, char *str, t_token token)
{
	t_redir	*new_node;
	t_redir	*tmp;

	new_node = (t_redir *)malloc(sizeof(t_redir));
	new_node->indx = index;
	new_node->str = ft_strdup(str);
	new_node->token = token;
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_redir	*copy_redirs(t_lexer *head_double)
{
	t_redir	*head;
	t_lexer	*tmp;

	head = NULL;
	tmp = head_double;
	while (tmp)
	{
		append(&head, tmp->i, tmp->str, tmp->token);
		tmp = tmp->next;
	}
	return (head);
}

char	**ft_copy_commands(char **src_argv)
{
	char	**new_argv;
	int		argc;
	int		i;

	new_argv = NULL;
	argc = 0;
	i = 0;
	while (src_argv[argc] != NULL)
		argc++;
	new_argv = malloc(sizeof(char *) * (argc + 1));
	while (i < argc)
	{
		new_argv[i] = ft_strdup(src_argv[i]);
		i++;
	}
	new_argv[argc] = NULL;
	return (new_argv);
}
