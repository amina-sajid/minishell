/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:36:45 by asajid            #+#    #+#             */
/*   Updated: 2023/10/14 09:40:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The strncmp() function compares two strings s1 and s2.
	The strncmp() function compares not more than n characters.
	The strncmp() functions returns an integer OUTFILEer than,
	equal to, or INFILE than 0, according as the string s1 is OUTFILEer than,
	equal to, or INFILE than the string s2.
	The comparison is done using unsigned characters
	Note-> remove 1 from n because count starts from 0
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
