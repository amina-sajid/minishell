/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:46:26 by asajid            #+#    #+#             */
/*   Updated: 2023/12/07 23:46:27 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*allocate_and_copy_strings(char *result, char *dollar_sign, char *value,
		char *end)
{
	int		key_length;
	int		value_length;
	int		result_length;
	int		new_length;
	char	*new_result;

	key_length = end - dollar_sign;
	value_length = ft_strlen(value);
	result_length = ft_strlen(result);
	new_length = result_length - key_length + value_length;
	new_result = (char *)malloc(new_length + 1);
	if (!new_result)
	{
		perror("Memory allocation error");
		exit(1);
	}
	ft_strncpy(new_result, result, dollar_sign - result);
	ft_strcpy(new_result + (dollar_sign - result), value);
	ft_strcpy(new_result + (dollar_sign - result) + value_length, end);
	result = new_result;
	return (result);
}

char	*expand_key(char *result, char *dollar_sign, char *end, t_env *env)
{
	char		*key;
	char		*value;
	t_keymap	*current;

	key = malloc((end - dollar_sign) * (sizeof(char)));
	ft_strncpy(key, dollar_sign + 1, end - dollar_sign - 1);
	key[end - dollar_sign - 1] = '\0';
	current = env->keymap;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (current->val)
				value = current->val;
			else
				value = "";
			result = allocate_and_copy_strings(result, dollar_sign, value, end);
			break ;
		}
		current = current->next;
	}
	return (free(key), result);
}

char	*dollar_with_quotes(char *end, char *dollar_sign, char *result,
		t_env *env)
{
	char	*quote_start;
	int		inside_single_quote;
	int		inside_double_quote;

	quote_start = result;
	inside_single_quote = 0;
	inside_double_quote = 0;
	while (quote_start < dollar_sign)
	{
		if (*quote_start == '\'')
			inside_single_quote++;
		else if (*quote_start == '"')
			inside_double_quote++;
		quote_start++;
	}
	if (inside_double_quote > 0)
		result = expand_key(result, dollar_sign, end, env);
	else if (inside_single_quote)
		return (result);
	else
		result = expand_key(result, dollar_sign, end, env);
	return (result);
}

char	*dollar_expander(char *input, t_env *env)
{
	char	*result;
	char	*dollar_sign;
	char	*end;
	char	*free_us;

	result = ft_strdup(input);
	free_us = result;
	if (!result)
		perror("Memory allocation error");
	dollar_sign = ft_strchr(result, '$');
	while (dollar_sign)
	{
		end = dollar_sign + 1;
		if (*end == '?')
			result = dollar_qstn();
		while (ft_check(end))
			end++;
		if (end > dollar_sign + 1)
			result = dollar_with_quotes(end, dollar_sign, result, env);
		dollar_sign = ft_strchr(end, '$');
	}
	if (ft_strcmp(result, free_us) != 0)
		free(free_us);
	return (result);
}

char	**after_dollar(t_pipe *node, t_env *env)
{
	int		i;
	char	**node_array;
	int		j;
	char	*new;

	i = 0;
	j = count_str(node->cmd);
	node_array = ft_calloc(j + 1, sizeof(char *));
	while (node->cmd[i] != NULL)
	{
		new = dollar_expander(node->cmd[i], env);
		node_array[i] = ft_strdup(new);
		free(new);
		i++;
	}
	free_double(node->cmd);
	return (node_array);
}
