/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 13:30:45 by swquinc           #+#    #+#             */
/*   Updated: 2020/10/31 02:01:55 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*free_str(char **strings)
{
	int		a;

	a = 0;
	while (strings[a])
	{
		free(strings[a]);
		a++;
	}
	free(strings);
	return (0);
}

static size_t	delimiter(char *s, char c)
{
	size_t		i;

	i = 0;
	while (s[i] != c && s[i] != 0)
		i++;
	return (i);
}

static size_t	string_count(char const *s, char c)
{
	size_t		a;
	size_t		b;

	a = 0;
	b = 0;
	while (*s)
	{
		if (b == 0 && *s != c)
		{
			b = 1;
			a++;
		}
		else if (b == 1 && *s == c)
			b = 0;
		s++;
	}
	return (a);
}

char			**ft_split(char const *s, char c)
{
	char		**strings;
	size_t		a;
	size_t		count_words;

	a = 0;
	if (!s)
		return (NULL);
	count_words = string_count((char*)s, c);
	if (!(strings = (char**)malloc(sizeof(char*) * (count_words + 1))))
		return (0);
	while (count_words--)
	{
		while (*s == c && *s != 0)
			s++;
		strings[a] = ft_substr((char*)s, 0, delimiter((char*)s, c));
		if (!strings[a])
			return (free_str(strings));
		s = s + delimiter((char*)s, c);
		a++;
	}
	strings[a] = NULL;
	return (strings);
}
