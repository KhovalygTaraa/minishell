/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:46:39 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/04 19:08:23 by swquinc          ###   ########.fr       */
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
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
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
