/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:25:11 by iganiev           #+#    #+#             */
/*   Updated: 2023/01/18 22:20:05 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (!s)
		return ;
	i = ft_strlen(s);
	while (j < i)
	{
		(*f)(j, s);
		j++;
		s++;
	}
}
