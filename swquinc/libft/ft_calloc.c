/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 18:32:57 by swquinc           #+#    #+#             */
/*   Updated: 2020/05/25 16:34:29 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			a;
	unsigned char	*b;

	a = count * size;
	b = malloc(a);
	if (!b)
		return (NULL);
	else
		ft_memset(b, 0, a);
	return (b);
}
