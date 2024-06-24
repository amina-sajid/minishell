/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:09:42 by iganiev           #+#    #+#             */
/*   Updated: 2023/01/12 12:26:35 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int			i;
	unsigned char			*dest;
	unsigned const char		*arr;

	i = 0;
	dest = (unsigned char *)dst;
	arr = (unsigned const char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = arr[i];
		i++;
	}
	return (dst);
}
