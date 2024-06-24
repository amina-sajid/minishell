/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:18:22 by iganiev           #+#    #+#             */
/*   Updated: 2023/01/18 10:43:13 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needlesize;

	i = 0;
	j = 0;
	needlesize = ft_strlen(needle);
	if (!*needle || needle[0] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j]
			&& i + j < len)
			j++;
		if (needlesize == j)
			return ((char *)&haystack[i]);
		i++;
		j = 0;
	}
	return (0);
}
