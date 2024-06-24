/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:49:33 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 22:54:24 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_pwd(t_env *env)
{
	char		*cwd;
	char		*pwd;
	t_keymap	*head;
	t_keymap	*key;

	cwd = NULL;
	pwd = NULL;
	head = env->keymap;
	pwd = getcwd(cwd, 0);
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		free(pwd);
		return ;
	}
	else
	{
		key = find_key(head, "PWD");
		if (key)
			pwd = key->val;
		printf("%s\n", pwd);
	}
}

// void	get_pwd(void)
// {
// 	char	*cwd;
// 	size_t	size;

// 	cwd = NULL;
// 	size = 1024;
// 	while (1)
// 	{
// 		cwd = (char *)malloc(size);
// 		if (cwd == NULL)
// 		{
// 			perror("malloc_cwd");
// 			return ;
// 		}
// 		if (getcwd(cwd, size) != NULL)
// 		{
// 			printf("%s\n", cwd);
// 			free(cwd);
// 			return ;
// 		}
// 		size *= 2;
// 		free(cwd);
// 	}
// }
