/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:32:57 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:10:39 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_child(t_cmd *cmd, char **argv)
{
	unsigned long long	val;

	g_sig.exit_status = 0;
	clean_child_exit(cmd);
	if (!argv || !argv[1])
	{
		free_cmd(cmd);
		ft_putstr_fd("exit\n", 1);
		exit(g_sig.exit_status);
	}
	if (argv[2])
		panic_child("exit: too many arguments\n", 1, cmd);
	val = ft_atoull(argv[1]);
	if (!ft_isnumber(val, argv[1]))
		panic_child("exit: numeric argument required\n", 255, cmd);
	ft_putstr_fd("exit\n", 1);
	g_sig.exit_status = (int)(val % 256);
	free_cmd(cmd);
	exit(g_sig.exit_status);
}

int	ft_exit(t_cmd *cmd, char **argv)
{
	unsigned long long	val;

	g_sig.exit_status = 0;
	if (argv && argv[1] && argv[2])
		return (perror("exit: too many arguments\n"), -1);
	clean_exit(cmd);
	if (!argv || !argv[1])
	{
		ft_free(argv);
		ft_putstr_fd("exit\n", 1);
		exit(g_sig.exit_status);
	}
	val = ft_atoull(argv[1]);
	if (!ft_isnumber(val, argv[1]))
		panic("exit: numeric argument required\n", 255, argv);
	ft_putstr_fd("exit\n", 1);
	g_sig.exit_status = (int)(val % 256);
	ft_free(argv);
	exit(g_sig.exit_status);
	return (0);
}
