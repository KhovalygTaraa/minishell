/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 20:45:20 by hovalygtara       #+#    #+#             */
/*   Updated: 2020/10/31 23:58:46 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		array2_free(char **array)
{
	int			i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int		delimiter(char *str)
{
	int			i;
	int			num;

	num = 1;
	i = 0;
	while (str[i] != '\0')
	{
		num = num * 10;
		i++;
	}
	return (num);
}

static float	plus_minus(int b, int a, int i, int delimiter)
{
	float		res;

	if (a == 0 && b == 0)
		return (0);
	if (b >= 0)
	{
		res = (float)b + ((float)a / delimiter);
		res = res * i;
	}
	if (b < 0)
		res = (float)b - ((float)a / delimiter);
	return (res);
}

float			ft_atof(const char *str)
{
	float		res;
	char		**nums;
	int			i;
	int			a;
	int			b;

	i = 1;
	a = 0;
	if (!(nums = ft_split(str, '.')))
		return (0);
	while (nums[a] != NULL)
		a++;
	if (a > 2)
		return (0);
	if (nums[0][0] == '-' && nums[0][1] == '0')
		i = -1;
	b = ft_atoi(nums[0]);
	res = b;
	if (a == 2)
	{
		a = ft_atoi(nums[1]);
		res = plus_minus(b, a, i, delimiter(nums[1]));
	}
	array2_free(nums);
	return (res);
}
