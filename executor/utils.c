/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:04:27 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 14:57:21 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_all(char **s1, char **s2)
{
	ft_free(s1);
	ft_free(s2);
}

void	*free_pipes(int **pipes, int count)
{
	int	counter;

	counter = 0;
	while (count > counter)
	{
		close_pipe_fd(pipes[counter]);
		counter++;
	}
	free(pipes);
	return (NULL);
}

void	get_exit_status(int status)
{
	if (status)
		g_sig.exit_status = WEXITSTATUS(status);
	else
		g_sig.exit_status = 0;
}
