/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 15:34:31 by swquinc           #+#    #+#             */
/*   Updated: 2020/05/28 16:51:59 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lvl(int n)
{
	int		a;

	a = 1;
	while (n > 9)
	{
		n = n / 10;
		a = a * 10;
	}
	return (a);
}

void		ft_putnbr_fd(int n, int fd)
{
	int		a;

	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			n = n * -1;
			ft_putchar_fd('-', fd);
		}
		if (n <= 9)
			ft_putchar_fd((n + 48), fd);
		else
		{
			a = lvl(n);
			while (a != 0)
			{
				ft_putchar_fd((((n / a) % 10) + 48), fd);
				a = a / 10;
			}
		}
	}
}
