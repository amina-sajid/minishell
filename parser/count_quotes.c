/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:38:02 by asajid            #+#    #+#             */
/*   Updated: 2023/12/07 18:20:39 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_remove(char *input, char *out, int i, int index)
{
	while (input[i])
	{
		if (input[i] == '"')
		{
			i++;
			while (input[i] != '"')
				out[index++] = input[i++];
		}
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				out[index++] = input[i++];
		}
		if (input[i] != '\'' && input[i] != '"')
			out[index++] = input[i];
		i++;
	}
	out[index] = '\0';
	return (out);
}

char	*remove_quotes(char *input)
{
	int		len;
	int		index;
	int		i;
	char	*out;

	len = ft_strlen(input);
	index = 0;
	i = 0;
	out = (char *)malloc(len + 1);
	if (out == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	out = ft_remove(input, out, i, index);
	free(input);
	return (out);
}

int	do_single(t_tools *tools, int i)
{
	tools->quotes = 0;
	i++;
	while (tools->args[i])
	{
		if (tools->args[i] == '\'')
		{
			tools->quotes = 1;
			break ;
		}
		i++;
	}
	return (i);
}

int	do_double(t_tools *tools, int i)
{
	tools->quotes = 0;
	i++;
	while (tools->args[i])
	{
		if (tools->args[i] == '\"')
		{
			tools->quotes = 2;
			break ;
		}
		i++;
	}
	return (i);
}

int	count_quotes(t_tools *tools, t_env *env)
{
	int	i;

	(void)*env;
	i = 0;
	while (tools->args[i] != '\0')
	{
		if (tools->args[i] == '\'')
			i = do_single(tools, i);
		else if (tools->args[i] == '\"')
			i = do_double(tools, i);
		if (tools->args[i])
			i++;
	}
	return (tools->quotes);
}
