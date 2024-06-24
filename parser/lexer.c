/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:52:58 by asajid            #+#    #+#             */
/*   Updated: 2023/12/05 14:30:15 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inside_quotes(int i, char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
	}
	return (j);
}

t_token	ft_sort(int c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INFILE);
	else if (c == '>')
		return (OUTFILE);
	return (0);
}

int	ft_is_words(int i, char *str, t_lexer **list)
{
	int	j;

	j = 0;
	while ((str[i + j]) && !(ft_sort(str[i + j])))
	{
		j += inside_quotes(i + j, str, 34);
		j += inside_quotes(i + j, str, 39);
		if (str[i + j] == ' ' || (str[i + j] > 8 && str[i + j] < 14))
		{
			break ;
		}
		else
			j++;
	}
	if (!add_to_list(ft_substr(str, i, j), 0, list))
		return (-1);
	return (j);
}

int	ft_is_token(char *str, int i, t_lexer **list)
{
	t_token	token;
	t_token	token1;

	token = ft_sort(str[i]);
	token1 = ft_sort(str[i + 1]);
	if (token == OUTFILE && token1 == OUTFILE)
	{
		if (!add_to_list(NULL, APPEND, list))
			return (-1);
		return (2);
	}
	else if (token == INFILE && token1 == INFILE)
	{
		if (!add_to_list(NULL, HEREDOC, list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!add_to_list(NULL, token, list))
			return (-1);
		return (1);
	}
	return (0);
}

int	lexer(t_tools *tools)
{
	int	i;
	int	j;

	i = 0;
	while (tools->args[i])
	{
		j = 0;
		while (tools->args[i + j] == ' ' || (tools->args[i + j] > 8
				&& tools->args[i + j] < 14))
		{
			j++;
		}
		i += j;
		if (ft_sort(tools->args[i]))
			j = ft_is_token(tools->args, i, &tools->list);
		else if (tools->args[i])
			j = ft_is_words(i, tools->args, &tools->list);
		if (j < 0)
			return (0);
		if (tools->args[i])
			i += j;
	}
	return (1);
}
