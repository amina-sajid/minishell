/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:17:06 by asajid            #+#    #+#             */
/*   Updated: 2023/12/07 23:41:50 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*dollar_qstn(void)
{
	char	*out;

	out = ft_itoa(g_sig.exit_status);
	return (out);
}

int	ft_check(char *end)
{
	return (*end && (*end == '_' || (*end >= 'a' && *end <= 'z')
			|| (*end >= 'A' && *end <= 'Z') || (*end >= '0'
				&& *end <= '9')));
}
