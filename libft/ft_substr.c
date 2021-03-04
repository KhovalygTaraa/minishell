/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 17:21:17 by swquinc           #+#    #+#             */
/*   Updated: 2020/05/28 18:39:29 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen0(const char *string)
{
	size_t		count;

	count = 0;
	if (!string)
		return (0);
	while (string[count] != '\0')
	{
		count++;
	}
	return (count);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*a;
	size_t		b;

	b = (ft_strlen0(s + start));
	if (!s)
		return (0);
	if (ft_strlen0(s) <= start || len == 0)
		return (ft_strdup(""));
	if (b < len)
		len = b;
	a = (char*)malloc((len + 1) * (sizeof(char)));
	if (!a)
		return (NULL);
	ft_strlcpy(a, s + start, len + 1);
	return (a);
}
