/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:45:07 by swquinc           #+#    #+#             */
/*   Updated: 2020/05/24 15:36:17 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t s)
{
	size_t i;
	size_t p;

	i = ft_strlen(dst);
	p = 0;
	while (i + 1 < s && ((unsigned char*)src)[p] != 0)
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[p];
		p++;
		i++;
	}
	((unsigned char*)dst)[i] = 0;
	i = ft_strlen(dst) - p;
	if (i >= s)
		return ((ft_strlen(src)) + s);
	else
		return (i + (ft_strlen(src)));
}
