/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 23:15:26 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/01 17:15:22 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	size;
	char	*ptr;

	ptr = (char*)s;
	size = ft_strlen(s);
	i = 0;
	while (i < size + 1)
	{
		if (ptr[i] == (char)c)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}
