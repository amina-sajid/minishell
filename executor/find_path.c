/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:17:14 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/08 09:39:25 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_path(t_env *env)
{
	t_keymap	*current;

	current = env->keymap;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

char	*get_path(t_env *env)
{
	t_keymap	*current;

	current = env->keymap;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
			return (current->val);
		current = current->next;
	}
	return (NULL);
}

char	*find_path(char *command, t_env *env)
{
	t_path	data;

	if (search_path(env) == 0)
		return (command);
	if (ft_strchr(command, '/') || ft_strchr(command, ' '))
		return (command);
	data.path = ft_split(get_path(env), ':');
	data.split_cmd = ft_split(command, ' ');
	data.i = -1;
	while (data.path[++data.i])
	{
		data.env_path = ft_strjoin(data.path[data.i], "/");
		data.join_cmd = ft_strjoin(data.env_path, data.split_cmd[0]);
		free(data.env_path);
		if (access(data.join_cmd, F_OK | X_OK) == 0)
		{
			free_all(data.path, data.split_cmd);
			return (data.join_cmd);
		}
		free(data.join_cmd);
	}
	free_all(data.path, data.split_cmd);
	return (NULL);
}
