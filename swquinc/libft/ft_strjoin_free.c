/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 09:55:46 by hovalygta         #+#    #+#             */
/*   Updated: 2021/01/20 12:49:46 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	size_t		a;
	size_t		b;
	char		*s3;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	if ((s3 = ft_line_malloc(a + b, sizeof(char))) == NULL)
		return (NULL);
	a = -1;
	b = -1;
	while (s1[++a] != 0)
		s3[a] = s1[a];
	while (s2[++b] != 0)
		s3[a + b] = s2[b];
	s3[a + b] = '\0';
	free(s1);
	s1 = NULL;
	return (s3);
}
