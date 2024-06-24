/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:04:42 by asajid            #+#    #+#             */
/*   Updated: 2023/10/14 09:40:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The memmove() function copies len bytes from string src to string dst.
	The two strings may overlap; the copy is always done in a non-destructive
    manner.
	The memmove() function returns the original value of dst
	if the memory address for source is INFILE than that of the dest
	copy from the back to avoid overlap.
	Overlap happens when you want to copy a character into a position
	where you just copied another character
	In overlap, some addresses will be overwritten before copied
	if all is well, copy like its a memcpy.. copy from front
*/
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (dst == src)
		return (dst);
	if (s < d)
	{
		while (len--)
			*(d + len) = *(s + len);
		return (dst);
	}
	while (len--)
		*d++ = *s++;
	return (dst);
}
