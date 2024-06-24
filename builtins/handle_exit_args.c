/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:48:32 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:08:52 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static int	number_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		i++;
	}
	return (i);
}

static int	valid_arg(const char *str, const char *range)
{
	int	i;
	int	flag;
	int	len;

	i = 0;
	flag = 0;
	len = number_len(str);
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	while (i < len)
	{
		if (str[i] < range[i])
		{
			return (0);
		}
		else if (!flag && str[i] > range[i])
		{
			flag = 1;
		}
		i++;
	}
	return (flag);
}

unsigned long long	ft_atoull(const char *str)
{
	int					i;
	unsigned long long	num;
	int					sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (sign > 0 && valid_arg(&str[i], "9223372036854775807"))
		return ((unsigned long long)-1);
	else if (sign < 0 && valid_arg(&str[i], "9223372036854775808"))
		return (0);
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * (unsigned long long)sign);
}

int	ft_isnumber(unsigned long long num, const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i == 1 && !ft_isdigit(str[0]))
		return (0);
	if ((num == (unsigned long long)-1 || num == 0) && i >= 19)
		return (0);
	return (1);
}
