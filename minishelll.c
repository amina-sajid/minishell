/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:07:09 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/08 09:29:27 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig_stat	g_sig;

static void	validate_shell(int ac, char *av[])
{
	if (ac != 1 || av[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
}

static void	init_global_var(void)
{
	g_sig.exit_status = 0;
	g_sig.heredoc_fd = -1;
}

int	main(int ac, char *av[], char **env)
{
	t_tools		tools;
	t_env		*env_data;
	t_export	*exp_data;

	validate_shell(ac, av);
	init_global_var();
	define_input_signals();
	env_data = get_env(env);
	exp_data = get_export(env_data);
	while (1)
	{
		tools.args = readline("\033[1;36mminishell\033[36m$ \033[0m ");
		if (!tools.args)
		{
			free_env(env_data);
			free_export(exp_data);
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
		add_history(tools.args);
		if (tools.args[0])
			minishell(&tools, env_data, exp_data);
	}
	return (0);
}
