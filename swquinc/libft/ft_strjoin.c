/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:46:39 by swquinc           #+#    #+#             */
/*   Updated: 2020/05/28 09:07:41 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t		a;
	size_t		b;
	char		*s3;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return ((char*)s2);
	if (!s2)
		return ((char*)s1);
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	if (!(s3 = malloc((a + b + 1) * sizeof(char))))
		return (0);
	a = -1;
	b = -1;
	while (s1[++a] != 0)
		s3[a] = s1[a];
	while (s2[++b] != 0)
		s3[a + b] = s2[b];
	s3[a + b] = 0;
	return (s3);
}
