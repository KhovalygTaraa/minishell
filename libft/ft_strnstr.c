/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 20:59:47 by swquinc           #+#    #+#             */
/*   Updated: 2020/10/03 23:36:52 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	if (!*s2)
		return ((char*)s1);
	while (s1[a] != 0 && a < len)
	{
		if (s1[a] == s2[0])
		{
			b = 0;
			while (s1[a + b] == s2[b] && (a + b) < len)
			{
				if (s2[b + 1] == 0)
					return ((char*)&s1[a]);
				b++;
			}
		}
		a++;
	}
	return (0);
}
