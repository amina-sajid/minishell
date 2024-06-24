/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:41:23 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:02:08 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../libft/libft.h"
#include "../minishell.h"

static int	check_flag(char *flag)
{
	int	i;

	i = 0;
	if (flag != NULL)
	{
		if (flag[i] != '-')
			return (1);
		i++;
		while (flag[i])
		{
			if (flag[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

void	ft_echo(char **argv)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 1;
	while (check_flag(argv[i]) == 0)
	{
		n_flag++;
		i++;
	}
	while (argv[i] && argv)
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (n_flag == 0)
		printf("\n");
}
