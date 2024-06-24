/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:16:15 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:43:37 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_len(t_env *env)
{
	int			count;
	t_keymap	*current;

	count = 0;
	current = env->keymap;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	*ft_strjoin_free(char *s1, char *s2, int free_arg)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (free_arg == 1)
		free(s1);
	else if (free_arg == 2)
		free(s2);
	else if (free_arg == 3)
	{
		free(s1);
		free(s2);
	}
	return (result);
}

char	**env_to_array(t_env *env)
{
	int			env_count;
	char		**char_env;
	int			i;
	t_keymap	*current;

	env_count = env_len(env);
	char_env = malloc((env_count + 1) * sizeof(char *));
	if (!char_env)
		return (NULL);
	i = 0;
	current = env->keymap;
	while (current)
	{
		char_env[i] = ft_strjoin(current->key, "=");
		if (current->val)
			char_env[i] = ft_strjoin_free(char_env[i], current->val, 1);
		current = current->next;
		i++;
	}
	char_env[i] = NULL;
	return (char_env);
}

void	execute_cmd(t_cmd *cmd, char **argv, t_env *env)
{
	char	*path;
	char	**env_arr;

	path = NULL;
	if (argv[0])
		path = find_path(argv[0], env);
	if (path)
	{
		env_arr = env_to_array(env);
		if (execve(path, argv, env_arr) == -1)
		{
			perror("ERROR1");
			ft_free(env_arr);
			ft_clean(cmd);
			exit(126);
		}
		ft_free(env_arr);
	}
	else
	{
		perror("ERROR2");
		ft_clean(cmd);
		exit(127);
	}
}

void	child_execute(t_cmd *cmd, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (fd_in != STDIN_FILENO)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out != STDOUT_FILENO)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		execute_cmd(cmd, cmd->argv, cmd->env);
	}
	if (fd_in > 2)
		close(fd_in);
	if (fd_in > 2)
		close(fd_out);
}
