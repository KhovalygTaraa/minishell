/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 23:17:52 by swquinc           #+#    #+#             */
/*   Updated: 2020/05/27 19:58:27 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;
	char	*ptr;

	size = ft_strlen(s);
	ptr = (char*)s + size;
	if (c == '\0')
		return (ptr);
	while ((size + 1) != 0)
	{
		if (*ptr == c)
			return (&*ptr);
		size--;
		ptr--;
	}
	return (0);
}
