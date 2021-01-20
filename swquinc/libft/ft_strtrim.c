/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 20:18:53 by swquinc           #+#    #+#             */
/*   Updated: 2020/10/31 15:34:16 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	beg(char const *s1, char const *set)
{
	size_t		i;
	size_t		p;

	i = 0;
	p = 0;
	if (!set)
		return (0);
	while (set[i] != 0)
	{
		if (set[i] == s1[p])
		{
			p++;
			i = -1;
		}
		i++;
	}
	return (p);
}

static size_t	end(char const *s1, char const *set)
{
	size_t		i;
	size_t		p;
	size_t		a;

	i = 0;
	p = ft_strlen(s1);
	a = p;
	if (!set)
		return (0);
	while (set[i] != 0)
	{
		if (set[i] == s1[p - 1])
		{
			p--;
			i = -1;
		}
		i++;
	}
	if (a == p)
		return (0);
	return (a - p);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t		a;
	size_t		b;
	size_t		c;

	if (s1 == set)
		return (ft_strdup(""));
	if (!s1)
		return (0);
	if (!set)
		return ((char*)s1);
	a = beg(s1, set);
	b = end(s1, set);
	c = ft_strlen(s1);
	return (ft_substr(s1, (unsigned int)a, (c - (a + b))));
}
