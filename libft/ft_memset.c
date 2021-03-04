/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 15:51:07 by swquinc           #+#    #+#             */
/*   Updated: 2020/05/14 18:09:12 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *a, int b, size_t n)
{
	unsigned char *ptr;

	ptr = (unsigned char*)a;
	while (n > 0)
	{
		*ptr = (unsigned char)b;
		ptr++;
		n--;
	}
	return (a);
}
