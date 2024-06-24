/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iganiev <iganiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:40:07 by iganiev           #+#    #+#             */
/*   Updated: 2023/01/18 13:27:51 by iganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*buf;

	if (size && SIZE_MAX / size < count)
		return (NULL);
	buf = (void *)malloc(count * size);
	if (buf == NULL)
		return (buf);
	ft_bzero(buf, count * size);
	return (buf);
}
