/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:33:21 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:36:13 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (ft_strequals(cmd->argv[0], "cd"))
		return (1);
	else if (ft_strequals(cmd->argv[0], "env"))
		return (1);
	else if (ft_strequals(cmd->argv[0], "pwd"))
		return (1);
	else if (ft_strequals(cmd->argv[0], "echo"))
		return (1);
	else if (ft_strequals(cmd->argv[0], "export"))
		return (1);
	else if (ft_strequals(cmd->argv[0], "unset"))
		return (1);
	else
		return (0);
}

int	parent_builtin(t_cmd *cmd)
{
	if (ft_strequals(cmd->argv[0], "exit"))
		return (1);
	else if (ft_strequals(cmd->argv[0], "cd"))
		return (1);
	else if (ft_strequals(cmd->argv[0], "export") && cmd->argv[1])
		return (1);
	else if (ft_strequals(cmd->argv[0], "unset") && cmd->argv[1])
		return (1);
	else
		return (0);
}
