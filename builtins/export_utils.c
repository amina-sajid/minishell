/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:10:02 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/06 15:30:53 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify_key(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_swap(t_keymap *a, t_keymap *b)
{
	char	*temp_key;
	char	*temp_val;

	temp_key = a->key;
	a->key = b->key;
	b->key = temp_key;
	temp_val = a->val;
	a->val = b->val;
	b->val = temp_val;
}

void	sort_export(t_keymap *keymap)
{
	int			swapped;
	t_keymap	*ptr1;
	t_keymap	*lptr;

	swapped = 1;
	lptr = NULL;
	if (keymap == NULL || keymap->next == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = keymap;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				ft_swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void	print_export(t_keymap *keymap)
{
	while (keymap != NULL)
	{
		if (keymap->val)
			printf("declare -x %s=\"%s\"\n", keymap->key, keymap->val);
		else
			printf("declare -x %s\n", keymap->key);
		keymap = keymap->next;
	}
}
