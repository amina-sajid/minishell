/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:07:20 by asajid            #+#    #+#             */
/*   Updated: 2023/10/04 13:09:08 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *destination, const char *source, size_t num)
{
	char	*dest;

	dest = destination;
	while (*source != '\0' && num > 0)
	{
		*dest = *source;
		dest++;
		source++;
		num--;
	}
	while (num > 0)
	{
		*dest = '\0';
		dest++;
		num--;
	}
	return (destination);
}
