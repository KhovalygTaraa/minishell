/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 20:17:33 by swquinc           #+#    #+#             */
/*   Updated: 2020/05/28 09:02:27 by swquinc          ###   ########.fr       */
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

size_t			ft_strlcpy(char *dst, const char *src, size_t s)
{
	size_t		i;
	size_t		p;

	if (!src)
		return (0);
	p = ft_strlen0((char*)src);
	i = 0;
	if (s == 0)
		return (p);
	if (dst && src && s)
	{
		while (src[i] != 0 && i < s - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (p);
}
