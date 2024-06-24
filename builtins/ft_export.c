/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:22:13 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:14:43 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	verify_key(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[i] == '=')
// 		return (0);
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (str[i] != '_' && !ft_isalnum(str[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// void	ft_swap(t_keymap *a, t_keymap *b)
// {
// 	char	*temp_key;
// 	char	*temp_val;

// 	temp_key = a->key;
// 	a->key = b->key;
// 	b->key = temp_key;
// 	temp_val = a->val;
// 	a->val = b->val;
// 	b->val = temp_val;
// }

// void	sort_export(t_keymap *keymap)
// {
// 	int			swapped;
// 	t_keymap	*ptr1;
// 	t_keymap	*lptr;

// 	swapped = 1;
// 	lptr = NULL;
// 	if (keymap == NULL || keymap->next == NULL)
// 		return ;
// 	while (swapped)
// 	{
// 		swapped = 0;
// 		ptr1 = keymap;
// 		while (ptr1->next != lptr)
// 		{
// 			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
// 			{
// 				ft_swap(ptr1, ptr1->next);
// 				swapped = 1;
// 			}
// 			ptr1 = ptr1->next;
// 		}
// 		lptr = ptr1;
// 	}
// }

// void	print_export(t_keymap *keymap)
// {
// 	while (keymap != NULL)
// 	{
// 		if (keymap->val)
// 			printf("declare -x %s=\"%s\"\n", keymap->key, keymap->val);
// 		else
// 			printf("declare -x %s\n", keymap->key);
// 		keymap = keymap->next;
// 	}
// }

// t_keymap	*find_key(t_keymap *head, char *key)
// {
// 	t_keymap	*current;

// 	current = head;
// 	while (current != NULL)
// 	{
// 		if (ft_strcmp(current->key, key) == 0)
// 			return (current);
// 		current = current->next;
// 	}
// 	return (NULL);
// }

// void	add_env(t_keymap **head, char *key, char *val)
// {
// 	t_keymap	*new_keymap;
// 	t_keymap	*current;

// 	new_keymap = malloc(sizeof(t_keymap));
// 	if (!new_keymap)
// 	{
// 		perror("Memory allocation error");
// 		return ;
// 	}
// 	new_keymap->key = ft_strdup(key);
// 	if (val != NULL)
// 		new_keymap->val = ft_strdup(val);
// 	else
// 		new_keymap->val = NULL;
// 	new_keymap->next = NULL;
// 	if (*head == NULL)
// 		*head = new_keymap;
// 	else
// 	{
// 		current = *head;
// 		while (current->next != NULL)
// 			current = current->next;
// 		current->next = new_keymap;
// 	}
// }

t_export	*get_export(t_env *env)
{
	t_export	*export_data;
	t_keymap	*current;

	export_data = (t_export *)malloc(sizeof(t_export));
	if (export_data == NULL)
		return (perror("Memory allocation error"), NULL);
	export_data->keymap = NULL;
	current = env->keymap;
	while (current != NULL)
	{
		add_env(&(export_data->keymap), current->key, current->val);
		current = current->next;
	}
	return (export_data);
}

// void	update_or_add_keymap(t_keymap **head, char *key, char *val)
// {
// 	t_keymap	*existing_keymap;

// 	existing_keymap = find_key(*head, key);
// 	if (existing_keymap != NULL)
// 	{
// 		if (existing_keymap->val)
// 			free(existing_keymap->val);
// 		existing_keymap->val = ft_strdup(val);
// 	}
// 	else
// 		add_env(head, key, val);
// }

void	export_arg(t_env *env, t_export *export, char *arg)
{
	char	*equals;
	char	*key;
	char	*val;

	equals = ft_strchr(arg, '=');
	key = arg;
	if (equals != NULL && verify_key(arg))
	{
		*equals = '\0';
		val = equals + 1;
		update_or_add_keymap(&(env->keymap), key, val);
		update_or_add_keymap(&(export->keymap), key, val);
		*equals = '=';
	}
	else
		add_env(&(export->keymap), key, NULL);
}

void	ft_export(t_env *env, t_export *export, char **argv)
{
	int	i;

	i = 1;
	if (argv[i] == NULL)
	{
		sort_export(export->keymap);
		print_export(export->keymap);
	}
	else
	{
		while (argv[i] != NULL)
		{
			export_arg(env, export, argv[i]);
			i++;
		}
	}
}
