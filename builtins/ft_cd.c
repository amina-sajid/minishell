/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:09:49 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 22:53:27 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_env *env, char *key, char *new_val)
{
	t_keymap	*current;

	current = env->keymap;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->val);
			current->val = ft_strdup(new_val);
			return ;
		}
		current = current->next;
	}
}

char	*spetial_path(t_env *env, char *path)
{
	t_keymap	*current;
	t_keymap	*temp;

	current = env->keymap;
	if (ft_strcmp(path, "~") == 0)
	{
		temp = find_key(current, "HOME");
		path = temp->val;
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		temp = find_key(current, "OLDPWD");
		path = temp->val;
	}
	return (path);
}

void	ft_cd(t_env *env, char *new_path)
{
	char	current_path[1024];

	if (new_path == NULL)
		return ;
	getcwd(current_path, sizeof(current_path));
	if ((ft_strcmp(new_path, "~") == 0) || (ft_strcmp(new_path, "-") == 0))
		new_path = spetial_path(env, new_path);
	if (chdir(new_path) == 0)
	{
		update_env(env, "OLDPWD", current_path);
		getcwd(current_path, sizeof(current_path));
		update_env(env, "PWD", current_path);
	}
	else
		perror("chdir");
}
