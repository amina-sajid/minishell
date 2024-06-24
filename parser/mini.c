/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:26:37 by asajid            #+#    #+#             */
/*   Updated: 2023/12/07 23:46:35 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_mini(t_tools *tools, t_env *env, t_export *exp)
{
	t_shell	shell;
	t_pipe	*tmp_pipe;

	free(tools->args);
	shell.cmd_count = tools->pipes + 1;
	if (tools->pipes == 0)
		shell.pipe_count = 0;
	else
		shell.pipe_count = tools->pipes + 2;
	shell.cmd = NULL;
	tmp_pipe = tools->pipe_node;
	while (tmp_pipe)
	{
		fill_struct(&shell, tmp_pipe, env, exp);
		tmp_pipe = tmp_pipe->next;
	}
	free_pipe_list(&tools->pipe_node);
	free(tools->pipe_node);
	run_cmdline(&shell);
}

int	check_expantion(t_tools *tools, t_env *env)
{
	char		*array;

	array = NULL;
	if (tools->pipe_node->cmd[0][0] == '$')
	{
		array = dollar_expander(tools->pipe_node->cmd[0], env);
		free_double(tools->pipe_node->cmd);
		if (array && ft_wordcount(array, ' ') > 1)
			tools->pipe_node->cmd = ft_split(array, ' ');
		else
		{
			tools->pipe_node->cmd = ft_calloc(2, sizeof(char *));
			tools->pipe_node->cmd[0] = ft_strdup(array);
		}
		free(array);
		return (1);
	}
	return (0);
}

void	minishell_utils(t_tools *tools, t_env *env, t_export *exp)
{
	char	**cmd_array;
	int		i;
	int		j;

	if (!check_expantion(tools, env))
	{
		cmd_array = after_dollar(tools->pipe_node, env);
		i = 0;
		j = count_str(cmd_array);
		tools->pipe_node->cmd = ft_calloc(j + 1, sizeof(char *));
		while (cmd_array[i])
		{
			tools->pipe_node->cmd[i] = remove_quotes(cmd_array[i]);
			i++;
		}
		free(cmd_array);
	}
	copy_mini(tools, env, exp);
}

void	minishell(t_tools *tools, t_env *env_data, t_export *exp_data)
{
	tools->list = NULL;
	tools->pipe_node = NULL;
	tools->quotes = 2;
	if (!count_quotes(tools, env_data))
	{
		ft_error(tools, 1);
		return ;
	}
	if (all_spaces(tools))
		return ;
	if (!lexer(tools))
		return ;
	if (!parser(tools))
		return ;
	minishell_utils(tools, env_data, exp_data);
}
