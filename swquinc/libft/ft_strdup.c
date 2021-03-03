/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 19:51:11 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/03 21:24:35 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		i;
	char		*s2;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1) + 1;
	s2 = (char*)malloc(i);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, i);
	return (s2);
}
