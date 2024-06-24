/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:48:29 by iganiev           #+#    #+#             */
/*   Updated: 2023/12/07 16:02:18 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcount(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_wordsize(const char *str, char c)
{
	size_t	i;
	char	*word;

	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**newstr;
	int		i;
	int		wordsnum;

	if (!s)
		return (NULL);
	wordsnum = ft_wordcount(s, c);
	newstr = malloc(sizeof(char *) * (wordsnum + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < wordsnum)
	{
		while (*s && *s == c)
			s++;
		newstr[i] = ft_wordsize(s, c);
		while (*s && *s != c)
			s++;
		i++;
	}
	newstr[i] = NULL;
	return (newstr);
}
